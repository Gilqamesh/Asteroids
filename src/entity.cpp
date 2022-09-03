entity *AddEntity(world *World, Rectangle Bound = {}, entity_type EntityType = EntityType_Wall)
{
    ASSERT(World->EntitiesSize < ArrayCount(World->Entities));
    entity *Result = &World->Entities[World->EntitiesSize++];
    Result->Bound = Bound;
    Result->P = { Bound.x + Bound.width / 2.0f, Bound.y + Bound.height / 2.0f };
    Result->Type = EntityType;

    return (Result);
}
