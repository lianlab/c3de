
#include "D3DRenderer.h"
#include "C3DESkinnedMesh.h"
#include "ResourceManager.h"
#include "C3DESkinnedMeshFX.h"
#include "BufferReader.h"
#include "DebugMemory.h"


C3DESkinnedMesh::C3DESkinnedMesh(char *a_meshBuffer, char *a_bonesBuffer, Image *a_texture, int frameDuration)
{

	m_animationFramesDuration = new vector<int>;
	m_animationsTotalFrames = new vector<int>;

	m_poseMatrices = new vector<D3DXMATRIX *>;

	
	m_vertices3 = new vector<VertexPosBones>;
	m_indices = new vector<int>;

	

	//GENERATED CODE
	
	//#include "C:\documents and Settings\csabino\Desktop\exportedMeshes\outBones.txt"
	//#include "C:\documents and Settings\csabino\Desktop\exportedMeshes\out.txt"

	BufferReader *t_reader = new BufferReader(a_bonesBuffer);
	m_totalFrames = t_reader->ReadNextInt();
	m_totalBones = t_reader->ReadNextInt();
	m_roots = (D3DXMATRIX*)malloc(sizeof(D3DXMATRIX) * m_totalBones);
	m_currentFrameToRoots = (D3DXMATRIX*)malloc(sizeof(D3DXMATRIX) * m_totalBones);
	m_bonesBegin = (D3DXVECTOR3*)malloc(sizeof(D3DXVECTOR3) * m_totalBones);
	m_bonesEnd = (D3DXVECTOR3*)malloc(sizeof(D3DXVECTOR3) * m_totalBones);
	D3DXMATRIX *t_frameMatrices;
	D3DXMATRIX t_toRoot;
	D3DXMATRIX t_currentFrameMatrix;

	

	

	for(int i = 0; i < m_totalFrames; i++)
	{
		t_frameMatrices = (D3DXMATRIX*)malloc(sizeof(D3DXMATRIX) * m_totalBones);
		for(int j = 0; j < m_totalBones; j++)
		{			
			//UpperArm_L
			D3DXMatrixIdentity(&t_toRoot);
			D3DXMatrixTranslation(&t_toRoot, 0.578768f, 5.570874f, -0.234539f);
			m_roots[j] = t_toRoot;
			D3DXMatrixIdentity(&t_currentFrameMatrix);

			t_currentFrameMatrix._11 = t_reader->ReadNextFloat();
			t_currentFrameMatrix._12 = t_reader->ReadNextFloat();
			t_currentFrameMatrix._13 = t_reader->ReadNextFloat();
			t_currentFrameMatrix._14 = t_reader->ReadNextFloat();
			t_currentFrameMatrix._21 = t_reader->ReadNextFloat();
			t_currentFrameMatrix._22 = t_reader->ReadNextFloat();
			t_currentFrameMatrix._23 = t_reader->ReadNextFloat();
			t_currentFrameMatrix._24 = t_reader->ReadNextFloat();
			t_currentFrameMatrix._31 = t_reader->ReadNextFloat();
			t_currentFrameMatrix._32 = t_reader->ReadNextFloat();
			t_currentFrameMatrix._33 = t_reader->ReadNextFloat();
			t_currentFrameMatrix._34 = t_reader->ReadNextFloat();
			t_currentFrameMatrix._41 = t_reader->ReadNextFloat();
			t_currentFrameMatrix._42 = t_reader->ReadNextFloat();
			t_currentFrameMatrix._43 = t_reader->ReadNextFloat();
			t_currentFrameMatrix._44 = t_reader->ReadNextFloat();

			m_currentFrameToRoots[j] = t_currentFrameMatrix;//for now
			t_frameMatrices[j] = t_currentFrameMatrix;//for now
			m_bonesBegin[j] = D3DXVECTOR3(0.578768f, 5.570874f, -0.234539f);
			m_bonesEnd[j] = D3DXVECTOR3(1.038907f, 4.669971f, -0.390199f);

			
		}
		m_poseMatrices->push_back(t_frameMatrices);
		m_animationFramesDuration->push_back(frameDuration);
	}

	int totalAnimations = t_reader->ReadNextInt();
	for(int i = 0; i < totalAnimations; i++)
	{
		m_animationsTotalFrames->push_back(t_reader->ReadNextInt());
	}
		

	delete t_reader;
	t_reader = NULL;
	t_reader = new BufferReader(a_meshBuffer);

	int totalVertices = t_reader->ReadNextInt();
	int totalIndices = t_reader->ReadNextInt();
	for(int i = 0; i < totalVertices; i++)
	{
		float posx = t_reader->ReadNextFloat();
		float posy = t_reader->ReadNextFloat();
		float posz = t_reader->ReadNextFloat();
		float nx = t_reader->ReadNextFloat();
		float ny = t_reader->ReadNextFloat();
		float nz = t_reader->ReadNextFloat();
		float u = t_reader->ReadNextFloat();
		float v = t_reader->ReadNextFloat();
		float b0Weight = t_reader->ReadNextFloat();

		
		int b0 = t_reader->ReadNextInt();
		int b1 = t_reader->ReadNextInt();
		m_vertices3->push_back(VertexPosBones(	posx,posy, posz, nx, ny, nz, u, v, b0Weight, b0, b1));
		m_indices->push_back(i);
	}
	

	m_animationsTotalFrames->push_back(m_totalFrames);
	
	
	
	Update(0);
	AddTexture((Image *) a_texture);

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

	totalVertices = m_vertices3->size();
	totalIndices = m_indices->size();
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
	CalculateOBB(t_min, t_max);

	
	
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

C3DESkinnedMesh::C3DESkinnedMesh(char *a_meshBuffer, vector<char *> *a_bonesBuffer, Image *a_texture, int frameDuration)
{

	m_animationFramesDuration = new vector<int>;
	m_animationsTotalFrames = new vector<int>;

	m_poseMatrices = new vector<D3DXMATRIX *>;
	
	m_vertices3 = new vector<VertexPosBones>;
	m_indices = new vector<int>;

	int totalAnimationFiles = a_bonesBuffer->size();

	m_totalFrames = 0;

	D3DXMATRIX *t_frameMatrices = NULL;
	D3DXMATRIX t_currentFrameMatrix;

	

	for(int i = 0; i < totalAnimationFiles; i++)
	{
		//each file
		BufferReader *t_reader = new BufferReader((*a_bonesBuffer)[i]);
		int t_totalFrames = t_reader->ReadNextInt();
		m_totalFrames += t_totalFrames;
		m_totalBones = t_reader->ReadNextInt();

		

		for(int i = 0; i < t_totalFrames; i++)
		{
			//each frame
			t_frameMatrices = (D3DXMATRIX*)malloc(sizeof(D3DXMATRIX) * m_totalBones);
			
			for(int j = 0; j < m_totalBones; j++)
			{			
				//each bone
				D3DXMatrixIdentity(&t_currentFrameMatrix);

				t_currentFrameMatrix._11 = t_reader->ReadNextFloat();
				t_currentFrameMatrix._12 = t_reader->ReadNextFloat();
				t_currentFrameMatrix._13 = t_reader->ReadNextFloat();
				t_currentFrameMatrix._14 = t_reader->ReadNextFloat();
				t_currentFrameMatrix._21 = t_reader->ReadNextFloat();
				t_currentFrameMatrix._22 = t_reader->ReadNextFloat();
				t_currentFrameMatrix._23 = t_reader->ReadNextFloat();
				t_currentFrameMatrix._24 = t_reader->ReadNextFloat();
				t_currentFrameMatrix._31 = t_reader->ReadNextFloat();
				t_currentFrameMatrix._32 = t_reader->ReadNextFloat();
				t_currentFrameMatrix._33 = t_reader->ReadNextFloat();
				t_currentFrameMatrix._34 = t_reader->ReadNextFloat();
				t_currentFrameMatrix._41 = t_reader->ReadNextFloat();
				t_currentFrameMatrix._42 = t_reader->ReadNextFloat();
				t_currentFrameMatrix._43 = t_reader->ReadNextFloat();
				t_currentFrameMatrix._44 = t_reader->ReadNextFloat();

				//m_currentFrameToRoots[j] = t_currentFrameMatrix;//for now
				t_frameMatrices[j] = t_currentFrameMatrix;//for now
				//m_bonesBegin[j] = D3DXVECTOR3(0.578768f, 5.570874f, -0.234539f);
				//m_bonesEnd[j] = D3DXVECTOR3(1.038907f, 4.669971f, -0.390199f);

				
			}
			m_poseMatrices->push_back(t_frameMatrices);
			m_animationFramesDuration->push_back(frameDuration);
		}

		//delete t_frameMatrices;
		//t_frameMatrices = NULL;

		int totalAnimations = t_reader->ReadNextInt();
		m_animationsTotalFrames->push_back(t_reader->ReadNextInt());

		delete t_reader;
		t_reader = NULL;
		
	}

	

	
	BufferReader * t_reader = new BufferReader(a_meshBuffer);

	int totalVertices = t_reader->ReadNextInt();
	int totalIndices = t_reader->ReadNextInt();

	float minX = FLT_MAX;
	float minY = FLT_MAX;
	float minZ = FLT_MAX;

	float maxX = FLT_MIN;
	float maxY = FLT_MIN;
	float maxZ = FLT_MIN;
	for(int i = 0; i < totalVertices; i++)
	{
		float posX = t_reader->ReadNextFloat();
		float posY = t_reader->ReadNextFloat();
		float posZ = t_reader->ReadNextFloat();
		float nx = t_reader->ReadNextFloat();
		float ny = t_reader->ReadNextFloat();
		float nz = t_reader->ReadNextFloat();
		float u = t_reader->ReadNextFloat();
		float v = t_reader->ReadNextFloat();
		float b0Weight = t_reader->ReadNextFloat();

		maxX = max(maxX, posX);
		maxY = max(maxY, posY);
		maxZ = max(maxZ, posZ);

		minX = min(minX, posX);
		minY = min(minY, posY);
		minZ = min(minZ, posZ);

		
		int b0 = t_reader->ReadNextInt();
		int b1 = t_reader->ReadNextInt();
		m_vertices3->push_back(VertexPosBones(	posX,posY, posZ, nx, ny, nz, u, v, b0Weight, b0, b1));
		m_indices->push_back(i);
	}

	m_boundingBox = new AABB(D3DXVECTOR3(minX, minY, minZ), D3DXVECTOR3(maxX, maxY, maxZ));
	

	delete t_reader;
	t_reader = NULL;
	//m_animationsTotalFrames->push_back(m_totalFrames);
	
	
	
	Update(0);
	AddTexture((Image *) a_texture);

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

	totalVertices = m_vertices3->size();
	totalIndices = m_indices->size();
	DWORD indices = totalIndices/3;
	DWORD vertices = totalVertices;
	
	HRESULT err = D3DXCreateMesh(indices, vertices, D3DXMESH_MANAGED, VertexPosElements, D3DRenderer::GetDevice(), &m_xMesh);
	
	VertexPosBones *v = NULL;
	m_xMesh->LockVertexBuffer(0, (void**)&v);

	

	for(int i = 0; i < totalVertices; i++)
	{
		v[i] = m_vertices3->at(i);
	}

	//D3DXVECTOR3 t_min;
	//D3DXVECTOR3 t_max;

	//HR(D3DXComputeBoundingBox((D3DXVECTOR3*)v, m_xMesh->GetNumVertices(), 
	//	sizeof(VertexPosBones), &t_min, &t_max));

	//m_boundingBox = new AABB(t_min, t_max);
	//CalculateTopCollisionArea();
	//CalculateOBB(t_min, t_max);

	
	
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

	int totalPoseMatrices = m_poseMatrices->size();

	for(int i = 0; i < totalPoseMatrices; i++)
	{
		free((*m_poseMatrices)[i]);
	}	

	delete m_animationFramesDuration;
	delete m_animationsTotalFrames;
	delete m_poseMatrices;	
	delete m_vertices3;

	m_animationFramesDuration = NULL;
	m_animationsTotalFrames = NULL;
	m_poseMatrices = NULL;	
	m_vertices3 = NULL;
	//delete m_indices;
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