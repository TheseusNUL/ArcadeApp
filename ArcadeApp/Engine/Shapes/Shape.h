#pragma once
#include <vector>

#include "../Maths/Vector2.h"

class Shape
{
public:
	virtual ~Shape() {}

	virtual Vector2 GetCentrePoint() const = 0;
	
	inline virtual std::vector<Vector2> GetPoints() const { return m_points; }

	void MoveBy(const Vector2& offset);

protected:
	std::vector<Vector2> m_points;
};