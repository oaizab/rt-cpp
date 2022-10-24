#pragma once

#include "Color.hpp"

class Pattern
{
	public:
		Pattern();
		virtual ~Pattern() = 0;

		virtual Color pattern_at(float u, float v) = 0;
};
