#ifndef INTERSECTION_HPP
# define INTERSECTION_HPP

# include <iostream>
# include <string>
# include "Sphere.hpp"

class Sphere;

class Intersection
{

	public:

		Intersection(float t, Sphere const &sphere);
		Intersection(Intersection const &src);
		~Intersection();

		Intersection &operator=(Intersection const &rhs);
		float getT() const;
		Sphere getObject() const;

		bool operator==(Intersection const &rhs) const;

		static Intersection nothing();

	private:
	
		float _t;
		Sphere _object;
		Intersection();

};

std::ostream &operator<<(std::ostream &o, Intersection const &i);

#endif /* INTERSECTION_H */