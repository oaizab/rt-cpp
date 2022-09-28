#pragma once

#include <iostream>
#include <string>
#include "Color.hpp"
#include "Tuple.hpp"
#include "Light.hpp"

class Material
{

	public:

		Material();
		Material(Material const &src);
		~Material();

		Material &operator=(Material const &rhs);

		Color getColor() const;
		float getAmbient() const;
		float getDiffuse() const;
		float getSpecular() const;
		float getShininess() const;

		void setColor(Color const &color);
		void setAmbient(float ambient);
		void setDiffuse(float diffuse);
		void setSpecular(float specular);
		void setShininess(float shininess);

		Color lighting(Light const &light, Tuple const &position, Tuple const &eye, Tuple const &normal) const;

	private:

		Color _color;
		float _ambient;
		float _diffuse;
		float _specular;
		float _shininess;

};

std::ostream &operator<<(std::ostream &o, Material const &i);
