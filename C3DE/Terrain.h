#ifndef TERRAIN_H
#define TERRAIN_H

#include "D3DMesh.h"

class Terrain : public D3DMesh
{
	public:
	Terrain(int a_id, int a_rows, int a_cols, IDirect3DDevice9* a_device, IDirect3DTexture9 *a_texture, float maxHeight, float cellSize = 1.0f);
	~Terrain();

	int GetID(){return m_id;}

	void SetShaderHandlers();

private:

	//D3DXHANDLE   m_hTex;

protected:
	void InitializeEffectHandles();
	int m_id;
};
#endif
