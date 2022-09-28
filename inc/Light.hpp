#pragma once

#include <iostream>
#include <string>
#include "Tuple.hpp"
#include "Color.hpp"

class Light
{

	public:

		Light();
		Light(Tuple const position, Color const intensity);
		Light(Light const &src);
		~Light();

		Tuple getPosition() const;
		Color getIntensity() const;

		void setPosition(Tuple const &position);
		void setIntensity(Color const &intensity);

		Light &operator=(Light const &rhs);

	private:
	
		Tuple _position;
		Color _intensity;

};

std::ostream &operator<<(std::ostream &o, Light const &i);
