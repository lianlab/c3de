#ifndef BILLBOARD_MESH_H
#define BILLBOARD_MESH_H
	
#include "D3DMesh.h"
#include "Camera.h"
#include "D3DImage.h"

class BillboardMesh : public D3DMesh
{
public:
	BillboardMesh(D3DImage * a_texture);
	~BillboardMesh();
	void SetShaderHandlers();

};
#endif