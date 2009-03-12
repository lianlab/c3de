#ifndef TREE2_H
#define TREE2_H

#include "D3DMesh.h"



class Tree2 : public D3DMesh
{
public:
	Tree2();
	~Tree2();
	

	void SetShaderHandlers();

	void PreRender(Renderer * a_renderer);
	void PosRender(Renderer * a_renderer);

	
protected:

	
	D3DXHANDLE  m_hTex;
	D3DXHANDLE	m_shaderAlpha;//galpha

	
	
};
#endif

