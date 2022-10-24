#pragma once

#include "Shape.hpp"
#include "Intersections.hpp"

class Cylinder: public Shape
{
	public:
		Cylinder();
		Cylinder(float min, float max);
		virtual ~Cylinder();

		virtual Tuple normalAt(const Tuple& point);
		virtual Intersections intersect(Ray const &r);
		virtual UV uvAt(Tuple const &point);

		bool checkCap(Ray const &r, float t);
		Intersections intersectCaps(Ray const &r, Intersections *xs = nullptr);

		float min;
		float max;
};