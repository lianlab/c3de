#ifndef LANDSCAPE_MESH_H
#define LANDSCAPE_MESH_H

#include "D3DMesh.h"



class LandscapeMesh : public D3DMesh
{
public:
	LandscapeMesh(int a_meshId, int a_texId);
	~LandscapeMesh();
	

	void SetShaderHandlers();

	void UniformScale(float a_value);

	void PreRender(Renderer * a_renderer);
	void PosRender(Renderer * a_renderer);

	
protected:

	
	D3DXHANDLE  m_hTex;
	D3DXHANDLE	m_shaderAlpha;//galpha

	
	
};
#endif

