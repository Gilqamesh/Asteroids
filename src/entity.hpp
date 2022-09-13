#ifndef ENTITY_HPP
# define ENTITY_HPP

enum entity_type
{
    EntityType_Invalid,
    EntityType_Bullet,
    EntityType_Ship,
    EntityType_RockBig,
    EntityType_RockMedium,
    EntityType_RockSmall,
    EntityType_Particle,
    EntityType_Ufo,
    EntityType_Size,
};

enum collider_type
{
    Collider_Invalid,
    Collider_Circle,
    Collider_Polygon
};

// TODO(david) think about an Entity-Component framework maybe
enum
{
    Component_Collider,
    Component_RemainingDistance,
    Component_Tint,
    Component_Scale,
    Component_Bullet,
    Component_Parent,
    Component_Texture,
    Component_Rotation,
    Component_Velocity,
};

struct polygon
{
    Vector2 Points[16];
    u32 Size;
};

struct entity
{
    u32 ComponentsFlag;
    u32 Id;
    b32 Collides;
    b32 IsAlive;
    b32 HasDistanceRemaining;
    r32 DistanceRemaining;
    Vector2 P;
    Vector2 dP;
    r32 Drag;
    Vector2 FacingDirection;
    r32 Acceleration;
    entity_type Type;
    r32 RotationJaw;
    r32 dRotationJaw;
    r32 dRotationJawMax;
    Texture texture;
    entity *Parent;
    entity_type ParentType; // for bullets.. as the parent entity might get invalidated, we need another way to know if it was the ship's bullet
    u32 Bullets;
    u32 MaxBullets;
    u32 Score;
    Vector2 WrapSize;
    collider_type ColliderType;
    // for circle collider
    r32 Radius;
    // for polygon collider
    polygon Collider;
    Color Tint;
    b32 ChangesTint;
    Color TintChange;
    b32 ChangesScale;
    r32 ScaleChangeRatio;
    r32 Scale;
};

#endif
