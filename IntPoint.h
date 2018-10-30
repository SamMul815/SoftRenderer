#pragma once
#include "Vector.h"
struct IntPoint
{
public:
	int x;
	int y;
public:
	IntPoint() : x(0), y(0) {}
	IntPoint(int InX, int InY) : x(InX), y(InY){}
	IntPoint(Vector2 InVector2) : x((int)InVector2.x), y((int)InVector2.y) {}

	Vector2 ToVector2() { return Vector2((float)x, (float)y); }

};