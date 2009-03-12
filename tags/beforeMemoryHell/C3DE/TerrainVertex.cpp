#include "TerrainVertex.h"

const DWORD TerrainVertex::FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE;

TerrainVertex::TerrainVertex()
{

}

TerrainVertex::TerrainVertex(D3DXVECTOR3 pos, D3DCOLOR col)
{
	position = pos;
	color = col;
	normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
}