#include "Tuple.hpp"
#include "utils.hpp"
#include <cmath>
#include <iomanip>

Tuple::Tuple()
{
	_x = 0;
	_y = 0;
	_z = 0;
	_w = 0;
}

Tuple::Tuple(const Tuple &src)
{
	*this = src;
}

Tuple::~Tuple()
{
}

Tuple &Tuple::operator=(Tuple const &rhs)
{
	if (this != &rhs)
	{
		_x = rhs._x;
		_y = rhs._y;
		_z = rhs._z;
		_w = rhs._w;
	}
	return *this;
}

std::ostream &operator<<(std::ostream &o, Tuple const &i)
{
	o << "Tuple(" << std::fixed << std::setprecision(5) << i.getX() << ", " << i.getY() << ", " << i.getZ() << ", " << i.getW() << ")";
	return o;
}

Tuple::Tuple(float x, float y, float z, float w)
{
	_x = x;
	_y = y;
	_z = z;
	_w = w;
}

bool Tuple::operator==(Tuple const &rhs) const
{
	return (feq(_x, rhs._x) && feq(_y, rhs._y) && feq(_z, rhs._z) && feq(_w, rhs._w));
}

Tuple Tuple::operator+(Tuple const &rhs) const
{
	Tuple t;
	t._x = _x + rhs._x;
	t._y = _y + rhs._y;
	t._z = _z + rhs._z;
	t._w = _w + rhs._w;
	if (feq(t._w, 2))
		t._w = 1;
	return t;
}

Tuple Tuple::operator-(Tuple const &rhs) const
{
	Tuple t;
	t._x = _x - rhs._x;
	t._y = _y - rhs._y;
	t._z = _z - rhs._z;
	t._w = _w - rhs._w;
	if (feq(t._w, -1))
		t._w = 1;
	return t;
}

Tuple Tuple::operator-() const
{
	Tuple t;
	t._x = -_x;
	t._y = -_y;
	t._z = -_z;
	t._w = -_w;
	return t;
}

Tuple Tuple::operator*(float const &rhs) const
{
	Tuple t;
	t._x = _x * rhs;
	t._y = _y * rhs;
	t._z = _z * rhs;
	t._w = _w * rhs;
	return t;
}

Tuple Tuple::operator/(float const &rhs) const
{
	Tuple t;
	t._x = _x / rhs;
	t._y = _y / rhs;
	t._z = _z / rhs;
	t._w = _w / rhs;
	return t;
}

float Tuple::magnitude() const
{
	return sqrt(_x * _x + _y * _y + _z * _z + _w * _w);
}

Tuple Tuple::normalize() const
{
	float mag = magnitude();
	Tuple t;
	t._x = _x / mag;
	t._y = _y / mag;
	t._z = _z / mag;
	t._w = _w / mag;
	return t;
}

float Tuple::dot(Tuple const &rhs) const
{
	return _x * rhs._x + _y * rhs._y + _z * rhs._z + _w * rhs._w;
}

Tuple Tuple::cross(Tuple const &rhs) const
{
	Tuple t;
	t._x = _y * rhs._z - _z * rhs._y;
	t._y = _z * rhs._x - _x * rhs._z;
	t._z = _x * rhs._y - _y * rhs._x;
	t._w = 0;
	return t;
}

float Tuple::getX() const
{
	return _x;
}

float Tuple::getY() const
{
	return _y;
}

float Tuple::getZ() const
{
	return _z;
}

float Tuple::getW() const
{
	return _w;
}

void Tuple::setX(float x)
{
	_x = x;
}

void Tuple::setY(float y)
{
	_y = y;
}

void Tuple::setZ(float z)
{
	_z = z;
}

void Tuple::setW(float w)
{
	_w = w;
}

Tuple Tuple::point(float x, float y, float z)
{
	Tuple t(x, y, z, 1);
	return t;
}

Tuple Tuple::vector(float x, float y, float z)
{
	Tuple t(x, y, z, 0);
	return t;
}
