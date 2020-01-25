#include "Utils.h"
#include "../Maths/Vector2.h"
#include <cmath>

bool bIsEqualTo(float x, float y)
{
	return fabsf(x - y) < EPSILON;
}

bool bIsGreaterThanOrEqualTo(float x, float y)
{
	return x > y || bIsEqualTo(x, y);
}

bool bIsLessThanOrEqualTo(float x, float y)
{
	return x < y || bIsEqualTo(x, y);
}