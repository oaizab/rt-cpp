#pragma once

#include "Shape.hpp"
#include "Computation.hpp"

class Intersection
{
	public:
		Intersection();
		Intersection(float t, Shape *shape);
		Intersection(float t, Shape &shape);
		Intersection(Intersection const &src);

		Computation prepareComputation(Ray const &ray);
		Shape* object;
		float t;
};