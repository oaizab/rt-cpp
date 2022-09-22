#ifndef SPHERE_HPP
# define SPHERE_HPP

# include <iostream>
# include <string>
# include "Ray.hpp"
# include "Matrix.hpp"
# include "Material.hpp"

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

		Matrix getTransform() const;
		void setTransform(Matrix const &m);
		void addTransform(Matrix const &m);

		static Sphere nothing;

		Tuple normalAt(Tuple const p) const;

		// Material getMaterial() const;
		Material &getMaterial();
		void setMaterial(Material const &m);

	private:
	
		static int _count;
		int _id;
		Matrix _transform;
		Material _material;

};

std::ostream &operator<<(std::ostream &o, Sphere const &i);

#endif /* SPHERE_H */