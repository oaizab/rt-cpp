#include "Ray.hpp"

Ray::Ray(): origin(Tuple::point(0, 0, 0)), direction(Tuple::vector(0, 0, 0))
{
}

Ray::Ray(Tuple const &origin, Tuple const &direction):
	origin(origin), direction(direction)
{
}

Ray::Ray(Ray const &src): origin(src.origin), direction(src.direction)
{
}

Ray::~Ray()
{
}

Ray &Ray::operator=(Ray const &rhs)
{
	if (this != &rhs)
	{
		origin = rhs.origin;
		direction = rhs.direction;
	}
	return *this;
}

bool Ray::operator==(Ray const &rhs) const
{
	return origin == rhs.origin && direction == rhs.direction;
}

Tuple Ray::position(float t) const
{
	return origin + direction * t;
}

Ray Ray::transform(Matrix const &m) const
{
	return Ray(m * origin, m * direction);
}
