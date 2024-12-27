#include "framework.h"
#include "Vector2.h"


#define    PI           3.141592f
#define    FLOAT_EQUAL  0.000001f
Vector2::Vector2()
{
	x = 0.0f;
	y = 0.0f;
}

Vector2::Vector2(const float& x, const float& y)
{
	this->x = x;
	this->y = y;
}

Vector2::Vector2(const double& x, const double& y)
{
	this->x = (float)x;
	this->y = (float)y;
}

Vector2::Vector2(const int& x, const int& y)
{
	this->x = (float)x;
	this->y = (float)y;
}

Vector2::Vector2(const LONG& x, const LONG& y)
{
	this->x = (float)x;
	this->y = (float)y;
}

Vector2 Vector2::operator+(const Vector2& v)
{
	// Vector2 A(1,1)
	// Vector2 B(3,3)
	// Vector2 C(4,4) = A + B;
	Vector2  result;

	result.x = this->x + v.x;
	result.y = this->y + v.y;
	return result;
}

Vector2 Vector2::operator-(const Vector2& v)
{
	Vector2  result;

	result.x = this->x - v.x;
	result.y = this->y - v.y;
	return result;
}

Vector2 Vector2::operator+=(const Vector2& v)
{
	Vector2  result;

	result.x = this->x + v.x;
	result.y = this->y + v.y;
	return result;
}

Vector2 Vector2::operator-=(const Vector2& v)
{
	Vector2  result;

	result.x = this->x - v.x;
	result.y = this->y - v.y;
	return result;
}

Vector2 Vector2::operator*(const Vector2& v)
{
	Vector2  result;

	result.x = this->x * v.x;
	result.y = this->y * v.y;
	return result;
}

Vector2 Vector2::operator*(const float& scalar)
{
	Vector2  result;

	result.x = this->x * scalar;
	result.y = this->y * scalar;
	return result;
}

Vector2 Vector2::operator/(const Vector2& v)
{
	Vector2  result;

	result.x = this->x / v.x;
	result.y = this->y / v.y;
	return result;
}

Vector2 Vector2::operator/(const float& scalar)
{
	Vector2  result;

	result.x = this->x / scalar;
	result.y = this->y / scalar;
	return result;
}
//  Sx        0
//     Sy     0
//        Sz  0   
//  tx ty tx  1  [ px py pz ]


Vector2 Vector2::operator*(const Matrix& v)
{
	Float2 coord(x, y);
	XMVECTOR temp = XMLoadFloat2(&coord);     // XMVECTOR로 변환
	// XMVector2TransformCoord       : w->1
	// XMVector2TransformCoordNormal : w->0
	temp = XMVector2TransformCoord(temp, v);
	XMStoreFloat2(&coord, temp);
	return Vector2(coord.x, coord.y);
}

const bool Vector2::operator==(const Vector2& v)
{
	if (IsEqual(this->x, v.x))
	{
		if (IsEqual(this->y, v.y))
			return true;
	}
	return false;
}

const bool Vector2::operator!=(const Vector2& v)
{
	return !((*this) == v);
}

bool Vector2::IsEqual(float x1, float x2)
{
	float gap = fabs(x2 - x1);
	if (gap <= FLOAT_EQUAL)
		return true;
	return false;
}
float Vector2::Length()
{
	return sqrtf(x * x + y * y);
}
// A 에서 B로 추적
// 방향 = B-A
// Normailze
// A위치 = A위치 + 방향*힘
Vector2 Vector2::Normalize(Vector2 InVector)
{
	Vector2  result = InVector;
	Float3   data = Float3(InVector.x, InVector.y, 0.0f);
	XMVECTOR test = XMLoadFloat3(&data);
	test = XMVector3Normalize(test);
	XMStoreFloat3(&data, test);

	// 두점간의 거리 = sqrt(x2-x1*x2-x1 + y2-y1*y2-y1)
	//float length = sqrtf(result.x*result.x + result.y*result.y);
	//
	//result.x /= length;
	//result.y /= length;
	result.x = data.x;
	result.y = data.y;

	return result;
}
//////////////////////////////////////////////////////////
//  벡터의 내적
// #define   dot(u,v)   ( (u).x*(v).x + (u).y*(v).y)  // AdotB   = |A*B|cos() 내적
// #define   cross(u,v) ( (u).x*(v).y - (u).y*(v).x)  // AcrossB = |A*B|sin() 외적
//////////////////////////////////////////////////////////
float Vector2::Dot(Vector2 A, Vector2 B)
{
	float result = A.x * B.x + A.y * B.y;
	return result;
}
//////////////////////////////////////////////////////////
//  벡터의 외적
//////////////////////////////////////////////////////////
float Vector2::Cross(Vector2 A, Vector2 B)
{
	float result = A.x * B.y - A.y * B.x;
	return result;
}

float Vector2::Length(Vector2 A, Vector2 B)
{
	float length = sqrtf((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
	return length;
}

float Vector2::Cos(Vector2 from, Vector2 to)
{
	return Dot(from, to) / (from.Length() * to.Length());
}

float Vector2::ToRadian(Vector2 from, Vector2 to)
{
	Vector2 delta = to - from;

	return atan2f(delta.y, delta.x);



	if (delta.y > 0) return acosf(Cos(from, to));
	else return 2.0f * PI - acosf(Cos(from, to));
}

float Vector2::Clamp(float min, float max, float value)
{
	if (value < min)
		value = min;
	if (value > max)
		value = max;
	return value;
}

Vector2 Vector2::Direction(float radian)
{
	return Vector2(cosf(radian), sinf(radian));
}

Vector2 Vector2::Lerp(Vector2 start, Vector2 end, float t)
{
	Vector2 value;

	value.x = start.x + (end.x - start.x) * t;
	value.y = start.y + (end.y - start.y) * t;

	return value;
}
