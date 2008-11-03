#ifndef PIVOT_H
#define PIVOT_H

#include "D3DMesh.h"

class Pivot : public D3DMesh
{
public:
	Pivot();
	virtual ~Pivot();
	void SetShaderHandlers();
};
#endif