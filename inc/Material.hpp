#pragma once

#include "Tuple.hpp"
#include "Color.hpp"
#include "Light.hpp"
#include <vector>

class Material
{
	public:
		Material();
		Material(Color color, float ambient, float diffuse, float specular, float shininess);
		Material(const Material &m);
		~Material();
		Material &operator=(const Material &m);

		Color lighting(Light const &light, Tuple const &position, Tuple const &eye, Tuple const &normal, bool in_shadow);

		Color color;
		float ambient;
		float diffuse;
		float specular;
		float shininess;
};
