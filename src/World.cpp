#include "World.hpp"
#include <iostream>
#include "Sphere.hpp"

World::World()
{
}

World::World(World const & src): objects(src.objects), lights(src.lights)
{
}

World::~World()
{
}

// World & World::operator=(World const & rhs)
// {
// 	if (this != &rhs)
// 	{
// 		lights = rhs.lights;
// 		objects = rhs.objects;
// 	}
// 	return *this;
// }

World World::defaultWorld()
{
	World w;
	w.lights.push_back(Light(Tuple::point(-10, 10, -10), Color(1, 1, 1)));
	Sphere s1;
	s1.material.color = Color(0.8, 1.0, 0.6);
	s1.material.diffuse = 0.7;
	s1.material.specular = 0.2;
	w.objects.push_back(&s1);
	Sphere s2;
	s2.setTransform(Matrix::scaling(0.5, 0.5, 0.5));
	w.objects.push_back(&s2);
	return w;
}

Intersections World::intersect_world(Ray r)
{
	Intersections xs;
	for (Shape *s : objects)
	{
		Intersections i = s->intersect(r);
		int j = 0;
		while (j < i.count)
		{
			xs.add(i[j]);
			j++;
		}
		// if (i.count > 0)
		// {
		// 	xs.add(i[0]);
		// 	xs.add(i[1]);
		// }
	}
	return xs;
}

Color World::shade_hit(Computation comp)
{
	Color c = Color(0, 0, 0);
	for (Light l : lights)
	{
		bool in_shadow = is_shadowed(comp.over_point, l);
		c = c + comp.object->material.lighting(l, comp.over_point, comp.eyev, comp.normalv, in_shadow);
	}
	return c;
}

Color World::color_at(Ray r)
{
	Intersections xs = intersect_world(r);
	Intersection *hit = xs.hit();
	if (hit == NULL)
		return Color(0, 0, 0);
	Computation comp = hit->prepareComputation(r);
	return shade_hit(comp);
}

bool World::is_shadowed(Tuple point, Light &light)
{
	Tuple v = light.position - point;
	float distance = v.magnitude();
	Tuple direction = v.normalize();
	Ray r = Ray(point, direction);
	Intersections xs = intersect_world(r);
	Intersection *hit = xs.hit();
	if (hit != NULL && hit->t < distance)
		return true;
	return false;
}
// {
// 	for (Light l : lights)
// 	{
// 		Tuple v = l.position - point;
// 		float distance = v.magnitude();
// 		Tuple direction = v.normalize();
// 		Ray r = Ray(point, direction);
// 		Intersections xs = intersect_world(r);
// 		Intersection *hit = xs.hit();
// 		if (hit != NULL && hit->t < distance)
// 			return true;
// 	}
// 	// Tuple v = lights[0].position - point;
// 	// float distance = v.magnitude();
// 	// Tuple direction = v.normalize();
// 	// Ray r = Ray(point, direction);
// 	// Intersections xs = intersect_world(r);
// 	// Intersection *hit = xs.hit();
// 	// if (hit != NULL && hit->t < distance)
// 	// 	return true;
// 	return false;
// }
