internal inline
void MoveEntity(game_state *GameState, entity *Entity, game_window *Window)
{
    Entity->RotationJaw += Entity->dRotationJaw;
    if (Entity->RotationJaw > 2.0f * PI)
    {
        Entity->RotationJaw -= 2.0f * PI;
    }
    if (Entity->RotationJaw < 0.0f)
    {
        Entity->RotationJaw += 2.0f * PI;
    }
    Entity->FacingDirection.x = cos(Entity->RotationJaw);
    Entity->FacingDirection.y = sin(Entity->RotationJaw);
    Vector2 Acceleration = { Entity->FacingDirection.x * Entity->Acceleration, Entity->FacingDirection.y * Entity->Acceleration };
    Vector2 Drag = -Entity->Drag * Entity->dP;
    Acceleration = Acceleration + Drag;
    Entity->dP += GameState->dt * Acceleration;

    Vector2 Displacement = GameState->dt * Entity->dP + GameState->dt * GameState->dt * Acceleration / 2.0f;
    if (Entity->HasDistanceRemaining)
    {
        Entity->DistanceRemaining -= VectorLen(Displacement);
        if (Entity->DistanceRemaining < 0.0f)
        {
            RemoveEntity(GameState, Entity);
        }
    }

    if (Entity->IsAlive)
    {
        Vector2 NextEntityP = Entity->P + Displacement;
        if (NextEntityP.x + Entity->WrapSize.x < 0.0f)
        {
            Displacement.x = (r32)Window->Width - 2.0f * NextEntityP.x + Displacement.x;
            // Entity->P.x = (r32)Window->Width - Entity->P.x;
        }
        else if (NextEntityP.x - Entity->WrapSize.x > (r32)Window->Width)
        {
            Displacement.x = -(2.0f * Entity->WrapSize.x + Window->Width + Displacement.x);
            // Entity->P.x = Entity->P.x - 2.0f * Entity->WrapSize.x - Window->Width;
        }
        if (NextEntityP.y + Entity->WrapSize.y < 0.0f)
        {
            Displacement.y = (r32)Window->Height - 2.0f * NextEntityP.y + Displacement.y;
            // Entity->P.y = (r32)Window->Height - Entity->P.y;
        }
        else if (NextEntityP.y - Entity->WrapSize.y > (r32)Window->Height)
        {
            Displacement.y = -(2.0f * Entity->WrapSize.y + Window->Height + Displacement.y);
            // Entity->P.y = Entity->P.y - 2.0f * Entity->WrapSize.y - Window->Height;
        }
        Entity->P += Displacement;

        if (Entity->ColliderType == Collider_Polygon)
        {
            for (u32 PointIndex = 0;
                PointIndex <= Entity->Collider.Size;
                ++PointIndex)
            {
                Entity->Collider.Points[PointIndex] += Displacement;
                Entity->Collider.Points[PointIndex] = VectorRotate(Entity->Collider.Points[PointIndex], Entity->P, Entity->dRotationJaw);
            }
        }
    }
}
