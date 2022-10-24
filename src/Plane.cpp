#include "Plane.hpp"
#include "utils.hpp"


Plane::Plane(): Shape()
{
	normal = Tuple::vector(0, 1, 0);
}

Plane::~Plane()
{
}

Tuple Plane::normalAt(const Tuple& point)
{
	(void) point;
	Tuple worldNormal = inverse().transpose() * normal;
	worldNormal.w = 0;
	return worldNormal.normalize();
}

Intersections Plane::intersect(Ray const &r)
{
	Ray ray = r.transform(inverse());
	if (feq(ray.direction.y, 0))
		return Intersections();
	Intersections xs;
	float t = -ray.origin.y / ray.direction.y;
	xs.add(Intersection(t, this));
	xs.add(Intersection(t, this));
	return xs;
}
