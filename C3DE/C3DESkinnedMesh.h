#ifndef C3DE_SKINNED_MESH_H
#define C3DE_SKINNED_MESH_H

#include "D3DMesh.h"



class C3DESkinnedMesh : public D3DMesh
{
public:
	C3DESkinnedMesh();
	~C3DESkinnedMesh();	
	void SetShaderHandlers();

protected:

	
	//D//3DXHANDLE  m_hTex;
	//D3DXHANDLE	m_shaderAlpha;//galpha

	//D3DXMATRIX m_matrices[2];

	D3DXMATRIX *m_roots;
	D3DXMATRIX *m_currentFrameToRoots;
	
	
};
#endif

