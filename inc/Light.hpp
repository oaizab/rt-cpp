#pragma once

#include "Tuple.hpp"
#include "Color.hpp"

class Light
{
	public:
		Light();
		Light(Tuple position, Color intensity);
		Light(Tuple position, Color color, float ratio);
		Light(const Light &l);
		~Light();
		Light &operator=(const Light &l);
		Light &setRatio(float ratio);

		Tuple position;
		Color color;
		float ratio;
		Color intensity;
};
