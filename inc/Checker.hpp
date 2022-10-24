#pragma once

#include "Color.hpp"
#include "Tuple.hpp"
#include "Pattern.hpp"

class Checker: public Pattern
{
	public:
		Checker();
		Checker(int width, int height, Color const &a, Color const &b);
		Checker(Checker const &c);
		~Checker();

		virtual Color pattern_at(float u, float v);
		Color a;
		Color b;
		int width;
		int height;
};