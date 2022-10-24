#pragma once

#include "Shape.hpp"
#include "Intersections.hpp"

class Plane : public Shape
{
	public:
		Plane();
		virtual ~Plane();

		virtual Tuple normalAt(const Tuple& point);
		virtual Intersections intersect(Ray const &r);

		Tuple normal;
};