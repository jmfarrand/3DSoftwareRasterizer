#pragma once

class Vector3D;

class Vertex
{
public:
	Vertex();
	Vertex(float x, float y, float z, float w);

	// Copy constructor.  
	Vertex(const Vertex& v);

	// Destructer
	~Vertex();

	float X() const;
	void setX(const float x);
	float Y() const;
	void setY(const float y);
	float Z() const;
	void setZ(const float z);
	float W() const;
	void setW(const float w);

	// Assignment operator
	Vertex& operator=(const Vertex& rhs);
	bool operator==(const Vertex& rhs) const;
	const Vertex operator+(const Vertex& rhs) const;
	Vector3D operator-(const Vertex& rhs);
	void DehomogeniseVertex();

private:
	float _x;
	float _y;
	float _z;
	float _w;
};

