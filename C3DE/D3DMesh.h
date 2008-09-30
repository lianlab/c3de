#ifndef D3DMESH_H
#define D3DMESH_H

#include "Mesh.h"
#include <d3dx9.h>
#include <vector>
#include "D3DCommonDefs.h"
#include "D3DImage.h"

using namespace std;

//BOOK
#if 0
struct VertexPos
{
	VertexPos():pos(0.0f, 0.0f, 0.0f){}
	VertexPos(float x, float y, float z):pos(x,y,z){}
	VertexPos(const D3DXVECTOR3 &v):pos(v){}

	static IDirect3DVertexDeclaration9 *Decl;

	D3DXVECTOR3 pos;	
};

struct VertexPos
{
	VertexPos()
		:pos(0.0f, 0.0f, 0.0f),
		normal(0.0f, 0.0f, 0.0f){}
	VertexPos(float x, float y, float z, 
		float nx=0.0f, float ny=1.0f, float nz=0.0f):pos(x,y,z), normal(nx,ny,nz){}
	VertexPos(const D3DXVECTOR3& v, const D3DXVECTOR3& n)
		:pos(v),normal(n){}
	

	D3DXVECTOR3 pos;
	D3DXVECTOR3 normal;
	static IDirect3DVertexDeclaration9* Decl;
};
#endif

struct VertexPos
{
	VertexPos()
		:pos(0.0f, 0.0f, 0.0f),
		normal(0.0f, 0.0f, 0.0f),
		tex0(0.0f, 0.0f){}
	VertexPos(float x, float y, float z, 
		float nx = 0.0f, float ny = 1.0f, float nz = 0.0f,
		float u = 0.0f, float v=0.0f):pos(x,y,z), normal(nx,ny,nz), tex0(u,v){}
	VertexPos(const D3DXVECTOR3& v, const D3DXVECTOR3& n, const D3DXVECTOR2& uv)
		:pos(v),normal(n), tex0(uv){}

	D3DXVECTOR3 pos;
	D3DXVECTOR3 normal;
	D3DXVECTOR2 tex0;

	static IDirect3DVertexDeclaration9* Decl;
};


class D3DMesh : public Mesh
{
public:
	D3DMesh();
	~D3DMesh();
	IDirect3DVertexDeclaration9 * GetVertexDeclaration(){return m_vertexDeclaration;}
	void SetVertexDeclaration(IDirect3DVertexDeclaration9 *vertexDeclaration){m_vertexDeclaration = vertexDeclaration;}
	IDirect3DVertexBuffer9 * GetVertexBuffer();
	IDirect3DIndexBuffer9 * GetIndexBuffer();
	void SetBuffers(IDirect3DVertexBuffer9 *vertexBuffer, IDirect3DIndexBuffer9 *indexBuffer);
	
	void Update(int deltaTime);

	void SetTexture(Image *tex){m_texture = tex;}
	Image * GetTexture(){return m_texture;}

	vector<VertexPos> * GetVertices(){return m_vertices;}
	vector<int> * GetIndices(){return m_indices;}

	int GetVertexSize(){return sizeof(VertexPos);}

	D3DXMATRIX GetTransformMatrix();

	//called for setting shaders variables before drawing in the D3DRenderer
	virtual void SetEffectHandles(ID3DXEffect*) = 0;

	//initializes any effect Handles
	virtual void InitializeEffectHandles(ID3DXEffect* fx) = 0;

	void Translate(float x, float y, float z);
	float GetX(){return m_x;}
	float GetY(){return m_y;}
	float GetZ(){return m_z;}

	virtual D3DXHANDLE *GetShaderViewMatrix(){return m_shaderViewMatrix;}
	virtual D3DXHANDLE *GetShaderTechnique(){return m_shaderTechnique;}
	virtual D3DXHANDLE *GetShaderWorldMatrix(){return m_shaderWorldMatrix;}
	virtual D3DXHANDLE *GetShaderWorldInverseTransposeMatrix(){return m_shaderWorldInverseTransposeMatrix;}
	virtual D3DXHANDLE *GetShaderEyePosition(){return m_shaderEyePosition;}

	
	
protected:
	IDirect3DVertexBuffer9 * m_vertexBuffer;
	IDirect3DIndexBuffer9 * m_indexBuffer;
	IDirect3DVertexDeclaration9 *m_vertexDeclaration;

	vector<VertexPos> *m_vertices;
	vector<int> *m_indices;

	
	int m_updateTime;

	bool m_fxHandlesInitialized;

	ID3DXEffect * m_effect;

	D3DXHANDLE *m_shaderWorldMatrix;//gWorld
	D3DXHANDLE *m_shaderWorldInverseTransposeMatrix;//gWorldInverseTranspose
	D3DXHANDLE *m_shaderEyePosition;//gEyePosW
	D3DXHANDLE *m_shaderViewMatrix;//gWVP	
	D3DXHANDLE *m_shaderTechnique;

	
	
};
#endif

