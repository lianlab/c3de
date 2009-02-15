#ifndef TERRAIN_H
#define TERRAIN_H

#include "D3DMesh.h"

struct SubGrid
{
	const static int NUM_ROWS  = 33;
	const static int NUM_COLS  = 33;
	const static int NUM_TRIS  = (NUM_ROWS-1)*(NUM_COLS-1)*2;
	const static int NUM_VERTS = NUM_ROWS*NUM_COLS;
};

class Terrain : public D3DMesh
{
	public:
	Terrain(int a_id, int a_rows, int a_cols, IDirect3DDevice9* a_device, IDirect3DTexture9 *a_texture, float maxHeight, float cellSize = 1.0f);
	~Terrain();



	int GetID(){return m_id;}

	void SetShaderHandlers();

	vector<Mesh *> *GetSubMeshes(){return m_subMeshes;}

	void fleps();

	IDirect3DTexture9 *m_eps;

private:
	void CreateMeshBuffers(IDirect3DDevice9 *a_device);

	void GenerateXMesh(IDirect3DDevice9* a_device);
	//D3DXHANDLE   m_hTex;

	vector<Mesh *> *m_subMeshes;

	int m_fleps;

protected:
	void InitializeEffectHandles();
	int m_id;
};
#endif
