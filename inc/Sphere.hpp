#pragma once

#include "Shape.hpp"

class Sphere : public Shape
{
	public:
		Sphere();
		virtual ~Sphere();

		virtual Intersections intersect(Ray const &ray);
		virtual Tuple normalAt(Tuple const &point);
};