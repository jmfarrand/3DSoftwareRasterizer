#pragma once
#include <vector>
#include <algorithm>
#include "AmbientLight.h"
#include "DirectionalLight.h"

class Polygon3D;
class Matrix;
class Vertex;

using namespace std;

class Model
{
public:
	Model();
	~Model();

	// Accessors
	vector<Polygon3D>&	GetPolygons();
	vector<Vertex>&		GetVerticies();
	size_t				GetPolygonCount() const;
	size_t				GetVertexCount() const;
	void				AddVertex(float x, float y, float z);
	void				AddPolygon(int i0, int i1, int i2);
	void				ApplyTransformToLocalVerticies(const Matrix &transform);
	void				ApplyTransformToTransformedVerticies(const Matrix &transform);
	void				DehomogeniseVerticies();
	void				CalculateBackfaces(const Vertex& cameraPosition);
	void				Sort(void);
	void				CalculateLightingAmbient(AmbientLight& light);
	void				CalculateLightingDirectional(vector<DirectionalLight>& lights);

private:
	vector<Polygon3D>	_polygons;
	vector<Vertex>		_verticies;
	vector<Vertex>		_transformedVerticies;
	float ka_red;
	float ka_green;
	float ka_blue;
	float kd_red;
	float kd_green;
	float kd_blue;
	float ks_red;
	float ks_green;
	float ks_blue;
};
