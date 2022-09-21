#include "Matrix.hpp"
#include "utils.hpp"
#include <stdexcept>
#include <cmath>
#include <iomanip>

Matrix::Matrix()
{
	width = 0;
	height = 0;
	matrix = NULL;
}

Matrix::Matrix(int rows, int cols)
{
	width = cols;
	height = rows;
	matrix = new float*[height];
	for (int i = 0; i < height; i++)
	{
		matrix[i] = new float[width];
		for (int j = 0; j < width; j++)
			matrix[i][j] = 0;
	}
}

Matrix::Matrix(int dim) : Matrix(dim, dim)
{
}

Matrix::Matrix(int dim, float values[])
{
	width = dim;
	height = dim;
	matrix = new float*[height];
	for (int i = 0; i < height; i++)
	{
		matrix[i] = new float[width];
		for (int j = 0; j < width; j++)
			matrix[i][j] = values[i * width + j];
	}
}

Matrix::Matrix(const Matrix &src)
{
	*this = src;
}

Matrix::~Matrix()
{
	for (int i = 0; i < height; i++)
		delete[] matrix[i];
	delete[] matrix;
}

Matrix &Matrix::operator=(Matrix const &rhs)
{
	if (this != &rhs)
	{
		for (int i = 0; i < height; i++)
			delete[] matrix[i];
		delete[] matrix;
		width = rhs.width;
		height = rhs.height;
		matrix = new float*[height];
		for (int i = 0; i < height; i++)
		{
			matrix[i] = new float[width];
			for (int j = 0; j < width; j++)
				matrix[i][j] = rhs.matrix[i][j];
		}
	}
	return *this;
}

std::ostream &operator<<(std::ostream &o, Matrix const &i)
{
	o << "Matrix(" << i.getWidth() << ", " << i.getHeight() << ")";
	for (int j = 0; j < i.getHeight(); j++)
	{
		o << '\n';
		for (int k = 0; k < i.getWidth(); k++)
			o << std::fixed << std::setprecision(5) << i(j, k) << " ";
	}
	return o;
}

bool Matrix::operator==(Matrix const &rhs) const
{
	if (this->width != rhs.width || this->height != rhs.height)
		return false;
	for (int i = 0; i < this->height; i++)
		for (int j = 0; j < this->width; j++)
			if (feq(this->matrix[i][j], rhs.matrix[i][j]) == false)
				return false;
	return true;
}

bool Matrix::operator!=(Matrix const &rhs) const
{
	return !(*this == rhs);
}

Matrix Matrix::operator*(Matrix const &rhs) const
{
	if (this->width != rhs.height)
		throw std::invalid_argument("Matrix::operator*(): invalid dimensions");
	Matrix result(this->height, rhs.width);
	for (int i = 0; i < result.height; i++)
		for (int j = 0; j < result.width; j++)
			for (int k = 0; k < this->width; k++)
				result(i, j) += this->matrix[i][k] * rhs.matrix[k][j];
	return result;
}

Tuple Matrix::operator*(Tuple const &rhs) const
{
	if (this->width != 4 || this->height != 4)
		throw std::invalid_argument("Matrix::operator*(): invalid dimensions");
	Tuple t[4];
	for (int i = 0; i < 4; i++)
		t[i] = Tuple(this->matrix[i][0], this->matrix[i][1], this->matrix[i][2], this->matrix[i][3]);
	return Tuple(t[0].dot(rhs), t[1].dot(rhs), t[2].dot(rhs), t[3].dot(rhs));
}

float Matrix::operator()(int row, int col) const
{
	if (row < 0 || row >= height || col < 0 || col >= width)
		throw std::invalid_argument("Matrix::operator(): invalid index");
	return matrix[row][col];
}

float &Matrix::operator()(int row, int col)
{
	if (row < 0 || row >= height || col < 0 || col >= width)
		throw std::invalid_argument("Matrix::operator(): invalid index");
	return matrix[row][col];
}

