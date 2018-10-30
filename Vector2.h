#pragma once
#include "stdafx.h"
#include "Matrix.h"
struct Vector2
{
public:
	float x;
	float y;

public:
	Vector2() : x(0), y(0) {}
	Vector2(float InX, float InY) : x(InX), y(InY) {}
	
	static float Dist(const Vector2 &v1, const Vector2 &v2);
	static float DistSquared(const Vector2 &v1, const Vector2 &v2);
	
	Vector2 operator*(const Matrix2 &mat) const;
	
	bool Equals(const Vector2& V, float tolerance = KINDA_SMALL_NUMBER) const;

};