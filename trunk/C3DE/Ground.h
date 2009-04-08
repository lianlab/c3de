#ifndef GROUND_H
#define GROUND_H

#include "Plane.h"


class Ground : public Plane
{
public:
	//Plane(int numRows, int numCols, float dx, float dz);
	Ground();
	~Ground();

	void SetShaderHandlers();


protected:
	void InitializeEffectHandles();

};

#endif