#ifndef PATCH_H
#define PATCH_H

#include <d3dx9.h>
#include "HeightMap.h"
#include "TerrainVertex.h"

struct Patch
{
	Patch();
	~Patch();
	void Release();
	HRESULT CreateMesh(HeightMap &hm, RECT source, IDirect3DDevice9 *Dev, int index);
	void Render();
	IDirect3DDevice9 *m_pDevice;
	ID3DXMesh *m_pMesh;
};
#endif