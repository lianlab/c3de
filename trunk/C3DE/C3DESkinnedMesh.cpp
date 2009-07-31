
#include "D3DRenderer.h"
#include "C3DESkinnedMesh.h"
#include "ResourceManager.h"
#include "C3DESkinnedMeshFX.h"

#include "DebugMemory.h"


C3DESkinnedMesh::C3DESkinnedMesh()
{
	m_selectedBoneIndex = -1;
	m_offset = 0.0f;
	m_vertices3 = new vector<VertexPosBones>;
	m_indices = new vector<int>;


	//GENERATED CODE
	#include "C:\documents and Settings\csabino\Desktop\exportedMeshes\outBones.txt"
	#include "C:\documents and Settings\csabino\Desktop\exportedMeshes\out.txt"

#if 0
	//vertices

	m_vertices3->push_back(VertexPosBones(-1.0f, -1.0f, -1.0f,	0.0f, 0.0f, -1.0f,	0.0f, 1.0f));
	m_vertices3->push_back(VertexPosBones(-1.0f,  1.0f, -1.0f,	0.0f, 0.0f, -1.0f,	0.0f, 0.0f));
	m_vertices3->push_back(VertexPosBones( 1.0f,  1.0f, -1.0f,	0.0f, 0.0f, -1.0f,	1.0f, 0.0f));
	m_vertices3->push_back(VertexPosBones( 1.0f, -1.0f, -1.0f,	0.0f, 0.0f, -1.0f,	1.0f, 1.0f));

	// Fill in the back face vertex data.
	m_vertices3->push_back(VertexPosBones(-1.0f, -1.0f, 1.0f,		0.0f, 0.0f, 1.0f,	1.0f, 1.0f));
	m_vertices3->push_back(VertexPosBones( 1.0f, -1.0f, 1.0f,		0.0f, 0.0f, 1.0f,	0.0f, 1.0f));
	m_vertices3->push_back(VertexPosBones( 1.0f,  1.0f, 1.0f,		0.0f, 0.0f, 1.0f,	0.0f, 0.0f));
	m_vertices3->push_back(VertexPosBones(-1.0f,  1.0f, 1.0f,		0.0f, 0.0f, 1.0f,	1.0f, 0.0f));

	// Fill in the top face vertex data.
	m_vertices3->push_back(VertexPosBones(-1.0f, 1.0f, -1.0f,		0.0f, 1.0f, 0.0f,	0.0f, 1.0f));
	m_vertices3->push_back(VertexPosBones(-1.0f, 1.0f,  1.0f,		0.0f, 1.0f, 0.0f,	0.0f, 0.0f));
	m_vertices3->push_back(VertexPosBones( 1.0f, 1.0f,  1.0f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f));
	m_vertices3->push_back(VertexPosBones( 1.0f, 1.0f, -1.0f,		0.0f, 1.0f, 0.0f,	1.0f, 1.0f));

	// Fill in the bottom face vertex data.
	m_vertices3->push_back(VertexPosBones(-1.0f, -1.0f, -1.0f,	0.0f, -1.0f, 0.0f,	1.0f, 1.0f));
	m_vertices3->push_back(VertexPosBones( 1.0f, -1.0f, -1.0f,	0.0f, -1.0f, 0.0f,	0.0f, 1.0f));
	m_vertices3->push_back(VertexPosBones( 1.0f, -1.0f,  1.0f,	0.0f, -1.0f, 0.0f,	0.0f, 0.0f));
	m_vertices3->push_back(VertexPosBones(-1.0f, -1.0f,  1.0f,	0.0f, -1.0f, 0.0f,	1.0f, 0.0f));

	// Fill in the left face vertex data.
	m_vertices3->push_back(VertexPosBones(-1.0f, -1.0f,  1.0f,	-1.0f, 0.0f, 0.0f,	0.0f, 1.0f));
	m_vertices3->push_back(VertexPosBones(-1.0f,  1.0f,  1.0f,	-1.0f, 0.0f, 0.0f,	0.0f, 0.0f));
	m_vertices3->push_back(VertexPosBones(-1.0f,  1.0f, -1.0f,	-1.0f, 0.0f, 0.0f,	1.0f, 0.0f));
	m_vertices3->push_back(VertexPosBones(-1.0f, -1.0f, -1.0f,	-1.0f, 0.0f, 0.0f,	1.0f, 1.0f));

	// Fill in the right face vertex data.
	m_vertices3->push_back(VertexPosBones( 1.0f, -1.0f, -1.0f,	1.0f, 0.0f, 0.0f,	0.0f, 1.0f));
	m_vertices3->push_back(VertexPosBones( 1.0f,  1.0f, -1.0f,	1.0f, 0.0f, 0.0f,	0.0f, 0.0f));
	m_vertices3->push_back(VertexPosBones( 1.0f,  1.0f,  1.0f,	1.0f, 0.0f, 0.0f,	1.0f, 0.0f));
	m_vertices3->push_back(VertexPosBones( 1.0f, -1.0f,  1.0f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f));
	
	m_indices->push_back(0);
	m_indices->push_back(1);
	m_indices->push_back(2);
	m_indices->push_back(0);
	m_indices->push_back(2);
	m_indices->push_back(3);
	
	m_indices->push_back(4);
	m_indices->push_back(5);
	m_indices->push_back(6);
	m_indices->push_back(4);
	m_indices->push_back(6);
	m_indices->push_back(7);

	m_indices->push_back(8);
	m_indices->push_back(9);
	m_indices->push_back(10);
	m_indices->push_back(8);
	m_indices->push_back(10);
	m_indices->push_back(11);

	m_indices->push_back(12);
	m_indices->push_back(13);
	m_indices->push_back(14);
	m_indices->push_back(12);
	m_indices->push_back(14);
	m_indices->push_back(15);
	m_indices->push_back(16);
	m_indices->push_back(17);
	m_indices->push_back(18);
	m_indices->push_back(16);
	m_indices->push_back(18);
	m_indices->push_back(19);
	m_indices->push_back(20);
	m_indices->push_back(21);
	m_indices->push_back(22);
	m_indices->push_back(20);
	m_indices->push_back(22);
	m_indices->push_back(23);	
#endif
	D3DImage * d3dImage = new D3DImage(ResourceManager::GetInstance()->GetTextureByID(IMAGE_FEMALE_SKIN_ID));	
	AddTexture((Image *) d3dImage);

	Material *t_material = new Material(	D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),
										D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f), 16.0f);	

	AddMaterial(t_material);


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
	t_effect->SetRootMatrices(m_roots, m_totalBones);
	//t_effect->SetFrameRootMatrices(m_currentFrameToRoots, m_totalBones);

	t_effect->SetSelectedBoneIndex(-1);



	//BEGIN CREATINg BONES VERTEX BUFFER
	int totalBufferVertices = m_totalBones * 2;
	HR(D3DRenderer::GetDevice()->CreateVertexBuffer(totalBufferVertices * sizeof(VertexCol), D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED, &m_bonesVertexBuffer, 0));
	VertexCol *vc = 0;
	HR(m_bonesVertexBuffer->Lock(0,0,(void**)&vc,0));
	

	for (int i = 0; i < m_totalBones; i++)
	//for (int i = 0; i < 1; i++)
	{
		vc[i*2] = VertexCol(GetBonesBegins()[i].x, GetBonesBegins()[i].y, GetBonesBegins()[i].z, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		vc[(i*2)+1] = VertexCol(GetBonesEnd()[i].x, GetBonesEnd()[i].y, GetBonesEnd()[i].z, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	}
	
	
	HR(m_bonesVertexBuffer->Unlock());
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

	t_effect->SetSelectedBoneIndex(m_selectedBoneIndex);

	t_effect->SetFrameRootMatrices(m_currentFrameToRoots, m_totalBones);

	

	t_effect->SetOffset(m_offset);
	
}

void C3DESkinnedMesh::SetSelectedBoneIndex(int index)
{
	m_selectedBoneIndex = index;
}

int C3DESkinnedMesh::GetSelectedBoneIndex()
{
	return m_selectedBoneIndex;
}

void C3DESkinnedMesh::SetOffset(float offset)
{
	m_offset = offset;
}

float C3DESkinnedMesh::GetOffset()
{
	return m_offset;
}

int C3DESkinnedMesh::GetTotalBones()
{
	return m_totalBones;
}

D3DXVECTOR3 * C3DESkinnedMesh::GetBonesBegins()
{
	return m_bonesBegin;
}

D3DXVECTOR3 * C3DESkinnedMesh::GetBonesEnd()
{
	return m_bonesEnd;
}

IDirect3DVertexBuffer9 * C3DESkinnedMesh::GetBonesVertexBuffer()
{
	return m_bonesVertexBuffer;
}