Matrix Matrix::transpose() const
{
	Matrix result(this->width, this->height);
	for (int i = 0; i < this->height; i++)
		for (int j = 0; j < this->width; j++)
			result(j, i) = this->matrix[i][j];
	return result;
}

float Matrix::determinant() const
{
	if (this->width != this->height)
		throw std::invalid_argument("Matrix::determinant(): invalid dimensions");
	if (this->width == 2)
		return this->matrix[0][0] * this->matrix[1][1] - this->matrix[0][1] * this->matrix[1][0];
	float result = 0;
	for (int i = 0; i < this->width; i++)
		result += this->matrix[0][i] * this->cofactor(0, i);
	return result;
}

Matrix Matrix::submatrix(int row, int col) const
{
	if (row < 0 || row >= this->height || col < 0 || col >= this->width)
		throw std::invalid_argument("Matrix::submatrix(): invalid index");
	Matrix result(this->height - 1, this->width - 1);
	for (int i = 0; i < this->height; i++)
		for (int j = 0; j < this->width; j++)
			if (i != row && j != col)
				result(i < row ? i : i - 1, j < col ? j : j - 1) = this->matrix[i][j];
	return result;
}

float Matrix::minor(int row, int col) const
{
	return this->submatrix(row, col).determinant();
}

float Matrix::cofactor(int row, int col) const
{
	return (row + col) % 2 == 0 ? this->minor(row, col) : -this->minor(row, col);
}

bool Matrix::isInvertible() const
{
	return this->determinant() != 0;
}

Matrix Matrix::inverse() const
{
	if (this->isInvertible() == false)
		throw std::invalid_argument("Matrix::inverse(): matrix is not invertible");
	float det = this->determinant();
	Matrix result(this->height, this->width);
	for (int i = 0; i < this->height; i++)
		for (int j = 0; j < this->width; j++)
			result(j, i) = this->cofactor(i, j) / det;
	return result;
}

Matrix Matrix::identity(int size)
{
	Matrix result(size, size);
	for (int i = 0; i < size; i++)
		result(i, i) = 1;
	return result;
}

Matrix Matrix::translation(float x, float y, float z)
{
	Matrix result = Matrix::identity(4);
	result(0, 3) = x;
	result(1, 3) = y;
	result(2, 3) = z;
	return result;
}

Matrix Matrix::scaling(float x, float y, float z)
{
	Matrix result = Matrix::identity(4);
	result(0, 0) = x;
	result(1, 1) = y;
	result(2, 2) = z;
	return result;
}

Matrix Matrix::rotationX(float r)
{
	Matrix result = Matrix::identity(4);
	result(1, 1) = cos(r);
	result(1, 2) = -sin(r);
	result(2, 1) = sin(r);
	result(2, 2) = cos(r);
	return result;
}

Matrix Matrix::rotationY(float r)
{
	Matrix result = Matrix::identity(4);
	result(0, 0) = cos(r);
	result(0, 2) = sin(r);
	result(2, 0) = -sin(r);
	result(2, 2) = cos(r);
	return result;
}

Matrix Matrix::rotationZ(float r)
{
	Matrix result = Matrix::identity(4);
	result(0, 0) = cos(r);
	result(0, 1) = -sin(r);
	result(1, 0) = sin(r);
	result(1, 1) = cos(r);
	return result;
}

Matrix Matrix::shearing(float xy, float xz, float yx, float yz, float zx, float zy)
{
	Matrix result = Matrix::identity(4);
	result(0, 1) = xy;
	result(0, 2) = xz;
	result(1, 0) = yx;
	result(1, 2) = yz;
	result(2, 0) = zx;
	result(2, 1) = zy;
	return result;
}

int Matrix::getWidth() const
{
	return this->width;
}

int Matrix::getHeight() const
{
	return this->height;
}
