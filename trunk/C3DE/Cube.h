#ifndef CUBE_H
#define CUBE_H

#include "D3DMesh.h"



class Cube : public D3DMesh
{
public:
	Cube();
	~Cube();
	

	void SetShaderHandlers();

protected:

	
	D3DXHANDLE  m_hTex;
	D3DXHANDLE	m_shaderAlpha;//galpha

	
	
};
#endif

