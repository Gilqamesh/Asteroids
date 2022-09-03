#ifndef GAMELAYER_HPP
#define GAMELAYER_HPP

#include "platform.hpp"
#include "raylib.h"

/***
 * Large and contiguous world
 * Large number of entities
 *  -> simulate entire world by using simulating rectangular regions
 * Procedural world generation
 */

struct memory_arena
{
    memory_index Size;
    u8 *Base;
    memory_index Used;
};

internal void
InitializeArena(memory_arena *Arena, memory_index Size, u8 *Base)
{
    Arena->Size = Size;
    Arena->Base = Base;
    Arena->Used = 0;
}

#define PushStruct(Arena, type) (type *)PushSize_(Arena, sizeof(type))
#define PushArray(Arena, Count, type) (type *)PushSize_(Arena, (Count) * sizeof(type))
void *
PushSize_(memory_arena *Arena, memory_index Size)
{
    ASSERT((Arena->Used + Size) <= Arena->Size);
    void *Result = Arena->Base + Arena->Used;
    Arena->Used += Size;

    return (Result);
}

# include "entity.hpp"
# include "world.hpp"

enum loading_state
{
    LoadingState_Waiting,
    LoadingState_Loading,
    LoadingState_Finished
};

enum
{
    Texture_Bunnies,
    Texture_Running_Hero,
    Texture_Reserved_0,
    Texture_Reserved_1,
    Texture_Reserved_2,
    Texture_Reserved_3,
    Texture_Reserved_4,
    Texture_Reserved_5,
    Texture_Reserved_6,
    Texture_Reserved_7,
    Texture_Reserved_8,
    Texture_Reserved_9,
    Texture_Reserved_10,
    Texture_Reserved_11,
    Texture_Reserved_12,
    Texture_Reserved_13,
    Texture_Size
};

struct texture
{
    Texture2D t;
    b32 IsLoaded;
};

#include <thread>

struct sim_region
{
    entity Entities[256];
    Rectangle Region; // grow region by the next position of entities to check for collision
};

struct game_state
{
    memory_arena WorldArena;
    raylib_wrapper_code RaylibWrapper;
    i32 TargetFPS;

    RenderTexture2D Render_World;
    Rectangle Render_World_Rec;
    RenderTexture2D Render_UI;
    Rectangle Render_UI_Rec;
    RenderTexture2D Render_Overlay;
    Rectangle Render_Overlay_Rec;

    texture Textures[Texture_Size];

    Camera2D Camera;
    entity *CameraFollowingEntity;

    loading_state LoadingState;
    u32 LoadingBar;
    u32 LoadingBarMax;
    thread LoadingThread;

    world *World;
    Font Fonts[16];
    u8 FontsLoaded;
};

#endif
