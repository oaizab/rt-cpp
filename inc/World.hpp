#pragma once

#include "Light.hpp"
#include "Shape.hpp"
#include <vector>
#include "Intersections.hpp"
#include "Ray.hpp"

class World
{
	public:
		World();
		World(World const & src);
		~World();

		World & operator=(World const & rhs);

		static World defaultWorld();

		Intersections intersect_world(Ray r);
		Color shade_hit(Computation comp);
		Color color_at(Ray r);
		bool is_shadowed(Tuple point, Light &light);
		
		std::vector<Shape *> objects;
		std::vector<Light> lights;
};
