#include "Image.hpp"

Image::Image()
{
}

Image::Image(Canvas &c)
{
	canvas = &c;
}

Image::Image(Image const &c)
{
	*this = c;
}

Image::~Image()
{
}

Color Image::pattern_at(float u, float v)
{
	int x = (int)(u * (canvas->width() - 1) + 0.5);
	int y = (int)(v * (canvas->height() - 1) + 0.5);
	return canvas->pixel_at(x, y);
}
