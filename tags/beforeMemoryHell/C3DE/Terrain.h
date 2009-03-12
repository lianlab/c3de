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

	vector<D3DMesh* > *GetSubMeshes(){return m_subMeshes;}

	float getHeight(float x, float z){return 0.0f;}

	D3DXVECTOR2 GetCoords(float x, float z);

	float GetHeight(float x, float z);

	vector<AABB*> * GetBoundingBoxes(){return m_boundingBoxes;}

private:

	void BuildSubGridMesh(RECT& R, VertexPos* gridVerts);
	
	//D3DXHANDLE   m_hTex;

	vector<D3DMesh*> *m_subMeshes;

	int m_fleps;

	float m_cellSize;

protected:
	IDirect3DDevice9* m_device;
	void InitializeEffectHandles();
	int m_id;

	vector<AABB*> *m_boundingBoxes;

	int m_numCols;
	int m_numRows;

	float *m_heights;
};
#endif
