#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include "Framework.h"
#include "Matrix.h"
#include "Model.h"
#include "Camera.h"
#include "Vertex.h"
#include "MD2Loader.h"
#include "Polygon3D.h"
#include "AmbientLight.h"
#include "DirectionalLight.h"

class Bitmap;

class Rasteriser : public Framework
{
public:
	Rasteriser();
	~Rasteriser();
	bool Initialise();
	void Update(Bitmap &bitmap);
	void Render(Bitmap &bitmap);
	void DrawWireFrame(Bitmap &bitmap);
	void DrawSolidFlat(Bitmap &bitmap);
	void GeneratePerspectiveMatrix(float d, float aspectRatio);
	void GenerateViewMatrix(float d, int width, int height);
	void UpdateTransformation();

private:
	Model _model;
	Matrix _modelTransformation = Matrix::CreateIdentityMatrix();
	Matrix _perspectiveMatrix;
	Matrix _viewMatrix;
	Camera _camera;

	AmbientLight aLight;
	vector<DirectionalLight> _directionalLights;
	void DrawString(Bitmap &bitmap, LPCTSTR text);
	void ResetTransformation();
	void DrawRotationStrings(Bitmap& bitmap);
	int currentFrame = 1;
};
