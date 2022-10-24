#include "Intersections.hpp"

Intersections::Intersections(): count(0)
{
}

Intersections::Intersections(Intersection const &i1, Intersection const &i2): count(2)
{
	intersections.push_back(i1);
	intersections.push_back(i2);
}

Intersections::Intersections(Intersections const &src)
{
	*this = src;
}

Intersections::~Intersections()
{
}

Intersection &Intersections::operator[](int i)
{
	return intersections[i];
}

void Intersections::add(Intersection const &i)
{
	intersections.push_back(i);
	count++;
}

void Intersections::add(Intersections const &i)
{
	for (int j = 0; j < i.count; j++)
	{
		intersections.push_back(i.intersections[j]);
		count++;
	}
}

Intersection *Intersections::hit()
{
	Intersection *hit = NULL;
	float min = -1;
	for (int i = 0; i < count; i++)
	{
		if (intersections[i].t > 0 && (min < 0 || intersections[i].t < min))
		{
			min = intersections[i].t;
			hit = &intersections[i];
		}
	}
	return hit;
}