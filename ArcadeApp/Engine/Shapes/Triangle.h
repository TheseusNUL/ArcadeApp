#pragma once
#include "Shape.h"

class Triangle : public Shape
{
public:
	Triangle() : Triangle(Vector2::Zero, Vector2::Zero, Vector2::Zero) {}
	Triangle(const Vector2& point, const Vector2& point1, const Vector2& point2);

	inline void SetPoint(const Vector2& point) { m_points[0] = point; }
	inline void SetPoint1(const Vector2& point) { m_points[1] = point; }
	inline void SetPoint2(const Vector2& point) { m_points[2] = point; }
	inline Vector2 GetPoint() const { return m_points[0]; }
	inline Vector2 GetPoint1() const { return m_points[1]; }
	inline Vector2 GetPoint2() const { return m_points[2]; }

	Vector2 GetCentrePoint() const override;

	float Area() const;
	bool ContainsPoint(const Vector2& point) const;

private:
	float Area(const Vector2& point, const Vector2& point1, const Vector2& point2) const;
};
