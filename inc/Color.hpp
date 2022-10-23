#pragma once

#include <algorithm>

class Color
{
	public:
		Color();
		Color(Color const &src);
		~Color() = default;
		Color(float r, float g, float b);

		Color &operator=(Color const &rhs);

		int r255() const;
		int g255() const;
		int b255() const;

		Color operator+(Color const &c) const;
		Color operator-(Color const &c) const;
		Color operator*(Color const &c) const;
		Color operator*(float const &f) const;
		Color add(Color const &c) const;

		Color normalize();

		float r;
		float g;
		float b;

		// static Colors

		static Color black;
		static Color white;
		static Color red;
		static Color green;
		static Color blue;

};
