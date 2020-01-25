#pragma once

#include "../../../Engine/Maths/Vector2.h"

#include "../../../Engine/Shapes/Line.h"

enum E_BOUNDRY_TYPE
{
	E_BOTTOM, 
	E_TOP,
	E_LEFT,
	E_RIGHT,
	E_MAX_NUM_BOUND
};

//normals
static const Vector2 UP_DIR = Vector2(0, -1);
static const Vector2 DOWN_DIR = Vector2(0, 1);
static const Vector2 LEFT_DIR = Vector2(-1, 0);
static const Vector2 RIGHT_DIR = Vector2(1, 0);

struct Boundry
{
	Vector2 normal;
	Line edge;
};