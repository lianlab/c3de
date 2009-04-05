#ifndef DWARF_H
#define DWARF_H

#include "D3DMesh.h"



class Dwarf : public D3DMesh
{
public:
	Dwarf();
	~Dwarf();
	

	void SetShaderHandlers();

	void PreRender(Renderer * a_renderer);
	void PosRender(Renderer * a_renderer);

	
protected:

	
	D3DXHANDLE  m_hTex;
	D3DXHANDLE	m_shaderAlpha;//galpha

	
	
};
#endif

