#pragma once
#include <iostream>
#include <cmath>

class Vector2D
{
public:
	float x;
	float y;

	Vector2D();
	Vector2D(float x, float y);

	Vector2D& Add(const Vector2D& vector);
	Vector2D& Subtract(const Vector2D& vector);
	Vector2D& Multiply(const Vector2D& vector);
	Vector2D& Divide(const Vector2D& vector);
	float DotProduct(const Vector2D& vector) const;

	friend Vector2D& operator+(Vector2D& vectorOne, Vector2D& vectorTwo);
	friend Vector2D& operator-(Vector2D& vectorOne, Vector2D& vectorTwo);
	friend Vector2D& operator*(Vector2D& vectorOne, Vector2D& vectorTwo);
	friend Vector2D& operator/(Vector2D& vectorOne, Vector2D& vectorTwo);

	Vector2D& operator+=(const Vector2D& vector);
	Vector2D& operator-=(const Vector2D& vector);
	Vector2D& operator*=(const Vector2D& vector);
	Vector2D& operator/=(const Vector2D& vector);

	Vector2D operator*(const int& i);
	Vector2D Zero();
	Vector2D& Normalize();

	friend std::ostream& operator<<(std::ostream& stream, const Vector2D& vector);

};

