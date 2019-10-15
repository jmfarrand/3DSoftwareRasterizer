#include "Polygon3D.h"
#include "Vertex.h"

Polygon3D::Polygon3D()
{
	for (int i = 0; i < NOOFINDICIES; i++)
	{
		_indicies[i] = 0;
	}
	_culling = false;
	_normal = Vector3D();
	_depth = 0.0f;
	_colour = COLORREF();
}

Polygon3D::Polygon3D(int index0, int index1, int index2)
{
	_indicies[0] = index0;
	_indicies[1] = index1;
	_indicies[2] = index2;
	_culling = false;
	_normal = Vector3D();
	_depth = 0.0f;
	_colour = COLORREF();
}

Polygon3D::~Polygon3D()
{
}

Polygon3D::Polygon3D(const Polygon3D& p)
{
	for (int i = 0; i < NOOFINDICIES; i++)
	{
		_indicies[i] = 0;
	}
	_culling = false;
	_normal = Vector3D();
	_depth = 0.0f;
	_colour = COLORREF();

	Copy(p);
}

int Polygon3D::GetIndex(int index) const
{
	return _indicies[index];
}

bool Polygon3D::Culling() const
{
	return _culling;
}

void Polygon3D::SetCulling(bool culling)
{
	_culling = culling;
}

Vector3D Polygon3D::Normal() const
{
	return _normal;
}

void Polygon3D::SetNormal(const Vector3D normal)
{
	_normal = normal;
}

void Polygon3D::CalculateZDepth(const Vertex& v0, const Vertex& v1, const Vertex& v2)
{
	_depth = (v0.Z() + v1.Z() + v2.Z()) / 3;
}

float Polygon3D::Depth() const
{
	return _depth;
}

COLORREF Polygon3D::Colour() const
{
	return _colour;
}

void Polygon3D::SetColour(const COLORREF colour)
{
	_colour = colour;
}

Polygon3D& Polygon3D::operator= (const Polygon3D& rhs)
{
	for (int i = 0; i < NOOFINDICIES; i++)
	{
		_indicies[i] = 0;
	}
	_culling = false;
	_normal = Vector3D();
	_depth = 0.0f;
	_colour = COLORREF();
	Copy(rhs);
	return *this;
}

bool Polygon3D::Greator(const Polygon3D & p1, const Polygon3D & p2)
{
	if (p1.Depth() > p2.Depth())
	{
		return true;
	}
	else
	{
		return false;
	}
}

// private method that copyies the contents of
// one Polygon3D object to another
void Polygon3D::Copy(const Polygon3D& other)
{
	for (int i = 0; i < NOOFINDICIES; i++)
	{
		_indicies[i] = other.GetIndex(i);
	}
	_culling = other.Culling();
	_normal = other.Normal();
	_depth = other.Depth();
	_colour = other.Colour();
}