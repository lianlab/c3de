#ifndef SKYBOX_H
#define SKYBOX_H

#include "D3DMesh.h"

class Skybox : public D3DMesh
{
public:
	Skybox(float size);
	~Skybox();

	void SetShaderHandlers();

	protected:

	
	D3DXHANDLE  m_hTex;
	D3DXHANDLE	m_shaderAlpha;//galpha
};

#endif