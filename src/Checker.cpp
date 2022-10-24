#include "Checker.hpp"

Checker::Checker()
{
}

Checker::Checker(int width, int height, Color const &a, Color const &b): a(a), b(b)
{
	this->width = width;
	this->height = height;
}

Checker::Checker(Checker const &c)
{
	*this = c;
}

Checker::~Checker()
{
}

Color Checker::pattern_at(float u, float v)
{
	int x = (int)(u * width);
	int y = (int)(v * height);
	if ((x + y) % 2 == 0)
		return a;
	return b;
}