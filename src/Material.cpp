#include "Material.hpp"
#include <cmath>
#include <vector>
#include <algorithm>
#include "utils.hpp"
#include "Shape.hpp"

Material::Material()
{
	color = Color(1, 1, 1);
	ambient = 0.1;
	diffuse = 0.9;
	specular = 0.9;
	shininess = 200.0;
	pattern = false;
}

Material::Material(Color color, float ambient, float diffuse, float specular, float shininess):
	color(color), ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess), \
	pattern(false)
{
}

Material::Material(const Material &m)
{
	*this = m;
}

Material::~Material()
{
}

Material &Material::operator=(const Material &m)
{
	if (this != &m)
	{
		color = m.color;
		ambient = m.ambient;
		diffuse = m.diffuse;
		specular = m.specular;
		shininess = m.shininess;
		pattern = m.pattern;
		checker = m.checker;
	}
	return *this;
}

Color Material::lighting(Light const &light, Shape &object, Tuple const &position, Tuple const &eye, Tuple const &normal, bool in_shadow)
{
	Color c;
	if (object.material.pattern)
	{
		UV uv = object.uvAt(position);
		c = checker->pattern_at(uv.u, uv.v);
	}
	else
		c = color;
	Color effective_color = c * light.intensity;
	Color ambient_color = effective_color * ambient;
	if (in_shadow)
		return ambient_color;
	Tuple lightv = (light.position - position).normalize();
	float light_dot_normal = lightv.dot(normal);
	Color diffuse_color;
	Color specular_color;
	if (light_dot_normal < 0.0f)
	{
		diffuse_color = Color(0, 0, 0);
		specular_color = Color(0, 0, 0);
	}
	else
	{
		diffuse_color = effective_color * diffuse * light_dot_normal;
		Tuple reflectv = (-lightv).reflect(normal);
		float reflect_dot_eye = reflectv.dot(eye);
		if (reflect_dot_eye <= 0.0f)
			specular_color = Color(0, 0, 0);
		else
		{
			float factor = pow(reflect_dot_eye, shininess);
			specular_color = light.intensity * specular * factor;
		}
	}
	return ambient_color + diffuse_color + specular_color;
}

void Material::setPattern(Pattern const &c)
{
	pattern = true;
	checker = (Pattern *) &c;
}
