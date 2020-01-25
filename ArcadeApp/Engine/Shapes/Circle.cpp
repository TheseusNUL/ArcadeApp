#include "Circle.h"

#include "../Utils/Utils.h"

Circle::Circle(const Vector2 centrePoint, float radius) :
	m_radius(radius)
{
	m_points.push_back(centrePoint);
}

bool Circle::bIntersects(const Circle& other) const
{
	return GetCentrePoint().DistanceBetweenPoints(other.GetCentrePoint()) < m_radius + other.m_radius;
}

bool Circle::bContainsPoint(const Vector2& point) const
{
	return bIsLessThanOrEqualTo(GetCentrePoint().DistanceBetweenPoints(point), m_radius);
}
