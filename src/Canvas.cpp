#include "Canvas.hpp"
#include <fstream>

Canvas::Canvas() : _width(0), _height(0), _pixels(nullptr)
{
}

Canvas::Canvas(int width, int height) : _width(width), _height(height), _pixels(new Color*[height])
{
	for (int i = 0; i < height; i++)
	{
		_pixels[i] = new Color[width];
		for (int j = 0; j < width; j++)
			_pixels[i][j] = Color::black;
	}
}

Canvas::Canvas(Canvas const &src) : _width(src._width), _height(src._height), _pixels(new Color*[src._height])
{
	for (int i = 0; i < src._height; i++)
	{
		_pixels[i] = new Color[src._width];
		for (int j = 0; j < src._width; j++)
			_pixels[i][j] = src._pixels[i][j];
	}
}

Canvas &Canvas::operator=(Canvas const &rhs)
{
	if (this != &rhs)
	{
		for (int i = 0; i < _height; i++)
			delete[] _pixels[i];
		delete[] _pixels;
		_width = rhs._width;
		_height = rhs._height;
		_pixels = new Color*[_height];
		for (int i = 0; i < _height; i++)
		{
			_pixels[i] = new Color[_width];
			for (int j = 0; j < _width; j++)
				_pixels[i][j] = rhs._pixels[i][j];
		}
	}
	return *this;
}

int Canvas::width() const
{
	return _width;
}

int Canvas::height() const
{
	return _height;
}

Color Canvas::pixel_at(int x, int y) const
{
	if (x < 0 || x >= _width || y < 0 || y >= _height)
		return Color::black;
	return _pixels[y][x];
}

void Canvas::write_pixel(int x, int y, Color const &c)
{
	if (x < 0 || x >= _width || y < 0 || y >= _height)
		return;
	_pixels[y][x] = c;
}

void Canvas::save_to_ppm(std::string const &filename) const
{
	std::ofstream file;
	file.open(filename);
	file << "P3\n" << _width << " " << _height << "\n255\n";
	for (int i = 0; i < _height; i++)
	{
		for (int j = 0; j < _width; j++)
		{
			file << _pixels[i][j].r255() << " " << _pixels[i][j].g255() << " " << _pixels[i][j].b255() << " ";
		}
		file << "\n";
	}
	file.close();
}
