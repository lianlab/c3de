#ifndef WOMAN_MESH_H
#define WOMAN_MESH_H

#include "D3DSkinnedMesh.h"



class WomanMesh : public D3DSkinnedMesh
{
public:
	WomanMesh();
	~WomanMesh();
	void SetShaderHandlers();

	static const int ANIMATION_BYE = 0;
	static const int ANIMATION_JOGGING = 1;
	static const int ANIMATION_WALKING = 2;
	static const int ANIMATION_IDLE = 3;
	

};
#endif