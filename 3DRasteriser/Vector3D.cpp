#include "Vector3D.h"
#include <math.h>

Vector3D::Vector3D()
{
	_x = 0.0f;
	_y = 0.0f;
	_z = 0.0f;
}

Vector3D::~Vector3D()
{
}

Vector3D::Vector3D(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;
}

Vector3D::Vector3D(const Vector3D& other)
{
	_x = other.X();
	_y = other.Y();
	_z = other.Z();
}

float Vector3D::X() const
{
	return _x;
}

void Vector3D::setX(const float x)
{
	_x = x;
}

float Vector3D::Y() const
{
	return _y;
}

void Vector3D::setY(const float y)
{
	_y = y;
}

float Vector3D::Z() const
{
	return _z;
}

void Vector3D::setZ(const float z)
{
	_z = z;
}


float Vector3D::CalculateLength() const
{
	return (float)sqrt(_x * _x + _y * _y + _z * _z); 
}

void Vector3D::NormaliseVector()
{
	float length = this->CalculateLength();
	this->setX(this->X() / length);
	this->setY(this->Y() / length);
	this->setZ(this->Z() / length);
}

Vector3D& Vector3D::operator=(const Vector3D& rhs)
{
	if (this != &rhs)
	{
		_x = rhs.X();
		_y = rhs.Y();
		_z = rhs.Z();
	}
	return *this;
}

bool Vector3D::operator==(const Vector3D& rhs) const
{
	bool comparison;
	if (_x == rhs.X() && _y == rhs.Y() && _z == rhs.Z())
	{
		comparison = true;
	}
	else
	{
		comparison = false;
	}
	return comparison;
}

const Vector3D Vector3D::operator+(const Vector3D& rhs) const
{
	return Vector3D(_x + rhs.X(), _y + rhs.Y(), _z + rhs.Z());
}

float Vector3D::DotProduct(const Vector3D& u,const Vector3D& v)
{
	return (u.X() * v.X()) + (u.Y() * v.Y()) + (u.Z() * v.Z());

}

Vector3D Vector3D::CrossProduct(const Vector3D& u, const Vector3D& v)
{
	return Vector3D((u.Y() * v.Z()) - (u.Z() * v.Y()),
		(u.Z() * v.X()) - (u.X() * v.Z()),
		(u.X() * v.Y()) - (u.Y() * v.X()));
}
