#ifndef D3DMESH_H
#define D3DMESH_H

#include "Mesh.h"
#include <d3dx9.h>
#include <vector>
#include "D3DCommonDefs.h"
#include "D3DImage.h"
#include "ShaderManager.h"
#include "FX.h"

using namespace std;


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
	
	void SetPosition(float x, float y, float z);
	void Scale(float x, float y, float z);


	void Update(int deltaTime);

	void SetTexture(Image *tex){m_texture = tex;}
	Image * GetTexture(){return m_texture;}

	vector<VertexPos> * GetVertices(){return m_vertices;}
	vector<int> * GetIndices(){return m_indices;}

	int GetVertexSize(){return sizeof(VertexPos);}

	D3DXMATRIX GetTransformMatrix();

	
	void SetShaderHandlers();
		

	FX * GetEffect(){return m_effect;}
	void SetEffect(FX *effect){m_effect = effect;}

	void SetTransformMatrix(D3DXMATRIX matrix);
	

protected:
	UINT m_numShaderPasses;
	IDirect3DVertexBuffer9 * m_vertexBuffer;
	IDirect3DIndexBuffer9 * m_indexBuffer;
	IDirect3DVertexDeclaration9 *m_vertexDeclaration;

	vector<VertexPos> *m_vertices;
	vector<int> *m_indices;

	D3DXHANDLE m_shaderObjectAmbientMaterial;//gAmbientMtrl
	D3DXHANDLE m_shaderObjectDiffuseMaterial;//gDiffuseMtrl
	D3DXHANDLE m_shaderObjectSpecularMaterial;//gSpecMtrl
	D3DXHANDLE m_shaderSpecularLightPower;//gSpecPower

	
	FX * m_effect;
	
	int m_updateTime;

	D3DXMATRIX m_transformMatrix;
	
};
#endif

