#include "Intersection.hpp"
#include "utils.hpp"

Intersection::Intersection()
{
}

Intersection::Intersection(float t, Sphere const &sphere) : _t(t), _object(sphere)
{
}

Intersection::Intersection(const Intersection &src)
{
	*this = src;
}

Intersection::~Intersection()
{
}

Intersection &Intersection::operator=(Intersection const &rhs)
{
	if (this != &rhs)
	{
		_t = rhs._t;
		_object = rhs._object;
	}
	return *this;
}

std::ostream &operator<<(std::ostream &o, Intersection const &i)
{
	o << "Intersection " << i.getT() << " " << i.getObject();
	return o;
}

float Intersection::getT() const
{
	return _t;
}

Sphere Intersection::getObject() const
{
	return _object;
}

bool Intersection::operator==(Intersection const &rhs) const
{
	return feq(_t, rhs._t) && _object == rhs._object;
}

Intersection Intersection::nothing()
{
	return Intersection(-1, Sphere::nothing);
}

bool Intersection::operator!=(Intersection const &rhs) const
{
	return !(*this == rhs);
}
