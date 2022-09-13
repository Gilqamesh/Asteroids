internal inline b32
IsEntityRockType(entity *Entity)
{
    return (Entity->Type == EntityType_RockBig || Entity->Type == EntityType_RockMedium || Entity->Type == EntityType_RockSmall);
}

internal inline entity *
AddEntity(world *World)
{
    entity *Result;

    u32 Id;
    if (World->FreeEntitiesSize)
    {
        Id = World->FreeEntities[--World->FreeEntitiesSize];
        Result = &World->Entities[Id];
    }
    else
    {
        ASSERT(World->EntitiesSize < ArrayCount(World->Entities));
        Id = World->EntitiesSize++;
        Result = &World->Entities[Id];
    }
    *Result = {};
    Result->Id = Id;
    Result->IsAlive = true;

    return (Result);
}

internal inline void
RemoveEntity(game_state *GameState, entity* Entity)
{
    switch (Entity->Type)
    {
        case EntityType_Bullet:
        {
            if (Entity->Parent && Entity->Parent->Bullets)
            {
                --Entity->Parent->Bullets;
            }
        } break ;
        case EntityType_RockBig: case EntityType_RockMedium: case EntityType_RockSmall:
        {
            ASSERT(GameState->RocksSize);
            --GameState->RocksSize;
        } break ;
        case EntityType_Ship:
        {
            ASSERT(GameState->ShipLifes);
            --GameState->ShipLifes;
            GameState->Ship = 0;
        } break ;
        case EntityType_Ufo:
        {
            GameState->Ufo = 0;
        } break ;
        default:
        {
        } break ;
    }
    GameState->World->FreeEntities[GameState->World->FreeEntitiesSize++] = Entity->Id;
    *Entity = {};
}

internal inline entity*
AddShipEntity(game_state *GameState, game_window *GameWindow)
{
    entity *Result = AddEntity(GameState->World);
    GameState->Ship = Result;
    Result->P = {(r32)GameWindow->Width / 2.0f, (r32)GameWindow->Height / 2.0f};
    Result->dP = {};
    Result->WrapSize.x = 30.0f;
    Result->WrapSize.y = 22.0f;
    Result->Type = EntityType_Ship;
    Result->RotationJaw = -PI / 2.0f;
    Result->dRotationJawMax = 0.10f;
    Result->FacingDirection = {};
    Result->texture = GameState->Textures[Texture_Ship].t;
    Result->Collides = true;
    Result->ColliderType = Collider_Polygon;
    Result->Collider.Points[0] = {-19.0f, -22.0f};
    Result->Collider.Points[1] = {30.0f, 0.0f};
    Result->Collider.Points[2] = {-20.0f, 22.0f};
    Result->Collider.Size = 3;
    for (u32 i = 0;
         i < Result->Collider.Size;
         ++i)
    {
        Result->Collider.Points[i] += Result->P;
        Result->Collider.Points[i] = VectorRotate(Result->Collider.Points[i], Result->P, Result->RotationJaw);
    }
    Result->Tint = BLUE;
    Result->Scale = 1.0f;
    Result->MaxBullets = 3;
    Result->Drag = 1.0f;

    return (Result);
}

