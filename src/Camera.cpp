#include "Camera.hpp"
#include <thread>

Camera::Camera(int hsize, int vsize, float fov)
	: hsize(hsize), vsize(vsize), fov(fov), transform(Matrix::identity()),
		inv(false)
{
	float half_view = std::tan(fov / 2);
	float aspect = (float)hsize / (float)vsize;
	if (aspect >= 1)
	{
		half_width = half_view;
		half_height = half_view / aspect;
	}
	else
	{
		half_width = half_view * aspect;
		half_height = half_view;
	}
	pixel_size = (half_width * 2) / hsize;
}

Camera::Camera(Camera const &src)
	: hsize(src.hsize), vsize(src.vsize), fov(src.fov), transform(src.transform),
	  pixel_size(src.pixel_size), half_width(src.half_width), half_height(src.half_height),
	  _inverse(src._inverse), inv(src.inv)
{
}

Camera &Camera::operator=(Camera const &rhs)
{
	if (this != &rhs)
	{
		hsize = rhs.hsize;
		vsize = rhs.vsize;
		fov = rhs.fov;
		transform = rhs.transform;
		pixel_size = rhs.pixel_size;
		half_width = rhs.half_width;
		half_height = rhs.half_height;
	}
	return *this;
}

Ray Camera::ray_for_pixel(int px, int py)
{
	float xoffset = (px + 0.5) * pixel_size;
	float yoffset = (py + 0.5) * pixel_size;
	float world_x = half_width - xoffset;
	float world_y = half_height - yoffset;
	Tuple pixel = inverse() * Tuple::point(world_x, world_y, -1);
	Tuple origin = inverse() * Tuple::point(0, 0, 0);
	Tuple direction = (pixel - origin).normalize();
	return Ray(origin, direction);
}

Matrix Camera::inverse()
{
	if (!inv)
	{
		_inverse = transform.inverse();
		inv = true;
	}
	return _inverse;
}

void Camera::set_transform(Matrix const &m)
{
	transform = m;
	inv = false;
}

static void p_render(Camera &c, World &w, Canvas &image, int v)
{
	for (int y = v*(c.vsize/4); y < (v+1)*c.vsize/4; y++)
	{
		for (int x = 0; x < c.hsize; x++)
		{
			Ray r = c.ray_for_pixel(x, y);
			Color c = w.color_at(r);
			image.write_pixel(x, y, c);
		}
	}
}

Canvas Camera::render(World &w)
{
	Canvas image(hsize, vsize);
	std::thread t1(p_render, std::ref(*this), std::ref(w), std::ref(image), 0);
	std::thread t2(p_render, std::ref(*this), std::ref(w), std::ref(image), 1);
	std::thread t3(p_render, std::ref(*this), std::ref(w), std::ref(image), 2);
	std::thread t4(p_render, std::ref(*this), std::ref(w), std::ref(image), 3);
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	return image;
}
