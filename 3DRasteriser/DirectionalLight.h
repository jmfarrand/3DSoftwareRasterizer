#pragma once
#include <Windows.h>
#include "Light.h"
#include "Vector3D.h"

class DirectionalLight : public Light
{
public:
	DirectionalLight();
	~DirectionalLight();
	DirectionalLight(const int red, const int green, const int blue, const Vector3D& direction);
	DirectionalLight(const DirectionalLight& l);

	// = operator
	DirectionalLight& operator=(const DirectionalLight& rhs);
	COLORREF Colour() const;
	void SetColour(const COLORREF colour);
	Vector3D Direction() const;
	void SetDirection(const Vector3D& direction);

private:
	Vector3D _direction;

	void Copy(const DirectionalLight& other);
};