internal inline entity*
AddRockEntity(game_state *GameState, game_window *GameWindow, entity_type EntityType)
{
    entity *Result = AddEntity(GameState->World);
    ASSERT(Result);

    ASSERT(GameState->RocksSize < ArrayCount(GameState->Rocks));
    GameState->Rocks[GameState->RocksSize++] = Result;
    Result->Type = EntityType;
    Result->P.x = ((GetRand(0, 1) & 1) ? GetRand(0.0f, 2.0f * (r32)GameWindow->Width / 5.0f) : GetRand(3.0f * (r32)GameWindow->Width / 5.0f, (r32)GameWindow->Width));
    Result->P.y = ((GetRand(0, 1) & 1) ? GetRand(0.0f, 2.0f * (r32)GameWindow->Height / 5.0f) : GetRand(3.0f * (r32)GameWindow->Height / 5.0f, (r32)GameWindow->Height));
    Result->FacingDirection = { GetRand(-1.0f, 1.0f), GetRand(-1.0f, 1.0f) };
    Result->FacingDirection = VectorNormalize(Result->FacingDirection);
    Result->Collides = true;
    Result->ColliderType = Collider_Circle;
    Result->Scale = 1.0f;
    switch (EntityType)
    {
        case EntityType_RockBig:
        {
            Result->dP.x = Result->FacingDirection.x * 100.0f;
            Result->dP.y = Result->FacingDirection.y * 100.0f;
            Result->Radius = 50.0f;
            Result->WrapSize = { 50.0f, 50.0f };
            Result->dRotationJaw = (GetRand(0, 1) & 1 ? GetRand(-0.035f, -0.025f) : GetRand(0.025f, 0.035f));
            Result->texture = GameState->Textures[Texture_RockBig].t;
            Result->Score = 20;
            Result->Tint = {170, 170, 170, 255};
        } break ;
        case EntityType_RockMedium:
        {
            Result->dP.x = Result->FacingDirection.x * 175.0f;
            Result->dP.y = Result->FacingDirection.y * 175.0f;
            Result->Radius = 30.0f;
            Result->WrapSize = { 30.0f, 30.0f };
            Result->dRotationJaw = (GetRand(0, 1) & 1 ? GetRand(-0.065f, -0.05f) : GetRand(0.05f, 0.065f));
            Result->texture = GameState->Textures[Texture_RockMedium].t;
            Result->Score = 50;
            Result->Tint = {130, 130, 130, 255};
        } break ;
        case EntityType_RockSmall:
        {
            Result->dP.x = Result->FacingDirection.x * 225.0f;
            Result->dP.y = Result->FacingDirection.y * 225.0f;
            Result->Radius = 15.0f;
            Result->WrapSize = { 15.0f, 15.0f };
            Result->dRotationJaw = (GetRand(0, 1) & 1 ? GetRand(-0.1f, -0.85f) : GetRand(0.85f, 0.1f));
            Result->dRotationJaw = GetRand(-0.1f, 0.1f);
            Result->texture = GameState->Textures[Texture_RockSmall].t;
            Result->Score = 100;
            Result->Tint = {100, 100, 100, 255};
        } break ;
        default: ASSERT(false);
    }

    return (Result);
}

internal void
SplitRock(game_state *GameState, game_window *GameWindow, entity *Entity)
{
    switch (Entity->Type)
    {
        case EntityType_RockBig:
        {
            for (u32 i = 0;
                 i < 2;
                 ++i)
            {
                entity *NewRock = AddRockEntity(GameState, GameWindow, EntityType_RockMedium);
                NewRock->P = Entity->P;
                NewRock->P.x += GetRand(-20.0f, 20.0f);
                NewRock->P.y += GetRand(-20.0f, 20.0f);
            }
        } break ;
        case EntityType_RockMedium:
        {
            for (u32 i = 0;
                 i < 2;
                 ++i)
            {
                entity *NewRock = AddRockEntity(GameState, GameWindow, EntityType_RockSmall);
                NewRock->P = Entity->P;
                NewRock->P.x += GetRand(-20.0f, 20.0f);
                NewRock->P.y += GetRand(-20.0f, 20.0f);
            }
        } break ;
        case EntityType_RockSmall:
        {
        } break ;
        default: ASSERT(false);
    }
    RemoveEntity(GameState, Entity);
}

