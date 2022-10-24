#include "Cylinder.hpp"
#include "utils.hpp"
#include <cmath>

Cylinder::Cylinder(): Shape()
{
	min = 0;
	max = 1;
}

Cylinder::Cylinder(float min, float max): Shape()
{
	this->min = min;
	this->max = max;
}

Cylinder::~Cylinder()
{
}

Tuple Cylinder::normalAt(const Tuple& point)
{
	Tuple objectPoint = inverse() * point;
	float dist = objectPoint.x * objectPoint.x + objectPoint.z * objectPoint.z;
	Tuple objectNormal;
	if (dist < 1 && objectPoint.y >= max - 0.00001)
		objectNormal = Tuple::vector(0, 1, 0);
	else if (dist < 1 && objectPoint.y <= min + 0.00001)
		objectNormal = Tuple::vector(0, -1, 0);
	else
		objectNormal = Tuple::vector(objectPoint.x, 0, objectPoint.z);
	Tuple worldNormal = inverse().transpose() * objectNormal;
	worldNormal.w = 0;
	return worldNormal.normalize();
}

Intersections Cylinder::intersect(Ray const &r)
{
	Ray ray = r.transform(inverse());
	float a = ray.direction.x * ray.direction.x + ray.direction.z * ray.direction.z;
	if (feq(a, 0))
	{
		return intersectCaps(ray);
	}
	float b = 2 * ray.origin.x * ray.direction.x + 2 * ray.origin.z * ray.direction.z;
	float c = ray.origin.x * ray.origin.x + ray.origin.z * ray.origin.z - 1;
	float disc = b * b - 4 * a * c;
	if (disc < 0)
	{
		return Intersections();
	}
	float sqrt_disc = sqrt(disc);
	float t0 = (-b - sqrt_disc) / (2 * a);
	float t1 = (-b + sqrt_disc) / (2 * a);
	float y0 = ray.origin.y + ray.direction.y * t0;
	float y1 = ray.origin.y + ray.direction.y * t1;
	Intersections xs;
	if (y0 > min && y0 < max)
	{
		xs.add(Intersection(t0, this));
	}
	if (y1 > min && y1 < max)
	{
		xs.add(Intersection(t1, this));
	}
	intersectCaps(ray, &xs);
	if (xs.count == 1)
	{
		xs.add(xs[0]);
	}
	return Intersections(xs);
}

bool Cylinder::checkCap(Ray const &r, float t)
{
	float x = r.origin.x + t * r.direction.x;
	float z = r.origin.z + t * r.direction.z;
	return (x * x + z * z) <= 1;
}

Intersections Cylinder::intersectCaps(Ray const &r, Intersections *xs)
{
	if (feq(r.direction.y, 0))
	{
		return Intersections();
	}
	Intersections xss;
	float t = (min - r.origin.y) / r.direction.y;
	if (checkCap(r, t))
	{
		if (xs)
		{
			xs->add(Intersection(t, this));
		}
		else
		{
			xss.add(Intersection(t, this));
		}
	}
	t = (max - r.origin.y) / r.direction.y;
	if (checkCap(r, t))
	{
		if (xs)
		{
			xs->add(Intersection(t, this));
		}
		else
		{
			xss.add(Intersection(t, this));
		}
	}
	return xss;
}
