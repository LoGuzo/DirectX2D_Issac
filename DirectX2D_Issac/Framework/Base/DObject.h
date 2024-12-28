#pragma once
class Vector2;
class Vector3;

class Object
{
public:
    Vector2& Pos() { return mPosition; }
    Vector2& Scale() { return mScale; }
    Vector3& Rotation() { return mRotation; }
    Vector2  HalfSize() { return mScale * 0.5f; }

protected:
    Vector2 mPosition = Vector2(0, 0);
    Vector2 mScale = Vector2(1, 1);
    Vector3 mRotation = Vector3(0, 0, 0);
};