#include "Line.h"

float Line::MinDistanceFrom(const Vector2& point, bool limitToSegment) const
{
	return point.DistanceBetweenPoints(ClosestPoint(point, limitToSegment));
}

Vector2 Line::ClosestPoint(const Vector2& point, bool limitToSegment) const
{

	Vector2 vector = point - m_point;
	Vector2 line = m_point1 - m_point; 

	float lineMag = line.MagSquared();
	float dotProd = vector.DotProduct(line);

	float projection = dotProd / lineMag;

	if (limitToSegment)
		projection = std::fmax(0, std::fmin(1.0f, projection)); //limits to line segment.

	return m_point + m_point1 * projection;
}

Vector2 Line::Midpoint() const
{
	return Vector2((m_point.x + m_point1.x) / 2.0f, (m_point.y + m_point1.y) / 2.0f);
}

float Line::Slope() const
{
	//rise / run

	float slopeX = m_point1.x - m_point.x;

	if (fabsf(slopeX) < EPSILON)
		return 0.0f;

	float slopeY = m_point1.y - m_point.y;
	return slopeY / slopeX;
}

float Line::Length() const
{
	return m_point1.DistanceBetweenPoints(m_point);
}
