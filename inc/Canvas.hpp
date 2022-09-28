#pragma once

#include <iostream>
#include <string>
#include "Color.hpp"

class Canvas
{

	public:

		Canvas(int width, int height);
		Canvas(Canvas const &src);
		~Canvas();

		Canvas &operator=(Canvas const &rhs);

		void writePixel(int x, int y, Color color);
		void saveToPPM(std::string filename);
		void writePixelCentered(int x, int y, Color color);
		Color getPixel(int x, int y);

		int getWidth() const;
		int getHeight() const;

	private:
			
		int width;
		int height;
		Color **pixels;
		Canvas();

};

std::ostream &operator<<(std::ostream &o, Canvas const &i);
