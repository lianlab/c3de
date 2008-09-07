#include "D3DMesh.h"

IDirect3DVertexDeclaration9* VertexPos::Decl = 0;

D3DMesh::D3DMesh()
{
	m_effect = NULL;
}

D3DMesh::~D3DMesh()
{

}

void D3DMesh::Update(int deltaTime)
{

}


void D3DMesh::SetEffectHandles()
{
 int fdsggffd=987;
}


D3DXHANDLE D3DMesh::GetShaderViewMatrix()
{
	return m_shaderViewMatrix;
}

D3DXHANDLE D3DMesh::GetShaderTechnique()
{
	return m_shaderTechnique;
}

void D3DMesh::Translate(float x, float y, float z)
{
	m_x = x;
	m_y = y;
	m_z = z;

	D3DXMATRIX T;
	D3DXMatrixTranslation(&T, x, y, z);
	
	VertexPos *v = 0;
	HR(m_vertexBuffer->Lock(0,0,(void**)&v,0));

	int vertexSize = m_vertices->size();

	for(int i = 0; i < vertexSize; i++)
	{
		VertexPos vertex = v[i];
		D3DXVECTOR3 d3dVector = vertex.pos;
		D3DXVec3TransformCoord(&d3dVector, &d3dVector, &T);

		v[i] = d3dVector;
	}
	
	HR(m_vertexBuffer->Unlock());
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
