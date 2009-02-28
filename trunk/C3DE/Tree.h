#ifndef TREE_H
#define TREE_H

#include "D3DMesh.h"



class Tree : public D3DMesh
{
public:
	Tree();
	~Tree();
	

	void SetShaderHandlers();

	void PreRender(Renderer * a_renderer);
	void PosRender(Renderer * a_renderer);

	
protected:

	
	D3DXHANDLE  m_hTex;
	D3DXHANDLE	m_shaderAlpha;//galpha

	
	
};
#endif

