#pragma once
#include "stdafx.h"
#include "Matrix.h"
struct Vector3
{
public:
	float X;
	float Y;
	float Z;
public:
	Vector3() : X(0), Y(0), Z(0) {}
	Vector3(float InX, float InY, float InZ) : X(InX), Y(InY), Z(InZ) {}

	static float Dist(const Vector3 &V1, const Vector3 &V2);
	static float DisSquared(const Vector3 &V1, const Vector3 &V2);
	static float Dot(const Vector3 &V1, const Vector3 &V2);
	static Vector3 Make2DPoint(float Inx, float InY);
	static Vector3 Make2DVector(float InX, float InY);

	Vector3 operator*(const Matrix3 &mat) const;
	Vector3 operator*(const float &value)const;
	Vector3 operator+(const Vector3 &other)const;
	Vector3 operator-(const Vector3 &other)const;

	bool Equals(const Vector3 &V, float tolerance = KINDA_SMALL_NUMBER) const;


};
