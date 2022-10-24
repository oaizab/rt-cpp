#pragma once

#include "Tuple.hpp"
#include "Color.hpp"
#include "Light.hpp"
#include <vector>
#include "Checker.hpp"

class Shape;
class Material
{
	public:
		Material();
		Material(Color color, float ambient, float diffuse, float specular, float shininess);
		Material(const Material &m);
		~Material();
		Material &operator=(const Material &m);

		Color lighting(Light const &light, Shape &object, Tuple const &position, Tuple const &eye, Tuple const &normal, bool in_shadow);
		void setPattern(Pattern const &c);

		Color color;
		float ambient;
		float diffuse;
		float specular;
		float shininess;
		bool pattern;
		Pattern *checker;
};
