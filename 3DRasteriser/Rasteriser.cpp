#include "Rasteriser.h"

Rasteriser app;

Rasteriser::Rasteriser()
{
}

Rasteriser::~Rasteriser()
{
}

bool Rasteriser::Initialise()
{
	// This method override can be used to initialise any
	// variables
	if (!MD2Loader::LoadModel("teapot.md2", _model,
		&Model::AddPolygon,
		&Model::AddVertex))
	{
		return false;
	}
	_camera = Camera(0.0f, 0.0f, 0.0f, Vertex(0.0f, 0.0f, -10.0f, 1.0f));
	aLight = AmbientLight(255, 0, 0);
	Vector3D lightDirection = Vector3D(-50, 0, 0);
	DirectionalLight dlight = DirectionalLight(255, 0, 0, lightDirection);
	_directionalLights.push_back(dlight);
	// Make sure you return true unless there were any errors
	// in this method
	return true;
}

void Rasteriser::DrawString(Bitmap &bitmap, LPCTSTR text)
{
	HDC hdc = bitmap.GetDC();
	HFONT hFont, hOldFont;

	// Retrieve a handle to the variable stock font.  
	hFont = hFont = CreateFont(48, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Myfont"));

	// Select the variable stock font into the specified device context. 
	if (hOldFont = (HFONT)SelectObject(hdc, hFont))
	{
		SetTextColor(hdc, RGB(0, 0, 0));
		SetBkColor(hdc, RGB(255, 255, 255));

		// Display the text string.  
		TextOut(hdc, 10, 10, text, lstrlen(text));

		// Restore the original font.        
		SelectObject(hdc, hOldFont);
	}
	DeleteObject(hFont);
}

void Rasteriser::ResetTransformation()
{
	_modelTransformation = Matrix::CreateIdentityMatrix();
}

void Rasteriser::DrawRotationStrings(Bitmap & bitmap)
{
	// if statements for drawing string for the different model transformations
	if (currentFrame < 120)
	{
		DrawString(bitmap, L"Wireframe model - rotation around x axis");
	}
	else if (currentFrame < 240)
	{
		DrawString(bitmap, L"Wireframe model - rotation around y axis");
	}
	else if (currentFrame < 360)
	{
		DrawString(bitmap, L"Wireframe model - rotation around z axis");
	}
	else if (currentFrame < 480)
	{
		DrawString(bitmap, L"Wireframe model - scaling");
	}
	else if (currentFrame < 600)
	{
		DrawString(bitmap, L"Wireframe model - translation");
	}
}

void Rasteriser::Update(Bitmap &bitmap)
{
	if (currentFrame == 240)
	{
		ResetTransformation();
	}

	else if (currentFrame == 360)
	{
		ResetTransformation();
	}

	else if (currentFrame == 480)
	{
		ResetTransformation();
	}

	else if (currentFrame == 600)
	{
		ResetTransformation();
	}

	UpdateTransformation();
	GeneratePerspectiveMatrix(1, (float)bitmap.GetWidth() / bitmap.GetHeight());
	GenerateViewMatrix(1, bitmap.GetWidth(), bitmap.GetHeight());

	// if and else statement to increment currentFrame tracker
	if (currentFrame < 1060)
	{
		currentFrame++;
	}
	else
	{
		ResetTransformation();
		currentFrame = 1;
	}
}

void Rasteriser::Render(Bitmap &bitmap)
{
	// Clear the window to white
	bitmap.Clear(RGB(255, 255, 255));

	// model transformation
	_model.ApplyTransformToLocalVerticies(_modelTransformation);
	// backface culling
	_model.CalculateBackfaces(_camera.GetPosition());
	if (currentFrame > 720 && currentFrame < 840)
	{
		DrawString(bitmap, L"Solid shading with ambient lighting");
		// calculate ambient light
		_model.CalculateLightingAmbient(aLight);
	}
	else if (currentFrame > 720 && currentFrame < 1060)
	{
		DrawString(bitmap, L"Solid shading with directional lighting");
		// calculate directional lights
		_model.CalculateLightingDirectional(_directionalLights);
	}
	// calculate point lights
	//_model.CalculateLightingPoint(_pointLights);
	// camera transformation
	_model.ApplyTransformToTransformedVerticies(_camera.GetCameraMatrix());
	// sort backfaces
	_model.Sort();
	// perspective transformation
	_model.ApplyTransformToTransformedVerticies(_perspectiveMatrix);
	// dehomogenisation
	_model.DehomogeniseVerticies();
	// view transformation
	_model.ApplyTransformToTransformedVerticies(_viewMatrix);

	// draw the strings to be displayed when the model is going through the various transformations
	DrawRotationStrings(bitmap);

	if (currentFrame < 600)
	{
		// draw wireframe model
		DrawWireFrame(bitmap);
	}
	else if (currentFrame < 720)
	{
		DrawString(bitmap, L"Wireframe with backface culling");
		// draw wireframe model
		DrawWireFrame(bitmap);
	}
	else
	{
		// draw solid shaded model
		DrawSolidFlat(bitmap);
	}
}

void Rasteriser::DrawWireFrame(Bitmap &bitmap)
{
	vector<Vertex> v = _model.GetVerticies();
	HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	SelectObject(bitmap.GetDC(), pen);
	size_t polygonCount = _model.GetPolygonCount();
	for (int i = 0; i < polygonCount; i++)
	{
		Polygon3D p = _model.GetPolygons()[i];
		if (p.Culling() == false || currentFrame <= 600)
		{
			MoveToEx(bitmap.GetDC(), (int)v[p.GetIndex(0)].X(), (int)v[p.GetIndex(0)].Y(), NULL);
			LineTo(bitmap.GetDC(), (int)v[p.GetIndex(1)].X(), (int)v[p.GetIndex(1)].Y());
			LineTo(bitmap.GetDC(), (int)v[p.GetIndex(2)].X(), (int)v[p.GetIndex(2)].Y());
			LineTo(bitmap.GetDC(), (int)v[p.GetIndex(0)].X(), (int)v[p.GetIndex(0)].Y());
		}
	}
	DeleteObject(pen);
}

void Rasteriser::DrawSolidFlat(Bitmap & bitmap)
{
	vector<Vertex> v = _model.GetVerticies();
	POINT points[3];

	size_t polygonCount = _model.GetPolygonCount();
	for (int i = 0; i < polygonCount; i++)
	{

		Polygon3D p = _model.GetPolygons()[i];
		HPEN pen = CreatePen(PS_SOLID, 1, p.Colour());
		SelectObject(bitmap.GetDC(), pen);

		HBRUSH brush = CreateSolidBrush(p.Colour());
		SelectObject(bitmap.GetDC(), brush);
		points[0] = { (LONG)v[p.GetIndex(0)].X(), (LONG)v[p.GetIndex(0)].Y() };
		points[1] = { (LONG)v[p.GetIndex(1)].X(), (LONG)v[p.GetIndex(1)].Y() };
		points[2] = { (LONG)v[p.GetIndex(2)].X(), (LONG)v[p.GetIndex(2)].Y() };
		if (p.Culling() == false)
		{
			Polygon(bitmap.GetDC(), points, 3);
		}

		DeleteObject(pen);
		DeleteObject(brush);
	}
	
}

void Rasteriser::GeneratePerspectiveMatrix(float d, float aspectRatio)
{
	Matrix temp = Matrix(d / aspectRatio, 0.0f, 0.0f, 0.0f,
		0.0f, d, 0.0f, 0.0f,
		0.0f, 0.0f, d, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f);
	_perspectiveMatrix = temp;
}

void Rasteriser::GenerateViewMatrix(float d, int width, int height)
{
	Matrix temp = Matrix((float)width/2.0f, 0.0f, 0.0f, (float)width/2.0f,
		0.0f, -((float)height/2.0f), 0.0f, (float)height/2.0f,
		0.0f, 0.0f, d/2.0f, d/2.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
	_viewMatrix = temp;
}

void Rasteriser::UpdateTransformation()
{
	// ===== X ROTATION =====
	if (currentFrame < 120)
	{
		double xRotation = -1 * (M_PI / 180);
		Matrix xRotationMatrix = Matrix(1, 0, 0, 0,
			0, (float)cos(xRotation), (float)-sin(xRotation), 0,
			0, (float)sin(xRotation), (float)cos(xRotation), 0,
			0, 0, 0, 1);
		_modelTransformation = _modelTransformation * xRotationMatrix;
	}
	
	// ===== Y ROTATION =====
	else if (currentFrame < 240 || currentFrame > 600)
	{
		double yRotation = -1 * (M_PI / 180);
		Matrix yRotationMatrix = Matrix((float)cos(yRotation), 0, (float)sin(yRotation), 0,
			0, 1, 0, 0,
			(float)-sin(yRotation), 0, (float)cos(yRotation), 0,
			0, 0, 0, 1);
		_modelTransformation = _modelTransformation * yRotationMatrix;
	}
	
	// ===== Z ROTATION =====
	else if (currentFrame < 360)
	{
		double zRotation = -1 * (M_PI / 180);
		Matrix zRotationMatrix = Matrix((float)cos(zRotation), (float)-sin(zRotation), 0, 0,
			(float)sin(zRotation), (float)cos(zRotation), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);
		_modelTransformation = _modelTransformation * zRotationMatrix;
	}
	
	// ===== SCALING =====
	else if (currentFrame < 480)
	{
		Matrix scaling = Matrix(1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);
		_modelTransformation = _modelTransformation * scaling;
	}
	
	// ===== TRANSLATION =====
	else if (currentFrame < 600)
	{
		Matrix translation = Matrix(1, 0, 0, 1,
			0, 1, 0, 1,
			0, 0, 1, 1,
			0, 0, 0, 1);
		_modelTransformation = _modelTransformation * translation;
	}
}
