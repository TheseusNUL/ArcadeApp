#include "Utils.h"
#include "../Maths/Vector2.h"
#include <cmath>

bool IsEqualTo(float x, float y)
{
	return fabsf(x - y) < EPSILON;
}

bool IsGreaterThanOrEqualTo(float x, float y)
{
	return x > y || IsEqualTo(x, y);
}

bool IsLessThanOrEqualTo(float x, float y)
{
	return x < y || IsEqualTo(x, y);
}