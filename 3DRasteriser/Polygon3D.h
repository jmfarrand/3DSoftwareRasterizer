#pragma once
#include <Windows.h>
#include "Vector3D.h"

class Vertex;

const int NOOFINDICIES = 3;

class Polygon3D
{
public:
	Polygon3D();
	Polygon3D(int index0, int index1, int index2);
	~Polygon3D();
	Polygon3D(const Polygon3D& p);

	// Accessor to return index of specified vertex
	int GetIndex(int index) const;

	Polygon3D& operator=(const Polygon3D& rhs);
	static bool Greator(const Polygon3D& p1, const Polygon3D& p2);
	bool Culling() const;
	void SetCulling(const bool culling);
	Vector3D Normal() const;
	void SetNormal(const Vector3D normal);
	void CalculateZDepth(const Vertex& v0, const Vertex& v1, const Vertex& v2);
	float Depth() const;
	COLORREF Colour() const;
	void SetColour(const COLORREF colour);

private:
	int _indicies[NOOFINDICIES];
	bool _culling;
	Vector3D _normal;
	float _depth;
	COLORREF _colour;

	// private method to copy the contenst of
	// one Polygon3D object to another
	void Copy(const Polygon3D& other);
};
