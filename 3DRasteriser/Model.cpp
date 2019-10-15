#include "Model.h"
#include "Vertex.h"
#include "Vector3D.h"
#include "Polygon3D.h"
#include "Matrix.h"

Model::Model()
{
	ka_red = 1.0f;
	ka_green = 1.0f;
	ka_blue = 1.0f;
	kd_red = 1.0f;
	kd_green = 1.0f;
	kd_blue = 1.0f;
	ks_red = 1.0f;
	ks_green = 1.0f;
	ks_blue = 1.0f;
}

Model::~Model()
{
}

vector<Polygon3D>& Model::GetPolygons()
{
	return _polygons;
}

vector<Vertex>&	Model::GetVerticies()
{
	return _transformedVerticies;
}

size_t Model::GetPolygonCount() const
{
	return _polygons.size();
}

size_t Model::GetVertexCount() const
{
	return _verticies.size();
}

void Model::AddVertex(float x, float y, float z)
{
	Vertex temp = Vertex(x, y, z, 1);
	_verticies.push_back(temp);
}

void Model::AddPolygon(int i0, int i1, int i2)
{
	Polygon3D temp = Polygon3D(i0, i1, i2);
	_polygons.push_back(temp);
}

void Model::ApplyTransformToLocalVerticies(const Matrix &transform)
{
	_transformedVerticies.clear();
	size_t verticiesSize = _verticies.size();
	for (int i = 0; i < verticiesSize; i++)
	{
		Vertex temp = transform * _verticies[i];
		_transformedVerticies.push_back(temp);
	}
}

void Model::ApplyTransformToTransformedVerticies(const Matrix &transform)
{
	size_t transformedVerticiesSize = _transformedVerticies.size();
	for (int i = 0; i < transformedVerticiesSize; i++)
	{
		_transformedVerticies[i] = transform * _transformedVerticies[i];
	}
}

void Model::DehomogeniseVerticies()
{
	size_t verticiesSize = _verticies.size();
	for (int i = 0; i < verticiesSize; i++)
	{
		_transformedVerticies[i].DehomogeniseVertex();
	}
}

void Model::CalculateBackfaces(const Vertex& cameraPosition)
{
	size_t polyLen = _polygons.size();

	for (int i = 0; i < polyLen; i++)
	{
		Polygon3D p = _polygons[i];

		Vertex vertex0 = _transformedVerticies[p.GetIndex(0)];
		Vertex vertex1 = _transformedVerticies[p.GetIndex(1)];
		Vertex vertex2 = _transformedVerticies[p.GetIndex(2)];
		
		Vector3D vectorA = vertex0 - vertex1;
		Vector3D vectorB = vertex0 - vertex2;

		Vector3D normal = Vector3D::CrossProduct(vectorA, vectorB);
		normal.NormaliseVector();
		p.SetNormal(normal);

		Vector3D eyeVector = vertex0 - cameraPosition;
		eyeVector.NormaliseVector();

		float result = Vector3D::DotProduct(eyeVector, normal);
		if (result > 0)
		{
			p.SetCulling(true);
		}
		else
		{
			p.SetCulling(false);
		}
		_polygons[i] = p;
	}
}

void Model::Sort()
{
	size_t length = _polygons.size();
	for (int i = 0; i < length; i++)
	{
		Polygon3D p = _polygons[i];

		Vertex vertex0 = _transformedVerticies[p.GetIndex(0)];
		Vertex vertex1 = _transformedVerticies[p.GetIndex(1)];
		Vertex vertex2 = _transformedVerticies[p.GetIndex(2)];

		/*float averageZ = vertex0.Z() + vertex1.Z() + vertex2.Z();
		float averageZ2 = averageZ / 3;*/
		p.CalculateZDepth(vertex0, vertex1, vertex2);
		_polygons[i] = p;
	}
	std::sort(_polygons.begin(), _polygons.end(), Polygon3D::Greator);
}

void Model::CalculateLightingAmbient(AmbientLight & light)
{
	float totalR;
	float totalG;
	float totalB;

	size_t pLen = _polygons.size();
	for (int i = 0; i < pLen; i++)
	{
		Polygon3D tempPolygon = _polygons[i];
		totalR = GetRValue(light.Colour());
		totalG = GetGValue(light.Colour());
		totalB = GetBValue(light.Colour());

		totalR *= ka_red;
		totalG *= ka_green;
		totalB *= ka_blue;

		COLORREF rgbColour = RGB(totalR, totalG, totalB);
		tempPolygon.SetColour(rgbColour);

		_polygons[i] = tempPolygon;
	}
}

void Model::CalculateLightingDirectional(vector<DirectionalLight> & lights)
{
	float totalR;
	float totalG;
	float totalB;

	float tempR;
	float tempG;
	float tempB;

	size_t pLen = _polygons.size();
	for (int i = 0; i < pLen; i++)
	{
		Polygon3D p = _polygons[i];
		totalR = GetRValue(p.Colour());
		totalG = GetGValue(p.Colour());
		totalB = GetBValue(p.Colour());

		tempR = 0.0f;
		tempG = 0.0f;
		tempB = 0.0f;

		size_t dLen = lights.size();
		for (int j = 0; j < dLen; j++)
		{
			DirectionalLight light = lights[j];
			tempR = GetRValue(light.Colour());
			tempG = GetGValue(light.Colour());
			tempB = GetBValue(light.Colour());

			tempR *= kd_red;
			tempG *= kd_green;
			tempB *= kd_blue;
			
			Vector3D lightDir = light.Direction();
			lightDir.NormaliseVector();
		
			float dotProduct = Vector3D::DotProduct(lightDir, p.Normal());

			tempR *= dotProduct;
			tempG *= dotProduct;
			tempB *= dotProduct;

			totalR += tempR;
			totalG += tempG;
			totalB += tempB;
		}

		if (totalR < 0)
		{
			totalR = 0;
		}
		if (totalG < 0)
		{
			totalG = 0;
		}
		if (totalB < 0)
		{
			totalB = 0;
		}
		if (totalR > 255)
		{
			totalR = 255;
		}
		if (totalG > 255)
		{
			totalG = 255;
		}
		if (totalB > 255)
		{
			totalB = 255;
		}

		COLORREF rgbColour = RGB(totalR, totalG, totalB);
		p.SetColour(rgbColour);

		_polygons[i] = p;
	}
}
