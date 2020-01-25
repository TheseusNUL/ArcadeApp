#include "AARect.h"

AARect::AARect(const Vector2& topLeft, unsigned int width, unsigned int height)
{
	m_points.push_back(topLeft);
	m_points.push_back(Vector2(topLeft.x + width - 1, topLeft.y + height - 1));
}

AARect::AARect(const Vector2& topLeft, const Vector2& bottomRight)
{
	m_points.push_back(topLeft);
	m_points.push_back(bottomRight);
}

Vector2 AARect::GetCentrePoint() const
{
	return Vector2(GetTLP().x + m_width / 2, GetTLP().y + m_height / 2);
}

std::vector<Vector2> AARect::GetPoints() const
{
	//Get all the points in the rectangle

	std::vector<Vector2> points;

	Vector2 tr = Vector2(m_points[1].x, m_points[0].y);
	Vector2 bl = Vector2(m_points[0].x, m_points[1].y);

	points.push_back(m_points[0]); //top left
	points.push_back(tr); //top right
	points.push_back(m_points[1]); //bottom right
	points.push_back(bl); //bottom left

	return points;
}

void AARect::SetRectWidth()
{
	m_width = GetBRP().x - GetTLP().x + 1;
}

void AARect::SetRectHeight()
{
	m_height = GetBRP().y - GetTLP().y + 1;
}

void AARect::MoveTo(const Vector2& pos)
{
	SetTLP(pos);
	SetBRP(Vector2(pos.x + m_width - 1, pos.y + m_height - 1));
}

bool AARect::Intersects(const AARect& other) const
{
	float tlw = GetTLP().x;
	float brw = GetBRP().x;
	float tlh = GetTLP().y;
	float brh = GetBRP().y;

	float otlw = other.GetTLP().x;
	float obrw = other.GetBRP().x;
	float otlh = other.GetTLP().y;
	float obrh = other.GetBRP().y;

	return !(obrw < tlw || otlw > brw || obrh < tlh || otlh > brh);

}

bool AARect::CointainsPoint(const Vector2& point) const
{
	bool withinX = (point.x >= GetTLP().x) && (point.x <= GetBRP().x);
	bool withinY = (point.y >= GetTLP().y) && (point.y <= GetBRP().y);

	return withinX && withinY;
}

AARect AARect::Inset(const AARect& rect, Vector2& insets)
{
	return AARect(rect.GetTLP() + insets, rect.m_width - 2 * insets.x, rect.m_height - 2 * insets.y);
}
