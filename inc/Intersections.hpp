#ifndef INTERSECTIONS_HPP
# define INTERSECTIONS_HPP

# include <iostream>
# include <string>
# include <vector>
# include "Intersection.hpp"

class Intersection;

class Intersections
{

	public:

		Intersections();
		Intersections(Intersection const &i1, Intersection const &i2);
		Intersections(Intersections const &src);
		~Intersections();

		Intersections &operator=(Intersections const &rhs);
		Intersection operator[](int i) const;
		Intersection &operator[](int i);

		void add(Intersection const &i);

		int getCount() const;
		
		Intersection hit() const;

	private:
	
		std::vector<Intersection> _intersections;

};

std::ostream &operator<<(std::ostream &o, Intersections const &i);

#endif /* INTERSECTIONS_H */