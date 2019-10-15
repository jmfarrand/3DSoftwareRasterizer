#include "Camera.h"

#include <math.h>

Camera::Camera()
{
}

Camera::Camera(float xRotation, float yRotation, float zRotation, const Vertex& position)
{
	_xRotation = xRotation;
	_yRotation = yRotation;
	_zRotation = zRotation;
	_position = position;

	// x transformation matrix
	Matrix xTransform = Matrix(1, 0, 0, 0,
		0, (float)cos(xRotation), (float)sin(xRotation), 0,
		0, -(float)sin(xRotation), (float)cos(xRotation), 0,
		0, 0, 0, 1);
	// y transformation matrix
	Matrix yTransform = Matrix((float)cos(yRotation), 0, -(float)sin(yRotation), 0,
		0, 1, 0, 0,
		(float)sin(yRotation), 0, (float)cos(yRotation), 0,
		0, 0, 0, 1);
	// z transformation matrix
	Matrix zTransform = Matrix((float)cos(zRotation), (float)sin(zRotation), 0, 0,
		-(float)sin(zRotation), (float)cos(zRotation), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
	// focal point calculation matrix
	Matrix focalPoint = Matrix(1, 0, 0, -_position.X(),
		0, 1, 0, -_position.Y(),
		0, 0, 1, -_position.Z(),
		0, 0, 0, 1);

	_cameraMatrix = xTransform * yTransform * zTransform * focalPoint;
}

Camera::~Camera()
{
}

Matrix Camera::GetCameraMatrix() const
{
	return _cameraMatrix;
}

float Camera::GetXRotation() const
{
	return _xRotation;
}

void Camera::setXRotation(float xRotation)
{
	_xRotation = xRotation;
}

float Camera::GetYRotation() const
{
	return _yRotation;
}

void Camera::setYRotation(float yRotation)
{
	_yRotation = yRotation;
}

float Camera::GetZRotation() const
{
	return _zRotation;
}

void Camera::setZRotation(float zRotation)
{
	_zRotation = zRotation;
}

Vertex Camera::GetPosition() const
{
	return _position;
}

Camera& Camera::operator=(const Camera & rhs)
{
	if (this != &rhs)
	{
		_xRotation = rhs.GetXRotation();
		_yRotation = rhs.GetYRotation();
		_zRotation = rhs.GetZRotation();
		_cameraMatrix = rhs.GetCameraMatrix();
		_position = rhs.GetPosition();
	}
	return *this;
}
