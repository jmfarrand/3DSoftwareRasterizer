#pragma once
#include <Windows.h>

class Light
{
public:
	Light();
	~Light();
	Light(const Light& l);
	Light& operator=(const Light& rhs);

protected:
	COLORREF _colour;
	int _red;
	int _green;
	int _blue;

	void Copy(const Light& other);
};