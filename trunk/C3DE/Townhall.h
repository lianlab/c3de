#ifndef TOWNHALL_H
#define TOWNHALL_H

#include "D3DMesh.h"



class Townhall : public D3DMesh
{
public:
	Townhall();
	~Townhall();
	

	void SetShaderHandlers();

	void PreRender(Renderer * a_renderer);
	void PosRender(Renderer * a_renderer);

	
protected:

	
	D3DXHANDLE  m_hTex;
	D3DXHANDLE	m_shaderAlpha;//galpha

	
	
};
#endif

