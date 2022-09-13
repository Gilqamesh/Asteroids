#include "src/raylib.h"
#include <iostream>

using namespace std;

#define LOG(x) (cout << x << endl)

inline Vector2
operator+(Vector2 V, Vector2 W)
{
    V.x += W.x;
    V.y += W.y;

    return (V);
}

inline Vector2
operator*(float X, Vector2 V)
{
    V.x *= X;
    V.y *= X;

    return (V);
}

inline Vector2
operator*(Vector2 V, float X)
{
    V.x *= X;
    V.y *= X;

    return (V);
}

inline Vector2
operator-(Vector2 V, Vector2 W)
{
    V.x -= W.x;
    V.y -= W.y;

    return (V);
}

inline Vector2
operator-(Vector2 V)
{
    V.x *= -1.0f;
    V.y *= -1.0f;

    return (V);
}

int main()
{
    InitWindow(1280, 1000, "Moving objects");

    SetTargetFPS(60);

    Vector2 DynamicCircleO1 = { 100.0f, 300.0f };
    Vector2 VelocityCircle1 = { 40.0f, 30.0f };
    float RadiusCircle1 = 60.0f;

    Vector2 DynamicCircleO2 = { 1000.0f, 800.0f };
    Vector2 VelocityCircle2 = { -30.0f, -4.0f };
    float RadiusCircle2 = 75.0f;

    float TimeTillCollision = 0.0f;

    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(BLACK);

        float dt = GetFrameTime();
        TimeTillCollision += dt;
        // DynamicCircleO1 = DynamicCircleO1 + VelocityCircle1 * dt;
        // DynamicCircleO2 = DynamicCircleO2 + VelocityCircle2 * dt;
        // fixing circle2 and moving the first circle with (v - w) velocity each frame
        DynamicCircleO1 = DynamicCircleO1 + (VelocityCircle1 - VelocityCircle2) * dt;

        DrawCircleV(DynamicCircleO1, RadiusCircle1, WHITE);
        DrawCircleV(DynamicCircleO2, RadiusCircle2, YELLOW);
    
        EndDrawing();

        if (CheckCollisionCircles(DynamicCircleO1, RadiusCircle1, DynamicCircleO2, RadiusCircle2))
        {
            break ;
        }
    }

    LOG("Time until collision: " << TimeTillCollision << "s");

    CloseWindow();
}
