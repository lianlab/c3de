#ifndef TREE0_H
#define TREE0_H

#include "D3DMesh.h"



class Tree0 : public D3DMesh
{
public:
	Tree0();
	~Tree0();
	

	void SetShaderHandlers();

	void PreRender(Renderer * a_renderer);
	void PosRender(Renderer * a_renderer);

	
protected:

	
	D3DXHANDLE  m_hTex;
	D3DXHANDLE	m_shaderAlpha;//galpha

	
	
};
#endif

