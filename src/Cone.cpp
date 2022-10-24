#include "Cone.hpp"
#include "utils.hpp"
#include <cmath>

Cone::Cone(): Shape()
{
	min = 0;
	max = 1;
}

Cone::Cone(float min, float max): Shape()
{
	this->min = min;
	this->max = max;
}

Cone::~Cone()
{
}

Tuple Cone::normalAt(const Tuple& point)
{
	Tuple objectPoint = inverse() * point;
	float dist = objectPoint.x * objectPoint.x + objectPoint.z * objectPoint.z;
	Tuple objectNormal;
	if (dist < 1 && objectPoint.y >= max - 0.00001)
		objectNormal = Tuple::vector(0, 1, 0);
	else if (dist < 1 && objectPoint.y <= min + 0.00001)
		objectNormal = Tuple::vector(0, -1, 0);
	else
	{
		float y = sqrt(objectPoint.x * objectPoint.x + objectPoint.z * objectPoint.z);
		if (objectPoint.y > 0)
			y = -y;
		objectNormal = Tuple::vector(objectPoint.x, y, objectPoint.z);
	}
	Tuple worldNormal = inverse().transpose() * objectNormal;
	worldNormal.w = 0;
	return worldNormal.normalize();
}

Intersections Cone::intersect(Ray const &r)
{
	Ray ray = r.transform(inverse());
	float a = ray.direction.x * ray.direction.x - ray.direction.y * ray.direction.y + ray.direction.z * ray.direction.z;
	float b = 2 * ray.origin.x * ray.direction.x - 2 * ray.origin.y * ray.direction.y + 2 * ray.origin.z * ray.direction.z;
	if (feq(a, 0) and feq(b, 0))
	{
		return intersectCaps(ray);
	}
	float c = ray.origin.x * ray.origin.x + ray.origin.z * ray.origin.z - ray.origin.y * ray.origin.y;
	if (feq(a, 0))
	{
		float t = -c/(2 * b);
		return Intersections(Intersection(t, this), Intersection(t, this));
	}
	float disc = b * b - 4 * a * c;
	if (disc < 0)
	{
		return Intersections();
	}
	float sqrt_disc = sqrt(disc);
	float t0 = (-b - sqrt_disc) / (2 * a);
	float t1 = (-b + sqrt_disc) / (2 * a);
	// if (t0 > t1)
	// {
	// 	float tmp = t0;
	// 	t0 = t1;
	// 	t1 = tmp;
	// }
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
	// if (xs.count == 1)
	// {
	// 	xs.add(xs[0]);
	// }
	return Intersections(xs);
}

bool Cone::checkCap(Ray const &r, float t, float y)
{
	float x = r.origin.x + t * r.direction.x;
	float z = r.origin.z + t * r.direction.z;
	return (x * x + z * z) <= (y*y + 0.0001);
}

Intersections Cone::intersectCaps(Ray const &r, Intersections *xs)
{
	if (feq(r.direction.y, 0))
	{
		return Intersections();
	}
	Intersections xss;
	float t = (min - r.origin.y) / r.direction.y;
	if (checkCap(r, t, min))
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
	if (checkCap(r, t, max))
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

UV Cone::uvAt(Tuple const &point)
{
	Tuple objectPoint = inverse() * point;	
	float x = objectPoint.x;
	float y = objectPoint.y;
	float z = objectPoint.z;
	float theta = atan2(x, z);
	float u = 1 - (theta + M_PI) / (2 * M_PI);
	float v = y - (int)y;
	return UV(u, v);
}
// UV Cylinder::uvAt(Tuple const &point)
// {
// 	Tuple objectPoint = inverse() * point;
	
// 		float theta = atan2(objectPoint.x, objectPoint.z);
// 		float u = 1 - (theta + M_PI) / (2 * M_PI);
// 		float v = objectPoint.y - floor(objectPoint.y);
// 		return UV(u, v);
// }
