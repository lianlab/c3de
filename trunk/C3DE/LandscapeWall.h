#ifndef LANDSCAPE_WALL_H
#define LANDSCAPE_WALL_H

#include "D3DMesh.h"



class LandscapeWall : public D3DMesh
{
public:
	LandscapeWall(int texID);
	~LandscapeWall();

	void Scale(float x, float y, float z);
	

	void SetShaderHandlers();

protected:

	
	D3DXHANDLE  m_hTex;
	D3DXHANDLE	m_shaderAlpha;//galpha

	
	
};
#endif

