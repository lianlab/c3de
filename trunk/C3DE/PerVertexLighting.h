#ifndef PER_VERTEX_LIGHTING_H
#define PER_VERTEX_LIGHTING_H

#include "FX.h"

class PerVertexLighting : public FX
{
public:
	PerVertexLighting(ID3DXEffect * effect);
	~PerVertexLighting();
};
#endif