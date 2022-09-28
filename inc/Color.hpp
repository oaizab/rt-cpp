#pragma once

#include <iostream>
#include <string>

class Color
{

	public:

		Color();
		Color(Color const &src);
		~Color();
		Color(float r, float g, float b);

		Color &operator=(Color const &rhs);

		float getRed() const;
		float getGreen() const;
		float getBlue() const;

		int getRed255() const;
		int getGreen255() const;
		int getBlue255() const;

		void setRed(float r);
		void setGreen(float g);
		void setBlue(float b);

		Color operator+(Color const &rhs) const;
		Color operator-(Color const &rhs) const;
		Color operator*(Color const &rhs) const;
		Color operator*(float const &rhs) const;

	private:
	
		float red;
		float green;
		float blue;

};

std::ostream &operator<<(std::ostream &o, Color const &i);
