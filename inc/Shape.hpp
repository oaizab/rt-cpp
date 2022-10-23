#pragma once

#include "Ray.hpp"
#include "Matrix.hpp"
#include "Tuple.hpp"
#include "Material.hpp"

class Intersections; 

class Shape
{
	public:
		Shape();
		virtual ~Shape();

		virtual Intersections intersect(Ray const &ray) = 0;
		virtual Tuple normalAt(Tuple const &point) = 0;

		Matrix &inverse();
		void setTransform(Matrix const &m);
		void addTransform(Matrix const &m);

		static int count;
		int id;
		Matrix transform;
		Matrix _inverse;
		bool inv;
		Material material;
};
