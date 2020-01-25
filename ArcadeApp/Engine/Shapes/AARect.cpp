#include "AARect.h"

AARect::AARect(const Vector2& topLeft, unsigned int width, unsigned int height)
{
	m_points.push_back(topLeft);
	m_points.push_back(Vector2(topLeft.GetX() + width - 1, topLeft.GetY() + height - 1));
}

AARect::AARect(const Vector2& topLeft, const Vector2& bottomRight)
{
	m_points.push_back(topLeft);
	m_points.push_back(bottomRight);
}

Vector2 AARect::GetCentrePoint() const
{
	return Vector2(GetTLP().GetX() + m_width / 2, GetTLP().GetY() + m_height / 2);
}

std::vector<Vector2> AARect::GetPoints() const
{
	//Get all the points in the rectangle

	std::vector<Vector2> points;

	Vector2 tr = Vector2(m_points[1].GetX(), m_points[0].GetY());
	Vector2 bl = Vector2(m_points[0].GetX(), m_points[1].GetY());

	points.push_back(m_points[0]); //top left
	points.push_back(tr); //top right
	points.push_back(m_points[1]); //bottom right
	points.push_back(bl); //bottom left

	return points;
}

void AARect::SetRectWidth()
{
	m_width = GetBRP().GetX() - GetTLP().GetX() + 1;
}

void AARect::SetRectHeight()
{
	m_height = GetBRP().GetY() - GetTLP().GetY() + 1;
}

void AARect::MoveTo(const Vector2& pos)
{
	SetTLP(pos);
	SetBRP(Vector2(pos.GetX() + m_width - 1, pos.GetY() + m_height - 1));
}

bool AARect::bIntersects(const AARect& other) const
{
	float tlw = GetTLP().GetX();
	float brw = GetBRP().GetX();
	float tlh = GetTLP().GetY();
	float brh = GetBRP().GetY();

	float otlw = other.GetTLP().GetX();
	float obrw = other.GetBRP().GetX();
	float otlh = other.GetTLP().GetY();
	float obrh = other.GetBRP().GetY();

	return !(obrw < tlw || otlw > brw || obrh < tlh || otlh > brh);

}

bool AARect::bCointainsPoint(const Vector2& point) const
{
	bool withinX = (point.GetX() >= GetTLP().GetX()) && (point.GetX() <= GetBRP().GetX());
	bool withinY = (point.GetY() >= GetTLP().GetY()) && (point.GetY() <= GetBRP().GetY());

	return withinX && withinY;
}

AARect AARect::Inset(const AARect& rect, Vector2& insets)
{
	return AARect(rect.GetTLP() + insets, rect.m_width - 2 * insets.GetX(), rect.m_height - 2 * insets.GetY());
}