internal inline entity*
AddBulletEntity(game_state *GameState, game_window *GameWindow, entity *Source, Vector2 BulletDirection, Color Tint = WHITE)
{
    entity *Result = 0;
    if (Source->Bullets < Source->MaxBullets)
    {
        ++Source->Bullets;
        Result = AddEntity(GameState->World);
        ASSERT(Result);

        Result->Parent = Source;
        Result->ParentType = Source->Type;
        Result->Type = EntityType_Bullet;
        Result->P = Source->P;
        Result->FacingDirection = BulletDirection;
        Result->RotationJaw = atan2(Result->FacingDirection.x, -Result->FacingDirection.y);
        Result->dP.x = Result->FacingDirection.x * 700.0f;
        Result->dP.y = Result->FacingDirection.y * 700.0f;
        Result->Collides = true;
        Result->ColliderType = Collider_Polygon;
        Result->Collider.Points[0] = { -1.0f, -5.0f };
        Result->Collider.Points[1] = { 1.0f, -5.0f };
        Result->Collider.Points[2] = { -1.0f, 5.0f };
        Result->Collider.Points[3] = { 1.0f, 5.0f };
        Result->Collider.Size = 4;
        for (u32 i = 0;
            i < Result->Collider.Size;
            ++i)
        {
            Result->Collider.Points[i] += Result->P;
            Result->Collider.Points[i] = VectorRotate(Result->Collider.Points[i], Result->P, Result->RotationJaw);
        }
        Result->WrapSize = { 3.0f, 13.0f };
        Result->Radius = 3.0f;
        Result->texture = GameState->Textures[Texture_Bullet].t;
        Result->HasDistanceRemaining = true;
        Result->DistanceRemaining = 600.0f;
        Result->Tint = Tint;
        Result->Scale = 1.0f;
    }

    return (Result);
}

internal inline entity*
AddParticleEntity(game_state *GameState, Vector2 P, r32 DistanceRemaining = 100.0f, Color Tint = WHITE, r32 RotationJaw = 100.0f, r32 InitialScale = 1.0f, r32 ScaleRatio = 0.99f)
{
    entity *Result = AddEntity(GameState->World);
    ASSERT(Result);

    Result->Type = EntityType_Particle;
    Result->P = P;
    Result->P.x += GetRand(-10.0f, 10.0f);
    Result->P.y += GetRand(-10.0f, 10.0f);
    if (RotationJaw == 100.0f)
    {
        Result->RotationJaw = GetRand(-PI, PI);
    }
    else
    {
        Result->RotationJaw = RotationJaw + GetRand(-0.5f, 0.5f);
    }
    Result->Acceleration = -50.0f;
    r32 InitialSpeed = GetRand(200.0f, 600.0f);
    Result->FacingDirection.x = cos(Result->RotationJaw);
    Result->FacingDirection.y = sin(Result->RotationJaw);
    Result->dP.x = Result->FacingDirection.x * InitialSpeed;
    Result->dP.y = Result->FacingDirection.y * InitialSpeed;
    Result->texture = GameState->Textures[Texture_Particle].t;
    Result->HasDistanceRemaining = true;
    Result->DistanceRemaining = DistanceRemaining;
    Result->Collides = false;
    Result->Tint = Tint;
    Result->ChangesTint = true;
    Result->TintChange = { 0, 0, 0, 1 };
    Result->ChangesScale = true;
    Result->ScaleChangeRatio = ScaleRatio;
    Result->Scale = InitialScale;

    return (Result);
}

internal inline entity*
AddUfoEntity(game_state* GameState, game_window *GameWindow)
{
    entity *Result = AddEntity(GameState->World);
    ASSERT(Result);

    Result->Type = EntityType_Ufo;
    Result->texture = GameState->Textures[Texture_Ufo].t;
    Result->Tint = WHITE;
    b32 SpawnsLeft = (GetRand(0, 1) & 1);
    Result->P = { SpawnsLeft ? 0.0f : (r32)GameWindow->Width, (r32)(GameWindow->Height / 10.0f) };
    Result->dP = { SpawnsLeft ? 150.0f : -150.0f };
    Result->Scale = 1.0f;
    Result->MaxBullets = 5;
    Result->ColliderType = Collider_Polygon;
    Result->Collider.Points[0] = { -29.0f, 0.0f };
    Result->Collider.Points[1] = { -12.0f, -18.0f };
    Result->Collider.Points[2] = { 12.0f, -18.0f };
    Result->Collider.Points[3] = { 29.0f, 0.0f };
    Result->Collider.Points[4] = { 20.0f, 8.0f };
    Result->Collider.Points[5] = { -20.0f, 8.0f };
    Result->Collider.Size = 6;
    for (u32 i = 0;
         i < Result->Collider.Size;
         ++i)
    {
        Result->Collider.Points[i] += Result->P;
        Result->Collider.Points[i] = VectorRotate(Result->Collider.Points[i], Result->P, Result->RotationJaw);
    }
    Result->Radius = 30.0f;
    Result->Score = 200;

    return (Result);
}

