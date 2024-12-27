#pragma once
class Vector2
{
public:
	Vector2();
	Vector2(const float& x, const float& y);
	Vector2(const double& x, const double& y);
	Vector2(const int& x, const int& y);
	Vector2(const LONG& x, const LONG& y);

	// 연산자 overloding
	Vector2 operator+  (const Vector2& v);
	Vector2 operator-  (const Vector2& v);
	Vector2 operator+= (const Vector2& v);
	Vector2 operator-= (const Vector2& v);
	Vector2 operator*  (const Vector2& v);
	Vector2 operator*  (const float& scalar);
	Vector2 operator/  (const Vector2& v);
	Vector2 operator/  (const float& scalar);
	Vector2 operator*  (const Matrix& v);
	const   bool operator==(const Vector2& v);
	const   bool operator!=(const Vector2& v);

private:
	bool   IsEqual(float x1, float x2);
public:
	float  Length();
	static Vector2 Normalize(Vector2 InVector); // 0-1사이
	static float   Dot(Vector2 A, Vector2 B);   // 내적
	static float   Cross(Vector2 A, Vector2 B); // 외적
	static float   Length(Vector2 A, Vector2 B);
	static float   ToRadian(Vector2 from, Vector2 to);
	static float   Clamp(float min, float max, float value);
	static Vector2 Direction(float radian);
	static Vector2 Lerp(Vector2 A, Vector2 B, float t);

	static float   Cos(Vector2 from, Vector2 to);

public:
	float x = 0.0f;
	float y = 0.0f;
};

