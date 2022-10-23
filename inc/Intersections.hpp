#pragma once

#include "Intersection.hpp"
#include <vector>

class Intersection;

class Intersections
{
	public:
		Intersections();
		Intersections(Intersection const &i1, Intersection const &i2);
		Intersections(Intersection const &src);
		~Intersections();


		Intersection &operator[](int i);
		void add(Intersection const &i);
		void add(Intersections const &i);
		Intersection *hit();

		int count;
		std::vector<Intersection> intersections;
};