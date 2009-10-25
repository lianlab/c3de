#ifndef GAME_MESH_H
#define GAME_MESH_H

#include "D3DMesh.h"



class GameMesh : public D3DMesh
{
public:
	GameMesh(int a_meshId, int a_texId, bool a_calculateAABB = true);
	
	~GameMesh();
	

	void SetShaderHandlers();

	//void UniformScale(float a_value);

	void PreRender(Renderer * a_renderer);
	void PosRender(Renderer * a_renderer);

	
protected:

	
	D3DXHANDLE  m_hTex;
	D3DXHANDLE	m_shaderAlpha;//galpha

	
	
};
#endif

