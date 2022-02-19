#include "../PVP_SenoZaidimoPrototipas/Vectors.h"
#include <math.h>

Vector2 Vector2::up(.0, 1.0), Vector2::down(.0, -1.), Vector2::right(1.0, .0), Vector2::left(-1.0, .0), Vector2::zero(0,0);

Vector2::Vector2():x(0.), y(0.)
{
}

Vector2::Vector2(double X, double Y) : x(X), y(Y)
{
}

Vector2::~Vector2()
{
}

Vector2 Vector2::operator+(Vector2 foo)
{
	return Vector2(x + foo.x, y + foo.y);
}

Vector2 Vector2::operator-(Vector2 foo)
{
	return Vector2(x - foo.x, y - foo.y);
}

Vector2 Vector2::operator-()
{
	return Vector2(-x, -y);
}

Vector2 Vector2::operator*(double foo)
{
	return Vector2(x * foo, y * foo);
}

double Vector2::operator*(Vector2 foo)
{
	return x * foo.x + y * foo.y;
}

void Vector2::operator+=(Vector2 foo)
{
	x += foo.x;
	y += foo.y;
}

void Vector2::operator-=(Vector2 foo)
{
	x -= foo.x; 
	y -= foo.y;
}

bool Vector2::operator==(Vector2 foo)
{
	return x == foo.x && y == foo.y;
}

bool Vector2::operator!=(Vector2 foo)
{
	return x != foo.x || y != foo.y;
}

Vector2 Vector2::Normalize()
{
	Vector2 normalizedVec = *this;
	double magnitude = normalizedVec.Magnitude();
	normalizedVec.x /= magnitude;
	normalizedVec.y /= magnitude;
	return normalizedVec;
}

double Vector2::VectorAngle(Vector2 foo) // IN RADIANS
{
	return acos((*this * foo) / (Magnitude() * foo.Magnitude()));
}

double Vector2::Magnitude()
{
	return sqrt(x * x + y * y);
}

std::string Vector2::toString()
{
	int X = (int)x;
	int Y = (int)y;

	return std::to_string(X) + " " + std::to_string(Y);
}
