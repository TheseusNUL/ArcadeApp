#include "Vector2.h"

#include "../Shapes/Line.h"

#include "../Utils/Utils.h"

std::ostream& operator<<(std::ostream& consoleOut, const Vector2& vector)
{
	consoleOut << "X: " << vector.m_x << ", Y: " << vector.m_y << std::endl;
	return consoleOut;
}

bool operator==(const Vector2& lhs, const Vector2& rhs)
{
	return bIsEqualTo(lhs.m_x, rhs.m_x) && bIsEqualTo(lhs.m_y, rhs.m_y);
}

bool operator==(const Line& lhs, const Line& rhs)
{
	return (rhs.GetPoint() == lhs.m_point) && (rhs.GetPoint1() == lhs.m_point1);
}

Vector2 operator+(const Vector2& lhs, const Vector2 rhs)
{
	return Vector2(lhs.m_x + rhs.m_x, lhs.m_y + rhs.m_y);
}

Vector2 operator-(const Vector2& lhs, const Vector2& rhs)
{
	//Vector subtraction
	return Vector2(lhs.m_x - rhs.m_x, lhs.m_y - rhs.m_y);
}

Vector2 operator*(const Vector2& vectorLHS, float scalarRHS) 
{
	return Vector2(vectorLHS.m_x * scalarRHS, vectorLHS.m_y * scalarRHS);
}

Vector2 operator*(float scalarLHS, const Vector2 vectorRHS)
{
	return vectorRHS * scalarLHS;
}

Vector2 operator/(const Vector2& vectorLHS, float scalarRHS)
{
	assert(fabsf(scalarRHS) > EPSILON);
	return Vector2(vectorLHS.m_x / scalarRHS, vectorLHS.m_y / scalarRHS);
}
