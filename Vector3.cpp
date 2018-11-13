#include "stdafx.h"
#include "Vector3.h"

float Vector3::Dist(const Vector3 & V1, const Vector3 & V2)
{
	return sqrtf(DisSquared(V1, V2));
}

float Vector3::DisSquared(const Vector3 & V1, const Vector3 & V2)
{
	float xLength = V2.X - V1.X;
	float yLength = V2.Y - V1.Y;
	float zLength = V2.Z - V1.Z;

	return xLength * xLength + yLength * yLength + zLength + zLength;
}

float Vector3::Dot(const Vector3 & V1, const Vector3 & V2)
{
	return V1.X * V2.X + V1.Y * V2.Y + V1.Z * V2.Z;
}

Vector3 Vector3::Make2DPoint(float Inx, float InY)
{
	return Vector3(Inx,InY,1.0f);
}

Vector3 Vector3::Make2DVector(float InX, float InY)
{
	return Vector3(InX,InY,0.0f);
}

Vector3 Vector3::operator*(const Matrix3 & mat) const
{
	Vector3 result;

	result.X = X * mat._11 + Y * mat._12 + Z * mat._13;
	result.Y = X * mat._21 + Y * mat._22 + Z * mat._23;
	result.Z = X * mat._31 + Y * mat._32 + Z * mat._33;

	return result;
}

Vector3 Vector3::operator*(const float &value) const
{
	return Vector3(X * value,Y * value,Z * value);
}

Vector3 Vector3::operator+(const Vector3 & other) const
{
	return Vector3(X + other.X,Y + other.Y, Z + other.Z);
}

Vector3 Vector3::operator-(const Vector3 & other) const
{
	return Vector3(X - other.X, Y - other.Y,Z - other.Z);
}

bool Vector3::Equals(const Vector3 & V, float tolerance) const
{

	return (fabsf(V.X - X) < tolerance) && 
			(fabsf(V.Y - Y) < tolerance) &&
			(fabsf(V.Z - Z) < tolerance);
}



