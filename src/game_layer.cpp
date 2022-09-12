#include "platform.hpp"
#include "game_layer.hpp"
#include "types.hpp"
#include "misc.hpp"
#include <cmath>
#include "utils.cpp"
#include "ui.cpp"
#include "event.cpp"
#include "entity.cpp"
#include "movement.cpp"

#if defined(G_DEBUG)
game_memory *DebugGlobalMemory;
void DebugPrintCycleCounters(game_memory *GameMemory, char *Buffer, u32 BufferSize)
{
    u32 BufferIndex = 0;
    char *Msg = "DEBUG CYCLE COUNTS:\n";
    u32 MsgLen = strlen(Msg);
    if (BufferIndex + MsgLen >= BufferSize)
    {
        return ;
    }
    sprintf(Buffer, Msg);
    BufferIndex += MsgLen;
    for (u32 CounterIndex = 0;
         CounterIndex < ArrayCount(GameMemory->Counters);
         ++CounterIndex)
    {
        debug_cycle_counter *Counter = GameMemory->Counters + CounterIndex;

        if (Counter->HitCount)
        {
            char Buffer2[256];
            sprintf(Buffer2, "%u: %12llucy %12uh %12llucy/h",
                    CounterIndex,
                    Counter->CycleCount,
                    Counter->HitCount,
                    Counter->CycleCount / Counter->HitCount);
            Counter->HitCount = 0;
            Counter->CycleCount = 0;
            Counter->CycleCount = 0;
            MsgLen = strlen(Buffer2);
            if (BufferIndex + MsgLen >= BufferSize)
            {
                return ;
            }
            sprintf(Buffer + BufferIndex, Buffer2);
            BufferIndex += MsgLen;
        }
    }
}
#endif

internal void
ResetGameState(game_state *GameState, game_window *GameWindow, raylib_wrapper_code *RL)
{
    GameState->Ufo = 0;
    GameState->World->EntitiesSize = 0;
    GameState->World->FreeEntitiesSize = 0;
    GameState->RocksSize = 0;
    GameState->BeatPreviousScore = false;
    GameState->BigRocksInitialNumber = 3;
    for (u32 i = 0;
        i < GameState->BigRocksInitialNumber;
        ++i)
    {
        AddRockEntity(GameState, GameWindow, EntityType_RockBig);
    }
    GameState->Ship = AddShipEntity(GameState, GameWindow);
    GameState->ShipLifes = 3;
    GameState->PlayScore = 0;
    GameState->UfoSpawnTargetGameTick = GameState->GameTicks + 20 * GameState->TargetFPS;
    PushTimedEvent(GameState, GameState->UfoSpawnTargetGameTick, [](game_state *GameState, game_window *GameWindow, raylib_wrapper_code *RL){
        GameState->Ufo = AddUfoEntity(GameState, GameWindow);
    }, TimedEvent_Ufo);
    PushTimedEvent(GameState, GameState->GameTicks + 2 * GameState->TargetFPS, [](game_state *GameState, game_window *GameWindow, raylib_wrapper_code *RL){
        RL->RL_PlaySound(GameState->Sounds[Sound_Womp].sound);
    }, TimedEvent_Womp);
}

internal void
TransitionToNextLevel(game_state *GameState, game_window *GameWindow)
{
    ++GameState->BigRocksInitialNumber;
    for (u32 i = 0;
        i < GameState->BigRocksInitialNumber;
        ++i)
    {
        AddRockEntity(GameState, GameWindow, EntityType_RockBig);
    }
    if (!GameState->Ship)
    {   
        GameState->Ship = AddShipEntity(GameState, GameWindow);
        GameState->Ship->dP = {};
        GameState->Ship->P = { (r32)GameWindow->Width / 2.0f, (r32)GameWindow->Height / 2.0f };
    }
}

