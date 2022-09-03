#include "platform.hpp"
#include "GameLayer.hpp"
#include "types.hpp"
#include "misc.hpp"
#include <cmath>
#include "entity.cpp"
#include "world.cpp"

game_memory *DebugGlobalMemory;

extern "C"
{

    void SetupWindows(game_memory *GameMemory, game_window *GameWindow)
    {
        game_state *GameState = (game_state *)GameMemory->PermanentStorage;
        raylib_wrapper_code *RL = &GameMemory->RaylibWrapper;
        GameWindow->Width = 960;
        GameWindow->Height = 540;
        GameWindow->Shown = true;
        RL->InitWindow(GameWindow->Width, GameWindow->Height, "Asteroids");
        RL->SetWindowPosition(0, 30);

        GameState->TargetFPS = 60;
        RL->SetTargetFPS(GameState->TargetFPS);

        RL->SetRandomSeed(42);
    }

    void LoadResources(game_memory *GameMemory, game_window *GameWindow)
    {
        // TODO(david): Draw something for loading
        // RL_DrawText("Loading textures...", 500, 500, 20, YELLOW);
        game_state *GameState = (game_state *)GameMemory->PermanentStorage;
        raylib_wrapper_code *RL = &GameMemory->RaylibWrapper;
        GameState->Fonts[GameState->FontsLoaded++] = RL->LoadFont("fonts/alagard.png");
        GameState->Fonts[GameState->FontsLoaded++] = RL->LoadFont("fonts/alpha_beta.png");
        GameState->Fonts[GameState->FontsLoaded++] = RL->LoadFont("fonts/jupiter_crash.png");
        GameState->Fonts[GameState->FontsLoaded++] = RL->LoadFont("fonts/mecha.png");
        GameState->Fonts[GameState->FontsLoaded++] = RL->LoadFont("fonts/pixantiqua.png");
        GameState->Fonts[GameState->FontsLoaded++] = RL->LoadFont("fonts/pixelplay.png");
        GameState->Fonts[GameState->FontsLoaded++] = RL->LoadFont("fonts/romulus.png");
        GameState->Fonts[GameState->FontsLoaded++] = RL->LoadFont("fonts/setback.png");

        GameState->Textures[Texture_Bunnies].t = RL->LoadTexture("textures/textures_bunnymark.png");
        GameState->Textures[Texture_Bunnies].IsLoaded = true;

        GameState->Render_World = RL->LoadRenderTexture(2 * GameWindow->Width / 3.0, GameWindow->Height);
        GameState->Render_World_Rec = {0.0f, 0.0f, (r32)GameState->Render_World.texture.width, -(r32)GameState->Render_World.texture.height};
        GameState->Render_Overlay = RL->LoadRenderTexture(2 * GameWindow->Width / 3, GameWindow->Height);
        GameState->Render_Overlay_Rec = {0.0f, 0.0f, (r32)GameState->Render_Overlay.texture.width, -(r32)GameState->Render_Overlay.texture.height};
        GameState->Render_UI = RL->LoadRenderTexture(GameWindow->Width / 3, GameWindow->Height);
        GameState->Render_UI_Rec = {0.0f, 0.0f, (r32)GameState->Render_UI.texture.width, -(r32)GameState->Render_UI.texture.height};
    }

    void UpdateAndRender(game_memory *GameMemory, game_window *GameWindow)
    {
        DebugGlobalMemory = GameMemory;
        game_state *GameState = (game_state *)GameMemory->PermanentStorage;
        if (GameMemory->IsMemoryInitialized == false)
        {
            InitializeArena(&GameState->WorldArena, GameMemory->PermanentStorageSize - sizeof(game_state),
                            (u8 *)GameMemory->PermanentStorage + sizeof(game_state));
            GameState->World = PushStruct(&GameState->WorldArena, world);
            GameMemory->IsMemoryInitialized = true;

            // set up camera
            GameState->Camera.zoom = 1.0f;
        }
        world *World = GameState->World;
        raylib_wrapper_code *RL = &GameMemory->RaylibWrapper;

        r32 dt = RL->GetFrameTime();
        
        if (IsKeyPressed(KEY_L) && GameState->LoadingState == LoadingState_Waiting)
        {
            GameState->LoadingState = LoadingState_Loading;
            GameState->LoadingBar = 0;
            GameState->LoadingBarMax = 2000 * 2000 + 2;
            GameState->LoadingThread = thread([](game_state *TGameState,
                                                 raylib_wrapper_code *TRL){
                world *World = TGameState->World;
                if (TGameState->Textures[Texture_Running_Hero].IsLoaded == false)
                {
                    TGameState->Textures[Texture_Running_Hero].t = TRL->LoadTexture("textures/textures_sprite_anim.png");
                    TGameState->Textures[Texture_Running_Hero].IsLoaded = true;
                }
                ++TGameState->LoadingBar;
                if (TGameState->Textures[Texture_Reserved_0].IsLoaded == false)
                {
                    TGameState->Textures[Texture_Reserved_0].t = TRL->LoadTexture("textures/textures_blend_modes.png");
                    TGameState->Textures[Texture_Reserved_0].IsLoaded = true;
                }
                ++TGameState->LoadingBar;
                // generate world
                for (i32 x = -1000;
                     x < 1000;
                     ++x)
                {
                    for (i32 y = -1000;
                         y < 1000;
                         ++y)
                    {
                        if (TRL->GetRandomValue(1, 500) == 500)
                        {
                            Rectangle ChunkBound = {(r32)x * 10.0f, (r32)y * 10.0f, 20.0f, 20.0f};
                            AddEntity(World, ChunkBound, EntityType_Wall);
                            LOG("World->EntitiesSize: " << World->EntitiesSize);
                        }
                    }
                    TGameState->LoadingBar += 2000;
                }
                TGameState->LoadingState = LoadingState_Finished;
            }, GameState, RL);
        }
        if (GameState->LoadingState == LoadingState_Loading)
        {
            RL->BeginDrawing();
            RL->ClearBackground(WHITE);
            i32 LoadingBarW = 300;
            i32 LoadingBarH = 100;
            i32 LoadingBarX = GameState->Render_World.depth.width / 2 - LoadingBarW / 2;
            i32 LoadingBarY = GameState->Render_World.depth.height / 2 - LoadingBarH / 2;
            RL->RL_DrawText("Loading the game...", LoadingBarX,
                            GameState->Render_World.depth.height / 2 - LoadingBarH - 10, 20, RED);
            RL->DrawRectangle(LoadingBarX, LoadingBarY, LoadingBarW, LoadingBarH, GRAY);
            r32 P = (r32)LoadingBarX;
            r32 Q = (r32)LoadingBarX + (r32)LoadingBarW;
            r32 t = ((r32)GameState->LoadingBar / (r32)GameState->LoadingBarMax);
            RL->DrawRectangle(LoadingBarX, LoadingBarY, (i32)(t * (Q - P)),
                              LoadingBarH, RED);
            RL->RL_DrawText(to_string((i32)(t * 100)) + "%", 200, 100, 30, RED);

            RL->EndDrawing();
        }
        else
        {
            if (GameState->LoadingState == LoadingState_Finished)
            {
                GameState->LoadingThread.join();
                GameState->LoadingState = LoadingState_Waiting;
            }
            RL->BeginTextureMode(GameState->Render_World);
            RL->ClearBackground(SKYBLUE);
            RL->RL_DrawText(string("World Screen"), 20, 20, 20, BLACK);
            RL->EndTextureMode();

            RL->BeginTextureMode(GameState->Render_UI);
            RL->ClearBackground(BLACK);
            RL->RL_DrawText(string("UI Screen"), 5, 5, 20, RED);
            RL->EndTextureMode();

            RL->BeginTextureMode(GameState->Render_Overlay);
            RL->ClearBackground({0, 0, 0, 0});
            RL->DrawRectangleLinesEx({0.0f, 0.0f, (r32)GameState->Render_Overlay.depth.width,
                                      (r32)GameState->Render_Overlay.depth.height},
                                     10.0f, BROWN);
            RL->EndTextureMode();

            RL->BeginDrawing();
            RL->ClearBackground(GREEN);
            RL->DrawTextureRec(GameState->Render_World.texture, GameState->Render_World_Rec, {0.0f, 0.0f}, WHITE);
            RL->DrawTextureRec(GameState->Render_Overlay.texture, GameState->Render_Overlay_Rec, {0.0f, 0.0f}, WHITE);
            RL->DrawTextureRec(GameState->Render_UI.texture, GameState->Render_UI_Rec,
                               {2.0f * GameWindow->Width / 3.0f, 0.0f}, WHITE);

            if (!GameState->CameraFollowingEntity && IsKeyPressed(KEY_R))
            {
                entity *Entity = AddEntity(World, { -10.0f, -10.0f, 20.0f, 20.0f }, EntityType_Hero);
                GameState->CameraFollowingEntity = Entity;
            }

            GameState->Camera.offset = {(r32)GameState->Render_World_Rec.width / 2.0f, -(r32)GameState->Render_World_Rec.height / 2.0f};
            GameState->Camera.target = (GameState->CameraFollowingEntity ? GameState->CameraFollowingEntity->P : Vector2{0.0f, 0.0f});
            RL->BeginMode2D(GameState->Camera);

            if (GameState->CameraFollowingEntity)
            {
                entity *Hero = GameState->CameraFollowingEntity;
                Hero->ddP = {};
                if (RL->IsKeyDown(KEY_W))
                {
                    Hero->ddP.y = -50.0f;
                }
                if (RL->IsKeyDown(KEY_S))
                {
                    Hero->ddP.y = 50.0f;
                }
                if (RL->IsKeyDown(KEY_A))
                {
                    Hero->ddP.x = -50.0f;
                }
                if (RL->IsKeyDown(KEY_D))
                {
                    Hero->ddP.x = 50.0f;
                }
                Hero->dP.x += dt * Hero->ddP.x;
                Hero->dP.y += dt * Hero->ddP.y;

                r32 DisplacementX = dt * Hero->dP.x + dt * dt * Hero->ddP.x / 2.0f;
                r32 DisplacementY = dt * Hero->dP.y + dt * dt * Hero->ddP.y / 2.0f;
                Hero->P.x += DisplacementX;
                Hero->P.y += DisplacementY;

                Hero->Bound.x += DisplacementX;
                Hero->Bound.y += DisplacementY;
            }

            if (GameState->CameraFollowingEntity)
            {
                entity *Hero = GameState->CameraFollowingEntity;

                RL->DrawRectangleRec(Hero->Bound, RED);
                Vector2 NextP = Hero->P;
                NextP.x += 1000.0f * dt * Hero->dP.x;
                NextP.y += 1000.0f * dt * Hero->dP.y;
                RL->DrawLineV(Hero->P, NextP, BLACK);
            }

            for (u32 EntityIndex = 0;
                 EntityIndex < World->EntitiesSize;
                 ++EntityIndex)
            {
                entity *Entity = &World->Entities[EntityIndex];
                if (Entity->Type == EntityType_Wall)
                {
                    RL->DrawRectangleRec(Entity->Bound, BLACK);
                }
            }

            RL->EndMode2D();

            if (GameState->CameraFollowingEntity)
            {
                RL->RL_DrawText("Hero Position: \n"
                    + to_string((i32)GameState->CameraFollowingEntity->P.x) + "\n"
                    + to_string((i32)GameState->CameraFollowingEntity->P.y), 15, 40, 20, BLACK);
            }

            RL->EndDrawing();
        }

        if (RL->WindowShouldClose())
        {
            GameMemory->IsRunning = false;
        }
    }
}
