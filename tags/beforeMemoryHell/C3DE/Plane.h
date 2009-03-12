#ifndef PLANE_H
#define PLANE_H

#include "D3DMesh.h"

class Plane : public D3DMesh
{
public:
	//Plane(int numRows, int numCols, float dx, float dz);
	Plane(float width, float height);
	~Plane();

	void SetShaderHandlers();


protected:
	void InitializeEffectHandles();

};

#endif