internal inline void
AddCollisionRule(game_state *GameState, entity_type TypeFirst, entity_type TypeSecond, collision_handler *Handler)
{
    if (TypeFirst < TypeSecond)
    {
        entity_type Tmp = TypeFirst;
        TypeFirst = TypeSecond;
        TypeSecond = Tmp;
    }
    // TODO(david): better hashing function
    u32 HashValue = ((TypeFirst * 7 + TypeSecond * 11) & (ArrayCount(GameState->CollisionRuleHash) - 1));
    for (u32 i = HashValue;
         i < ArrayCount(GameState->CollisionRuleHash);
         ++i)
    {
        if (!GameState->CollisionRuleHash[i].Handler)
        {
            GameState->CollisionRuleHash[i].TypeFirst = TypeFirst;
            GameState->CollisionRuleHash[i].TypeSecond = TypeSecond;
            GameState->CollisionRuleHash[i].Handler = Handler;
            return ;
        }
    }
    for (u32 i = 0;
         i < HashValue;
         ++i)
    {
        if (!GameState->CollisionRuleHash[i].Handler)
        {
            GameState->CollisionRuleHash[i].TypeFirst = TypeFirst;
            GameState->CollisionRuleHash[i].TypeSecond = TypeSecond;
            GameState->CollisionRuleHash[i].Handler = Handler;
            return ;
        }
    }
    ASSERT(false);
}

internal inline collision_handler*
DoesCollisionExist(game_state *GameState, entity_type TypeFirst, entity_type TypeSecond)
{
    if (TypeFirst < TypeSecond)
    {
        entity_type Tmp = TypeFirst;
        TypeFirst = TypeSecond;
        TypeSecond = Tmp;
    }
    u32 HashValue = ((TypeFirst * 7 + TypeSecond * 11) & (ArrayCount(GameState->CollisionRuleHash) - 1));
    for (u32 i = HashValue;
         i < ArrayCount(GameState->CollisionRuleHash);
         ++i)
    {
        if (GameState->CollisionRuleHash[i].TypeFirst == TypeFirst &&
            GameState->CollisionRuleHash[i].TypeSecond == TypeSecond)
        {
            ASSERT(TypeFirst != EntityType_Bullet || TypeSecond != EntityType_Bullet);
            return (GameState->CollisionRuleHash[i].Handler);
        }
    }
    for (u32 i = 0;
         i < HashValue;
         ++i)
    {
        if (GameState->CollisionRuleHash[i].TypeFirst == TypeFirst &&
            GameState->CollisionRuleHash[i].TypeSecond == TypeSecond)
        {
            ASSERT(TypeFirst != EntityType_Bullet || TypeSecond != EntityType_Bullet);
            return (GameState->CollisionRuleHash[i].Handler);
        }
    }
    return (0);
}

