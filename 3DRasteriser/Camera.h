#pragma once
#include "Vertex.h"
#include "Matrix.h"

class Camera
{
public:
	Camera();
	Camera(float xRotation, float yRotation, float zRotation, const Vertex& position);
	~Camera();

	Matrix GetCameraMatrix() const;
	float GetXRotation() const;
	void setXRotation(float newXRotation);
	float GetYRotation() const;
	void setYRotation(float newYRotation);
	float GetZRotation() const;
	void setZRotation(float newZRotation);
	Vertex GetPosition() const;

	Camera& operator=(const Camera& rhs);
private:
	float _xRotation;
	float _yRotation;
	float _zRotation;

	// camera matrix
	Matrix _cameraMatrix;
	Vertex _position;
};
