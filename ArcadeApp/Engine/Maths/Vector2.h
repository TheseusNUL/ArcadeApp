#pragma once
#include <iostream>
#include <cassert>
#include <cmath>

#include "../Utils/Utils.h"

class Vector2
{
public:
	Vector2() : Vector2(0, 0) {}
	Vector2(float x, float y) : m_x(x), m_y(y) {}

	static const Vector2 Zero;

	inline void SetX(float x) { m_x = x; }
	inline void SetY(float y) { m_y = y; }
	inline float GetX() const { return m_x; }
	inline float GetY() const { return m_y; }
	
	friend std::ostream& operator<<(std::ostream& consoleOut, const Vector2& vector);
	friend Vector2 operator*(const Vector2& vectorLHS, float scalarRHS);
	friend Vector2 operator*(float scalarLHS, const Vector2 vectorRHS);
	friend Vector2 operator/(const Vector2& vectorLHS, float scalarRHS);
	friend Vector2 operator+(const Vector2& lhs, const Vector2 rhs);
	friend Vector2 operator-(const Vector2& lhs, const Vector2& rhs);
	friend bool operator==(const Vector2& lhs, const Vector2& rhs);

	bool operator!=(const Vector2 other) const;

	Vector2 operator-() const;
	Vector2& operator*=(float scalar);
	Vector2& operator/=(float scalar);
	Vector2& operator+=(const Vector2& other);
	Vector2& operator-=(const Vector2& other);

	float MagSquared() const;
	float L2_Norm() const;
	float DistanceBetweenPoints(const Vector2& other) const;
	float DotProduct(const Vector2& other) const;
	float AngleBetween(const Vector2& other) const;

	Vector2 GetUnitVector() const;
	Vector2& NormaliseVector();
	Vector2 Project(const Vector2& other) const;
	Vector2 Reflect(const Vector2& normal) const;

	void Rotate(float angle, const Vector2& point);
	Vector2 RotationalResult(float angle, const Vector2& point) const;


private:
	float m_x;
	float m_y;
};

