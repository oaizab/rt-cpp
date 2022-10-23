#include "Intersection.hpp"

Intersection::Intersection(float t, Shape *shape)
{
	this->t = t;
	this->object = shape;
}

Intersection::Intersection(float t, Shape &shape)
{
	this->t = t;
	this->object = &shape;
}

Intersection::Intersection(Intersection const &src)
{
	*this = src;
}

Computation Intersection::prepareComputation(Ray const &ray)
{
	Computation comp;
	comp.t = t;
	comp.object = object;
	comp.point = ray.position(t);
	comp.eyev = -ray.direction;
	comp.normalv = object->normalAt(comp.point);
	if (comp.normalv.dot(comp.eyev) < 0)
	{
		comp.inside = true;
		comp.normalv = -comp.normalv;
	}
	else
		comp.inside = false;
	comp.over_point = comp.point + comp.normalv * 0.005;
	return comp;
}
