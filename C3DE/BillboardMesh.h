#ifndef BILLBOARD_MESH_H
#define BILLBOARD_MESH_H

#include "D3DMesh.h"

struct BillboardVertex
{
	BillboardVertex() :pos(0.0f, 0.0f, 0.0f), tex0(0.0f, 0.0f), amplitude(0.0f){}
	BillboardVertex(const D3DXVECTOR3 &v, const D3DXVECTOR2 &uv, float amp) : pos(v), tex0(uv), amplitude(amp){}
	D3DXVECTOR3 pos;
	D3DXVECTOR3 quadPos;
	D3DXVECTOR2 tex0;
	float amplitude;
	D3DCOLOR colorOffset;
	static IDirect3DVertexDeclaration9 * Decl;
};

class BillboardMesh : public D3DMesh
{
public:
	BillboardMesh(D3DImage *a_texture);
	~BillboardMesh();
private:
	void BuildBillboard();
	void SetShaderHandlers();

	
	int m_numBlocks;
	D3DXVECTOR3 m_blockOffset;
};
#endif