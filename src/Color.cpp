#include "Color.hpp"

Color Color::black = Color(0, 0, 0);
Color Color::white = Color(1, 1, 1);
Color Color::red = Color(1, 0, 0);
Color Color::green = Color(0, 1, 0);
Color Color::blue = Color(0, 0, 1);

Color::Color() : r(0), g(0), b(0)
{
}

Color::Color(float r, float g, float b) : r(r), g(g), b(b)
{
}

Color::Color(Color const &src) : r(src.r), g(src.g), b(src.b)
{
}

Color &Color::operator=(Color const &rhs)
{
	r = rhs.r;
	g = rhs.g;
	b = rhs.b;
	return *this;
}

int Color::r255() const
{
	int ret = r * 255.999;
	if (ret > 255)
		ret = 255;
	if (ret < 0)
		ret = 0;
	return ret;
}

int Color::g255() const
{
	int ret = g * 255.999;
	if (ret > 255)
		ret = 255;
	if (ret < 0)
		ret = 0;
	return ret;
}

int Color::b255() const
{
	int ret = b * 255.999;
	if (ret > 255)
		ret = 255;
	if (ret < 0)
		ret = 0;
	return ret;
}

Color Color::operator+(Color const &c) const
{
	return Color(r + c.r, g + c.g, b + c.b);
}

Color Color::operator-(Color const &c) const
{
	return Color(r - c.r, g - c.g, b - c.b);
}

Color Color::operator*(Color const &c) const
{
	return Color(r * c.r, g * c.g, b * c.b);
}

Color Color::operator*(float const &f) const
{
	return Color(r * f, g * f, b * f);
}

Color Color::normalize()
{
	if (r > 1)
		r = 1;
	if (g > 1)
		g = 1;
	if (b > 1)
		b = 1;
	if (r < 0)
		r = 0;
	if (g < 0)
		g = 0;
	if (b < 0)
		b = 0;
	return *this;
}

Color Color::add(Color const &c) const
{
	return Color(std::max(r, c.r), std::max(g, c.g), std::max(b, c.b));
}
