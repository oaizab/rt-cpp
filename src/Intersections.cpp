#include "Intersections.hpp"

Intersections::Intersections()
{
}

Intersections::Intersections(Intersection const &i1, Intersection const &i2)
{
	_intersections.push_back(i1);
	_intersections.push_back(i2);
}

Intersections::Intersections(const Intersections &src)
{
	*this = src;
}

Intersections::~Intersections()
{
}

Intersections &Intersections::operator=(Intersections const &rhs)
{
	if (this != &rhs)
	{
		_intersections = rhs._intersections;
	}
	return *this;
}

std::ostream &operator<<(std::ostream &o, Intersections const &i)
{
	o << "Intersections " << i.getCount();
	for (int j = 0; j < i.getCount(); j++)
	{
		o << " " << i[j];
	}
	return o;
}

Intersection Intersections::operator[](int i) const
{
	if (i < 0 || i >= getCount())
	{
		throw std::out_of_range("Intersections::operator[]");
	}
	return _intersections[i];
}

Intersection &Intersections::operator[](int i)
{
	if (i < 0 || i >= getCount())
	{
		throw std::out_of_range("Intersections::operator[]");
	}
	return _intersections[i];
}

void Intersections::add(Intersection const &i)
{
	_intersections.push_back(i);
}

int Intersections::getCount() const
{
	return _intersections.size();
}

Intersection Intersections::hit() const
{
	int ret = -1;
	for (int i = 0; i < getCount(); i++)
	{
		if (_intersections[i].getT() >= 0 && (ret == -1 || _intersections[i].getT() < _intersections[ret].getT()))
		{
			ret = i;
		}
	}
	if (ret == -1)
	{
		return Intersection::nothing();
	}
	return _intersections[ret];
}
