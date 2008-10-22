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

	//void SetPosition(float x, float y, float z);
	//float GetX(){return m_x;}
	//float GetY(){return m_y;}
	//float GetZ(){return m_z;}	

	void SetShaderHandlers(){}

#if 0
	

	virtual void SetLightParameters(D3DXCOLOR ambientLightColor, D3DXCOLOR diffuseLightColor,
							D3DXCOLOR specularLightColor, D3DXVECTOR3 lightPosition, 
							D3DXVECTOR3 lightDirection, D3DXVECTOR3 lightAttenuation,
							float spotLightPower){};
	
	virtual void SetWorldParameters(D3DXMATRIX worldMatrix, D3DXMATRIX worldViewProjection,
									D3DXMATRIX worldInverseTranspose, D3DXVECTOR3 eyePosition){};

	virtual void SetPreRenderEffectHandles() = 0;
	virtual void CommitEffectHandles() = 0;


	int GetNumShaderPasses(){return m_numShaderPasses;}

	virtual void BeginShaderPass(int pass){}
	virtual void EndShaderPass(int pass){}
	virtual void BeginShader(){}
	virtual void EndShader(){}

#endif			
	//ID3DXEffect * GetEffect(){return m_effect;}

	FX * GetEffect(){return m_effect;}

protected:
	UINT m_numShaderPasses;
	IDirect3DVertexBuffer9 * m_vertexBuffer;
	IDirect3DIndexBuffer9 * m_indexBuffer;
	IDirect3DVertexDeclaration9 *m_vertexDeclaration;

	vector<VertexPos> *m_vertices;
	vector<int> *m_indices;

	
	FX * m_effect;
	
	int m_updateTime;

#if 0
	bool m_fxHandlesInitialized;

	ID3DXEffect * m_effect;

	D3DXHANDLE m_shaderWorldMatrix;//gWorld R
	D3DXHANDLE m_shaderWorldInverseTransposeMatrix;//gWorldInverseTranspose R
	D3DXHANDLE m_shaderEyePosition;//gEyePosW R
	D3DXHANDLE m_shaderViewMatrix;//gWVP	R
	D3DXHANDLE m_shaderTransformMatrix;//gSpotPower
	D3DXHANDLE m_shaderTechnique; //R

	D3DXHANDLE m_shaderAmbientLightMaterial;//gAmbientLigh
	D3DXHANDLE m_shaderDiffuseLightMaterial;//gDiffuseLight
	D3DXHANDLE m_shaderSpecularLightMaterial;//gSpecularLight
	D3DXHANDLE m_shaderLightPosition;//gLightPosW R
	D3DXHANDLE m_shaderLightDirection;//gLightDirW R
	D3DXHANDLE m_shaderLightAttenuation;//gAttenuation012
	D3DXHANDLE m_shaderSpotLightPower;//gSpotPower



	D3DXHANDLE m_shaderObjectAmbientMaterial;//gAmbientMtrl
	D3DXHANDLE m_shaderObjectDiffuseMaterial;//gDiffuseMtrl
	D3DXHANDLE m_shaderObjectSpecularMaterial;//gSpecMtrl
	D3DXHANDLE m_shaderSpecularLightPower;//gSpecPower
#endif

};
#endif

