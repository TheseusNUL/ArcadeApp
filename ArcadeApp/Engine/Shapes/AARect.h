#pragma once
#include "Shape.h"

class AARect : public Shape
{
public:
	AARect() : AARect(Vector2::Zero, Vector2::Zero) {}
	AARect(const Vector2& topLeft, unsigned int width, unsigned int height);
	AARect(const Vector2& topLeft, const Vector2& bottomRight);//ensures AA Rectangle

	inline void SetTLP(const Vector2& topLeft) { m_points[0] = topLeft; }
	inline void SetBRP(const Vector2& bottomRight) { m_points[1] = bottomRight; }
	inline Vector2 GetTLP() const { return m_points[0]; }
	inline Vector2 GetBRP() const { return m_points[1]; }

	Vector2 GetCentrePoint() const override;
	std::vector<Vector2> GetPoints() const override;

	void SetRectWidth();
	void SetRectHeight();
	void MoveTo(const Vector2& pos);

	bool bIntersects(const AARect& other) const;
	bool bCointainsPoint(const Vector2& point) const;

	static AARect Inset(const AARect& rect, Vector2& insets);

private:
	float m_width;
	float m_height;
};
