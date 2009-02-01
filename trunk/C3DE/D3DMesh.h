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

#if 1
struct Vertex
{
	Vertex(float _x, float _y, float _z, DWORD _color)
	{
        x = _x;  
        y = _y;   
        z = _z;
        color = _color;
	}

    float x, y, z;
    DWORD color;

	enum FVF
	{
		FVF_Flags = D3DFVF_XYZ | D3DFVF_DIFFUSE 
	};
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

struct VertexCol
{
	VertexCol()
		:pos(0.0f, 0.0f, 0.0f),
		col(0x000000ff){}
		
	VertexCol(float x, float y, float z, 
		D3DCOLOR c):pos(x,y,z), col(c){}
	VertexCol(float x, float y, float z):pos(x,y,z), col(0x000000ff){}
	VertexCol(const D3DXVECTOR3& v, D3DCOLOR c)
		:pos(v),col(c){}

	D3DXVECTOR3 pos;
	D3DCOLOR col;
	

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

	//void SetTexture(Image *tex){m_texture = tex;}

	//void SetCurrentD3DTexture(IDirect3DTexture9 *a_tex);
	
	//void SetD3DTexture(IDirect3DTexture9 *a_tex);
	//Image * GetTexture(){return m_texture;}

	vector<VertexPos> * GetVertices(){return m_vertices;}
	vector<int> * GetIndices(){return m_indices;}

	void SetVertices(vector<VertexPos> * a_vertices);
	void SetIndices(vector<int> * a_indices);

	int GetVertexSize(){return sizeof(VertexPos);}

	D3DXMATRIX GetTransformMatrix();

	
	void SetShaderHandlers();
		

	FX * GetEffect(){return m_effect;}
	void SetEffect(FX *effect){m_effect = effect;}

	void SetTransformMatrix(D3DXMATRIX matrix);

	void LoadFromXFile(	const std::string &filename, IDirect3DDevice9* a_device);

	int GetNumSubsets(){return m_numSubsets;}

	ID3DXMesh * GetXMesh(){
		return m_xMesh;
	}


	void CreateXMesh(IDirect3DDevice9 *a_device);
protected:

	//IDirect3DTexture9 *m_currentTex;

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

	ID3DXMesh *m_xMesh;

	ID3DXBuffer *m_adjBuffer;
	ID3DXBuffer * m_materialBuffer;

	void FreeTextures();
	void FreeMaterials();

	int m_ID;
	
	int m_updateTime;

	int m_numSubsets;

	D3DXMATRIX m_transformMatrix;

	
	
};
#endif

