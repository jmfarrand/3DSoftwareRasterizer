#include "AmbientLight.h"

AmbientLight::AmbientLight()
{
}

AmbientLight::~AmbientLight()
{
}

AmbientLight::AmbientLight(int red, int green, int blue)
{
	_red = red;
	_green = green;
	_blue = blue;
	_colour = RGB(_red, _green, _blue);
}

AmbientLight::AmbientLight(const AmbientLight & l)
{
	Copy(l);
}

AmbientLight & AmbientLight::operator=(const AmbientLight & rhs)
{
	Copy(rhs);
	return *this;
}

COLORREF AmbientLight::Colour() const
{
	return _colour;
}

void AmbientLight::SetColour(const COLORREF colour)
{
	_colour = colour;
}

void AmbientLight::Copy(const AmbientLight & other)
{
	Light::Copy(other);
}
