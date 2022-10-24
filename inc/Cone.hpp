#pragma once

#include "Shape.hpp"
#include "Intersections.hpp"

class Cone: public Shape
{
	public:
		Cone();
		Cone(float min, float max);
		virtual ~Cone();

		virtual Tuple normalAt(const Tuple& point);
		virtual Intersections intersect(Ray const &r);
		virtual UV uvAt(Tuple const &point);

		bool checkCap(Ray const &r, float t, float y);
		Intersections intersectCaps(Ray const &r, Intersections *xs = nullptr);

		float min;
		float max;
};