#pragma once
#include "Shape.h"

class Circle : public Shape
{
public:
	Circle() : Circle(Vector2::Zero, 0) {}
	Circle(const Vector2 centrePoint, float radius);

	inline Vector2 GetCentrePoint() const override { return m_points[0]; }
	inline float GetRadius() const { return m_radius; }
	inline void SetRadius(float radius) {m_radius = radius; }
	inline void MoveTo(const Vector2& pos) { m_points[0] = pos; }

	bool Intersects(const Circle& other) const;
	bool ContainsPoint(const Vector2& point) const;

private:
	float m_radius;
};