#pragma once

#include "Tuple.hpp"
#include "Shape.hpp"

class Computation
{
	public:
		Computation();
		Computation(Computation const &src);
		~Computation();

		float t;
		Shape *object;
		Tuple point;
		Tuple eyev;
		Tuple normalv;
		bool inside;
		Tuple over_point;
};
