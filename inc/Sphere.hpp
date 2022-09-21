#ifndef SPHERE_HPP
# define SPHERE_HPP

# include <iostream>
# include <string>
# include "Ray.hpp"

class Intersections;

class Sphere
{

	public:

		Sphere();
		Sphere(Sphere const &src);
		~Sphere();

		Sphere &operator=(Sphere const &rhs);
		bool operator==(Sphere const &rhs) const;

		int getId() const;
		Intersections intersect(Ray const &r) const;

		static Sphere nothing;

	private:
	
		static int _count;
		int _id;

};

std::ostream &operator<<(std::ostream &o, Sphere const &i);

#endif /* SPHERE_H */