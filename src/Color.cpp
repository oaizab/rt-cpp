#include "Color.hpp"

Color::Color()
{
	this->red = 0;
	this->green = 0;
	this->blue = 0;
}

Color::Color(const Color &src)
{
	*this = src;
}

Color::~Color()
{
}

Color &Color::operator=(Color const &rhs)
{
	if (this != &rhs)
	{
		this->red = rhs.getRed();
		this->green = rhs.getGreen();
		this->blue = rhs.getBlue();
	}
	return *this;
}

std::ostream &operator<<(std::ostream &o, Color const &i)
{
	o << "Color(" << i.getRed() << ", " << i.getGreen() << ", " << i.getBlue() << ")";
	return o;
}

Color::Color(float r, float g, float b)
{
	this->red = r;
	this->green = g;
	this->blue = b;
}

float Color::getRed() const
{
	return this->red;
}

float Color::getGreen() const
{
	return this->green;
}

float Color::getBlue() const
{
	return this->blue;
}

int Color::getRed255() const
{
	int r = this->red * 255.999;
	if (r > 255)
		r = 255;
	if (r < 0)
		r = 0;
	return r;
}

int Color::getGreen255() const
{
	int g = this->green * 255.999;
	if (g > 255)
		g = 255;
	if (g < 0)
		g = 0;
	return g;
}

int Color::getBlue255() const
{
	int b = this->blue * 255.999;
	if (b > 255)
		b = 255;
	if (b < 0)
		b = 0;
	return b;
}

void Color::setRed(float r)
{
	this->red = r;
}

void Color::setGreen(float g)
{
	this->green = g;
}

void Color::setBlue(float b)
{
	this->blue = b;
}

Color Color::operator+(Color const &rhs) const
{
	return Color(this->red + rhs.getRed(), this->green + rhs.getGreen(), this->blue + rhs.getBlue());
}

Color Color::operator-(Color const &rhs) const
{
	return Color(this->red - rhs.getRed(), this->green - rhs.getGreen(), this->blue - rhs.getBlue());
}

Color Color::operator*(Color const &rhs) const
{
	return Color(this->red * rhs.getRed(), this->green * rhs.getGreen(), this->blue * rhs.getBlue());
}

Color Color::operator*(float const &rhs) const
{
	return Color(this->red * rhs, this->green * rhs, this->blue * rhs);
}
