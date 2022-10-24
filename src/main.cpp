#include "main.hpp"

// int main()
// {
// 	Cylinder c;
// 	Tuple n = c.normalAt(Tuple::point(-1, 1, 0));
// 	std::cout << n.x << ' ' << n.y << ' ' << n.z << ' ' << n.w << std::endl;
// 	return 0;
// }

int main()
{

	Plane fl = Plane();
	fl.material.color = Color(1, 0.9, 0.9);
	fl.material.specular = 0.0f;

	Plane lw;
	lw.setTransform(Matrix::translation(0, 0, 5) * \
		Matrix::rotation_y(-M_PI / 4) * Matrix::rotation_x(M_PI / 2));
	lw.material = fl.material;

	Plane rw;
	rw.setTransform(Matrix::translation(0, 0, 5) * \
		Matrix::rotation_y(M_PI / 4) * Matrix::rotation_x(M_PI / 2));
	rw.material = fl.material;

	Sphere mid = Sphere();
	mid.setTransform(Matrix::translation(-0.5, 1, 0.5));
	mid.material = Material();
	mid.material.color = Color(0.1, 1, 0.5);
	mid.material.diffuse = 0.7;
	mid.material.specular = 1;
	mid.material.shininess = 300;

	Sphere right = Sphere();
	right.setTransform(Matrix::translation(1.5, 0.5, -0.5) * \
		Matrix::scaling(0.5, 0.5, 0.5));
	right.material = Material();
	right.material.color = Color(0.5, 1, 0.1);
	right.material.diffuse = 0.7;
	right.material.specular = 1;

	Cylinder left = Cylinder(-1.5, 1);
	left.setTransform(Matrix::translation(-1.5, 0.33, -0.75) * \
		Matrix::scaling(0.33, 0.33, 0.33) * Matrix::rotation_x(2*M_PI / 3));
	left.addTransform(Matrix::rotation_y(M_PI / 12));
	left.material = Material();
	left.material.color = Color(1, 0.8, 0.1);
	left.material.diffuse = 0.7;
	left.material.specular = 1;

	World w = World();
	w.lights.push_back(Light(Tuple::point(-10, 10, -10), Color(1, 1, 1)).setRatio(0.3));
	w.lights.push_back(Light(Tuple::point(10, 10, -10), Color(1, 1, 1)).setRatio(0.5));
	w.lights.push_back(Light(Tuple::point(0, 10, 0), Color(1, 1, 1)).setRatio(0.1));

	w.objects.push_back(&fl);
	w.objects.push_back(&lw);
	w.objects.push_back(&rw);

	w.objects.push_back(&mid);
	w.objects.push_back(&right);
	w.objects.push_back(&left);

	
	Camera c = Camera(1000, 500, M_PI / 3);
	c.transform = Matrix::view_transform(Tuple::point(0, 2, -5), \
		Tuple::point(0, 1, 0), Tuple::vector(0, 1, 0));
	
	Canvas image = c.render(w);
	image.save_to_ppm("image.ppm");

	return 0;
}
