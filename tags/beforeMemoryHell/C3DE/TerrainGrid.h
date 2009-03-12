#ifndef TERRAIN_GRID_H
#define TERRAIN_GRID_H

#include "D3DMesh.h"

class TerrainGrid : public D3DMesh
{
public:
	TerrainGrid(int a_id, int a_rows, int a_cols, IDirect3DTexture9 *a_texture, float maxHeight, float cellSize = 1.0f);
	~TerrainGrid();

	int GetID(){return m_id;}

	void SetShaderHandlers();

private:

	//D3DXHANDLE   m_hTex;

protected:
	void InitializeEffectHandles();
	int m_id;
};

#endif