#if defined(SINGLE_FILE_BUILD)
# else
extern "C"
{
#endif

    void SetupWindows(game_memory *GameMemory, game_window *GameWindow)
    {
        game_state *GameState = (game_state *)GameMemory->PermanentStorage;
        raylib_wrapper_code *RL = &GameMemory->RaylibWrapper;
        GameWindow->Width = 1280;
        GameWindow->Height = 720;
        GameWindow->Shown = true;
        RL->InitWindow(GameWindow->Width, GameWindow->Height, "Asteroids");
        RL->SetWindowPosition(0, 30);

        GameState->TargetFPS = 60;
        RL->SetTargetFPS(GameState->TargetFPS);
    }

    void LoadResources(game_memory *GameMemory, game_window *GameWindow)
    {
        // TODO(david): Draw something for loading
        game_state *GameState = (game_state *)GameMemory->PermanentStorage;
        raylib_wrapper_code *RL = &GameMemory->RaylibWrapper;

        if (GameMemory->IsMemoryInitialized == false)
        {
            InitializeArena(&GameState->WorldArena, GameMemory->PermanentStorageSize - sizeof(game_state),
                            (u8 *)GameMemory->PermanentStorage + sizeof(game_state));
            GameState->World = PushStruct(&GameState->WorldArena, world);
            GameMemory->IsMemoryInitialized = true;
        }

        GameState->Fonts[GameState->FontsLoaded++] = RL->LoadFont("fonts/alagard.png");
        GameState->Fonts[GameState->FontsLoaded++] = RL->LoadFont("fonts/alpha_beta.png");
        GameState->Fonts[GameState->FontsLoaded++] = RL->LoadFont("fonts/jupiter_crash.png");
        GameState->Fonts[GameState->FontsLoaded++] = RL->LoadFont("fonts/mecha.png");
        GameState->Fonts[GameState->FontsLoaded++] = RL->LoadFont("fonts/pixantiqua.png");
        GameState->Fonts[GameState->FontsLoaded++] = RL->LoadFont("fonts/pixelplay.png");
        GameState->Fonts[GameState->FontsLoaded++] = RL->LoadFont("fonts/romulus.png");
        GameState->Fonts[GameState->FontsLoaded++] = RL->LoadFont("fonts/setback.png");

        GameState->Render_MainMenu = RL->LoadRenderTexture(GameWindow->Width, GameWindow->Height);
        GameState->Render_MainMenu_Rec = {0.0f, 0.0f, (r32)GameState->Render_MainMenu.texture.width, -(r32)GameState->Render_MainMenu.texture.height};
        GameState->Render_SplashScreen = RL->LoadRenderTexture(GameWindow->Width, GameWindow->Height);
        GameState->Render_SplashScreen_Rec = {0.0f, 0.0f, (r32)GameState->Render_SplashScreen.texture.width, -(r32)GameState->Render_SplashScreen.texture.height};
        GameState->Render_World = RL->LoadRenderTexture(GameWindow->Width, GameWindow->Height);
        GameState->Render_World_Rec = {0.0f, 0.0f, (r32)GameState->Render_World.texture.width, -(r32)GameState->Render_World.texture.height};
        GameState->Render_Overlay = RL->LoadRenderTexture(GameWindow->Width, GameWindow->Height);
        GameState->Render_Overlay_Rec = {0.0f, 0.0f, (r32)GameState->Render_Overlay.texture.width, -(r32)GameState->Render_Overlay.texture.height};
        GameState->Render_GameOver = RL->LoadRenderTexture(GameWindow->Width, GameWindow->Height);
        GameState->Render_GameOver_Rec = {0.0f, 0.0f, (r32)GameState->Render_GameOver.texture.width, -(r32)GameState->Render_GameOver.texture.height};

        GameState->Textures[Texture_Ship].t = RL->LoadTexture("textures/Ship.png");
        GameState->Textures[Texture_Ship].Offset = {50, 50};
        GameState->Textures[Texture_ShipBlue].t = RL->LoadTexture("textures/ShipBlue.png");
        GameState->Textures[Texture_ShipBlue].Offset = {51, 51};
        GameState->Textures[Texture_Bullet].t = RL->LoadTexture("textures/Bullet.png");
        GameState->Textures[Texture_Bullet].Offset = {51, 51};
        GameState->Textures[Texture_RockBig].t = RL->LoadTexture("textures/RockBig.png");
        GameState->Textures[Texture_RockBig].Offset = {51, 51};
        GameState->Textures[Texture_RockMedium].t = RL->LoadTexture("textures/RockMedium.png");
        GameState->Textures[Texture_RockMedium].Offset = {51, 51};
        GameState->Textures[Texture_RockSmall].t = RL->LoadTexture("textures/RockSmall.png");
        GameState->Textures[Texture_RockSmall].Offset = {51, 51};
        GameState->Textures[Texture_Particle].t = RL->LoadTexture("textures/Particle.png");
        GameState->Textures[Texture_Particle].Offset = {10, 10};
        GameState->Textures[Texture_SplashScreen].t = RL->LoadTexture("textures/SplashScreen.png");
        GameState->Textures[Texture_SplashScreen].Offset = {0, 0};
        GameState->Textures[Texture_Ufo].t = RL->LoadTexture("textures/Ufo.png");
        GameState->Textures[Texture_Ufo].Offset = {50, 50};

        if (RL->IsAudioDeviceReady() == false)
        {
            RL->InitAudioDevice();
            if (RL->IsAudioDeviceReady())
            {
                RL->SetMasterVolume(0.1f);
                GameState->IsAudioDeviceInitialized = true;

                GameState->Sounds[Sound_Button].sound = RL->LoadSound("sounds/button.wav");
                GameState->Sounds[Sound_Button].ShouldPlay = true;
                GameState->Sounds[Sound_CorkPop].sound = RL->LoadSound("sounds/cork_pop.wav");
                GameState->Sounds[Sound_CorkPop].ShouldPlay = true;
                GameState->Sounds[Sound_Cymbals].sound = RL->LoadSound("sounds/cymbals.wav");
                GameState->Sounds[Sound_Cymbals].ShouldPlay = true;
                GameState->Sounds[Sound_Explosion].sound = RL->LoadSound("sounds/explosion.wav");
                GameState->Sounds[Sound_Explosion].ShouldPlay = true;
                GameState->Sounds[Sound_Explosion2].sound = RL->LoadSound("sounds/explosion2.wav");
                GameState->Sounds[Sound_Explosion2].ShouldPlay = true;
                GameState->Sounds[Sound_Fanfare].sound = RL->LoadSound("sounds/fanfare.wav");
                GameState->Sounds[Sound_Fanfare].ShouldPlay = true;
                GameState->Sounds[Sound_Laser].sound = RL->LoadSound("sounds/laser.wav");
                GameState->Sounds[Sound_Laser].ShouldPlay = true;
                GameState->Sounds[Sound_Phaser].sound = RL->LoadSound("sounds/phaser.wav");
                GameState->Sounds[Sound_Phaser].ShouldPlay = true;
                GameState->Sounds[Sound_Splash].sound = RL->LoadSound("sounds/splash.wav");
                GameState->Sounds[Sound_Splash].ShouldPlay = true;
                GameState->Sounds[Sound_TypeWriterClick].sound = RL->LoadSound("sounds/typewriter_click.wav");
                GameState->Sounds[Sound_TypeWriterClick].ShouldPlay = true;
                GameState->Sounds[Sound_Ufo].sound = RL->LoadSound("sounds/ufo.wav");
                GameState->Sounds[Sound_Ufo].ShouldPlay = true;
                GameState->Sounds[Sound_UniverseAmbient].sound = RL->LoadSound("sounds/universe_ambient.wav");
                GameState->Sounds[Sound_UniverseAmbient].ShouldPlay = true;
                GameState->Sounds[Sound_Womp].sound = RL->LoadSound("sounds/womp.wav");
                GameState->Sounds[Sound_Womp].ShouldPlay = true;
                GameState->Sounds[Sound_Womp2].sound = RL->LoadSound("sounds/womp2.wav");
                GameState->Sounds[Sound_Womp2].ShouldPlay = true;
                GameState->Sounds[Sound_Zag].sound = RL->LoadSound("sounds/zag.wav");
                GameState->Sounds[Sound_Zag].ShouldPlay = true;
            }
        }

        AddCollisionRule(GameState, EntityType_Bullet, EntityType_RockSmall, &BulletVsRock);
        AddCollisionRule(GameState, EntityType_Bullet, EntityType_RockMedium, &BulletVsRock);
        AddCollisionRule(GameState, EntityType_Bullet, EntityType_RockBig, &BulletVsRock);
        AddCollisionRule(GameState, EntityType_Ship, EntityType_RockSmall, &RockVsShip);
        AddCollisionRule(GameState, EntityType_Ship, EntityType_RockMedium, &RockVsShip);
        AddCollisionRule(GameState, EntityType_Ship, EntityType_RockBig, &RockVsShip);
        AddCollisionRule(GameState, EntityType_Ship, EntityType_Bullet, &BulletVsShip);
        AddCollisionRule(GameState, EntityType_Bullet, EntityType_Ufo, &BulletVsUfo);
        AddCollisionRule(GameState, EntityType_Ship, EntityType_Ufo, &ShipVsUfo);

        GameState->ScreenState = Screen_Splash;
    }

    void UpdateAndRender(game_memory *GameMemory, game_window *GameWindow)
    {
        game_state *GameState = (game_state *)GameMemory->PermanentStorage;
        world *World = GameState->World;
        raylib_wrapper_code *RL = &GameMemory->RaylibWrapper;

        r32 dt = RL->GetFrameTime();
        Vector2 MousePosition = RL->GetMousePosition();

        //
        // NOTE(david): game state dispatching
        //
        switch (GameState->ScreenState)
        {
            case Screen_Splash:
            {
                local_persist u32 LastFrameCounterSeen;

                if (LastFrameCounterSeen < GameState->FrameCounter - 1)
                {
                    RL->BeginTextureMode(GameState->Render_SplashScreen);
                    RL->ClearBackground(BLACK);
                    RL->EndTextureMode();

                    u32 StartTargetFrame = GameState->FrameCounter + 2 * GameState->TargetFPS;
                    u32 EndTargetFrame = GameState->FrameCounter + 8 * GameState->TargetFPS;
                    u32 NumberOfTransitions = 100;
                    for (u32 Transition = 0;
                         Transition < NumberOfTransitions;
                         ++Transition)
                    {
                        r32 t = (r32)Transition / (r32)NumberOfTransitions;
                        u8 Transparency = (u8)(255.0f + t * -255.0f);
                        u32 TargetFrame = (u32)((r32)StartTargetFrame + t * (r32)(EndTargetFrame - StartTargetFrame));
                        PushTimedEvent(GameState,TargetFrame, [](game_state *GameState, game_window *GameWindow, raylib_wrapper_code *RL){
                            RL->BeginTextureMode(GameState->Render_SplashScreen);
                            RL->ClearBackground(BLACK);
                            RL->DrawTextureRec(GameState->Textures[Texture_SplashScreen].t, { 0.0f, 0.0f, (r32)GameWindow->Width, (r32)GameWindow->Height }, {}, {(u8)GameState->CustomData, (u8)GameState->CustomData, (u8)GameState->CustomData, 255});
                            RL->EndTextureMode();
                        }, TimedEvent_SplashScreenSound, Transparency);
                    }
                    PushTimedEvent(GameState, StartTargetFrame, [](game_state *GameState, game_window *GameWindow, raylib_wrapper_code *RL){
                        RL->RL_PlaySound(GameState->Sounds[Sound_Splash].sound);
                    }, TimedEvent_SplashScreenSound);
                    PushTimedEvent(GameState, EndTargetFrame, [](game_state *GameState, game_window *GameWindow, raylib_wrapper_code *RL){
                        GameState->ScreenState = Screen_MainMenu;
                    }, TimedEvent_SplashToMain);
                }

                RL->BeginDrawing();
                RL->DrawTextureRec(GameState->Render_SplashScreen.texture, GameState->Render_SplashScreen_Rec, {}, WHITE);
                RL->EndDrawing();

                LastFrameCounterSeen = GameState->FrameCounter;
            } break ;
            case Screen_MainMenu:
            {
                button *StartButton = &GameState->MainMenuButtons[MainMenuButton_Start];
                button *QuitButton = &GameState->MainMenuButtons[MainMenuButton_Quit];

                RL->BeginTextureMode(GameState->Render_MainMenu);
                RL->ClearBackground(WHITE);
                ConfigureButton(&GameState->Render_MainMenu, StartButton, "Start Game", GameState->Fonts[0], 30.0f, BLUE, BLACK, YELLOW,
                                {5.0f, 5.0f}, {2.0f, 2.0f}, {6.0f, 4.0f}, MainMenuButton_Start, MainMenuButton_Size, MousePosition);
                DrawButton(RL, StartButton, 1.0f);

                ConfigureButton(&GameState->Render_MainMenu, QuitButton, "Quit Game", GameState->Fonts[0], 30.0f, BLUE, BLACK, YELLOW,
                                {5.0f, 5.0f}, {2.0f, 2.0f}, {6.0f, 4.0f}, MainMenuButton_Quit, MainMenuButton_Size, MousePosition);
                DrawButton(RL, QuitButton, 1.0f);

                if (StartButton->IsHighlighted || QuitButton->IsHighlighted)
                {
                    if (GameState->Sounds[Sound_TypeWriterClick].ShouldPlay)
                    {
                        RL->RL_PlaySound(GameState->Sounds[Sound_TypeWriterClick].sound);
                        GameState->Sounds[Sound_TypeWriterClick].ShouldPlay = false;
                    }
                }
                else
                {
                    GameState->Sounds[Sound_TypeWriterClick].ShouldPlay = true;
                }
                RL->EndTextureMode();

                RL->BeginDrawing();
                RL->DrawTextureRec(GameState->Render_MainMenu.texture, GameState->Render_MainMenu_Rec, {}, WHITE);
                RL->EndDrawing();

                if (RL->IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
                {
                    if (RecVsPoint(MousePosition, StartButton->ContentBound))
                    {
                        ResetGameState(GameState, GameWindow, RL);
                        GameState->ScreenState = Screen_Game;
                        RL->PlaySoundMulti(GameState->Sounds[Sound_TypeWriterClick].sound);
                    }
                    if (RecVsPoint(MousePosition, QuitButton->ContentBound))
                    {
                        GameMemory->IsRunning = false;
                    }
                }
            } break;
            case Screen_Game:
            {
                if (RL->IsKeyPressed(KEY_P))
                {
                    GameState->IsPaused ^= 1;
                }

                if (!GameState->IsPaused)
                {
                    ++GameState->GameTicks;
                    if (GameState->Ship)
                    {
                        if (RL->IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                        {
                            if (GameState->Ship->Bullets < GameState->Ship->MaxBullets)
                            {
                                RL->RL_PlaySound(GameState->Sounds[Sound_Laser].sound);
                                AddBulletEntity(GameState, GameWindow, GameState->Ship, GameState->Ship->FacingDirection, { 50, 50, 255, 255 });
                            }
                        }
                        GameState->Ship->Acceleration = 0.0f;
                        if (RL->IsKeyDown(KEY_W))
                        {
                            if (!RL->IsSoundPlaying(GameState->Sounds[Sound_UniverseAmbient].sound))
                            {
                                RL->RL_PlaySound(GameState->Sounds[Sound_UniverseAmbient].sound);
                            }
                            GameState->Ship->Acceleration = 600.0f;
                            u32 NumberOfParticles = 10;
                            for (u32 ParticleIndex = 0;
                                ParticleIndex < NumberOfParticles;
                                ++ParticleIndex)
                            {
                                AddParticleEntity(GameState, GameState->Ship->P - GameState->Ship->WrapSize.x * GameState->Ship->FacingDirection, 100.0f, { 50, 50, 255, 100 }, GameState->Ship->RotationJaw + PI);
                            }
                        }
                        else
                        {
                            if (RL->IsSoundPlaying(GameState->Sounds[Sound_UniverseAmbient].sound))
                            {
                                RL->StopSound(GameState->Sounds[Sound_UniverseAmbient].sound);
                            }
                        }
                        Vector2 M = MousePosition - GameState->Ship->P;
                        r32 MRotationJaw = atan2(M.y, M.x);
                        if (MRotationJaw < 0.0f) MRotationJaw += 2.0f * PI;
                        r32 dRotationJaw = abs(MRotationJaw - GameState->Ship->RotationJaw);
                        Vector2 P = GameState->Ship->FacingDirection;
                        if (M.x * P.y < M.y * P.x)
                        {
                            if (GameState->Ship->RotationSpeed > dRotationJaw)
                            {
                                GameState->Ship->RotationJaw += dRotationJaw;
                            }
                            else
                            {
                                GameState->Ship->RotationJaw += GameState->Ship->RotationSpeed;
                            }
                        }
                        else
                        {
                            if (GameState->Ship->RotationSpeed > dRotationJaw)
                            {
                                GameState->Ship->RotationJaw -= dRotationJaw;
                            }
                            else
                            {
                                GameState->Ship->RotationJaw -= GameState->Ship->RotationSpeed;
                            }
                        }
                    }
                    else if (GameState->ShipLifes && RL->IsKeyPressed(KEY_SPACE))
                    {
                        GameState->Ship = AddShipEntity(GameState, GameWindow);
                    }

                    if (GameState->ShipLifes && GameState->RocksSize == 0)
                    {
                        TransitionToNextLevel(GameState, GameWindow);
                    }

                    if (GameState->Ufo)
                    {
                        if (!RL->IsSoundPlaying(GameState->Sounds[Sound_Ufo].sound))
                        {
                            RL->RL_PlaySound(GameState->Sounds[Sound_Ufo].sound);
                        }
                    }
                    else
                    {
                        if (RL->IsSoundPlaying(GameState->Sounds[Sound_Ufo].sound))
                        {
                            RL->StopSound(GameState->Sounds[Sound_Ufo].sound);
                        }
                    }
                }
                else
                {
                    if (RL->IsSoundPlaying(GameState->Sounds[Sound_Ufo].sound))
                    {
                        RL->PauseSound(GameState->Sounds[Sound_Ufo].sound);
                    }
                }

                //
                // NOTE(david): timed event processing
                //
                while (GameState->TimedEventHeapSize && GameState->GameTicks == GameState->TimedEventHeap[0].Target)
                {
                    timed_event Event = PopTimedEvent(GameState);
                    
                    switch (Event.Type)
                    {
                        case TimedEvent_Womp:
                        {
                            if (!GameState->Ufo)
                            {
                                Event.Handler(GameState, GameWindow, RL);
                                r32 t = 1.0f - (((r32)GameState->UfoSpawnTargetGameTick - (r32)GameState->GameTicks) / (GameState->TargetFPS * 20));
                                u32 TargetGameTick = GameState->GameTicks + (u32)((r32)GameState->TargetFPS * 2 + t * (r32)(GameState->TargetFPS / 10 - GameState->TargetFPS * 2));
                                PushTimedEvent(GameState, TargetGameTick, [](game_state *GameState, game_window *GameWindow, raylib_wrapper_code *RL){
                                    RL->RL_PlaySound(GameState->Sounds[Sound_Womp2].sound);
                                }, TimedEvent_Womp2);
                            }
                        } break ;
                        case TimedEvent_Womp2:
                        {
                            if (!GameState->Ufo)
                            {
                                Event.Handler(GameState, GameWindow, RL);
                                r32 t = 1.0f - (((r32)GameState->UfoSpawnTargetGameTick - (r32)GameState->GameTicks) / (GameState->TargetFPS * 20));
                                u32 TargetGameTick = GameState->GameTicks + (u32)((r32)GameState->TargetFPS * 2 + t * (r32)(GameState->TargetFPS / 10 - GameState->TargetFPS * 2));
                                PushTimedEvent(GameState, TargetGameTick, [](game_state *GameState, game_window *GameWindow, raylib_wrapper_code *RL){
                                    RL->RL_PlaySound(GameState->Sounds[Sound_Womp].sound);
                                }, TimedEvent_Womp);
                            }
                        } break ;
                        case TimedEvent_Ufo:
                        {
                            Event.Handler(GameState, GameWindow, RL);
                        } break ;
                        default: ASSERT(false);
                    }
                }
                
                //
                // NOTE(david): Collision
                //
                for (u32 EntityId = 0;
                    EntityId < World->EntitiesSize;
                    ++EntityId)
                {
                    entity *OuterEntity = &World->Entities[EntityId];
                    if (OuterEntity->IsAlive)
                    {
                        for (u32 EntityId2 = EntityId + 1;
                            EntityId2 < World->EntitiesSize;
                            ++EntityId2)
                        {
                            entity *InnerEntity = &World->Entities[EntityId2];
                            if (InnerEntity->IsAlive)
                            {
                                collision_handler* Handler;
                                if ((Handler = DoesCollisionExist(GameState, InnerEntity->Type, OuterEntity->Type)))
                                {
                                    Handler(GameState, GameWindow, RL, InnerEntity, OuterEntity);
                                }
                            }
                        }
                    }
                }

                //
                // NOTE(david): Overlay
                //
                RL->BeginTextureMode(GameState->Render_Overlay);
                if (GameState->IsPaused)
                {
                    RL->ClearBackground({ 120, 120, 120, 100 });
                    if ((GameState->FrameCounter & 127) < 63)
                    {
                        PutText(GameState, RL, "Paused", { (r32)GameWindow->Width / 2.0f, (r32)GameWindow->Height / 2.0f }, 100.0f, RED);
                    }
                }
                else
                {
                    RL->ClearBackground(BLANK);
                }
                r32 LifeTextureXOffset = GameState->Textures[Texture_ShipBlue].t.width / 2.0f - GameState->Textures[Texture_ShipBlue].Offset.x;
                r32 LifeTextureYOffset = GameState->Textures[Texture_ShipBlue].t.height / 2.0f - GameState->Textures[Texture_ShipBlue].Offset.y;
                for (u32 LifeIndex = 0;
                    LifeIndex < GameState->ShipLifes;
                    ++LifeIndex)
                {
                    RL->DrawTextureRotated(GameState->Textures[Texture_ShipBlue].t, { LifeTextureXOffset, LifeTextureYOffset },
                        { LifeTextureXOffset + GameState->Textures[Texture_ShipBlue].Offset.x,
                        LifeTextureYOffset + GameState->Textures[Texture_ShipBlue].Offset.y }, -PI / 2.0f, WHITE);
                    LifeTextureXOffset += (r32)GameState->Textures[Texture_ShipBlue].t.width / 2.0f;
                }
                PutText(GameState, RL, to_string(GameState->PlayScore).c_str(), { (r32)GameWindow->Width / 2.0f, 15.0f }, 30.0f, WHITE);
                RL->EndTextureMode();

                RL->BeginTextureMode(GameState->Render_World);
                RL->ClearBackground(BLACK);
                //
                // NOTE(david): Update & Render
                //
                for (u32 EntityId = 0;
                    EntityId < World->EntitiesSize;
                    ++EntityId)
                {
                    entity *Entity = &World->Entities[EntityId];
                    if (Entity->IsAlive)
                    {
                        if (GameState->ShipLifes && !GameState->IsPaused)
                        {
                            switch (Entity->Type)
                            {
                                case EntityType_Bullet:
                                {
                                } break ;
                                case EntityType_RockBig: case EntityType_RockMedium: case EntityType_RockSmall:
                                {
                                    Entity->RotationJaw += Entity->RotationSpeed;
                                } break ;
                                case EntityType_Ship:
                                {
                                } break ;
                                case EntityType_Particle:
                                {
                                } break ;
                                case EntityType_Ufo:
                                {
                                    if (GameState->Ship && Entity->Bullets < Entity->MaxBullets && (GameState->FrameCounter & (32 - 1)) == 0)
                                    {
                                        Vector2 BulletDirection = GameState->Ship->P - Entity->P;
                                        BulletDirection = VectorRotate(BulletDirection, {}, GetRand(-0.7f, 0.7f));
                                        AddBulletEntity(GameState, GameWindow, Entity, VectorNormalize(BulletDirection), RED);
                                    }
                                } break ;
                                default: ASSERT(false);
                            }
                            if (Entity->IsAlive)
                            {
                                if (Entity->ChangesTint)
                                {
                                    Entity->Tint = ColorClamp(Entity->Tint - Entity->TintChange, 0, 255);
                                }
                                if (Entity->ChangesScale)
                                {
                                    Entity->Scale *= Entity->ScaleChangeRatio;
                                }
                                MoveEntity(GameState, Entity, GameWindow, dt);
                            }
                        }
                        if (Entity->IsAlive)
                        {
                            RL->DrawTextureRotatedScaled(Entity->texture,
                                { Entity->P.x - (r32)Entity->texture.width / 2.0f,
                                Entity->P.y - (r32)Entity->texture.height / 2.0f },
                                Entity->P, Entity->RotationJaw, Entity->Scale, Entity->Tint);
                        }
                    }
                }
                RL->EndTextureMode();

                RL->BeginDrawing();
                RL->DrawTextureRec(GameState->Render_World.texture, GameState->Render_World_Rec, {}, WHITE);
                RL->DrawTextureRec(GameState->Render_Overlay.texture, GameState->Render_Overlay_Rec, {}, WHITE);

                RL->EndDrawing();

                if (GameState->ShipLifes == 0)
                {
                    GameState->ScreenState = Screen_GameOver;
                }
            } break;
            case Screen_GameOver:
            {
                RL->BeginTextureMode(GameState->Render_GameOver);
                RL->ClearBackground({ 200, 200, 200, 200 });
                if (GameState->BeatPreviousScore)
                {
                    if (GameState->Sounds[Sound_Fanfare].ShouldPlay)
                    {
                        RL->RL_PlaySound(GameState->Sounds[Sound_Fanfare].sound);
                        GameState->Sounds[Sound_Fanfare].ShouldPlay = false;
                    }
                    PutText(GameState, RL, "Good job, you beat your previous high score!!", { (r32)GameWindow->Width / 2.0f, 200.0f }, 40.0f, YELLOW);
                }
                PutText(GameState, RL, "Game Over", { (r32)GameWindow->Width / 2.0f, (r32)GameWindow->Height / 2.0f }, 100.0f, BLACK);
                PutText(GameState, RL, ("High score: " + to_string(GameState->HighestPlayScore)).c_str(), { (r32)GameWindow->Width / 2.0f, (r32)GameWindow->Height / 2.0f + 100.0f }, 50.0f, BLACK);
                PutText(GameState, RL, "Press R to play again", { (r32)GameWindow->Width / 2.0f, (r32)GameWindow->Height / 2.0f + 250.0f }, 30.0f, { 200, 0, 0, 255 });
                RL->EndTextureMode();

                RL->BeginDrawing();

                RL->DrawTextureRec(GameState->Render_World.texture, GameState->Render_World_Rec, {}, WHITE);
                RL->DrawTextureRec(GameState->Render_Overlay.texture, GameState->Render_Overlay_Rec, {}, WHITE);
                RL->DrawTextureRec(GameState->Render_GameOver.texture, GameState->Render_GameOver_Rec, {}, WHITE);

                RL->EndDrawing();

                if (RL->IsKeyPressed(KEY_R))
                {
                    GameState->ScreenState = Screen_Game;
                    ResetGameState(GameState, GameWindow, RL);
                }
            } break ;
            default: ASSERT(false);
        }

        ++GameState->FrameCounter;

        //
        // NOTE(david): main timed events processing
        //
        while (GameState->TimedEventHeapSize && GameState->FrameCounter == GameState->TimedEventHeap[0].Target)
        {
            timed_event Event = PopTimedEvent(GameState);

            switch (Event.Type)
            {
                case TimedEvent_SplashScreenSound:
                {
                    GameState->CustomData = Event.CustomData;
                    Event.Handler(GameState, GameWindow, RL);
                } break ;
                case TimedEvent_SplashToMain:
                {
                    Event.Handler(GameState, GameWindow, RL);
                } break ;
                default: ASSERT(false);
            }
        }

        if (RL->WindowShouldClose())
        {
            GameMemory->IsRunning = false;

        }
    }
#if defined(SINGLE_FILE_BUILD)
# else
}
#endif
