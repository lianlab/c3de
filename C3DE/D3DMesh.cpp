#include "D3DMesh.h"
#include "DebugMemory.h"

IDirect3DVertexDeclaration9* VertexPos::Decl = 0;

D3DMesh::D3DMesh()
{
	
	

	m_numShaderPasses = 1;

	
	//m_fxHandlesInitialized = false;

	
	
}


D3DMesh::~D3DMesh()
{
	if(m_vertices)
	{
		delete m_vertices;
		m_vertices = NULL;
	}

	if(m_indices)
	{
		delete m_indices;
		m_indices =NULL;
	}

	if(m_texture)
	{
		delete m_texture;
		m_texture = NULL;
	}
}

void D3DMesh::SetShaderHandlers()
{
	m_effect->SetTransformMatrix(GetTransformMatrix());
}

void D3DMesh::Update(int deltaTime)
{
	m_updateTime = deltaTime;
	
}


D3DXMATRIX D3DMesh::GetTransformMatrix()
{
	D3DXMATRIX T;
	D3DXMATRIX S;
	D3DXMATRIX O;
	
	D3DXMatrixScaling(&S, m_scaleX, m_scaleY, m_scaleZ);
	
	D3DXMatrixTranslation(&T, m_x, m_y, m_z);

	D3DXMatrixMultiply(&O, &S, &T);
	return O;
}

void D3DMesh::SetPosition(float x, float y, float z)
{
	m_x = x;m_y=y;m_z=z;
	
}

void D3DMesh::Scale(float x, float y, float z)
{
	m_scaleX=x;m_scaleY=y;m_scaleZ=z;
	//m_effect->SetTransformMatrix(GetTransformMatrix());
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
