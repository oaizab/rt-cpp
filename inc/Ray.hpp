#pragma once

#include "Tuple.hpp"
#include "Matrix.hpp"

class Ray
{
	public:
		Ray();
		Ray(Tuple const &origin, Tuple const &direction);
		Ray(Ray const &src);
		~Ray();

		Ray &operator=(Ray const &rhs);
		bool operator==(Ray const &rhs) const;

		Tuple position(float t) const;

		Ray transform(Matrix const &m) const;

		Tuple origin;
		Tuple direction;
};
