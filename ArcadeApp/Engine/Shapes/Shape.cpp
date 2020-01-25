#include "Shape.h"

void Shape::MoveBy(const Vector2& offset)
{
	for(Vector2& point: m_points)
		point += offset;

	/*-----------------------------------------------------------------------------------
	for(std::vector<Vector2>::iterator it = m_points.begin(); it != m_points.end(); it++)
		*it += offset;
	-----------------------------------------------------------------------------------*/	
}