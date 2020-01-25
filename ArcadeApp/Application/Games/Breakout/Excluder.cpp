#include <cmath>
#include <cassert>

#include "Excluder.h"

#include "../../../Engine/Utils/Utils.h"

void Excluder::Init(const AARect& rect, bool reverseNormals)
{
	m_rect = rect;
	m_reverseNormals = reverseNormals;

	SetupBoundries();
}

bool Excluder::HasCollided(const AARect& rect, Boundry& edge)
{
	if (m_rect.Intersects(rect))
	{
		float x = GetXSize(rect);
		float y = GetYSize(rect);

		if (x > y) //collided top or bottom
		{
			if (rect.GetCentrePoint().y > m_rect.GetCentrePoint().y)
				edge = m_boundries[E_BOUNDRY_TYPE::E_BOTTOM];
			else
				edge = m_boundries[E_BOUNDRY_TYPE::E_TOP];
		}
		else //collided left or right
		{
			if (rect.GetCentrePoint().x > m_rect.GetCentrePoint().x)
				edge = m_boundries[E_BOUNDRY_TYPE::E_RIGHT];
			else
				edge = m_boundries[E_BOUNDRY_TYPE::E_LEFT];
		}
		
		return true;
	}

	return false;
}

Vector2 Excluder::GetCollisionOffset(const AARect& rect)
{
	Boundry edge;
	Vector2 offset = Vector2::Zero;

	if (HasCollided(rect, edge))
	{
		float x = GetXSize(rect);
		float y = GetYSize(rect);

		if (!IsEqualTo(edge.normal.y, 0))
			offset = (y + 1) * edge.normal;
		else
			offset = (x + 1) * edge.normal;
	}

	return offset;
}

void Excluder::MoveBy(const Vector2& delta)
{
	m_rect.MoveBy(delta);
	SetupBoundries();
}

void Excluder::MoveTo(const Vector2& point)
{
	m_rect.MoveTo(point);
	SetupBoundries();
}

const Boundry& Excluder::GetBoundry(E_BOUNDRY_TYPE edge) const
{
	assert(edge != E_MAX_NUM_BOUND);
	return m_boundries[edge];
}

void Excluder::SetupBoundries()
{
	m_boundries[E_BOUNDRY_TYPE::E_TOP].edge = Line(Vector2(m_rect.GetTLP().x, m_rect.GetTLP().y), Vector2(m_rect.GetBRP().x, m_rect.GetTLP().y));
	m_boundries[E_BOUNDRY_TYPE::E_TOP].normal = UP_DIR;

	m_boundries[E_BOUNDRY_TYPE::E_LEFT].edge = Line(Vector2(m_rect.GetTLP().x, m_rect.GetTLP().y), Vector2(m_rect.GetTLP().x, m_rect.GetBRP().y));
	m_boundries[E_BOUNDRY_TYPE::E_LEFT].normal = LEFT_DIR;

	m_boundries[E_BOUNDRY_TYPE::E_BOTTOM].edge = Line(Vector2(m_rect.GetTLP().x, m_rect.GetBRP().y), Vector2(m_rect.GetBRP().x, m_rect.GetBRP().y));
	m_boundries[E_BOUNDRY_TYPE::E_BOTTOM].normal = DOWN_DIR;

	m_boundries[E_BOUNDRY_TYPE::E_RIGHT].edge = Line(Vector2(m_rect.GetBRP().x, m_rect.GetTLP().y), Vector2(m_rect.GetBRP().x, m_rect.GetBRP().y));
	m_boundries[E_BOUNDRY_TYPE::E_RIGHT].normal = RIGHT_DIR;

	if (m_reverseNormals)
	{
		for (auto edge : m_boundries)
			edge.normal = -edge.normal;
	}
}

float Excluder::GetXSize(const AARect& rect)
{
	float min = m_rect.GetTLP().x >= rect.GetTLP().x ? m_rect.GetTLP().x : rect.GetTLP().x;
	float max = m_rect.GetBRP().x <= rect.GetBRP().x ? m_rect.GetBRP().x : rect.GetBRP().x;

	return max - min;
}

float Excluder::GetYSize(const AARect& rect)
{
	float min = m_rect.GetTLP().y >= rect.GetTLP().y ? m_rect.GetTLP().y : rect.GetTLP().y;
	float max = m_rect.GetBRP().y <= rect.GetBRP().y ? m_rect.GetBRP().y : rect.GetBRP().y;

	return max - min;
}
