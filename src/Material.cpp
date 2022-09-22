#include "Material.hpp"
#include <cmath>

Material::Material()
{
	_color = Color(1, 1, 1);
	_ambient = 0.1;
	_diffuse = 0.9;
	_specular = 0.9;
	_shininess = 200.0;
}

Material::Material(const Material &src)
{
	*this = src;
}

Material::~Material()
{
}

Material &Material::operator=(Material const &rhs)
{
	if (this != &rhs)
	{
		_color = rhs._color;
		_ambient = rhs._ambient;
		_diffuse = rhs._diffuse;
		_specular = rhs._specular;
		_shininess = rhs._shininess;
	}
	return *this;
}

std::ostream &operator<<(std::ostream &o, Material const &i)
{
	o << "Material(" << i.getColor() << ", " << i.getAmbient() << ", " << i.getDiffuse() << ", " << i.getSpecular() << ", " << i.getShininess() << ")";
	return o;
}

Color Material::getColor() const
{
	return _color;
}

float Material::getAmbient() const
{
	return _ambient;
}

float Material::getDiffuse() const
{
	return _diffuse;
}

float Material::getSpecular() const
{
	return _specular;
}

float Material::getShininess() const
{
	return _shininess;
}

void Material::setColor(Color const &color)
{
	_color = color;
}

void Material::setAmbient(float ambient)
{
	_ambient = ambient;
}

void Material::setDiffuse(float diffuse)
{
	_diffuse = diffuse;
}

void Material::setSpecular(float specular)
{
	_specular = specular;
}

void Material::setShininess(float shininess)
{
	_shininess = shininess;
}

Color Material::lighting(Light const &light, Tuple const &position, Tuple const &eye, Tuple const &normal) const
{
	Color effectiveColor = _color * light.getIntensity();
	Tuple lightVector = (light.getPosition() - position).normalize();
	float lightDotNormal = lightVector.dot(normal);
	Color ambient = effectiveColor * _ambient;
	Color diffuse;
	Color specular;
	if (lightDotNormal < 0)
	{
		diffuse = Color(0, 0, 0);
		specular = Color(0, 0, 0);
	}
	else
	{
		diffuse = effectiveColor * _diffuse * lightDotNormal;
		Tuple reflectVector = (-lightVector).reflect(normal);
		float reflectDotEye = reflectVector.dot(eye);
		if (reflectDotEye <= 0)
		{
			specular = Color(0, 0, 0);
		}
		else
		{
			float factor = pow(reflectDotEye, _shininess);
			specular = light.getIntensity() * _specular * factor;
		}
	}
	return ambient + diffuse + specular;
}
