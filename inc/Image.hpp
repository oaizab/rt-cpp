#pragma once

#include "Color.hpp"
#include "Canvas.hpp"
#include "Tuple.hpp"
#include "Pattern.hpp"
#include <cmath>

class Image: public Pattern
{
	public:
		Image();
		Image(Canvas &c);
		Image(Image const &c);
		~Image();

		virtual Color pattern_at(float u, float v);
		Canvas *canvas;
};