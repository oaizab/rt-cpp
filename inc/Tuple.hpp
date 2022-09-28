#pragma once

#include <iostream>
#include <string>

class Tuple
{

	public:

		Tuple();
		Tuple(Tuple const &src);
		~Tuple();
		Tuple(float x, float y, float z, float w);

		Tuple &operator=(Tuple const &rhs);

		bool operator==(Tuple const &rhs) const;
		Tuple operator+(Tuple const &rhs) const;
		Tuple operator-(Tuple const &rhs) const;
		Tuple operator-() const;
		Tuple operator*(float const &rhs) const;
		Tuple operator/(float const &rhs) const;

		float magnitude() const;
		Tuple normalize() const;
		float dot(Tuple const &rhs) const;
		Tuple cross(Tuple const &rhs) const;

		float getX() const;
		float getY() const;
		float getZ() const;
		float getW() const;
		void setX(float x);
		void setY(float y);
		void setZ(float z);
		void setW(float w);

		static Tuple point(float x, float y, float z);
		static Tuple vector(float x, float y, float z);

		Tuple reflect(Tuple const &normal) const;

	private:
	
		float _x;
		float _y;
		float _z;
		float _w;
};

std::ostream &operator<<(std::ostream &o, Tuple const &i);
