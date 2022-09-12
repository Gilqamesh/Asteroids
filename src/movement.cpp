internal inline
void WrapEntityIntoWindow(entity *Entity, game_window *Window)
{
    if (Entity->P.x + Entity->WrapSize.x < 0.0f)
    {
        Entity->P.x = (r32)Window->Width - Entity->P.x;
    }
    else if (Entity->P.x - Entity->WrapSize.x > (r32)Window->Width)
    {
        Entity->P.x = Entity->P.x - 2.0f * Entity->WrapSize.x - Window->Width;
    }
    if (Entity->P.y + Entity->WrapSize.y < 0.0f)
    {
        Entity->P.y = (r32)Window->Height - Entity->P.y;
    }
    else if (Entity->P.y - Entity->WrapSize.y > (r32)Window->Height)
    {
        Entity->P.y = Entity->P.y - 2.0f * Entity->WrapSize.y - Window->Height;
    }
}

internal inline
void MoveEntity(game_state *GameState, entity *Entity, game_window *Window, r32 dt)
{
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
    Entity->dP.x += dt * Acceleration.x;
    Entity->dP.y += dt * Acceleration.y;
    if (Entity->HasDistanceRemaining)
    {
        Vector2 PrevP = Entity->P;
        Vector2 NextP = Entity->P;
        NextP.x += dt * Entity->dP.x + dt * dt * Acceleration.x / 2.0f;
        NextP.y += dt * Entity->dP.y + dt * dt * Acceleration.y / 2.0f;
        Vector2 Displacement = { NextP.x - PrevP.x, NextP.y - PrevP.y };
        r32 Distance = VectorLen(Displacement);
        if (Entity->DistanceRemaining < Distance)
        {
            Displacement = VectorNormalize(Displacement);
            Displacement.x *= Entity->DistanceRemaining;
            Displacement.y *= Entity->DistanceRemaining;
            Entity->P.x += Displacement.x;
            Entity->P.y += Displacement.y;
            Entity->DistanceRemaining = 0;
            RemoveEntity(GameState, Entity);
        }
        else
        {
            Entity->DistanceRemaining -= Distance;
            Entity->P = NextP;
        }
    }
    else
    {
        Entity->P.x += dt * Entity->dP.x + dt * dt * Acceleration.x / 2.0f;
        Entity->P.y += dt * Entity->dP.y + dt * dt * Acceleration.y / 2.0f;
    }
    WrapEntityIntoWindow(Entity, Window);
}
