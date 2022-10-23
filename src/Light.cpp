#include "Light.hpp"
#include <iostream>

Light::Light(): position(Tuple::point(0, 0, 0)), color(Color(1, 1, 1)), ratio(1), intensity(Color(1, 1, 1))
{
}

Light::Light(Tuple position, Color intensity):
	position(position), color(intensity), ratio(1), intensity(intensity)
{
}

Light::Light(Tuple position, Color color, float ratio):
	position(position), color(color), ratio(ratio), intensity(color * ratio)
{
}

Light::Light(const Light &l):
	position(l.position), color(l.color), ratio(l.ratio), intensity(l.intensity)
{
}

Light::~Light()
{
}

Light &Light::operator=(const Light &l)
{
	position = l.position;
	intensity = l.intensity;
	ratio = l.ratio;
	color = l.color;
	return *this;
}

Light &Light::setRatio(float ratio)
{
	this->ratio = ratio;
	intensity = color * ratio;
	return *this;
}
