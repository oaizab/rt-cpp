#include "Sphere.hpp"
#include "Tuple.hpp"
#include <cmath>
#include "Intersections.hpp"

int Sphere::_count = 0;
Sphere Sphere::nothing = Sphere();

Sphere::Sphere() : _transform(Matrix::identity(4))
{
	_id = _count++;
}

Sphere::Sphere(const Sphere &src) : _transform(src._transform)
{
	*this = src;
}

Sphere::~Sphere()
{
}

Sphere &Sphere::operator=(Sphere const &rhs)
{
	if (this != &rhs)
	{
		_id = rhs._id;
		_transform = rhs._transform;
		_material = rhs._material;
	}
	return *this;
}

std::ostream &operator<<(std::ostream &o, Sphere const &i)
{
	o << "Sphere " << i.getId();
	return o;
}

bool Sphere::operator==(Sphere const &rhs) const
{
	return _id == rhs._id;
}

int Sphere::getId() const
{
	return _id;
}

Intersections Sphere::intersect(Ray const &r) const
{
	Intersections xs;
	Ray ray = r.transform(_transform.inverse());
	Tuple sphere_to_ray = ray.getOrigin() - Tuple::point(0, 0, 0);
	float a = ray.getDirection().dot(ray.getDirection());
	float b = 2 * ray.getDirection().dot(sphere_to_ray);
	float c = sphere_to_ray.dot(sphere_to_ray) - 1;
	float discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return xs;
	xs.add(Intersection((-b - sqrt(discriminant)) / (2 * a), *this));
	xs.add(Intersection((-b + sqrt(discriminant)) / (2 * a), *this));
	return xs;
}

Matrix Sphere::getTransform() const
{
	return _transform;
}

void Sphere::setTransform(Matrix const &m)
{
	_transform = m;
}

void Sphere::addTransform(Matrix const &m)
{
	_transform = m * _transform;
}

Tuple Sphere::normalAt(Tuple const p) const
{
	Tuple object_point = _transform.inverse() * p;
	Tuple object_normal = object_point - Tuple::point(0, 0, 0);
	Tuple world_normal = _transform.inverse().transpose() * object_normal;
	world_normal.setW(0);
	return world_normal.normalize();
}

// Material Sphere::getMaterial() const
// {
// 	return _material;
// }

Material &Sphere::getMaterial()
{
	return _material;
}

void Sphere::setMaterial(Material const &m)
{
	_material = m;
}
