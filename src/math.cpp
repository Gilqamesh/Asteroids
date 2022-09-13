#if defined(G_DEBUG)

ostream &operator<<(ostream &os, Vector2 vec)
{
    os << vec.x << " " << vec.y;

    return (os);
}

ostream &operator<<(ostream &os, Rec rec)
{
    os << rec.x << " " << rec.y << " " << rec.width << " " << rec.height;

    return (os);
}

#endif

internal inline Color
operator-(Color C1, Color C2)
{
    C1.r -= C2.r;
    C1.g -= C2.g;
    C1.b -= C2.b;
    C1.a -= C2.a;

    return (C1);
}

internal inline Color
operator+(Color C1, Color C2)
{
    C1.r += C2.r;
    C1.g += C2.g;
    C1.b += C2.b;
    C1.a += C2.a;

    return (C1);
}

internal inline Vector2
operator+(Vector2 V, Vector2 W)
{
    V.x += W.x;
    V.y += W.y;

    return (V);
}

internal inline Vector2
operator-(Vector2 V, Vector2 W)
{
    V.x -= W.x;
    V.y -= W.y;

    return (V);
}

internal inline Vector2
operator-(Vector2 V)
{
    V.x *= -1.0f;
    V.y *= -1.0f;

    return (V);
}

internal inline Vector2
operator*(r32 X, Vector2 V)
{
    V.x *= X;
    V.y *= X;

    return (V);
}

internal inline Vector2
operator/(Vector2 V, r32 X)
{
    V.x /= X;
    V.y /= X;

    return (V);
}

internal inline Vector2 &
operator *= (r32 X, Vector2 &V)
{
    V.x *= X;
    V.y *= X;

    return (V);
}

internal inline Vector2 &
operator *= (Vector2 &V, r32 X)
{
    V.x *= X;
    V.y *= X;

    return (V);
}

internal inline Vector2 &
operator += (Vector2 &V, Vector2 W)
{
    V.x += W.x;
    V.y += W.y;

    return (V);
}

internal inline Vector2 &
operator -= (Vector2 &V, Vector2 W)
{
    V.x -= W.x;
    V.y -= W.y;

    return (V);
}

internal inline Vector2
operator*(Vector2 V, r32 X)
{
    return (X * V);
}

internal inline Vector2
VectorNull(void)
{
    return {0.0f, 0.0f};
}

internal inline b32
VectorIsNull(Vector2 Vec)
{
    return (Vec.x == 0.0f && Vec.y == 0.0f);
}

internal inline r32
GetRand(r32 low, r32 high)
{
    static random_device dev;
    static mt19937 rng(dev());
    uniform_real_distribution<r32> dist(low, high);
    return (dist(rng));
}

internal inline i32
GetRand(i32 low, i32 high)
{
    static random_device dev;
    static mt19937 rng(dev());
    uniform_int_distribution<i32> dist(low, high);
    return (dist(rng));
}

internal inline r32
Inner(Vector2 V, Vector2 W)
{
    return (V.x * W.x + V.y * W.y);
}

internal inline r32
Square(r32 X)
{
    return (X * X);
}

internal inline Vector2
VectorRotate(Vector2 Vec, Vector2 Origin, r32 Rotation)
{
    // Translate it by origin
    Vec = Vec - Origin;

    // Rotate it
    r32 X = Vec.x;
    Vec.x = X * cos(Rotation) - Vec.y * sin(Rotation);
    Vec.y = X * sin(Rotation) + Vec.y * cos(Rotation);

    // Translate it back by origin
    Vec = Vec + Origin;

    return (Vec);
}

internal inline r32
VectorLen(Vector2 Vec)
{
    return (sqrt(Inner(Vec, Vec)));
}

internal inline Vector2
VectorNormalize(Vector2 Vec)
{
    Vector2 Result = Vec;

    r32 Len = VectorLen(Result);
    Result.x /= Len;
    Result.y /= Len;

    return (Result);
}

internal inline Vector2
VectorHadamard(Vector2 V, Vector2 W)
{
    V.x *= W.x;
    V.y *= W.y;

    return (V);
}

internal inline Vector2
VectorClamp(Vector2 Vec, r32 Min, r32 Max)
{
    if (Vec.x < Min) Vec.x = Min;
    if (Vec.y < Min) Vec.y = Min;
    if (Vec.x > Max) Vec.x = Max;
    if (Vec.y > Max) Vec.y = Max;

    return (Vec);
}

internal inline Vector2
VectorNormal(Vector2 Vec)
{
    r32 Tmp = Vec.x;
    Vec.x = -Vec.y;
    Vec.y = Tmp;

    return (Vec);
}

