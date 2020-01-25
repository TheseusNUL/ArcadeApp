#pragma once

#include "Boundries.h"

#include "../../../Engine/Shapes/AARect.h"

class Excluder
{
	virtual ~Excluder() {}

	void Init(const AARect& rect, bool reverseNormals = false);

	bool HasCollided(const AARect& rect, Boundry& edge);
	Vector2 GetCollisionOffset(const AARect& rect);
	
	//Wrappers
	void MoveBy(const Vector2& delta);
	void MoveTo(const Vector2& point);

	const Boundry& GetBoundry(E_BOUNDRY_TYPE edge) const;

private:
	void SetupBoundries();

	float GetXSize(const AARect& rect);
	float GetYSize(const AARect& rect);

	AARect m_rect;
	Boundry m_boundries[E_MAX_NUM_BOUND];

	bool m_reverseNormals;
};