COLLISION_HANDLER(BulletVsRock)
{
    entity *Bullet = EntityFirst;
    entity *Rock = EntitySecond;
    if (Bullet->Type != EntityType_Bullet)
    {
        entity *Tmp = Bullet;
        Bullet = Rock;
        Rock = Tmp;
    }
    ASSERT(Bullet->Type == EntityType_Bullet);
    ASSERT(IsEntityRockType(Rock));
    polygon ExtendedPolygon = ExtendPolygon(&Bullet->Collider, (Bullet->dP - Rock->dP) * GameState->dt);
    if (PolyVsCircle(&ExtendedPolygon, Rock->P, Rock->Radius))
    // if (CircleVsCircle(Bullet->P, Bullet->Radius, Rock->P, Rock->Radius))
    {
        if (Bullet->ParentType == EntityType_Ship)
        {
            AddScore(GameState, Rock->Score);
        }
        RL->RL_PlaySound(GameState->Sounds[Sound_Explosion].sound);
        u32 NumberOfParticles = 10;
        for (u32 ParticleIndex = 0;
            ParticleIndex < NumberOfParticles;
            ++ParticleIndex)
        {
            AddParticleEntity(GameState, Bullet->P, 75.0f, { 160, 160, 160, 200 });
        }
        RemoveEntity(GameState, Bullet);
        SplitRock(GameState, GameWindow, Rock);
    }
}

COLLISION_HANDLER(RockVsShip)
{
    entity *Rock = EntityFirst;
    entity *Ship = EntitySecond;
    if (Ship->Type != EntityType_Ship)
    {
        entity *Tmp = Rock;
        Rock = Ship;
        Ship = Tmp;
    }
    ASSERT(IsEntityRockType(Rock));
    ASSERT(Ship->Type == EntityType_Ship);
    // extend polygon's size
    polygon ExtendedPolygon = ExtendPolygon(&Ship->Collider, (Ship->dP - Rock->dP) * GameState->dt);
    RL->DrawLineStrip(ExtendedPolygon.Points, ExtendedPolygon.Size, GREEN);
    if (PolyVsCircle(&Ship->Collider, Rock->P, Rock->Radius))
    // if (CircleVsTriangle(Rock->P, Rock->Radius, Ship->Points[0] + Ship->P, Ship->Points[1] + Ship->P, Ship->Points[2] + Ship->P, Ship->P, Ship->RotationJaw))
    {
        u32 NumberOfParticles = 20;
        for (u32 ParticleIndex = 0;
            ParticleIndex < NumberOfParticles;
            ++ParticleIndex)
        {
            AddParticleEntity(GameState, Ship->P, 300.0f, { 200, 30, 0, 150 }, 100.0f, 2.0f);
        }
        RL->PlaySoundMulti(GameState->Sounds[Sound_Explosion2].sound);
        AddScore(GameState, Rock->Score);
        RemoveEntity(GameState, Ship);
        SplitRock(GameState, GameWindow, Rock);
    }
}

COLLISION_HANDLER(BulletVsShip)
{
    entity *Bullet = EntityFirst;
    entity *Ship = EntitySecond;
    if (Bullet->Type != EntityType_Bullet)
    {
        entity *Tmp = Bullet;
        Bullet = Ship;
        Ship = Tmp;
    }
    ASSERT(Bullet->Type == EntityType_Bullet);
    ASSERT(Ship->Type == EntityType_Ship);
    polygon ExtendedPolygon = ExtendPolygon(&Ship->Collider, (Ship->dP - Bullet->dP) * GameState->dt);
    if (Bullet->Parent != Ship && PolyVsPoly(&ExtendedPolygon, &Bullet->Collider))
    // if (Bullet->Parent != Ship && PolyVsCircle(&ExtendedPolygon, Bullet->P, Bullet->Radius))
    // if (Bullet->Parent != Ship && CircleVsTriangle(Bullet->P, Bullet->Radius, Ship->Points[0] + Ship->P, Ship->Points[1] + Ship->P, Ship->Points[2] + Ship->P, Ship->P, Ship->RotationJaw))
    {
        u32 NumberOfParticles = 20;
        for (u32 ParticleIndex = 0;
            ParticleIndex < NumberOfParticles;
            ++ParticleIndex)
        {
            AddParticleEntity(GameState, Ship->P, 300.0f, { 0, 30, 200, 150 }, 100.0f, 2.0f);
        }
        RL->PlaySoundMulti(GameState->Sounds[Sound_Explosion2].sound);
        RemoveEntity(GameState, Ship);
        RemoveEntity(GameState, Bullet);
    }
}