internal inline Color
ColorClamp(Color color, u32 Min, u32 Max)
{
    if (color.r < Min) color.r = Min;
    if (color.g < Min) color.g = Min;
    if (color.b < Min) color.b = Min;
    if (color.a < Min) color.a = Min;
    if (color.r > Max) color.r = Max;
    if (color.g > Max) color.g = Max;
    if (color.b > Max) color.b = Max;
    if (color.a > Max) color.a = Max;

    return (color);
}

internal inline r32
Clamp(r32 X, r32 Min, r32 Max)
{
    if (X < Min) X = Min;
    if (X > Max) X = Max;

    return (X);
}

internal inline b32
RecVsPoint(Vector2 Point, Rec Rec)
{
    return (Point.x >= Rec.x && Point.x <= Rec.x + Rec.width && Point.y >= Rec.y && Point.y <= Rec.y + Rec.height);
}

internal inline b32
RecVsPoint(Vector2 Point, r32 RecX, r32 RecY, r32 RecW, r32 RecH)
{
    return (Point.x >= RecX && Point.x <= RecX + RecW && Point.y >= RecY && Point.y <= RecY + RecH);
}

internal inline b32
CircleVsCircle(Vector2 P, r32 RadiusP, Vector2 Q, r32 RadiusQ)
{
    Vector2 PQ = {P.x - Q.x, P.y - Q.y};
    r32 DistanceSq = Inner(PQ, PQ);

    return (DistanceSq < Square(RadiusP + RadiusQ));
}

// vertices needs to follow clockwise ordered orientation
internal inline b32
CircleVsTriangle(Vector2 O, r32 Radius, Vector2 A, Vector2 B, Vector2 C, Vector2 Circumcenter, r32 Rotation)
{
    A = VectorRotate(A, Circumcenter, Rotation);
    B = VectorRotate(B, Circumcenter, Rotation);
    C = VectorRotate(C, Circumcenter, Rotation);

    // Check if the vertices are within the circle
    if (Inner(O - A, O - A) <= Square(Radius))
    {
        return (true);
    }
    if (Inner(O - B, O - B) <= Square(Radius))
    {
        return (true);
    }
    if (Inner(O - C, O - C) <= Square(Radius))
    {
        return (true);
    }

    // Check if circle center is within triangle
    if ((B.y - A.y) * (O.x - A.x) - (B.x - A.x) * (O.y - A.y) >= 0 &&
        (C.y - B.y) * (O.x - B.x) - (C.x - B.x) * (O.y - B.y) >= 0 &&
        (A.y - C.y) * (O.x - C.x) - (A.x - C.x) * (O.y - C.y) >= 0)
    {
        return (true);
    }

    // Check if the circle intersects the edges
    // First edge
    r32 CircleProjectedOnSide = Inner(B - A, O - A);

    if (CircleProjectedOnSide > 0)
    {
        r32 SideLen = VectorLen(B - A);
        CircleProjectedOnSide /= SideLen;

        if (CircleProjectedOnSide < SideLen)
        {
            if (sqrt(Inner(O - A, O - A) - Square(CircleProjectedOnSide)) <= Radius)
            {
                return (true);
            }
        }
    }

    // Second edge
    CircleProjectedOnSide = Inner(C - B, O - B);

    if (CircleProjectedOnSide > 0)
    {
        r32 SideLen = VectorLen(C - B);
        CircleProjectedOnSide /= SideLen;

        if (CircleProjectedOnSide < SideLen)
        {
            if (sqrt(Inner(O - B, O - B) - Square(CircleProjectedOnSide)) <= Radius)
            {
                return (true);
            }
        }
    }

    // Third edge
    CircleProjectedOnSide = Inner(A - C, O - C);

    if (CircleProjectedOnSide > 0)
    {
        r32 SideLen = VectorLen(A - C);
        CircleProjectedOnSide /= SideLen;

        if (CircleProjectedOnSide < SideLen)
        {
            if (sqrt(Inner(O - C, O - C) - Square(CircleProjectedOnSide)) <= Radius)
            {
                return (true);
            }
        }
    }

    return (false);
}

