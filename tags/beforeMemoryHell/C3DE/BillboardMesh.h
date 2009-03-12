#ifndef BILLBOARD_MESH_H
#define BILLBOARD_MESH_H

#include "D3DMesh.h"

class BillboardMesh : public D3DMesh
{
public:
	BillboardMesh(D3DImage *a_texture);
	~BillboardMesh();
private:
	
	void SetShaderHandlers();

	
	int m_numBlocks;
	D3DXVECTOR3 m_blockOffset;
};
#endif