COLLISION_HANDLER(BulletVsUfo)
{
    entity *Bullet = EntityFirst;
    entity *Ufo = EntitySecond;
    if (Bullet->Type != EntityType_Bullet)
    {
        entity *Tmp = Bullet;
        Bullet = Ufo;
        Ufo = Tmp;
    }
    ASSERT(Bullet->Type == EntityType_Bullet);
    ASSERT(Ufo->Type == EntityType_Ufo);
    polygon ExtendedPolygon = ExtendPolygon(&Bullet->Collider, (Bullet->dP - Ufo->dP) * GameState->dt);
    if (Bullet->ParentType != EntityType_Ufo && PolyVsPoly(&ExtendedPolygon, &Ufo->Collider))
    // if (Bullet->ParentType != EntityType_Ufo && CircleVsCircle(Bullet->P, Bullet->Radius, Ufo->P, Ufo->Radius))
    {
        AddScore(GameState, Ufo->Score);
        u32 NumberOfParticles = 20;
        for (u32 ParticleIndex = 0;
            ParticleIndex < NumberOfParticles;
            ++ParticleIndex)
        {
            AddParticleEntity(GameState, Ufo->P, 300.0f, { 200, 30, 0, 150 }, 100.0f, 2.0f);
        }
        RL->PlaySoundMulti(GameState->Sounds[Sound_Explosion].sound);
        RemoveEntity(GameState, Ufo);
        GameState->UfoSpawnTargetGameTick = GameState->GameTicks + 20 * GameState->TargetFPS;
        PushTimedEvent(GameState, GameState->UfoSpawnTargetGameTick, [](game_state *GameState, game_window *GameWindow, raylib_wrapper_code *RL){
            GameState->Ufo = AddUfoEntity(GameState, GameWindow);
        }, TimedEvent_Ufo);
        PushTimedEvent(GameState, GameState->GameTicks + 2 * GameState->TargetFPS, [](game_state *GameState, game_window *GameWindow, raylib_wrapper_code *RL){
            RL->RL_PlaySound(GameState->Sounds[Sound_Womp].sound);
        }, TimedEvent_Womp);
        RemoveEntity(GameState, Bullet);
    }
}

COLLISION_HANDLER(ShipVsUfo)
{
    entity *Ship = EntityFirst;
    entity *Ufo = EntitySecond;
    if (Ship->Type != EntityType_Ship)
    {
        entity *Tmp = Ship;
        Ship = Ufo;
        Ufo = Tmp;
    }
    ASSERT(Ship->Type == EntityType_Ship);
    ASSERT(Ufo->Type == EntityType_Ufo);
    polygon ExtendedPolygon = ExtendPolygon(&Ship->Collider, (Ship->dP - Ufo->dP) * GameState->dt);
    if (PolyVsPoly(&ExtendedPolygon, &Ufo->Collider))
    // if (CircleVsTriangle(Ufo->P, Ufo->Radius, Ship->Points[0] + Ship->P, Ship->Points[1] + Ship->P, Ship->Points[2] + Ship->P, Ship->P, Ship->RotationJaw))
    {
        u32 NumberOfParticles = 20;
        for (u32 ParticleIndex = 0;
            ParticleIndex < NumberOfParticles;
            ++ParticleIndex)
        {
            AddParticleEntity(GameState, Ship->P, 300.0f, { 0, 30, 200, 150 }, 100.0f, 2.0f);
        }
        for (u32 ParticleIndex = 0;
            ParticleIndex < NumberOfParticles;
            ++ParticleIndex)
        {
            AddParticleEntity(GameState, Ufo->P, 300.0f, { 200, 30, 0, 150 }, 100.0f, 2.0f);
        }
        RL->PlaySoundMulti(GameState->Sounds[Sound_Explosion].sound);
        RL->PlaySoundMulti(GameState->Sounds[Sound_Explosion2].sound);
        RemoveEntity(GameState, Ship);
        RemoveEntity(GameState, Ufo);
    }
}
