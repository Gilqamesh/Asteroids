#include "src/raylib.h"
#include <cassert>
#include <cmath>
#include <iostream>

using namespace std;

#define ArrayCount(x) (sizeof(x)/sizeof((x)[0]))
#define LOG(x) (cout << x << endl)
#define LINE() LOG(__LINE__)

inline Vector2
operator+(Vector2 V, Vector2 W)
{
    Vector2 Result = V;

    Result.x += W.x;
    Result.y += W.y;

    return (Result);
}

inline Vector2
operator-(Vector2 V, Vector2 W)
{
    Vector2 Result = V;

    Result.x -= W.x;
    Result.y -= W.y;

    return (Result);
}

inline Vector2
operator-(Vector2 V)
{
    V.x *= -1.0f;
    V.y *= -1.0f;

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
operator/(Vector2 V, float X)
{
    V.x /= X;
    V.y /= X;

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
VecNormal(Vector2 V)
{
    float Tmp = V.x;
    V.x = -V.y;
    V.y = Tmp;

    return (V);
}

inline float
Inner(Vector2 V, Vector2 W)
{
    float Result;

    Result = V.x * W.x + V.y * W.y;

    return (Result);
}

inline float
VectorLen(Vector2 Vec)
{
    return (sqrt(Inner(Vec, Vec)));
}

inline Vector2
VectorNormalize(Vector2 Vec)
{
    Vector2 Result = Vec;

    float Len = VectorLen(Result);
    Result.x /= Len;
    Result.y /= Len;

    return (Result);
}

// mid point of polygon A can't be "close" to mid point of polygon B, which should never happen?
bool
PolyVsPoly(Vector2 *PointsA, int PointCountA, Vector2 *PointsB, int PointCountB, Vector2 *MinimumTranslationVectorA = 0)
{
    float MinOverlap;
    Vector2 MinOverlapDirectionA = {};
    int NumberOfNormals = PointCountA + PointCountB;
    for (int NormalIndex = 0;
         NormalIndex < NumberOfNormals;
         ++NormalIndex)
    {
        Vector2 Normal;
        Vector2 Direction;
        if (NormalIndex < PointCountA - 1)
        {
            Direction = VectorNormalize(PointsA[NormalIndex + 1] - PointsA[NormalIndex]);
            Normal = VecNormal(Direction);
            // DrawLineV(Normal + PointsA[NormalIndex], PointsA[NormalIndex], BLUE);
        }
        else if (NormalIndex == PointCountA - 1)
        {
            Direction = VectorNormalize(PointsA[0] - PointsA[NormalIndex]);
            Normal = VecNormal(Direction);
            // DrawLineV(Normal + PointsA[NormalIndex], PointsA[NormalIndex], BLUE);
        }
        else if (NormalIndex - PointCountA < PointCountB - 1)
        {
            Direction = VectorNormalize(PointsB[NormalIndex - PointCountA + 1] - PointsB[NormalIndex - PointCountA]);
            Normal = VecNormal(Direction);
            // DrawLineV(Normal + PointsB[NormalIndex - PointCountA], PointsB[NormalIndex - PointCountA], BLUE);
        }
        else if (NormalIndex - PointCountA == PointCountB - 1)
        {
            Direction = VectorNormalize(PointsB[0] - PointsB[NormalIndex - PointCountA]);
            Normal = VecNormal(Direction);
            // DrawLineV(Normal + PointsB[NormalIndex - PointCountA], PointsB[NormalIndex - PointCountA], BLUE);
        }
        else
        {
            assert(false);
        }

        // get min and max projections from A onto the normal
        float MinProjectionA = Inner(PointsA[0], Normal);
        float MaxProjectionA = MinProjectionA;
        for (int i = 1;
             i < PointCountA;
             ++i)
        {
            float CurrentProj = Inner(PointsA[i], Normal);
            if (CurrentProj < MinProjectionA) MinProjectionA = CurrentProj;
            if (CurrentProj > MaxProjectionA) MaxProjectionA = CurrentProj;
        }

        // get min and max projections from B onto the normal
        float MinProjectionB = Inner(PointsB[0], Normal);
        float MaxProjectionB = MinProjectionB;
        for (int i = 1;
             i < PointCountB;
             ++i)
        {
            float CurrentProj = Inner(PointsB[i], Normal);
            if (CurrentProj < MinProjectionB) MinProjectionB = CurrentProj;
            if (CurrentProj > MaxProjectionB) MaxProjectionB = CurrentProj;
        }

        // if there is a gap in between the intervals, then the two polygons are not overlapped
        if (!((MinProjectionA < MaxProjectionB && MinProjectionA > MinProjectionB) ||
             (MinProjectionB < MaxProjectionA && MinProjectionB > MinProjectionA)))
        {
            return (false);
        }
        if (MinimumTranslationVectorA)
        {
            float Overlap = min(abs(MaxProjectionA - MinProjectionB), abs(MaxProjectionB - MinProjectionA));

            // update minimum overlap for mtv
            if (NormalIndex == 0)
            {
                MinOverlap = Overlap;
                MinOverlapDirectionA = Normal;
            }
            else if (Overlap < MinOverlap)
            {
                MinOverlap = Overlap;
                MinOverlapDirectionA = Normal;
            }
        }
    }

    if (MinimumTranslationVectorA)
    {
        Vector2 MidPointA = {};
        Vector2 MidPointB = {};
        for (int i = 0;
            i < PointCountA;
            ++i)
        {
            MidPointA = MidPointA + PointsA[i];
        }
        MidPointA = MidPointA / (float)PointCountA;
        for (int i = 0;
            i < PointCountB;
            ++i)
        {
            MidPointB = MidPointB + PointsB[i];
        }
        MidPointB = MidPointB / (float)PointCountB;
        Vector2 AB = MidPointB - MidPointA;

        MinOverlapDirectionA = MinOverlapDirectionA * MinOverlap;
        float OverlapDir = Inner(MinOverlapDirectionA, AB);
        if (OverlapDir > 0.0f)
        {
            MinOverlapDirectionA = -MinOverlapDirectionA;
        }
        *MinimumTranslationVectorA = MinOverlapDirectionA;
    }
    // there was an intersection in all intervals
    return (true);
}

bool
PolyVsCircle(Vector2 *Points, int PointCount, Vector2 Origin, float Radius)
{
    for (int PointIndex = 0;
         PointIndex < PointCount;
         ++PointIndex)
    {
        if (Inner(Points[PointIndex] - Origin, Points[PointIndex] - Origin) < Radius * Radius)
        {
            return (true);
        }
    }

    return (false);
}

struct polygon
{
    Vector2 Points[16];
    int Size;
};

polygon
ExtendPolygon(polygon Original, Vector2 Direction)
{
    polygon Result = {};

    polygon Extended = {};
    for (int i = 0;
         i < Original.Size;
         ++i)
    {
        Extended.Points[i] = Original.Points[i] + Direction;
    }

    Vector2 Normal = VecNormal(Direction);

    int MinIndex = 0;
    int MaxIndex = 0;
    float Min = Inner(Original.Points[0], Normal);
    float Max = Min;
    for (int i = 1;
         i < Original.Size;
         ++i)
    {
        float Proj = Inner(Original.Points[i], Normal);
        if (Proj < Min)
        {
            Min = Proj;
            MinIndex = i;
        }
        if (Proj > Max)
        {
            Max = Proj;
            MaxIndex = i;
        }
    }
    int MinIndexCpy = MinIndex;
    int MaxIndexCpy = MaxIndex;
    // NOTE(david): for drawing purposes this needs to be correct, for SAT purposes only checking for the normals this works either way
    int Add = (MinIndexCpy < MaxIndexCpy ? -1 : 1);
    while (MinIndexCpy != MaxIndexCpy)
    {
        Result.Points[Result.Size++] = Original.Points[MinIndexCpy];
        MinIndexCpy += Add;
        if (MinIndexCpy == Original.Size) MinIndexCpy = 0;
        if (MinIndexCpy < 0) MinIndexCpy = Original.Size - 1;
    }
    Result.Points[Result.Size++] = Original.Points[MinIndexCpy];
    MinIndexCpy = MinIndex;
    MaxIndexCpy = MaxIndex;
    while (MaxIndexCpy != MinIndexCpy)
    {
        Result.Points[Result.Size++] = Extended.Points[MaxIndexCpy];
        MaxIndexCpy += Add;
        if (MaxIndexCpy == Original.Size) MaxIndexCpy = 0;
        if (MaxIndexCpy < 0) MaxIndexCpy = Original.Size - 1;
    }
    Result.Points[Result.Size++] = Extended.Points[MaxIndexCpy];

    return (Result);
}

// polygon
// ExtendPolygon(polygon Original, Vector2 Direction)
// {
//     polygon Result = {};

//     Result.Size = Original.Size * 2;
//     for (int i = 0;
//          i < Original.Size * 2;
//          ++i)
//     {
//         if (i < Original.Size)
//         {
//             Result.Points[i] = Original.Points[i];
//         }
//         else
//         {
//             Result.Points[i] = Original.Points[i - Original.Size] + Direction;
//         }
//     }

//     return (Result);
// }

int main()
{
    InitWindow(1280, 720, "SAT");

    SetTargetFPS(60);

    polygon PolyA = {{
        { -20.0f, -10.0f },
        { 120.0f, 30.0f },
        { 100.0f, 150.0f },
        { 50.0f, 130.0f },
        { 10.0f, 60.0f },
        { -20.0f, -10.0f }
    }, 6};
    Vector2 PolyAOffset = { 1280.0f / 2.0f - 70.0f, 720.0f / 2.0f - 100.0f };
    float PolyAScale = 3.0f;
    for (int i = 0;
         i < PolyA.Size;
         ++i)
    {
        PolyA.Points[i] = PolyA.Points[i] * PolyAScale + PolyAOffset;
    }

    Vector2 PolyBOriginal[5] = {
        { 0.0f, 0.0f },
        { 120.0f, 50.0f },
        { 80.0f, 140.0f },
        { 20.0f, 50.0f },
        { 0.0f, 0.0f }
    };

    float PolyBScale = 0.1f;
    for (int i = 0;
         i < ArrayCount(PolyBOriginal);
         ++i)
    {
        PolyBOriginal[i] = PolyBOriginal[i] * PolyBScale;
    }

    Vector2 CircleP = { 600.0f, 600.0f };
    float CircleRadius = 100.0f;

    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(BLACK);

        Color PolyColor = WHITE;

        Vector2 MouseP = GetMousePosition();
        polygon PolyB;
        PolyB.Size = ArrayCount(PolyBOriginal) - 1;
        for (int i = 0;
             i < PolyB.Size;
             ++i)
        {
            PolyB.Points[i] = PolyBOriginal[i] + MouseP;
        }
        polygon ExtendedPolyB = ExtendPolygon(PolyB, { 50.0f, 20.0f });
        ExtendedPolyB.Points[ExtendedPolyB.Size] = ExtendedPolyB.Points[0];
        //
        // NOTE(david): Poly vs Poly check
        //
        Vector2 MinimumTranslationVectorA = {};
        if (PolyVsPoly( ExtendedPolyB.Points, ExtendedPolyB.Size, PolyA.Points, PolyA.Size - 1, &MinimumTranslationVectorA))
        {
            PolyColor = YELLOW;
        }
        DrawLineStrip(PolyA.Points, PolyA.Size, PolyColor);

        DrawLineV(MinimumTranslationVectorA + MouseP, MouseP, RED);

        //
        // NOTE(david): Poly vs Circle check
        //
        // if (PolyVsCircle(PolyB.Points, PolyB.Size - 1, CircleP, CircleRadius))
        // {
        //     PolyColor = YELLOW;
        // }
        // DrawCircleLines(CircleP.x, CircleP.y, CircleRadius, PolyColor);
        // DrawCircleV(CircleP, 2.0f, PolyColor);

        for (int i = 0;
             i <= ExtendedPolyB.Size;
             ++i)
        {
            ExtendedPolyB.Points[i] = ExtendedPolyB.Points[i] + MinimumTranslationVectorA;
        }
        DrawLineStrip(ExtendedPolyB.Points, ExtendedPolyB.Size + 1, PolyColor);
        // DrawLineStrip(PolyB.Points, PolyB.Size, PolyColor);

        EndDrawing();
    }
}
