#ifndef CASTLE_H
#define CASTLE_H

#include "D3DMesh.h"



class Castle : public D3DMesh
{
public:
	Castle();
	~Castle();
	

	void SetShaderHandlers();

	void PreRender(Renderer * a_renderer);
	void PosRender(Renderer * a_renderer);

	
protected:

	
	D3DXHANDLE  m_hTex;
	D3DXHANDLE	m_shaderAlpha;//galpha

	
	
};
#endif

