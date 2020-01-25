#include "Vector2.h"

#include "../Shapes/Line.h"

#include "../Utils/Utils.h"

std::ostream& operator<<(std::ostream& consoleOut, const Vector2& vector)
{
	consoleOut << "X: " << vector.x << ", Y: " << vector.y << std::endl;
	return consoleOut;
}

bool operator==(const Vector2& lhs, const Vector2& rhs)
{
	return IsEqualTo(lhs.x, rhs.x) && IsEqualTo(lhs.y, rhs.y);
}

bool operator==(const Line& lhs, const Line& rhs)
{
	return (rhs.GetPoint() == lhs.m_point) && (rhs.GetPoint1() == lhs.m_point1);
}

Vector2 operator+(const Vector2& lhs, const Vector2 rhs)
{
	return Vector2(lhs.x + rhs.x, lhs.y + rhs.y);
}

Vector2 operator-(const Vector2& lhs, const Vector2& rhs)
{
	//Vector subtraction
	return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
}

Vector2 operator*(const Vector2& vectorLHS, float scalarRHS) 
{
	return Vector2(vectorLHS.x * scalarRHS, vectorLHS.y * scalarRHS);
}

Vector2 operator*(float scalarLHS, const Vector2 vectorRHS)
{
	return vectorRHS * scalarLHS;
}

Vector2 operator/(const Vector2& vectorLHS, float scalarRHS)
{
	assert(fabsf(scalarRHS) > EPSILON);
	return Vector2(vectorLHS.x / scalarRHS, vectorLHS.y / scalarRHS);
}
