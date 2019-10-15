#pragma once

class Vertex;

// Class for a 4 x 4 matrix object.
const int ROWS = 4;
const int COLS = 4;

class Matrix
{
public:
	// Default constructor
	Matrix();

	// Constructor that initialises all elements.
	Matrix(float a, float b, float c, float d,
		float e, float f, float g, float h,
		float i, float j, float k, float l,
		float m, float n, float o, float p);

	// Copy contructor
	Matrix(const Matrix& other);

	// Destructor
	~Matrix();

	// Retrieve value in matrix at specified row and column
	float GetM(const int row, const int column) const;

	// Set value in matrix at specified row and column
	void SetM(const int row, const int column, const float value);

	// Copy assignment operator
	Matrix& operator= (const Matrix &rhs);

	// Multiply two matrices together
	const Matrix operator*(const Matrix &other) const;

	// Multiply a matrix by a vertex, returning a vertex
	const Vertex operator*(const Vertex &other) const;

	static Matrix CreateIdentityMatrix();
private:
	float _m[ROWS][COLS];

	// Private method to copy contents of one matrix
	// to another
	void Copy(const Matrix& other);
};