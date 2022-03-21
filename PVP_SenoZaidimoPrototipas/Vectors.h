#pragma once

#include <string>

# define PI           3.14159265358979323846  /* pi */
const static double Deg2Rad = (PI * 2.) / 360.;
const static double Rad2Deg = 360. / (PI * 2.);

enum class RandomVectorGenerationType
{
	Box = 0,
	Circle = 1
};

// Standartine 2D vektoriaus klase
class Vector2
{
public:
	static Vector2 up, down, right, left, zero;
	static Vector2 Random();
	static Vector2 Random(RandomVectorGenerationType genType);

	double x, y;

	Vector2();
	Vector2(double X, double Y);
	~Vector2();

	Vector2 operator +(Vector2 foo);
	Vector2 operator -(Vector2 foo);

	Vector2 operator -();

	Vector2 operator *(double foo);
	Vector2 operator /(double foo);

	double operator *(Vector2 foo);

	void operator +=(Vector2 foo);
	void operator -=(Vector2 foo);
	
	bool operator ==(Vector2 foo);
	bool operator !=(Vector2 foo);

	Vector2 Normalize();

	double VectorAngle(Vector2 foo);

	double Magnitude();

	std::string toString();
};