#ifndef WOMAN_MESH_H
#define WOMAN_MESH_H

#include "D3DSkinnedMesh.h"

class WomanMesh : public D3DSkinnedMesh
{
public:
	WomanMesh();
	~WomanMesh();
	void SetShaderHandlers();
};
#endif