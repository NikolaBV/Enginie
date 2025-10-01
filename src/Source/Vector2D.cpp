#include "../Header/Vector2D.h"

Vector2D::Vector2D() {
	x = 0;
	y = 0;
}
Vector2D::Vector2D(float x, float y) {
	this->x = x;
	this->y = y;
}

Vector2D& Vector2D::Add(const Vector2D& vector) {
	this->x += vector.x;
	this->y += vector.y;

	return *this;
}

Vector2D& Vector2D::Subtract(const Vector2D& vector) {
	this->x -= vector.x;
	this->y -= vector.y;

	return *this;
}

Vector2D& Vector2D::Multiply(const Vector2D& vector) {
	this->x *= vector.x;
	this->y *= vector.y;

	return *this;
}

Vector2D& Vector2D::Divide(const Vector2D& vector) {
	this->x /= vector.x;
	this->y /= vector.y;

	return *this;
}

Vector2D& Vector2D::Reflection(Vector2D& normalVector)
{
	float dotProduct = normalVector.DotProduct(*this);

	Vector2D normalVectorTimesDot;
	normalVectorTimesDot.x = normalVector.x * dotProduct;
	normalVectorTimesDot.y = normalVector.y * dotProduct;

	Vector2D twoProj;
	twoProj.x = normalVectorTimesDot.x * 2.0f;
	twoProj.y = normalVectorTimesDot.y * 2.0f;

	this->x = this->x - twoProj.x;
	this->y = this->y - twoProj.y;

	this->Normalize();
	return *this;
}

float Vector2D::DotProduct(const Vector2D& vector) const
{
    return this->x * vector.x + this->y * vector.y;
}    

Vector2D& operator+(Vector2D& vectorOne, Vector2D& vectorTwo) {
	return vectorOne.Add(vectorTwo);
}

Vector2D& operator-(Vector2D& vectorOne, Vector2D& vectorTwo) {
	return vectorOne.Subtract(vectorTwo);
}

Vector2D& operator*(Vector2D& vectorOne, Vector2D& vectorTwo) {
	return vectorOne.Multiply(vectorTwo);
}

Vector2D& operator/(Vector2D& vectorOne, Vector2D& vectorTwo) {
	return vectorOne.Divide(vectorTwo);
}

Vector2D& Vector2D::operator+=(const Vector2D& vector) {
	return this->Add(vector);
}

Vector2D& Vector2D::operator-=(const Vector2D& vector) {
	return this->Subtract(vector);
}

Vector2D& Vector2D::operator*=(const Vector2D& vector) {
	return this->Multiply(vector);
}
Vector2D& Vector2D::operator/=(const Vector2D& vector) {
	return this->Divide(vector);
}

std::ostream& operator<<(std::ostream& stream, const Vector2D& vector) {
	stream << "Vector2D{" << vector.x << ", " << vector.y << "}";
	return stream;
}

Vector2D Vector2D::operator*(const int& i) {
	this->x *= i;
	this->y *= i;
	return *this;
}

Vector2D Vector2D::Zero() {
	this->x = 0;
	this->y = 0;
	return *this;
}

Vector2D& Vector2D::Normalize()
{
	// TODO: insert return statement here
	float length = sqrt((this->x * this->x) + (this->y * this->y));
	this->x /= length;
	this->y /= length;
	return *this;
}
