#pragma once
#include "stdafx.h"
#include "Vector.h"
#include "IntPoint.h"

struct  Vertex
{
public:
	Vertex() : color(RGB32(0,0,0)){}
	Vertex(const Vector3 & InPosition, ULONG InColor) : position(InPosition), color(InColor) {}
	Vertex(const Vector3 & Inposition, ULONG InColor, Vector2 & InUV)
		:position(Inposition), color(InColor), uv(InUV) {}

	Vector3 position;
	Vector2 uv;
	ULONG color;
};