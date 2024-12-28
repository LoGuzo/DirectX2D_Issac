#pragma once
#include <math.h>
#include <algorithm>
class Vector3
{
public:
	float x, y, z;

public:
	Vector3() { x = 0; y = 0; z = 0; };
	Vector3(float xx) { x = xx; y = xx; z = xx; };
	Vector3(float xx, float yy, float zz) { x = xx; y = yy; z = zz; };
	~Vector3() {};
	float lengthSq() { return x * x + y * y + z * z; };
	float length() { return (float)sqrt(lengthSq()); };
	Vector3 operator * (float f)
	{
		return Vector3(x * f, y * f, z * f);
	}
	Vector3 operator / (float f)
	{
		return Vector3(x / f, y / f, z / f);
	}
	Vector3 operator + (Vector3 v)
	{
		return Vector3(x + v.x, y + v.y, z + v.z);
	}
	Vector3 operator - (Vector3 v)
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}
	Vector3& operator += (Vector3 v)
	{
		x += v.x, y += v.y, z += v.z; return *this;
	}
	Vector3& operator -= (Vector3 v)
	{
		x -= v.x, y -= v.y, z -= v.z; return *this;
	}
	Vector3 operator - ()
	{
		return Vector3(-x, -y, -z);
	}

	static 	float Dot(Vector3& v1, Vector3& v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}
	Vector3 Cross(Vector3& v1, Vector3& v2)
	{
		return Vector3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
	}
	Vector3 Normalized(Vector3* v)
	{
		float magSq = v->lengthSq();

		return magSq > 0 ? *v / sqrt(magSq) : Vector3();
	}
};