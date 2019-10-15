#include "DirectionalLight.h"

DirectionalLight::DirectionalLight()
{
	_direction = Vector3D();
}

DirectionalLight::~DirectionalLight()
{
}

DirectionalLight::DirectionalLight(const int red, const int green, const int blue, const Vector3D & direction)
{
	_red = red;
	_green = green;
	_blue = blue;
	_colour = RGB(_red, _green, _blue);
	_direction = direction;
}

DirectionalLight::DirectionalLight(const DirectionalLight & l)
{
	_direction = Vector3D();

	Copy(l);
}

DirectionalLight & DirectionalLight::operator=(const DirectionalLight & rhs)
{
	_red = 0;
	_green = 0;
	_blue = 0;
	_colour = COLORREF();
	_direction = Vector3D();

	Copy(rhs);
	return *this;
}

COLORREF DirectionalLight::Colour() const
{
	return _colour;
}

void DirectionalLight::SetColour(const COLORREF colour)
{
	_colour = colour;
}

Vector3D DirectionalLight::Direction() const
{
	return _direction;
}

void DirectionalLight::SetDirection(const Vector3D & direction)
{
	_direction = direction;
}

void DirectionalLight::Copy(const DirectionalLight & other)
{
	Light::Copy(other);
	_direction = other.Direction();
}
