#include "Shape.hpp"
#include "Intersections.hpp"

int Shape::count = 0;

Shape::Shape(): transform(Matrix::identity()), _inverse(Matrix::identity())
{
	id = count++;
	inv = true;
}

Shape::~Shape()
{
}

Matrix &Shape::inverse()
{
	if (!inv)
	{
		_inverse = transform.inverse();
		inv = true;
	}
	return _inverse;
}

void Shape::setTransform(Matrix const &m)
{
	transform = m;
	inv = false;
}

void Shape::addTransform(Matrix const &m)
{
	transform = m * transform;
	inv = false;
}