#ifndef GRASS_H
#define GRASS_H

#include "D3DMesh.h"

struct GrassVertex
{
	GrassVertex() :pos(0.0f, 0.0f, 0.0f), tex0(0.0f, 0.0f), amplitude(0.0f){}
	GrassVertex(const D3DXVECTOR3 &v, const D3DXVECTOR2 &uv, float amp) : pos(v), tex0(uv), amplitude(amp){}
	D3DXVECTOR3 pos;
	D3DXVECTOR3 quadPos;
	D3DXVECTOR2 tex0;
	float amplitude;
	D3DCOLOR colorOffset;
	static IDirect3DVertexDeclaration9 * Decl;
};

class Grass : public D3DMesh
{
public:
	Grass();
	~Grass();
private:
	void BuildGrass();
	void SetShaderHandlers();

	void BuildGrassFin(GrassVertex *v, WORD *k, int & indexOffset, D3DXVECTOR3 &worldPos, D3DXVECTOR3 &scale);
};
#endif