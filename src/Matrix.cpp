#include "Matrix.hpp"
#include "utils.hpp"
#include <cmath>
#include <algorithm>
#include <utility>
#include <cstdlib>

Matrix::Matrix() : _dim(4)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			_m[i][j] = 0;
}

Matrix::Matrix(int dim) : _dim(dim)
{
	for (int i = 0; i < dim; i++)
		for (int j = 0; j < dim; j++)
			_m[i][j] = 0;
}

Matrix::Matrix(Matrix const &src) : _dim(src._dim)
{
	for (int i = 0; i < _dim; i++)
		for (int j = 0; j < _dim; j++)
			_m[i][j] = src._m[i][j];
}

Matrix &Matrix::operator=(Matrix const &rhs)
{
	if (this != &rhs)
	{
		_dim = rhs._dim;
		for (int i = 0; i < _dim; i++)
			for (int j = 0; j < _dim; j++)
				_m[i][j] = rhs._m[i][j];
	}
	return *this;
}

bool Matrix::operator==(Matrix const &m) const
{
	if (_dim != m._dim)
		return false;
	for (int i = 0; i < _dim; i++)
		for (int j = 0; j < _dim; j++)
			if (!feq(_m[i][j], m._m[i][j]))
				return false;
	return true;
}

bool Matrix::operator!=(Matrix const &m) const
{
	return !(*this == m);
}

Matrix Matrix::operator*(Matrix const &m) const
{
	Matrix res(_dim);
	for (int i = 0; i < _dim; i++)
		for (int j = 0; j < _dim; j++)
			for (int k = 0; k < _dim; k++)
				res._m[i][j] += _m[i][k] * m._m[k][j];
	return res;
}

Tuple Matrix::operator*(Tuple const &t) const
{
	Tuple res[4];
	for (int i = 0; i < 4; i++)
		res[i] = Tuple(_m[i][0], _m[i][1], _m[i][2], _m[i][3]);
	return Tuple(res[0] * t, res[1] * t, res[2] * t, res[3] * t);
}

Matrix Matrix::transpose() const
{
	Matrix res(_dim);
	for (int i = 0; i < _dim; i++)
		for (int j = 0; j < _dim; j++)
			res._m[i][j] = _m[j][i];
	return res;
}

Matrix Matrix::inverse() const
{
	Matrix m = *this;
	Matrix res = identity();
	for (int col = 0; col < 4; col++)
	{
		if (feq(m._m[col][col], 0))
		{
			int big = col;
			for (int row = 0; row < 4; row++)
				if (fabs(m._m[row][col]) > fabs(m._m[big][col]))
					big = row;
				if (big == col)
					return *this;
				else
				{
					for (int j = 0; j < 4; j++)
					{
						// std::swap(m._m[col][j], m._m[big][j]);
						// std::swap(res._m[col][j], res._m[big][j]);
						float tmp = m._m[col][j];
						m._m[col][j] = m._m[big][j];
						m._m[big][j] = tmp;
						tmp = res._m[col][j];
						res._m[col][j] = res._m[big][j];
						res._m[big][j] = tmp;
					}
				}
		}
		for (int row = 0; row < 4; row++)
		{
			if (row == col)
				continue;
			float coeff = m._m[row][col] / m._m[col][col];
			if (!feq(coeff, 0))
			{
				for (int k = 0; k < 4; k++)
				{
					m._m[row][k] -= coeff * m._m[col][k];
					res._m[row][k] -= coeff * res._m[col][k];
				}
				m._m[row][col] = 0;
			}
		}
	}
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			res._m[row][col] /= m._m[row][row];
		}
	}
	return res;
}

Matrix Matrix::identity()
{
	Matrix res;
	for (int i = 0; i < 4; i++)
		res._m[i][i] = 1;
	return res;
}

Matrix Matrix::translation(float x, float y, float z)
{
	Matrix res = identity();
	res._m[0][3] = x;
	res._m[1][3] = y;
	res._m[2][3] = z;
	return res;
}

Matrix Matrix::scaling(float x, float y, float z)
{
	Matrix res = identity();
	res._m[0][0] = x;
	res._m[1][1] = y;
	res._m[2][2] = z;
	return res;
}

Matrix Matrix::rotation_x(float r)
{
	Matrix res = identity();
	res._m[1][1] = cos(r);
	res._m[1][2] = -sin(r);
	res._m[2][1] = sin(r);
	res._m[2][2] = cos(r);
	return res;
}

Matrix Matrix::rotation_y(float r)
{
	Matrix res = identity();
	res._m[0][0] = cos(r);
	res._m[0][2] = sin(r);
	res._m[2][0] = -sin(r);
	res._m[2][2] = cos(r);
	return res;
}

Matrix Matrix::rotation_z(float r)
{
	Matrix res = identity();
	res._m[0][0] = cos(r);
	res._m[0][1] = -sin(r);
	res._m[1][0] = sin(r);
	res._m[1][1] = cos(r);
	return res;
}

Matrix Matrix::shearing(float xy, float xz, float yx, float yz, float zx, float zy)
{
	Matrix res = identity();
	res._m[0][1] = xy;
	res._m[0][2] = xz;
	res._m[1][0] = yx;
	res._m[1][2] = yz;
	res._m[2][0] = zx;
	res._m[2][1] = zy;
	return res;
}

Matrix Matrix::view_transform(Tuple from, Tuple to, Tuple up)
{
	Tuple forward = (to - from).normalize();
	Tuple upn = up.normalize();
	Tuple left = forward.cross(upn);
	Tuple true_up = left.cross(forward);
	Matrix orientation = Matrix::identity();
	orientation._m[0][0] = left.x;
	orientation._m[0][1] = left.y;
	orientation._m[0][2] = left.z;
	orientation._m[1][0] = true_up.x;
	orientation._m[1][1] = true_up.y;
	orientation._m[1][2] = true_up.z;
	orientation._m[2][0] = -forward.x;
	orientation._m[2][1] = -forward.y;
	orientation._m[2][2] = -forward.z;
	return orientation * translation(-from.x, -from.y, -from.z);
}
