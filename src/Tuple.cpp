#include "Tuple.hpp"
#include "utils.hpp"
#include <cmath>

Tuple::Tuple() : x(0), y(0), z(0), w(0)
{
}

Tuple::Tuple(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
{
}

Tuple::Tuple(Tuple const &t) : x(t.x), y(t.y), z(t.z), w(t.w)
{
}

Tuple &Tuple::operator=(Tuple const &rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	w = rhs.w;
	return *this;
}

bool Tuple::operator==(Tuple const &t) const
{
	return feq(x, t.x) && feq(y, t.y) && feq(z, t.z) && feq(w, t.w);
}

bool Tuple::operator!=(Tuple const &t) const
{
	return !(*this == t);
}

Tuple Tuple::operator+(Tuple const &t) const
{
	return Tuple(x + t.x, y + t.y, z + t.z, w + t.w);
}

Tuple Tuple::operator-(Tuple const &t) const
{
	return Tuple(x - t.x, y - t.y, z - t.z, w - t.w);
}

Tuple Tuple::operator-() const
{
	return Tuple(-x, -y, -z, -w);
}

Tuple Tuple::operator*(float f) const
{
	return Tuple(x * f, y * f, z * f, w * f);
}

Tuple Tuple::operator/(float f) const
{
	return Tuple(x / f, y / f, z / f, w / f);
}

float Tuple::operator*(Tuple const &t) const
{
	return x * t.x + y * t.y + z * t.z + w * t.w;
}

float Tuple::magnitude() const
{
	return sqrt(x * x + y * y + z * z + w * w);
}

Tuple Tuple::normalize() const
{
	return *this / magnitude();
}

float Tuple::dot(Tuple const &t) const
{
	return *this * t;
}

Tuple Tuple::cross(Tuple const &t) const
{
	return Tuple(y * t.z - z * t.y, z * t.x - x * t.z, x * t.y - y * t.x, 0);
}

Tuple Tuple::reflect(Tuple const &normal) const
{
	return *this - normal * 2 * (*this * normal);
}

Tuple Tuple::point(float x, float y, float z)
{
	return Tuple(x, y, z, 1);
}

Tuple Tuple::vector(float x, float y, float z)
{
	return Tuple(x, y, z, 0);
}
