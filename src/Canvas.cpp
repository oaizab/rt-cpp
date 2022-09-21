#include "Canvas.hpp"
#include <fstream>

Canvas::Canvas()
{
	width = 0;
	height = 0;
	pixels = NULL;
}

Canvas::Canvas(const Canvas &src)
{
	*this = src;
}

Canvas::~Canvas()
{
	for (int i = 0; i < this->height; i++)
		delete[] this->pixels[i];
}

Canvas &Canvas::operator=(Canvas const &rhs)
{
	if (this != &rhs)
	{
		for (int i = 0; i < this->height; i++)
			delete[] this->pixels[i];
		delete[] this->pixels;
		this->width = rhs.width;
		this->height = rhs.height;
		this->pixels = new Color*[this->height];
		for (int i = 0; i < this->height; i++)
		{
			this->pixels[i] = new Color[this->width];
			for (int j = 0; j < this->width; j++)
				this->pixels[i][j] = rhs.pixels[i][j];
		}
	}
	return *this;
}

std::ostream &operator<<(std::ostream &o, Canvas const &i)
{
	o << "Canvas(" << i.getWidth() << ", " << i.getHeight() << ")";
	return o;
}

Canvas::Canvas(int width, int height)
{
	this->width = width;
	this->height = height;
	this->pixels = new Color*[this->height];
	for (int i = 0; i < this->height; i++)
	{
		this->pixels[i] = new Color[this->width];
		for (int j = 0; j < this->width; j++)
			this->pixels[i][j] = Color(0, 0, 0);
	}
}

void Canvas::writePixel(int x, int y, Color color)
{
	if (x < 0 || x >= this->width || y < 0 || y >= this->height)
		return;
	this->pixels[y][x] = color;
}

void Canvas::writePixelCentered(int x, int y, Color color)
{
	this->writePixel(x + this->width / 2, this->height / 2 - y, color);
}

Color Canvas::getPixel(int x, int y)
{
	if (x < 0 || x >= this->width || y < 0 || y >= this->height)
		return Color(0, 0, 0);
	return this->pixels[y][x];
}

int Canvas::getWidth() const
{
	return this->width;
}

int Canvas::getHeight() const
{
	return this->height;
}

void Canvas::saveToPPM(std::string filename)
{
	std::ofstream file;
	file.open(filename);
	file << "P3\n" << this->width << " " << this->height << "\n255\n";
	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			file << this->pixels[i][j].getRed255() << " " << this->pixels[i][j].getGreen255() << " " << this->pixels[i][j].getBlue255() << " ";
		}
		file << "\n";
	}
}
