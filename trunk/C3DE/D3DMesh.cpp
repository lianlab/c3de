#include "D3DMesh.h"

IDirect3DVertexDeclaration9* VertexPos::Decl = 0;

D3DMesh::D3DMesh()
{
	m_effect = NULL;
	m_x = 0;
	m_y = 0;
	m_z = 0;

	picles = 0.0f;
}

D3DMesh::~D3DMesh()
{

}

void D3DMesh::Update(int deltaTime)
{
	m_updateTime = deltaTime;
	picles += 0.001f;
}


void D3DMesh::SetEffectHandles()
{ 
	if(m_effect)
	{
		m_shaderTechnique = m_effect->GetTechniqueByName("HeightColorTech");
		m_shaderViewMatrix  = m_effect->GetParameterByName(0, "gWVP");
		m_shaderUpdateTime = m_effect->GetParameterByName(0, "gTime");
	}	
}

D3DXHANDLE D3DMesh::GetShaderUpdateTime()
{
	return m_shaderUpdateTime;
}


D3DXHANDLE D3DMesh::GetShaderViewMatrix()
{
	return m_shaderViewMatrix;
}

D3DXHANDLE D3DMesh::GetShaderTechnique()
{
	return m_shaderTechnique;
}

D3DXMATRIX D3DMesh::GetTransformMatrix()
{
	D3DXMATRIX T;
	D3DXMatrixTranslation(&T, m_x, m_y, m_z);
	return T;
}

void D3DMesh::Translate(float x, float y, float z)
{
	m_x += x;
	m_y += y;
	m_z += z;

}

IDirect3DVertexBuffer9 * D3DMesh::GetVertexBuffer()
{
	return m_vertexBuffer;
}

IDirect3DIndexBuffer9 * D3DMesh::GetIndexBuffer()
{
	return m_indexBuffer;
}

void D3DMesh::SetBuffers(IDirect3DVertexBuffer9 *vertexBuffer, IDirect3DIndexBuffer9 *indexBuffer)
{
	m_vertexBuffer = vertexBuffer;
	m_indexBuffer = indexBuffer;
}
