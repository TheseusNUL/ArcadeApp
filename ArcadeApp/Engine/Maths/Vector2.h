#pragma once
#include <iostream>
#include <cassert>
#include <cmath>

#include "../Utils/Utils.h"

class Vector2
{
public:
	Vector2() : Vector2(0, 0) {}
	Vector2(float px, float py) : x(x), y(py) {}

	static const Vector2 Zero;
	
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

	float x;
	float y;
};

