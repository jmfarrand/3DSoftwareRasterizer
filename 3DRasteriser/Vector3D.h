#pragma once

class Vector3D
{
public:
	Vector3D();
	Vector3D(float x, float y, float z);
	~Vector3D();
	
	Vector3D(const Vector3D& other);

	float X() const;
	void setX(const float x);
	float Y() const;
	void setY(const float y);
	float Z() const;
	void setZ(const float z);
	float CalculateLength() const;
	void NormaliseVector();

	// Operators
	Vector3D& operator=(const Vector3D& rhs);
	bool operator==(const Vector3D& rhs) const;
	const Vector3D operator+(const Vector3D& rhs) const;

	static float DotProduct(const Vector3D& u, const Vector3D& v);
	static Vector3D CrossProduct(const Vector3D& u,const Vector3D& v);

private:
	float _x;
	float _y;
	float _z;
};
