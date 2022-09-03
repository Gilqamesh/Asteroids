#ifndef ENTITY_HPP
# define ENTITY_HPP

enum entity_type
{
    EntityType_Hero,
    EntityType_Bullet,
    EntityType_Wall,
    EntityType_Ship,
    EntityType_RockBig,
    EntityType_RockMedium,
    EntityType_RockSmall,
    EntityType_Size,
};

struct entity
{
    u32 Id;
    b32 Collides;
    b32 HasWorldPosition;
    Vector2 P;
    Vector2 dP;
    Vector2 ddP;
    entity_type Type;
    Rectangle Bound;
};

#endif
