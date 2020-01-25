#pragma once
#include "../Maths/Vector2.h"

class Line
{
public:
	Line() : Line(Vector2::Zero, Vector2::Zero) {}
	Line(float x, float y, float x1, float y1) : Line(Vector2(x, y), Vector2(x1, y1)) {}
	Line(const Vector2& point, const Vector2& point1) : m_point(point), m_point1(point1) {}

	friend bool operator==(const Line& lhs, const Line& rhs);

	inline const Vector2& GetPoint() const { return m_point; }
	inline const Vector2& GetPoint1() const { return m_point1; }
	inline void SetPoint(const Vector2& point) { m_point = point; }
	inline void SetPoint1(const Vector2& point1) { m_point1 = point1; }

	float MinDistanceFrom(const Vector2& point, bool limitToSegment = false) const;
	Vector2 ClosestPoint(const Vector2& point, bool limitToSegment = false) const;
	Vector2 Midpoint() const;
	float Slope() const;
	float Length() const;

private:
	Vector2 m_point;
	Vector2 m_point1;
};
