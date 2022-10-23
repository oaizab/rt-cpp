#pragma once

#include "Tuple.hpp"

class Matrix
{
	public:
		Matrix();
		Matrix(int dim);
		Matrix(Matrix const &src);
		~Matrix() = default;

		Matrix &operator=(Matrix const &rhs);

		bool operator==(Matrix const &m) const;
		bool operator!=(Matrix const &m) const;

		Matrix operator*(Matrix const &m) const;
		Tuple operator*(Tuple const &t) const;

		static Matrix identity();
		static Matrix translation(float x, float y, float z);
		static Matrix scaling(float x, float y, float z);
		static Matrix rotation_x(float r);
		static Matrix rotation_y(float r);
		static Matrix rotation_z(float r);
		static Matrix shearing(float xy, float xz, float yx, float yz, float zx, float zy);
		static Matrix view_transform(Tuple from, Tuple to, Tuple up);

		Matrix transpose() const;
		Matrix inverse() const;

		float _m[4][4];
		int _dim;
};