internal b32
PolyVsPoly(polygon *PolygonA, polygon *PolygonB, Vector2 *MinimumTranslationVectorA = 0)
{
    u32 NumberOfNormals = PolygonA->Size + PolygonB->Size;
    r32 MinOverlap;
    Vector2 MinOverlapDirectionA = {};
    for (u32 NormalIndex = 0;
         NormalIndex < NumberOfNormals;
         ++NormalIndex)
    {
        Vector2 Normal;
        if (NormalIndex < PolygonA->Size - 1)
        {
            Normal = VectorNormal(PolygonA->Points[NormalIndex + 1] - PolygonA->Points[NormalIndex]);
        }
        else if (NormalIndex == PolygonA->Size - 1)
        {
            Normal = VectorNormal(PolygonA->Points[0] - PolygonA->Points[NormalIndex]);
        }
        else if (NormalIndex - PolygonA->Size < PolygonB->Size - 1)
        {
            Normal = VectorNormal(PolygonB->Points[NormalIndex - PolygonA->Size + 1] - PolygonB->Points[NormalIndex - PolygonA->Size]);
        }
        else if (NormalIndex - PolygonA->Size == PolygonB->Size - 1)
        {
            Normal = VectorNormal(PolygonB->Points[0] - PolygonB->Points[NormalIndex - PolygonA->Size]);
        }
        else
        {
            ASSERT(false);
        }

        // get min and max projections from A onto the normal
        r32 MinProjectionA = Inner(PolygonA->Points[0], Normal);
        r32 MaxProjectionA = MinProjectionA;
        for (u32 i = 1;
             i < PolygonA->Size;
             ++i)
        {
            r32 CurrentProj = Inner(PolygonA->Points[i], Normal);
            if (CurrentProj < MinProjectionA) MinProjectionA = CurrentProj;
            if (CurrentProj > MaxProjectionA) MaxProjectionA = CurrentProj;
        }

        // get min and max projections from B onto the normal
        r32 MinProjectionB = Inner(PolygonB->Points[0], Normal);
        r32 MaxProjectionB = MinProjectionB;
        for (u32 i = 1;
             i < PolygonB->Size;
             ++i)
        {
            r32 CurrentProj = Inner(PolygonB->Points[i], Normal);
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

    MinOverlapDirectionA = VectorNormalize(MinOverlapDirectionA);
    MinOverlapDirectionA *= MinOverlap;
    if (MinimumTranslationVectorA)
    {
        Vector2 MidPointA = {};
        Vector2 MidPointB = {};
        for (u32 i = 0;
            i < PolygonA->Size;
            ++i)
        {
            MidPointA = MidPointA + PolygonA->Points[i];
        }
        MidPointA = MidPointA / (r32)PolygonA->Size;
        for (u32 i = 0;
            i < PolygonB->Size;
            ++i)
        {
            MidPointB = MidPointB + PolygonB->Points[i];
        }
        MidPointB = MidPointB / (r32)PolygonB->Size;
        Vector2 AB = MidPointB - MidPointA;

        MinOverlapDirectionA = MinOverlapDirectionA * MinOverlap;
        r32 OverlapDir = Inner(MinOverlapDirectionA, AB);
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
PolyVsCircle(polygon *Polygon, Vector2 Origin, r32 Radius)
{
    for (int PointIndex = 0;
         PointIndex < Polygon->Size;
         ++PointIndex)
    {
        if (Inner(Polygon->Points[PointIndex] - Origin, Polygon->Points[PointIndex] - Origin) < Radius * Radius)
        {
            return (true);
        }
    }

    return (false);
}

polygon
ExtendPolygon(polygon *Original, Vector2 Direction)
{
    polygon Result = {};

    polygon Extended = {};
    for (u32 i = 0;
         i < Original->Size;
         ++i)
    {
        Extended.Points[i] = Original->Points[i] + Direction;
    }

    Vector2 Normal = VectorNormal(Direction);

    i32 MinIndex = 0;
    i32 MaxIndex = 0;
    r32 Min = Inner(Original->Points[0], Normal);
    r32 Max = Min;
    for (u32 i = 1;
         i < Original->Size;
         ++i)
    {
        r32 Proj = Inner(Original->Points[i], Normal);
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
    i32 MinIndexCpy = MinIndex;
    i32 MaxIndexCpy = MaxIndex;
    // NOTE(david): for drawing purposes this needs to be correct, for SAT purposes only checking for the normals this works either way
    i32 Add = (MinIndexCpy < MaxIndexCpy ? 1 : -1);
    while (MinIndexCpy != MaxIndexCpy)
    {
        Result.Points[Result.Size++] = Original->Points[MinIndexCpy];
        MinIndexCpy += Add;
        if (MinIndexCpy == Original->Size) MinIndexCpy = 0;
        if (MinIndexCpy < 0) MinIndexCpy = Original->Size - 1;
    }
    Result.Points[Result.Size++] = Original->Points[MinIndexCpy];
    MinIndexCpy = MinIndex;
    MaxIndexCpy = MaxIndex;
    while (MaxIndexCpy != MinIndexCpy)
    {
        Result.Points[Result.Size++] = Extended.Points[MaxIndexCpy];
        MaxIndexCpy += Add;
        if (MaxIndexCpy == Original->Size) MaxIndexCpy = 0;
        if (MaxIndexCpy < 0) MaxIndexCpy = Original->Size - 1;
    }
    Result.Points[Result.Size++] = Extended.Points[MaxIndexCpy];

    return (Result);
}
