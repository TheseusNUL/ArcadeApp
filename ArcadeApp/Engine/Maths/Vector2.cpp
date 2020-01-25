#include "Vector2.h"

const Vector2 Vector2::Zero;

Vector2 Vector2::operator-() const
{
	/*-------------------------------------------------------------------
	This function negates the vector. The operator is unary so only
	operates on one operand.This is done by not adding any parameters.The
	function is const so it does not modify the objects internals.
	--------------------------------------------------------------------*/
	return Vector2(-x, -y);
}

Vector2& Vector2::operator+=(const Vector2& other)
{
	*this = *this + other;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2& other)
{
	*this = *this - other;
	return *this;
}

Vector2& Vector2::operator*=(float scalar)
{
	*this = *this * scalar;
	return *this;
}

Vector2& Vector2::operator/=(float scalar)
{
	assert(fabsf(scalar) > EPSILON);
	*this = *this / scalar;
	return *this;
}

bool Vector2::operator!=(const Vector2 other) const
{
	//calls == function
	return !(*this == other);
}

float Vector2::MagSquared() const
{
	return DotProduct(*this);
}

float Vector2::L2_Norm() const
{
	return sqrt(MagSquared());
}

float Vector2::DistanceBetweenPoints(const Vector2& other) const
{
	//sqrt((x2 - x1)2 + (y2 - y1)2)
	return (other - *this).L2_Norm();
}

float Vector2::DotProduct(const Vector2& other) const
{
	//returns scalar
	return (x * other.x) + (y * other.y);
}

float Vector2::AngleBetween(const Vector2& other) const
{
	/*-------------------------------
	cos0 = adj / hyp
	a dot b = ||a|| x ||b|| x cos0
	-------------------------------*/
	return acosf(GetUnitVector().DotProduct(other.GetUnitVector()));
}

Vector2 Vector2::GetUnitVector() const
{
	//v^ = v / |v|2
	float magnitude = L2_Norm();

	if (magnitude > EPSILON)
		return *this / magnitude;

	return Vector2::Zero;
}

Vector2& Vector2::NormaliseVector()
{
	//Normalise - make unit vector
	float magnitude = L2_Norm();

	if (magnitude > EPSILON)
		*this /= magnitude;

	return *this;
}

Vector2 Vector2::Project(const Vector2& other) const
{
	Vector2 unitVector = other.GetUnitVector();

	//*this dot unitVector (returns scalar)
	float dotProduct = DotProduct(unitVector);

	//turns scalar back into vector
	return unitVector * dotProduct;
}

Vector2 Vector2::Reflect(const Vector2& normal) const
{
	// r = vector + -2((v dot n)n)
	return *this - 2 * Project(normal);
}

void Vector2::Rotate(float angle, const Vector2& point)
{
	/*---------------------------------------------
	[x, y] = [x cos0 - y sin0, x sin0 + y cos0]
	----------------------------------------------*/
	float cosine = cosf(angle); //takes radians
	float sine = sinf(angle);

	Vector2 thisVector(x, y);

	//move to center
	thisVector -= point;

	//do rotation
	float x = thisVector.x * cosine - thisVector.y * sine;
	float y = thisVector.x * sine + thisVector.y * cosine;

	Vector2 rotation = Vector2(x, y);
	
	//move back to point
	*this = rotation + point;
}

Vector2 Vector2::RotationalResult(float angle, const Vector2& point) const
{
	/*---------------------------------------------
	[x, y] = [x cos0 - y sin0, x sin0 + y cos0]
	----------------------------------------------*/
	float cosine = cosf(angle); //takes radians
	float sine = sinf(angle);

	Vector2 thisVector(x, y);

	//move to center
	thisVector -= point;

	//do rotation
	float x = thisVector.x * cosine - thisVector.y * sine;
	float y = thisVector.x * sine + thisVector.y * cosine;

	Vector2 rotation = Vector2(x, y);

	//move back to point
	return rotation + point;
}
