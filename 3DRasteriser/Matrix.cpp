#include "Matrix.h"
#include "Vertex.h"

Matrix::Matrix()
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			_m[i][j] = 0.0f;
		}
	}
}

// Constructor that initialises all elements.
Matrix::Matrix(float a, float b, float c, float d,
	float e, float f, float g, float h,
	float i, float j, float k, float l,
	float m, float n, float o, float p)
{
	_m[0][0] = a;
	_m[0][1] = b;
	_m[0][2] = c;
	_m[0][3] = d;
	_m[1][0] = e;
	_m[1][1] = f;
	_m[1][2] = g;
	_m[1][3] = h;
	_m[2][0] = i;
	_m[2][1] = j;
	_m[2][2] = k;
	_m[2][3] = l;
	_m[3][0] = m;
	_m[3][1] = n;
	_m[3][2] = o;
	_m[3][3] = p;
}

// Copy constructor
Matrix::Matrix(const Matrix& other)
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			_m[i][j] = 0.0f;
		}
	}

	Copy(other);
}

// Destructor
Matrix::~Matrix()
{
}

// Retrieve value in matrix at specified row and column
float Matrix::GetM(const int row, const int column) const
{
	return _m[row][column];
}

// Set value in matrix at specified row and column
void Matrix::SetM(const int row, const int column, const float value)
{
	_m[row][column] = value;
}

// Copy assignment operator
Matrix& Matrix::operator= (const Matrix &rhs)
{
	if (this != &rhs)
	{
		// Only do if not assigning to ourselves (remember that a = b is the same as a.operator=(b))
		Copy(rhs);
	}
	return *this;
}

// Multiply two matrices together
const Matrix Matrix::operator*(const Matrix &other) const
{
	Matrix result;
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			float resultVal = 0;
			for (int k = 0; k < ROWS; k++)
			{
				resultVal += _m[i][k] * other.GetM(k, j);
			}
			result.SetM(i, j, resultVal);
		}
	}
	return result;
}

// Multiply a matrix by a vertex, returning a vertex
const Vertex Matrix::operator*(const Vertex &other) const
{
	Vertex result;
	result.setX(_m[0][0] * other.X() + _m[0][1] * other.Y() + _m[0][2] * other.Z() + _m[0][3] * other.W());
	result.setY(_m[1][0] * other.X() + _m[1][1] * other.Y() + _m[1][2] * other.Z() + _m[1][3] * other.W());
	result.setZ(_m[2][0] * other.X() + _m[2][1] * other.Y() + _m[2][2] * other.Z() + _m[2][3] * other.W());
	result.setW(_m[3][0] * other.X() + _m[3][1] * other.Y() + _m[3][2] * other.Z() + _m[3][3] * other.W());
	return result;
}

Matrix Matrix::CreateIdentityMatrix()
{
	return Matrix(1, 0, 0, 0,
				  0, 1, 0, 0,
				  0, 0, 1, 0,
				  0, 0, 0, 1);
}

// Private method to copy contents of one matrix
// to another
void Matrix::Copy(const Matrix & other)
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			_m[i][j] = other.GetM(i, j);
		}
	}
}
