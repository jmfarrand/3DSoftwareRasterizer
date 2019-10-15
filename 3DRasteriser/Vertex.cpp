#include "Vertex.h"
#include "Vector3D.h"

Vertex::Vertex()
{
	_x = 0.0f;
	_y = 0.0f;
	_z = 0.0f;
	_w = 1.0f;
}

Vertex::Vertex(float x, float y, float z, float w)
{
	_x = x;
	_y = y;
	_z = z;
	_w = w;
}

// Copy constructor implementation
// Note that the parameter v is passed by reference, rather than value (that is what
// '&' indicates).  Note also the use of 'const' to indicate that the parameter v cannot
// be changed.

Vertex::Vertex(const Vertex& v)
{
	_x = v.X();
	_y = v.Y();
	_z = v.Z();
	_w = v.W();
}

Vertex::~Vertex()
{
}

float Vertex::X() const
{
	return _x;
}

void Vertex::setX(const float x)
{
	_x = x;
}

float Vertex::Y() const
{
	return _y;
}

void Vertex::setY(const float y)
{
	_y = y;
}

float Vertex::Z() const
{
	return _z;
}

void Vertex::setZ(const float z)
{
	_z = z;
}

float Vertex::W() const
{
	return _w;
}

void Vertex::setW(const float w)
{
	_w = w;
}

Vertex& Vertex::operator=(const Vertex& rhs)
{
	// Only do the assignment if we are not assigning
	// to ourselves
	if (this != &rhs)
	{
		_x = rhs.X();
		_y = rhs.Y();
		_z = rhs.Z();
		_w = rhs.W();
	}
	return *this;
}

// The const at the end of the declaraion for '==" indicates that this operation does not change
// any of the member variables in this class.

bool Vertex::operator==(const Vertex& rhs) const
{
	bool comparison;
	if (_x == rhs.X() && _y == rhs.Y() && _z == rhs.Z() && _w == rhs.W())
	{
		comparison = true;
	}
	else
	{
		comparison = false;
	}
	return comparison;
}

// You can see three different uses of 'const' here:
//
// The first const indicates that the method changes the return value, but it is not moved in memory
// The second const indicates that the parameter is passed by reference, but it is not modified
// The third const indicates that the operator does not change any of the memory variables in the class.

const Vertex Vertex::operator+(const Vertex& rhs) const
{
	return Vertex(_x + rhs.X(), _y + rhs.Y(), _z + rhs.Z(), _w + rhs.W());
}

Vector3D Vertex::operator-(const Vertex& rhs)
{
	return Vector3D(_x - rhs.X(), _y - rhs.Y(), _z - rhs.Z());
}

void Vertex::DehomogeniseVertex()
{
	this->setX(this->X() / this->W());
	this->setY(this->Y() / this->W());
	this->setZ(this->Z() / this->W());
	this->setW(1);
}
