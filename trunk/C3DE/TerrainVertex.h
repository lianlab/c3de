#ifndef TERRAIN_VERTEX_H
#define TERRAIN_VERTEX_H

#include <d3dx9.h>
#include <vector>

struct TerrainVertex
{
	TerrainVertex();
	TerrainVertex(D3DXVECTOR3 pos, D3DCOLOR col);
	D3DXVECTOR3 position, normal;
	D3DCOLOR color;
	static const DWORD FVF;
};
#endif
