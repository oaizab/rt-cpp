#pragma once

#include "utils.hpp"
#include "Matrix.hpp"
#include "Ray.hpp"
#include "Canvas.hpp"
#include "World.hpp"
#include <cmath>

class Camera
{
	public:
		Camera() = default;
		Camera(int hsize, int vsize, float fov);
		Camera(Camera const &src);
		~Camera() = default;

		Camera &operator=(Camera const &rhs);
		Ray ray_for_pixel(int px, int py);
		Matrix inverse();
		void set_transform(Matrix const &m);
		Canvas render(World &w);

		int hsize;
		int vsize;
		float fov;
		Matrix transform;
		float pixel_size;
		float half_width;
		float half_height;
	private:
		Matrix _inverse;
		bool inv;
};
