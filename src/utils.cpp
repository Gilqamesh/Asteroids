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
