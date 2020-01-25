#include "Triangle.h"
#include "Line.h"

Triangle::Triangle(const Vector2& point, const Vector2& point1, const Vector2& point2)
{
	m_points.push_back(point);
	m_points.push_back(point1);
	m_points.push_back(point2);
}

Vector2 Triangle::GetCentrePoint() const
{
	float x = (m_points[0].GetX() + m_points[1].GetX() + m_points[2].GetX()) / 3;
	float y = (m_points[0].GetY() + m_points[1].GetY() + m_points[2].GetY()) / 3;

	return Vector2(x, y);
}

float Triangle::Area() const
{
	return Area(GetPoint(), GetPoint1(), GetPoint2());
}

bool Triangle::bContainsPoint(const Vector2& point) const
{
	//divide triangle into three sub-triangles. If sum of sub-triangles is equal to area of triangle then triangle contains point

	float area = Area();

	float a1 = Area(point, GetPoint1(), GetPoint2());
	float a2 = Area(GetPoint(), point, GetPoint2());
	float a3 = Area(GetPoint(), GetPoint1(), point);

	return bIsEqualTo(area, a1 + a2 + a3);
}

float Triangle::Area(const Vector2& point, const Vector2& point1, const Vector2& point2) const
{
	//Heron's formula
	Line LineA(point, point1);
	Line LineB(point1, point2);
	Line LineC(point2, point);

	float a = LineA.Length();
	float b = LineB.Length();
	float c = LineC.Length();

	float s = (a + b + c) * 0.5f;

	float area = sqrt(s * (s - a) * (s - b) * (s - c));

	return area;
}
