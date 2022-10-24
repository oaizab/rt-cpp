#include "main.hpp"

// int main()
// {
// 	Canvas c = Canvas::canvas_from_ppm("image.ppm");
// 	c.save_to_ppm("test2.ppm");
// 	return 0;
// }

int main()
{

	// Plane fl = Plane();
	// //fl.addTransform(Matrix::translation(0, -2, 0));
	// fl.material.color = Color(1, 0.9, 0.9);
	// fl.material.specular = 0.0f;
	Canvas texture = Canvas::canvas_from_ppm("texture.ppm");
	Plane lw;
	lw.setTransform(Matrix::translation(0, 0, 5) * \
		Matrix::rotation_y(-M_PI / 4) * Matrix::rotation_x(M_PI / 2));
	//lw.material = fl.material;
	// lw.material.setPattern(Image(texture));

	// Plane rw;
	// rw.setTransform(Matrix::translation(0, 0, 5) * \
	// 	Matrix::rotation_y(M_PI / 4) * Matrix::rotation_x(M_PI / 2));
	// rw.material = fl.material;

	Sphere mid;// = Sphere();
	//mid.setTransform(Matrix::translation(-0.5, 1, 0.5));
	mid.addTransform(Matrix::rotation_x(M_PI));
	mid.addTransform(Matrix::rotation_z(M_PI));
	// mid.material.setPattern(Checker(24, 8, Color(0,0,0), Color(1,1,1)));
	mid.material.setPattern(Image(texture));
	mid.material.color = Color(0.1, 1, 0.5);
	mid.material.diffuse = 0.7;
	mid.material.specular = 1;
	mid.material.shininess = 300;

	// Sphere right = Sphere();
	// right.setTransform(Matrix::translation(1.5, 0.5, -0.5) * \
	// 	Matrix::scaling(0.5, 0.5, 0.5));
	// right.material.color = Color(0.5, 1, 0.1);
	// right.material.diffuse = 0.7;
	// right.material.specular = 1;

	// Cone left(-1, 0);// = Cone(-1, 0);
	// left.addTransform(Matrix::rotation_y(M_PI / 2));
	// left.addTransform(Matrix::translation(-0.5, 1, -1) * \
	// 	Matrix::rotation_x(-M_PI/2) * \
	// 	Matrix::scaling(0.33, 2, 0.33));
	// // left.addTransform(Matrix::rotation_y(-M_PI / 12));
	// // left.addTransform(Matrix::scaling(1,3,1));
	// // left.addTransform(Matrix::rotation_x(-M_PI / 2));
	// // left.addTransform(Matrix::rotation_y(radians(170)));
	// // left.addTransform(Matrix::rotation_x(radians(30)));
	// left.material = Material();
	// left.material.color = Color(1, 0.8, 0.1);
	// left.material.diffuse = 0.7;
	// left.material.specular = 1;

	World w = World();
	w.lights.push_back(Light(Tuple::point(-10, 10, -10), Color(1, 1, 1)).setRatio(0.3));
	w.lights.push_back(Light(Tuple::point(10, 10, -10), Color(1, 1, 1)).setRatio(0.5));
	w.lights.push_back(Light(Tuple::point(-20, 40, -30), Color(1, 1, 1)).setRatio(0.1));

	// w.objects.push_back(&fl);
	w.objects.push_back(&lw);
	// w.objects.push_back(&rw);

	w.objects.push_back(&mid);
	// w.objects.push_back(&right);
	// w.objects.push_back(&left);

	
	Camera c = Camera(1000, 500, M_PI / 3);
	c.transform = Matrix::view_transform(Tuple::point(0, 0, -5), \
		Tuple::point(0, 0, 0), Tuple::vector(0, 1, 0));
	
	Canvas image = c.render(w);
	image.save_to_ppm("image.ppm");

	return 0;
}
