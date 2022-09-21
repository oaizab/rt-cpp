#ifndef RAY_HPP
# define RAY_HPP

# include <iostream>
# include <string>
# include "Tuple.hpp"

class Ray
{

	public:

		Ray();
		Ray(Tuple origin, Tuple direction);
		Ray(Ray const &src);
		~Ray();

		Ray &operator=(Ray const &rhs);
		bool operator==(Ray const &rhs) const;

		Tuple getOrigin() const;
		Tuple getDirection() const;
		void setOrigin(Tuple &origin);
		void setDirection(Tuple &direction);

		Tuple position(float t) const;

	private:
		
		Tuple _origin;
		Tuple _direction;
};

std::ostream &operator<<(std::ostream &o, Ray const &i);

#endif /* RAY_H */