#pragma once

#include <iostream>
#include <string>
#include "Tuple.hpp"

class Matrix
{

	public:

		Matrix(int rows, int cols);
		Matrix(int dim);
		Matrix(int dim, float values[]);
		Matrix(Matrix const &src);
		~Matrix();

		Matrix &operator=(Matrix const &rhs);

		int getWidth() const;
		int getHeight() const;
		float getValue(int row, int col) const;
		void setValue(int row, int col, float value);

		bool operator==(Matrix const &rhs) const;
		bool operator!=(Matrix const &rhs) const;

		Matrix operator*(Matrix const &rhs) const;
		Tuple operator*(Tuple const &rhs) const;
		float operator()(int row, int col) const;
		float &operator()(int row, int col);

		static Matrix identity(int size);
		static Matrix translation(float x, float y, float z);
		static Matrix scaling(float x, float y, float z);
		static Matrix rotationX(float r);
		static Matrix rotationY(float r);
		static Matrix rotationZ(float r);
		static Matrix shearing(float xy, float xz, float yx, float yz, float zx, float zy);

		Matrix transpose() const;
		float determinant() const;
		Matrix submatrix(int row, int col) const;
		float minor(int row, int col) const;
		float cofactor(int row, int col) const;
		bool isInvertible() const;
		Matrix inverse() const;

	private:
			
		int width;
		int height;
		float **matrix;
		Matrix();

};

std::ostream &operator<<(std::ostream &o, Matrix const &i);
