#include <cmath>
#include "utils.hpp"

bool feq(float a, float b)
{
	const float EPSILON = 0.00001;
	if (fabs(a-b) < EPSILON)
		return true;
	else
		return false;
}

float radians(float deg)
{
	return (PI*deg/180);
}