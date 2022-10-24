#pragma once

#include <string>
#include "Color.hpp"

class Canvas
{
	public:
		Canvas();
		Canvas(int width, int height);
		Canvas(Canvas const &src);
		~Canvas() = default;

		Canvas &operator=(Canvas const &rhs);

		int width() const;
		int height() const;
		Color pixel_at(int x, int y) const;
		void write_pixel(int x, int y, Color const &c);
		void save_to_ppm(std::string const &filename) const;
		
		static Canvas canvas_from_ppm(std::string const &filename);

	private:
		int _width;
		int _height;
		Color **_pixels;
};