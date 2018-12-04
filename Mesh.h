#pragma once

#include "stdafx.h"
#include "Triangle.h"

struct Mesh
{
public:
	Mesh() : Triangles(NULL) {}
public:
	Triangle * Triangles;
};

