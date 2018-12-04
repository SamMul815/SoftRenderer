#pragma once
#include "Vector.h"
struct IntPoint
{
public:
	int x;
	int y;
	int z;
public:
	IntPoint() : x(0), y(0), z(0){}
	IntPoint(int InX, int InY) : x(InX), y(InY), z(1){}
	IntPoint(int InX, int InY, int InZ) : x(InX), y(InY), z(InZ) {}
	IntPoint(Vector2 InVector2) : x((int)InVector2.x), y((int)InVector2.y), z(1) {}
	IntPoint(Vector3 InVector3) : x((int)InVector3.X), y((int)InVector3.Y), z((int)InVector3.Z) {}


	Vector2 ToVector2() { return Vector2((float)x, (float)y); }
	Vector3 ToVector3() { return Vector3((float)x, (float)y, (float)z); }
};