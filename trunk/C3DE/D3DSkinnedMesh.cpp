#include "D3DSkinnedMesh.h"


//=============================================================================
// SkinnedMesh.cpp by Frank Luna (C) 2005 All Rights Reserved.
//=============================================================================

#include "AllocMeshHierarchy.h"
#include "ResourceManager.h"	
#include "DebugMemory.h"

#if 0

IDirect3DVertexDeclaration9* VertexPNT::Decl = 0;

#endif

D3DSkinnedMesh::D3DSkinnedMesh() : D3DMesh()
{
	
	m_currentAnimation = 0;

}

int D3DSkinnedMesh::GetAnimation()
{
	return m_currentAnimation;
}


void D3DSkinnedMesh::SetAnimation(int a_animationIdx)
{
	LPD3DXANIMATIONSET t_animationSet;	
	m_animCtrl->GetAnimationSet(a_animationIdx, &t_animationSet);	
	m_animCtrl->SetTrackAnimationSet(0, t_animationSet);
	m_animCtrl->ResetTime();
	m_currentAnimation = a_animationIdx;
}

void D3DSkinnedMesh::LoadFromXFile(const std::string &XFilename, IDirect3DDevice9 *a_device)
{
	
	D3DVERTEXELEMENT9 VertexPNTElements[] = 
	{
		{0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
		{0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
		D3DDECL_END()
	};	
	//HR(a_device->CreateVertexDeclaration(VertexPNTElements, &VertexPNT::Decl));
	HR(a_device->CreateVertexDeclaration(VertexPNTElements, &VertexPos::Decl));

	m_device = a_device;
	AllocMeshHierarchy allocMeshHierarchy;
	HR(D3DXLoadMeshHierarchyFromX(XFilename.c_str(), D3DXMESH_SYSTEMMEM,
		a_device, &allocMeshHierarchy, 0, /* ignore user data */ 
		&m_root,	&m_animCtrl));

	
	
	

	// In this demo we assume that the input .X file contains only one
	// mesh.  So search for that one and only mesh.
	D3DXFRAME* f = findNodeWithMesh(m_root);
	if( f == 0 ) HR(E_FAIL);
	D3DXMESHCONTAINER* meshContainer = f->pMeshContainer;
	m_skinInfo = meshContainer->pSkinInfo;
	m_skinInfo->AddRef();

	m_numBones = meshContainer->pSkinInfo->GetNumBones();
	m_finalXForms.resize(m_numBones);
	m_toRootXFormPtrs.resize(m_numBones, 0);
	
	buildSkinnedMesh(meshContainer->MeshData.pMesh);
	buildToRootXFormPtrArray();



	D3DXVECTOR3 t_min;
	D3DXVECTOR3 t_max;
	VertexPos *v = NULL;
	m_xMesh->LockVertexBuffer(0, (void**)&v);

	HR(D3DXComputeBoundingBox((D3DXVECTOR3*)v, m_xMesh->GetNumVertices(), 
		sizeof(VertexPos), &t_min, &t_max));

	m_xMesh->UnlockVertexBuffer();

	m_boundingBox = new AABB(t_min, t_max);

	
	
}

D3DSkinnedMesh::~D3DSkinnedMesh()
{
	if( m_root )
	{
		AllocMeshHierarchy allocMeshHierarchy;
		HR(D3DXFrameDestroy(m_root, &allocMeshHierarchy));
		m_root = 0;
	}

	ReleaseCOM(m_xMesh);
	ReleaseCOM(m_skinInfo);
	ReleaseCOM(m_animCtrl);
}

UINT D3DSkinnedMesh::numVertices()
{
	return m_xMesh->GetNumVertices();
}

UINT D3DSkinnedMesh::numTriangles()
{
	return m_xMesh->GetNumFaces();
}

UINT D3DSkinnedMesh::numBones()
{
	return m_numBones;
}

const D3DXMATRIX* D3DSkinnedMesh::getFinalXFormArray()
{
	return &m_finalXForms[0];
}

void D3DSkinnedMesh::Update(int deltaTime)
{
	// Animate the mesh.  The AnimationController has pointers to the  hierarchy frame
	// transform matrices.  The AnimationController updates these matrices to reflect 
	// the given pose at the current time by interpolating between animation keyframes.
	float t_time = (float) deltaTime / 1000;
	HR(m_animCtrl->AdvanceTime(t_time, 0));

	
	// Recurse down the tree and generate a frame's toRoot transform from the updated pose.
	D3DXMATRIX identity;
	D3DXMatrixIdentity(&identity);
	buildToRootXForms((FrameEx*)m_root, identity);


	// Premultiply the offset-transform to transform the vertices to the bone's local
	// coordinate system first, before applying the other transforms.
	D3DXMATRIX offsetTemp, toRootTemp;
	for(UINT i = 0; i < m_numBones; ++i)
	{
		offsetTemp = *m_skinInfo->GetBoneOffsetMatrix(i);
		toRootTemp = *m_toRootXFormPtrs[i];
		m_finalXForms[i] = offsetTemp * toRootTemp;
	}
}


D3DXFRAME* D3DSkinnedMesh::findNodeWithMesh(D3DXFRAME* frame)
{
	if( frame->pMeshContainer )
		if( frame->pMeshContainer->MeshData.pMesh != 0 )
			return frame;

	D3DXFRAME* f = 0;
	if(frame->pFrameSibling)
		if( f = findNodeWithMesh(frame->pFrameSibling) )	
			return f;

	if(frame->pFrameFirstChild)
		if( f = findNodeWithMesh(frame->pFrameFirstChild) )
			return f;

	return 0;
}

bool D3DSkinnedMesh::hasNormals(ID3DXMesh* mesh)
{
	D3DVERTEXELEMENT9 elems[MAX_FVF_DECL_SIZE];
	HR(mesh->GetDeclaration(elems));
	
	bool hasNormals = false;
	for(int i = 0; i < MAX_FVF_DECL_SIZE; ++i)
	{
		// Did we reach D3DDECL_END() {0xFF,0,D3DDECLTYPE_UNUSED, 0,0,0}?
		if(elems[i].Stream == 0xff)
			break;

		if( elems[i].Type == D3DDECLTYPE_FLOAT3 &&
			elems[i].Usage == D3DDECLUSAGE_NORMAL &&
			elems[i].UsageIndex == 0 )
		{
			hasNormals = true;
			break;
		}
	}
	return hasNormals;
}

void D3DSkinnedMesh::buildSkinnedMesh(ID3DXMesh* mesh)
{
	//====================================================================
	// First add a normal component and 2D texture coordinates component.

	D3DVERTEXELEMENT9 elements[64];
	UINT numElements = 0;
	//VertexPNT::Decl->GetDeclaration(elements, &numElements);
	VertexPos::Decl->GetDeclaration(elements, &numElements);

	ID3DXMesh* tempMesh = 0;
	HR(mesh->CloneMesh(D3DXMESH_SYSTEMMEM, elements, m_device, &tempMesh));
	 
	if( !hasNormals(tempMesh) )
		HR(D3DXComputeNormals(tempMesh, 0));

	//====================================================================
	// Optimize the mesh; in particular, the vertex cache.
	DWORD* adj = new DWORD[tempMesh->GetNumFaces()*3];
	ID3DXBuffer* remap = 0;
	HR(tempMesh->GenerateAdjacency(EPSILON, adj));
	ID3DXMesh* optimizedTempMesh = 0;
	HR(tempMesh->Optimize(D3DXMESH_SYSTEMMEM | D3DXMESHOPT_VERTEXCACHE | 
		D3DXMESHOPT_ATTRSORT, adj, 0, 0, &remap, &optimizedTempMesh));

	ReleaseCOM(tempMesh); // Done w/ this mesh.
	delete[] adj;         // Done with buffer.

	// In the .X file (specifically the array DWORD vertexIndices[nWeights]
	// data member of the SkinWeights template) each bone has an array of
	// indices which identify the vertices of the mesh that the bone influences.
	// Because we have just rearranged the vertices (from optimizing), the vertex 
	// indices of a bone are obviously incorrect (i.e., they index to vertices the bone
	// does not influence since we moved vertices around).  In order to update a bone's 
	// vertex indices to the vertices the bone _does_ influence, we simply need to specify
	// where we remapped the vertices to, so that the vertex indices can be updated to 
	// match.  This is done with the ID3DXSkinInfo::Remap method.
	HR(m_skinInfo->Remap(optimizedTempMesh->GetNumVertices(), 
		(DWORD*)remap->GetBufferPointer()));
	ReleaseCOM(remap); // Done with remap info.

	//====================================================================
	// The vertex format of the source mesh does not include vertex weights 
	// nor bone index data, which are both needed for vertex blending.
	// Therefore, we must convert the source mesh to an "indexed-blended-mesh,"
	// which does have the necessary data.

	DWORD        numBoneComboEntries = 0;
	ID3DXBuffer* boneComboTable      = 0;
	HR(m_skinInfo->ConvertToIndexedBlendedMesh(optimizedTempMesh, D3DXMESH_MANAGED | D3DXMESH_WRITEONLY,  
		MAX_NUM_BONES_SUPPORTED, 0, 0, 0, 0, &m_maxVertInfluences,
		&numBoneComboEntries, &boneComboTable, &m_xMesh));

	ReleaseCOM(optimizedTempMesh); // Done with tempMesh.
	ReleaseCOM(boneComboTable); // Don't need bone table.

#if defined(DEBUG) | defined(_DEBUG)
	// Output to the debug output the vertex declaration of the mesh at this point.
	// This is for insight only to see what exactly ConvertToIndexedBlendedMesh
	// does to the vertex declaration.
	D3DVERTEXELEMENT9 elems[MAX_FVF_DECL_SIZE];
	HR(m_xMesh->GetDeclaration(elems));
	
	OutputDebugString("\nVertex Format After ConvertToIndexedBlendedMesh\n");
	int i = 0;
	while( elems[i].Stream != 0xff ) // While not D3DDECL_END()
	{
		if( elems[i].Type == D3DDECLTYPE_FLOAT1)
			OutputDebugString("Type = D3DDECLTYPE_FLOAT1; ");
		if( elems[i].Type == D3DDECLTYPE_FLOAT2)
			OutputDebugString("Type = D3DDECLTYPE_FLOAT2; ");
		if( elems[i].Type == D3DDECLTYPE_FLOAT3)
			OutputDebugString("Type = D3DDECLTYPE_FLOAT3; ");
		if( elems[i].Type == D3DDECLTYPE_UBYTE4)
			OutputDebugString("Type = D3DDECLTYPE_UBYTE4; ");
	
		if( elems[i].Usage == D3DDECLUSAGE_POSITION)
			OutputDebugString("Usage = D3DDECLUSAGE_POSITION\n");
		if( elems[i].Usage == D3DDECLUSAGE_BLENDWEIGHT)
			OutputDebugString("Usage = D3DDECLUSAGE_BLENDWEIGHT\n");
		if( elems[i].Usage == D3DDECLUSAGE_BLENDINDICES)
			OutputDebugString("Usage = D3DDECLUSAGE_BLENDINDICES\n");
		if( elems[i].Usage == D3DDECLUSAGE_NORMAL)
			OutputDebugString("Usage = D3DDECLUSAGE_NORMAL\n");
		if( elems[i].Usage == D3DDECLUSAGE_TEXCOORD)
			OutputDebugString("Usage = D3DDECLUSAGE_TEXCOORD\n");
		++i;
	} 
#endif
}

void D3DSkinnedMesh::buildToRootXFormPtrArray()
{
	// Get a pointer to each frame's to-root transformation (store in an
	// array) such that the ith element corresponds with the ith bone
	// offset matrix.  In this way, we can access a frame's to-root 
	// transformation with a simple array look up, instead of traversing the
	// tree.

	for(UINT i = 0; i < m_numBones; ++i)
	{
		// Find the frame that corresponds with the ith bone offset matrix.
		const char* boneName = m_skinInfo->GetBoneName(i);
		D3DXFRAME* frame = D3DXFrameFind(m_root, boneName);
		if( frame )
		{
			FrameEx* frameEx = static_cast<FrameEx*>( frame );
			m_toRootXFormPtrs[i] = &frameEx->toRoot;
		}
	}
}

void D3DSkinnedMesh::buildToRootXForms(FrameEx* frame, 
									D3DXMATRIX& parentsToRoot) 
{
	// Save some references to economize line space.
    D3DXMATRIX& toParent = frame->TransformationMatrix;
	D3DXMATRIX& toRoot   = frame->toRoot;

    toRoot = toParent * parentsToRoot;

    FrameEx* sibling    = (FrameEx*)frame->pFrameSibling;
    FrameEx* firstChild = (FrameEx*)frame->pFrameFirstChild;

	// Recurse down siblings.
	if( sibling )
		buildToRootXForms(sibling, parentsToRoot);

	// Recurse to first child.
	if( firstChild )
		buildToRootXForms(firstChild, toRoot);
}

