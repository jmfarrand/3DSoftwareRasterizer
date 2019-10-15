#pragma once
#include <Windows.h>
#include "Light.h"

class AmbientLight : public Light
{
public:
	AmbientLight();
	~AmbientLight();
	AmbientLight(int red, int green, int blue);
	AmbientLight(const AmbientLight& l);

	// = operator
	AmbientLight& operator=(const AmbientLight& rhs);
	COLORREF Colour() const;
	void SetColour(const COLORREF colour);

private:
	void Copy(const AmbientLight& other);
};