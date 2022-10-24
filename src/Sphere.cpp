#include "Sphere.hpp"
#include <cmath>
#include "Intersections.hpp"

Sphere::Sphere(): Shape()
{
}

Sphere::~Sphere()
{
}

Intersections Sphere::intersect(Ray const &r)
{
	Ray ray = r.transform(inverse());
	Tuple sphereToRay = ray.origin - Tuple::point(0, 0, 0);
	float a = ray.direction.dot(ray.direction);
	float b = 2 * ray.direction.dot(sphereToRay);
	float c = sphereToRay.dot(sphereToRay) - 1;
	float discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return Intersections();
	float sqrtD = sqrt(discriminant);
	float t1 = (-b - sqrtD) / (2 * a);
	float t2 = (-b + sqrtD) / (2 * a);
	return Intersections(Intersection(t1, this), Intersection(t2, this));
}

Tuple Sphere::normalAt(Tuple const &point)
{
	Tuple objectPoint = inverse() * point;
	Tuple objectNormal = objectPoint - Tuple::point(0, 0, 0);
	Tuple worldNormal = inverse().transpose() * objectNormal;
	worldNormal.w = 0;
	return worldNormal.normalize();
}

UV Sphere::uvAt(Tuple const &point)
{
	// Tuple objectPoint = point;
	Tuple objectPoint = inverse() * point;
	float theta = atan2(objectPoint.x, objectPoint.z);
	Tuple vec = Tuple::vector(objectPoint.x, objectPoint.y, objectPoint.z);
	float phi = acos(objectPoint.y / vec.magnitude());
	return UV(1 - (theta / (2 * M_PI) + 0.5), 1 - phi / M_PI);
}