#ifndef WALL_H
#define WALL_H

#include "D3DMesh.h"

class Wall : public D3DMesh
{
public:
	Wall();
	virtual ~Wall();
	void SetShaderHandlers();
};
#endif