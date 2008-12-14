//=============================================================================
// SkinnedMesh.h by Frank Luna (C) 2005 All Rights Reserved.
//=============================================================================

#ifndef D3D_SKINNED_MESH_H
#define D3D_SKINNED_MESH_H

#include "AllocMeshHierarchy.h"
#include "D3DMesh.h"
#include <string>
#include <vector>


const float EPSILON  = 0.001f;

#if 0
struct VertexPNT
{
	VertexPNT()
		:pos(0.0f, 0.0f, 0.0f),
		normal(0.0f, 0.0f, 0.0f),
		tex0(0.0f, 0.0f){}
	VertexPNT(float x, float y, float z, 
		float nx, float ny, float nz,
		float u, float v):pos(x,y,z), normal(nx,ny,nz), tex0(u,v){}
	VertexPNT(const D3DXVECTOR3& v, const D3DXVECTOR3& n, const D3DXVECTOR2& uv)
		:pos(v),normal(n), tex0(uv){}

	D3DXVECTOR3 pos;
	D3DXVECTOR3 normal;
	D3DXVECTOR2 tex0;

	static IDirect3DVertexDeclaration9* Decl;
};

#endif

class D3DSkinnedMesh : public D3DMesh
{
public:
	
	D3DSkinnedMesh();
	~D3DSkinnedMesh();

	void LoadFromXFile(const std::string &filename, IDirect3DDevice9 *a_device);

	UINT numVertices();
	UINT numTriangles();
	UINT numBones();
	const D3DXMATRIX* getFinalXFormArray();

	virtual void Update(int deltaTime);
	//void draw();

	
protected:
	
	D3DXFRAME* findNodeWithMesh(D3DXFRAME* frame);
	bool hasNormals(ID3DXMesh* mesh);
	void buildSkinnedMesh(ID3DXMesh* mesh);
	void buildToRootXFormPtrArray();
	void buildToRootXForms(FrameEx* frame, D3DXMATRIX& parentsToRoot);

	// We do not implement the required functionality to do deep copies,
	// so restrict copying.
	D3DSkinnedMesh(const D3DSkinnedMesh& rhs);
	D3DSkinnedMesh& operator=(const D3DSkinnedMesh& rhs);
	

protected:
	
	//ID3DXMesh*     mSkinnedMesh;
	D3DXFRAME*     mRoot;
	DWORD          mMaxVertInfluences;
	DWORD          mNumBones;
	ID3DXSkinInfo* mSkinInfo;
	ID3DXAnimationController* mAnimCtrl;  
	
	std::vector<D3DXMATRIX>  mFinalXForms;
	std::vector<D3DXMATRIX*> mToRootXFormPtrs;

	static const int MAX_NUM_BONES_SUPPORTED = 35; 

	IDirect3DDevice9 *m_device;
	
};

#endif // SKINNED_MESH_H