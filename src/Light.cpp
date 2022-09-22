#include "Light.hpp"

Light::Light()
{
	_position = Tuple::point(0, 0, 0);
	_intensity = Color(1, 1, 1);
}

Light::Light(Tuple const position, Color const intensity)
{
	_position = position;
	_intensity = intensity;
}

Light::Light(const Light &src)
{
	*this = src;
}

Light::~Light()
{
}

Light &Light::operator=(Light const &rhs)
{
	if (this != &rhs)
	{
		_position = rhs._position;
		_intensity = rhs._intensity;
	}
	return *this;
}

std::ostream &operator<<(std::ostream &o, Light const &i)
{
	o << "Light(" << i.getPosition() << ", " << i.getIntensity() << ")";
	return o;
}

Tuple Light::getPosition() const
{
	return _position;
}

Color Light::getIntensity() const
{
	return _intensity;
}

void Light::setPosition(Tuple const &position)
{
	_position = position;
}

void Light::setIntensity(Color const &intensity)
{
	_intensity = intensity;
}
