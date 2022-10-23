#include "Computation.hpp"

Computation::Computation() 
{
}

Computation::Computation(Computation const &src): object(src.object)
{
	t = src.t;
	point = src.point;
	eyev = src.eyev;
	normalv = src.normalv;
	inside = src.inside;
	over_point = src.over_point;
}

Computation::~Computation()
{
}
