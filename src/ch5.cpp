#include "main.hpp"
#include <thread>

int tmain()
{
	int canvas_pixels = 1000;
	Canvas c(canvas_pixels, canvas_pixels);
	int smain(int page, int canvas_pixels, Canvas &c);
	std::thread t1(smain, 1, canvas_pixels, std::ref(c));
	std::thread t2(smain, 2, canvas_pixels, std::ref(c));
	std::thread t3(smain, 3, canvas_pixels, std::ref(c));
	std::thread t4(smain, 4, canvas_pixels, std::ref(c));
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	c.saveToPPM("sphere.ppm");
	return 0;
}

int smain(int page, int canvas_pixels, Canvas &c)
{
	Tuple ray_origin = Tuple::point(0, 0, -5);
	float wall_z = 10;
	float wall_size = 7.0;
	float pixel_size = wall_size / canvas_pixels;
	float half = wall_size / 2;
	int startx = 0, finishx = canvas_pixels, starty = 0, finishy = canvas_pixels;
	switch (page)
	{
	case 1:
		startx = 0;
		finishx = canvas_pixels / 2;
		starty = 0;
		finishy = canvas_pixels / 2;
		break;
	case 2:
		startx = canvas_pixels / 2;
		finishx = canvas_pixels;
		starty = 0;
		finishy = canvas_pixels / 2;
		break;
	case 3:
		startx = 0;
		finishx = canvas_pixels / 2;
		starty = canvas_pixels / 2;
		finishy = canvas_pixels;
		break;
	case 4:
		startx = canvas_pixels / 2;
		finishx = canvas_pixels;
		starty = canvas_pixels / 2;
		finishy = canvas_pixels;
		break;
	default:
		break;
	}
	
	Color red = Color(0.4, 0.6, 0.8);
	Sphere s;
	s.setMaterial(Material());
	s.getMaterial().setColor(red);
	// s.getMaterial().setSpecular(0);
	// s.setTransform(Matrix::scaling(0.25, 0.25, 0.5));
	// s.addTransform(Matrix::shearing(1, 0, 0, 0, 0, 0));
	// s.addTransform(Matrix::rotationZ(M_PI / 4));
	Light light = Light(Tuple::point(-10, 10, -10), Color(1, 1, 1));
	for (int y = starty; y < finishy; y++)
	{
		float world_y = half - pixel_size * y;
		for (int x = startx; x < finishx; x++)
		{
			float world_x = -half + pixel_size * x;
			Tuple position = Tuple::point(world_x, world_y, wall_z);
			Tuple r = position - ray_origin;
			Ray ray(ray_origin, r.normalize());
			Intersections xs = s.intersect(ray);
			Intersection hit = xs.hit();
			if (hit.getT() != -1)
			{
				Tuple point = ray.position(hit.getT());
				Tuple normal = s.normalAt(point);
				Tuple eye = -ray.getDirection();
				Color color = hit.getObject().getMaterial().lighting(light, point, eye, normal);
				c.writePixel(x, y, color);
			}
		}
	}
	return 0;
}
