#ifndef TREE3_H
#define TREE3_H

#include "D3DMesh.h"



class Tree3 : public D3DMesh
{
public:
	Tree3();
	~Tree3();
	

	void SetShaderHandlers();

	void PreRender(Renderer * a_renderer);
	void PosRender(Renderer * a_renderer);

	
protected:

	
	D3DXHANDLE  m_hTex;
	D3DXHANDLE	m_shaderAlpha;//galpha

	
	
};
#endif

