#pragma once

class Tuple
{
	public:
		Tuple();
		Tuple(float x, float y, float z, float w);
		Tuple(Tuple const &t);
		~Tuple() = default;

		Tuple &operator=(Tuple const &rhs);

		bool operator==(Tuple const &t) const;
		bool operator!=(Tuple const &t) const;
		
		Tuple operator+(Tuple const &t) const;
		Tuple operator-(Tuple const &t) const;
		Tuple operator-() const;
		Tuple operator*(float f) const;
		Tuple operator/(float f) const;
		float operator*(Tuple const &t) const;

		float magnitude() const;
		Tuple normalize() const;
		float dot(Tuple const &t) const;
		Tuple cross(Tuple const &t) const;
		Tuple reflect(Tuple const &normal) const;

		static Tuple point(float x, float y, float z);
		static Tuple vector(float x, float y, float z);

		float x;
		float y;
		float z;
		float w;
};
