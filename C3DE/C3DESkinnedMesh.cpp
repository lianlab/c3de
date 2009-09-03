
#include "D3DRenderer.h"
#include "C3DESkinnedMesh.h"
#include "ResourceManager.h"
#include "C3DESkinnedMeshFX.h"

#include "DebugMemory.h"


C3DESkinnedMesh::C3DESkinnedMesh()
{
	//m_currentAnimationStartFrame = 0;
	//m_currentAnimationTotalTime = 0;
	//m_currentAnimation = 0;
	
	//m_elapsedTime = 0;
	m_animationFramesDuration = new vector<int>;
	m_animationsTotalFrames = new vector<int>;

	
	//m_poseMatrix = NULL;
	
	m_poseMatrices = new vector<D3DXMATRIX *>;

	
	m_vertices3 = new vector<VertexPosBones>;
	m_indices = new vector<int>;

	

	//GENERATED CODE
	
	#include "C:\documents and Settings\csabino\Desktop\exportedMeshes\outBones.txt"
	#include "C:\documents and Settings\csabino\Desktop\exportedMeshes\out.txt"
	

	m_animationsTotalFrames->push_back(8);
	//m_animationsTotalFrames->push_back(1);
	

	//SetCurrentAnimation(0);
	
	Update(0);

	D3DImage * d3dImage = new D3DImage(ResourceManager::GetInstance()->GetTextureByID(IMAGE_MALE_SKIN_ID));	
	AddTexture((Image *) d3dImage);

	Material *t_material = new Material(	D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),
										D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f), 16.0f);	

	AddMaterial(t_material);

	D3DXVECTOR3 tt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	

	//CREATE MESH
	if(m_xMesh)
	{
		ReleaseCOM(m_xMesh);
		delete m_xMesh;
		m_xMesh = NULL;
	}	

	D3DVERTEXELEMENT9 VertexPosElements[] = 
	{
		{0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
		{0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
		{0, 32, D3DDECLTYPE_FLOAT1, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDWEIGHT, 0},
		{0, 36, D3DDECLTYPE_UBYTE4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDINDICES, 0},
		{0, 40, D3DDECLTYPE_UBYTE4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDINDICES, 1},
		D3DDECL_END()
	};	

	D3DVERTEXELEMENT9 elems[MAX_FVF_DECL_SIZE];

	int totalVertices = m_vertices3->size();
	int totalIndices = m_indices->size();
	DWORD indices = totalIndices/3;
	DWORD vertices = totalVertices;
	
	HRESULT err = D3DXCreateMesh(indices, vertices, D3DXMESH_MANAGED, VertexPosElements, D3DRenderer::GetDevice(), &m_xMesh);
	
	VertexPosBones *v = NULL;
	m_xMesh->LockVertexBuffer(0, (void**)&v);

	

	for(int i = 0; i < totalVertices; i++)
	{
		v[i] = m_vertices3->at(i);
	}

	D3DXVECTOR3 t_min;
	D3DXVECTOR3 t_max;

	HR(D3DXComputeBoundingBox((D3DXVECTOR3*)v, m_xMesh->GetNumVertices(), 
		sizeof(VertexPosBones), &t_min, &t_max));

	m_boundingBox = new AABB(t_min, t_max);
	CalculateTopCollisionArea();
	
	
	m_xMesh->UnlockVertexBuffer();

	WORD *k = NULL;

	m_xMesh->LockIndexBuffer(0, (void**)&k);

	for(int i = 0; i < totalIndices; i++)
	{
		k[i] = GetIndices()->at(i);
	}

	m_xMesh->UnlockIndexBuffer();
	

	//END OF CREATING MESH


	m_effect = ShaderManager::GetInstance()->GetFXByID(SHADER_C3DE_SKINNED_MESH_FX_ID);

	
	C3DESkinnedMeshFX *t_effect = (C3DESkinnedMeshFX *) m_effect;


	t_effect->SetSelectedBoneIndex(-1);

}

C3DESkinnedMesh::~C3DESkinnedMesh()
{
	ReleaseCOM(m_vertexDeclaration);

	FreeTextures();
	//CRASH
	FreeMaterials();
}

void C3DESkinnedMesh::SetShaderHandlers()
{		
	C3DESkinnedMeshFX *t_effect = (C3DESkinnedMeshFX *) m_effect;
	
	t_effect->SetObjectMaterials(	m_currentMaterial->GetAmbient(), m_currentMaterial->GetDiffuse(),
									m_currentMaterial->GetSpecular(), m_currentMaterial->GetSpecularPower());

	D3DImage *t_d3dText = (D3DImage *) m_currentTexture;
	t_effect->SetObjectTexture(t_d3dText->GetTexture());

	t_effect->SetTransformMatrix(GetTransformMatrix());

	//t_effect->SetSelectedBoneIndex(m_selectedBoneIndex);

	//t_effect->SetFrameRootMatrices(m_currentFrameToRoots, m_totalBones);

	
	//t_effect->SetFrameRootMatrices(m_poseMatrix, m_totalBones);
	
	

	//t_effect->SetOffset(m_offset);
	
}




vector<D3DXMATRIX *> *C3DESkinnedMesh::GetPoseMatrices()
{
	return m_poseMatrices;
}




	

D3DXMATRIX * C3DESkinnedMesh::GetMatrices()
{
	return m_roots;
}
	
int C3DESkinnedMesh::GetTotalBones()
{
	return m_totalBones;
}
	
int C3DESkinnedMesh::GetTotalFrames()
{
	return m_totalFrames;
}
	
vector<int> * C3DESkinnedMesh::GetAnimationFramesDuration()
{
	return m_animationFramesDuration;
}
	
vector<int> * C3DESkinnedMesh::GetAnimationTotalFrames()
{
	return m_animationsTotalFrames;
}