#include "Ray.hpp"

Ray::Ray()
{
	_origin = Tuple::point(0, 0, 0);
	_direction = Tuple::vector(0, 0, 0);
}

Ray::Ray(Tuple origin, Tuple direction)
{
	_origin = origin;
	_direction = direction;
}

Ray::Ray(const Ray &src)
{
	*this = src;
}

Ray::~Ray()
{
}

Ray &Ray::operator=(Ray const &rhs)
{
	if (this != &rhs)
	{
		_origin = rhs.getOrigin();
		_direction = rhs.getDirection();
	}
	return *this;
}

std::ostream &operator<<(std::ostream &o, Ray const &i)
{
	o << "Ray(" << i.getOrigin() << ", " << i.getDirection() << ")";
	return o;
}

Tuple Ray::getOrigin() const
{
	return _origin;
}

Tuple Ray::getDirection() const
{
	return _direction;
}

void Ray::setOrigin(Tuple &origin)
{
	_origin = origin;
}

void Ray::setDirection(Tuple &direction)
{
	_direction = direction;
}

bool Ray::operator==(Ray const &rhs) const
{
	return (_origin == rhs.getOrigin() && _direction == rhs.getDirection());
}

Tuple Ray::position(float t) const
{
	return _origin + _direction * t;
}

Ray Ray::transform(Matrix const &m) const
{
	return Ray(m * _origin, m * _direction);
}
