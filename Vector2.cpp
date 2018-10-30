#include "stdafx.h"
#include "Vector2.h"

float Vector2::Dist(const Vector2 & v1, const Vector2 & v2)
{	
	float dx = v1.x - v2.x;
	float dy = v1.y - v2.y;
	return sqrtf(dx * dx + dy * dy);
}

float Vector2::DistSquared(const Vector2 & v1, const Vector2 & v2)
{
	float dx = v1.x - v2.x;
	float dy = v1.y - v2.y;
	return dx * dx + dy * dy;
}

Vector2 Vector2::operator*(const Matrix2 & mat) const
{
	Vector2 result;
	result.x = x * mat._11 + y * mat._12;
	result.y = x * mat._21 + y * mat._22;
	return result;
}

bool Vector2::Equals(const Vector2 & V, float tolerance) const
{
	return (fabsf(V.x - x) < tolerance) && (fabsf(V.y - y) < tolerance);
}
