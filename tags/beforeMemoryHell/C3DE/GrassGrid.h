#ifndef GRASS_GRID_H
#define GRASS_GRID_H

#include "D3DMesh.h"
#include "Grass.h"

class GrassGrid : public D3DMesh
{
public:
	GrassGrid(int a_numBlockRows, int a_numBlocksCols, D3DXVECTOR3 a_blockOffset, D3DImage * a_texture, float t_randomPositionOffset = -1.0f, float t_randomScaleOffset = -1.0f);
	~GrassGrid();
	void Update(int deltaTime);
private:
	void BuildGrass();
	void SetShaderHandlers();	

	int m_numBlocksRows;
	int m_numBlocksCols;
	D3DXVECTOR3 m_blockOffset;
	float m_randomPositionOffset;
	float m_randomScaleOffset;

	float m_time;
};
#endif