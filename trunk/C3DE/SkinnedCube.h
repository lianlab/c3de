#if 0
#ifndef SKINNED_CUBE_H
#define SKINNED_CUBE_H

#include "D3DSkinnedMesh.h"

class SkinnedCube : public D3DSkinnedMesh
{
public:
	SkinnedCube();
	~SkinnedCube();
	void SetShaderHandlers();
};
#endif

#endif