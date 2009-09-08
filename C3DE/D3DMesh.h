#ifndef D3DMESH_H
#define D3DMESH_H

#include "Mesh.h"
#include <d3dx9.h>
#include <vector>
#include "D3DCommonDefs.h"
#include "D3DImage.h"
#include "ShaderManager.h"
#include "FX.h"
#include "AABB.h"
#include "OBB.h"
#include "TopCollisionArea.h"


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
#if 0
struct VertexPosSkin
{
	VertexPosSkin()
		:pos(0.0f, 0.0f, 0.0f),
		normal(0.0f, 0.0f, 0.0f),
		tex0(0.0f, 0.0f),jiraya(0.0f)
		//tex0(0.0f, 0.0f)
	{}
	VertexPosSkin(float x, float y, float z, 
		float nx = 0.0f, float ny = 1.0f, float nz = 0.0f,
		float u = 0.0f, float v=0.0f, float a_jiraya = 1.0f){pos = D3DXVECTOR3(x,y,z); normal = D3DXVECTOR3(nx,ny,nz); tex0 = D3DXVECTOR2(u,v);jiraya = a_jiraya;}
		//float u = 0.0f, float v=0.0f):pos(x,y,z), normal(nx,ny,nz), tex0(u,v){}
	VertexPosSkin(const D3DXVECTOR3& v, const D3DXVECTOR3& n, const D3DXVECTOR2& uv)
	//VertexPosSkin(const D3DXVECTOR3& v, const D3DXVECTOR3& n, const D3DXVECTOR2& uv)
		:pos(v),normal(n), tex0(uv){jiraya = 0.0f;}
		//:pos(v),normal(n), tex0(uv){}

	D3DXVECTOR3 pos;
	D3DXVECTOR3 normal;
	D3DXVECTOR2 tex0;
	float jiraya;

	static IDirect3DVertexDeclaration9* Decl;
};
#endif

struct VertexPosSkin
{
	
	VertexPosSkin(float x, float y, float z, 
		float nx = 0.0f, float ny = 1.0f, float nz = 0.0f,
		float u = 0.0f, float v=0.0f, float a_jiraya = 0.0f ,int index = 0);
		

	D3DXVECTOR3 pos;
	D3DXVECTOR3 normal;
	D3DXVECTOR2 tex0;
	float jiraya;
	int index;

	static IDirect3DVertexDeclaration9* Decl;
};

struct VertexPosBones
{
	
	VertexPosBones(float x, float y, float z, 
		float nx = 0.0f, float ny = 1.0f, float nz = 0.0f,
		float u = 0.0f, float v=0.0f, float a_boneWeight0 = 0.0f ,int a_boneIndex0 = -1, int a_boneIndex1 = -1);
		

	D3DXVECTOR3 pos;
	D3DXVECTOR3 normal;
	D3DXVECTOR2 tex0;
	float boneWeight0;
	int boneIndex0;
	int boneIndex1;

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

	
	vector<VertexPos> * GetVertices(){return m_vertices;}
	vector<VertexPosSkin> * GetVertices2(){return m_vertices2;}
	vector<int> * GetIndices(){return m_indices;}

	void SetVertices(vector<VertexPos> * a_vertices);
	void SetIndices(vector<int> * a_indices);

	int GetVertexSize(){return sizeof(VertexPos);}
	//int GetVertexSize2(){return sizeof(VertexPosSkin);}

	D3DXMATRIX GetTransformMatrix();

	
	void SetShaderHandlers();
		

	FX * GetEffect(){return m_effect;}
	void SetEffect(FX *effect){m_effect = effect;}

	void SetTransformMatrix(D3DXMATRIX matrix);

	void LoadFromXFile(	const std::string &filename, IDirect3DDevice9* a_device);

	void LoadFromC3DEFile(char *meshBuffer);
	int GetNumSubsets(){return m_numSubsets;}

	ID3DXMesh * GetXMesh(){
		return m_xMesh;
	}

	void SetXMesh(ID3DXMesh *a_mesh);

	void CreateXMesh(IDirect3DDevice9 *a_device);

	AABB* GetBoundingBox();

	void SetBoundingBox(D3DXVECTOR3 a_min, D3DXVECTOR3 a_max);

	void SetBoundingBox(AABB *a_aabb){m_boundingBox = a_aabb;}

	bool Collides(D3DMesh *target);

	//void CalculateRealBoxPoints();
	//void SetCollisionPoints(D3DXVECTOR3 a_min, D3DXVECTOR3 a_max);
	//AABB *GetCollisionPoints();

	TopCollisionArea * GetTopCollisionArea();
	void SetTopCollisionArea(D3DXVECTOR3 upLeft, D3DXVECTOR3 upRight, D3DXVECTOR3 downLeft, D3DXVECTOR3 downRight);

	float GetCollisionRadius();
protected:

	void CalculateTopCollisionArea();
	void CalculateCollisionRadius();

	void CalculateOBB(D3DXVECTOR3 &meshMin, D3DXVECTOR3 &meshMax);
	float m_collisionRadius;

	D3DXVECTOR3 m_fleps;
	D3DXVECTOR3 m_auei;
	AABB *m_boundingBox;
	AABB *m_transformedBox;

	TopCollisionArea *m_topCollisionArea;

	//AABB *m_collisionPoints;
	//D3DXVECTOR3 m_collisionPointMax;


	
	UINT m_numShaderPasses;
	IDirect3DVertexBuffer9 * m_vertexBuffer;
	IDirect3DIndexBuffer9 * m_indexBuffer;
	IDirect3DVertexDeclaration9 *m_vertexDeclaration;

	vector<VertexPos> *m_vertices;
	vector<VertexPosSkin> *m_vertices2;
	vector<VertexPosBones> *m_vertices3;
	vector<int> *m_indices;

	D3DXHANDLE m_shaderObjectAmbientMaterial;//gAmbientMtrl
	D3DXHANDLE m_shaderObjectDiffuseMaterial;//gDiffuseMtrl
	D3DXHANDLE m_shaderObjectSpecularMaterial;//gSpecMtrl
	D3DXHANDLE m_shaderSpecularLightPower;//gSpecPower

	
	OBB *m_obb;
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

	int * m_hack;





	float axisX[4];
	float axisY[4];

	
	float aPointsX[4];
	float aPointsY[4];

	
	float bPointsX[4];
	float bPointsY[4];

	
	float aProjectedX[4];
	float aProjectedY[4];
	
	float bProjectedX[4];
	float bProjectedY[4];

	
	
};
#endif

