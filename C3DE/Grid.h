#ifndef GRID_H
#define GRID_H

#include "D3DMesh.h"

class Grid : public D3DMesh
{
public:
	Grid(int numRows, int numCols, float dx, float dz/*, std::vector<D3DXVECTOR3>& verts, std::vector<DWORD>& indices*/);
	~Grid();

	void SetEffectHandles(ID3DXEffect* fx);
	void InitializeEffectHandles(ID3DXEffect* fx);

private:


	D3DXHANDLE   m_hTex;

};

#endif