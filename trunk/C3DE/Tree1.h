#ifndef TREE1_H
#define TREE1_H

#include "D3DMesh.h"



class Tree1 : public D3DMesh
{
public:
	Tree1();
	~Tree1();
	

	void SetShaderHandlers();

	void PreRender(Renderer * a_renderer);
	void PosRender(Renderer * a_renderer);

	
protected:

	
	D3DXHANDLE  m_hTex;
	D3DXHANDLE	m_shaderAlpha;//galpha

	
	
};
#endif

