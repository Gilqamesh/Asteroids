#ifndef GAMELAYER_HPP
# define GAMELAYER_HPP

# include "raylib.h"
# include "rlgl.h"
# include "platform.hpp"

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

#include "entity.hpp"

enum
{
    Texture_Ship,
    Texture_ShipBlue,
    Texture_Bullet,
    Texture_RockBig,
    Texture_RockMedium,
    Texture_RockSmall,
    Texture_Particle,
    Texture_SplashScreen,
    Texture_Ufo,
    Texture_Size
};

struct texture
{
    Texture2D t;
    Vector2 Offset;
    b32 IsLoaded;
};

struct world
{
    entity Entities[8192];
    u32 EntitiesSize;
    u32 FreeEntities[8192];
    u32 FreeEntitiesSize;
};

enum loading_state
{
    LoadingState_Waiting,
    LoadingState_Loading,
    LoadingState_Finished
};

enum screen_state
{
    Screen_Splash,
    Screen_MainMenu,
    Screen_Game,
    Screen_GameOver
};

#include <thread>

enum
{
    MainMenuButton_Start,
    MainMenuButton_Quit,
    MainMenuButton_Size
};

struct button
{
    Vector2 Content;
    Vector2 ContentSize;
    Vector2 PaddingSize;
    Vector2 BorderSize;
    Vector2 MarginSize;
    const char *Text;
    Font font;
    r32 FontSize;
    Color ContentColor;
    Color BorderColor;
    Rec ContentBound; // redundant, but makes it easier to use
    b32 IsHighlighted;
};

enum
{
    Sound_Button,
    Sound_CorkPop,
    Sound_Cymbals,
    Sound_Explosion,
    Sound_Explosion2,
    Sound_Fanfare,
    Sound_Laser,
    Sound_Phaser,
    Sound_Splash,
    Sound_TypeWriterClick,
    Sound_Ufo,
    Sound_UniverseAmbient,
    Sound_Womp,
    Sound_Womp2,
    Sound_Zag,
    Sound_Size
};

struct game_sound
{
    Sound sound;
    b32 ShouldPlay;
};

struct game_state;
# define COLLISION_HANDLER(name) void name(game_state *GameState, game_window *GameWindow, raylib_wrapper_code *RL, entity *EntityFirst, entity *EntitySecond)
typedef COLLISION_HANDLER(collision_handler);
struct pair_wise_collision_rule
{
    entity_type TypeFirst;
    entity_type TypeSecond;

    collision_handler *Handler;
};

#include "event.hpp"

struct game_state
{
    memory_arena WorldArena;
    world *World;

    // NOTE(david): Must be a power of two
    pair_wise_collision_rule CollisionRuleHash[256];

    timed_event TimedEventHeap[1024]; // min heap
    u32 TimedEventHeapSize;

    r32 dt;

    entity *Ship;
    u32 ShipLifes;

    entity *Rocks[512];
    u32 RocksSize;
    u32 BigRocksInitialNumber;

    i32 TargetFPS;
    u32 FrameCounter; // Always progresses
    u32 GameTicks; // Progresses only during the game (not in pause, not during cutscene etc.)

    u32 PlayScore;
    u32 HighestPlayScore;
    b32 BeatPreviousScore;

    entity *Ufo;
    u32 UfoSpawnTargetGameTick;

    b32 IsPaused;

    b32 IsAudioDeviceInitialized;
    game_sound Sounds[Sound_Size];

    screen_state ScreenState;

    RenderTexture2D Render_MainMenu;
    Rec Render_MainMenu_Rec;
    RenderTexture2D Render_SplashScreen;
    Rec Render_SplashScreen_Rec;
    RenderTexture2D Render_World;
    Rec Render_World_Rec;
    RenderTexture2D Render_Overlay;
    Rec Render_Overlay_Rec;
    RenderTexture2D Render_GameOver;
    Rec Render_GameOver_Rec;

    texture Textures[Texture_Size];

    loading_state LoadingState;
    u32 LoadingBar;
    u32 LoadingBarMax;
    thread LoadingThread;

    // TODO(david): Temporary solution instead of using capture for lambda when pushing an event handler
    u32 CustomData;

    button MainMenuButtons[MainMenuButton_Size];

    Font Fonts[16];
    u8 FontsLoaded;
};

internal void
AddScore(game_state *GameState, u32 Score)
{
    GameState->PlayScore += Score;
    if (GameState->HighestPlayScore < GameState->PlayScore)
    {
        GameState->BeatPreviousScore = true;
        GameState->HighestPlayScore = GameState->PlayScore;
    }
}

#endif
