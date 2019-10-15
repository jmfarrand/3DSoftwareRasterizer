#include "Light.h"

Light::Light()
{
	_red = 0;
	_green = 0;
	_blue = 0;
	_colour = COLORREF();
}

Light::~Light()
{
}

Light::Light(const Light & l)
{
	_red = 0;
	_green = 0;
	_blue = 0;
	_colour = COLORREF();
	Copy(l);
}

Light & Light::operator=(const Light & rhs)
{
	_red = 0;
	_green = 0;
	_blue = 0;
	_colour = COLORREF();

	Copy(rhs);

	return *this;
}

void Light::Copy(const Light & other)
{
	_red = other._red;
	_green = other._green;
	_blue = other._blue;
	_colour = other._colour;
}
