
#include "D3DRenderer.h"
#include "C3DESkinnedMesh.h"
#include "ResourceManager.h"
#include "C3DESkinnedMeshFX.h"

#include "DebugMemory.h"

#if 1

C3DESkinnedMesh::C3DESkinnedMesh()
{
	
	m_vertices2 = new vector<VertexPosSkin>;
	m_vertices3 = new vector<VertexPosBones>;
	m_indices = new vector<int>;

//GENERATED CODE
	int totalBones = 2;
m_roots = (D3DXMATRIX*)malloc(sizeof(D3DXMATRIX) * totalBones);
m_currentFrameToRoots = (D3DXMATRIX*)malloc(sizeof(D3DXMATRIX) * totalBones);

D3DXMATRIX t_toRoot0;
D3DXMatrixIdentity(&t_toRoot0);
D3DXMatrixTranslation(&t_toRoot0, 0.000000f, 0.000000f, 0.000000f);
m_roots[0] = t_toRoot0;
m_currentFrameToRoots[0] = t_toRoot0;//for now

D3DXMATRIX t_toRoot1;
D3DXMatrixIdentity(&t_toRoot1);
D3DXMatrixTranslation(&t_toRoot1, 2.000000f, 0.000000f, 0.000000f);
m_roots[1] = t_toRoot1;
m_currentFrameToRoots[1] = t_toRoot1;//for now


	
	

	//vertices
m_vertices3->push_back(VertexPosBones(5.000000f, 0.999999f, -1.000000f, 0.333323f, 0.666646f, -0.666646f, 0.000000f, 0.000000f, 1.000000f, 1, -1));
m_vertices3->push_back(VertexPosBones(5.000000f, 0.999999f, 1.000000f, 0.816492f, 0.408246f, 0.408246f, 0.000000f, 0.000000f, 1.000000f, 1, -1));
m_vertices3->push_back(VertexPosBones(5.000000f, -1.000001f, -1.000000f, 0.816492f, -0.408246f, -0.408246f, 0.000000f, 0.000000f, 1.000000f, 1, -1));
m_vertices3->push_back(VertexPosBones(5.000000f, 0.999999f, 1.000000f, 0.816492f, 0.408246f, 0.408246f, 0.000000f, 0.000000f, 1.000000f, 1, -1));
m_vertices3->push_back(VertexPosBones(4.999999f, -1.000001f, 1.000000f, 0.333323f, -0.666646f, 0.666646f, 0.000000f, 0.000000f, 1.000000f, 1, -1));
m_vertices3->push_back(VertexPosBones(5.000000f, -1.000001f, -1.000000f, 0.816492f, -0.408246f, -0.408246f, 0.000000f, 0.000000f, 1.000000f, 1, -1));
m_vertices3->push_back(VertexPosBones(2.000000f, -1.000000f, -1.000000f, 0.000000f, -0.707083f, -0.707083f, 0.000000f, 0.000000f, 1.000000f, 0, 1));
m_vertices3->push_back(VertexPosBones(2.000000f, 1.000000f, -1.000000f, 0.000000f, 0.554674f, -0.832026f, 0.000000f, 0.000000f, 1.000000f, 0, 1));
m_vertices3->push_back(VertexPosBones(5.000000f, 0.999999f, -1.000000f, 0.333323f, 0.666646f, -0.666646f, 0.000000f, 0.000000f, 1.000000f, 1, -1));
m_vertices3->push_back(VertexPosBones(2.000000f, -1.000000f, -1.000000f, 0.000000f, -0.707083f, -0.707083f, 0.000000f, 0.000000f, 1.000000f, 0, 1));
m_vertices3->push_back(VertexPosBones(5.000000f, 0.999999f, -1.000000f, 0.333323f, 0.666646f, -0.666646f, 0.000000f, 0.000000f, 1.000000f, 1, -1));
m_vertices3->push_back(VertexPosBones(5.000000f, -1.000001f, -1.000000f, 0.816492f, -0.408246f, -0.408246f, 0.000000f, 0.000000f, 1.000000f, 1, -1));
m_vertices3->push_back(VertexPosBones(2.000000f, 1.000000f, -1.000000f, 0.000000f, 0.554674f, -0.832026f, 0.000000f, 0.000000f, 1.000000f, 0, 1));
m_vertices3->push_back(VertexPosBones(2.000000f, 0.999999f, 1.000000f, 0.000000f, 0.799982f, 0.599994f, 0.000000f, 0.000000f, 1.000000f, 0, 1));
m_vertices3->push_back(VertexPosBones(5.000000f, 0.999999f, -1.000000f, 0.333323f, 0.666646f, -0.666646f, 0.000000f, 0.000000f, 1.000000f, 1, -1));
m_vertices3->push_back(VertexPosBones(2.000000f, 0.999999f, 1.000000f, 0.000000f, 0.799982f, 0.599994f, 0.000000f, 0.000000f, 1.000000f, 0, 1));
m_vertices3->push_back(VertexPosBones(5.000000f, 0.999999f, 1.000000f, 0.816492f, 0.408246f, 0.408246f, 0.000000f, 0.000000f, 1.000000f, 1, -1));
m_vertices3->push_back(VertexPosBones(5.000000f, 0.999999f, -1.000000f, 0.333323f, 0.666646f, -0.666646f, 0.000000f, 0.000000f, 1.000000f, 1, -1));
m_vertices3->push_back(VertexPosBones(1.999999f, -1.000001f, 1.000000f, 0.000000f, -0.707083f, 0.707083f, 0.000000f, 0.000000f, 1.000000f, 0, 1));
m_vertices3->push_back(VertexPosBones(2.000000f, -1.000000f, -1.000000f, 0.000000f, -0.707083f, -0.707083f, 0.000000f, 0.000000f, 1.000000f, 0, 1));
m_vertices3->push_back(VertexPosBones(4.999999f, -1.000001f, 1.000000f, 0.333323f, -0.666646f, 0.666646f, 0.000000f, 0.000000f, 1.000000f, 1, -1));
m_vertices3->push_back(VertexPosBones(2.000000f, -1.000000f, -1.000000f, 0.000000f, -0.707083f, -0.707083f, 0.000000f, 0.000000f, 1.000000f, 0, 1));
m_vertices3->push_back(VertexPosBones(5.000000f, -1.000001f, -1.000000f, 0.816492f, -0.408246f, -0.408246f, 0.000000f, 0.000000f, 1.000000f, 1, -1));
m_vertices3->push_back(VertexPosBones(4.999999f, -1.000001f, 1.000000f, 0.333323f, -0.666646f, 0.666646f, 0.000000f, 0.000000f, 1.000000f, 1, -1));
m_vertices3->push_back(VertexPosBones(2.000000f, 0.999999f, 1.000000f, 0.000000f, 0.799982f, 0.599994f, 0.000000f, 0.000000f, 1.000000f, 0, 1));
m_vertices3->push_back(VertexPosBones(1.999999f, -1.000001f, 1.000000f, 0.000000f, -0.707083f, 0.707083f, 0.000000f, 0.000000f, 1.000000f, 0, 1));
m_vertices3->push_back(VertexPosBones(4.999999f, -1.000001f, 1.000000f, 0.333323f, -0.666646f, 0.666646f, 0.000000f, 0.000000f, 1.000000f, 1, -1));
m_vertices3->push_back(VertexPosBones(2.000000f, 0.999999f, 1.000000f, 0.000000f, 0.799982f, 0.599994f, 0.000000f, 0.000000f, 1.000000f, 0, 1));
m_vertices3->push_back(VertexPosBones(4.999999f, -1.000001f, 1.000000f, 0.333323f, -0.666646f, 0.666646f, 0.000000f, 0.000000f, 1.000000f, 1, -1));
m_vertices3->push_back(VertexPosBones(5.000000f, 0.999999f, 1.000000f, 0.816492f, 0.408246f, 0.408246f, 0.000000f, 0.000000f, 1.000000f, 1, -1));
m_vertices3->push_back(VertexPosBones(2.000000f, 0.999999f, 1.000000f, 0.000000f, 0.799982f, 0.599994f, 0.000000f, 0.000000f, 1.000000f, 0, 1));
m_vertices3->push_back(VertexPosBones(2.000000f, 1.000000f, -1.000000f, 0.000000f, 0.554674f, -0.832026f, 0.000000f, 0.000000f, 1.000000f, 0, 1));
m_vertices3->push_back(VertexPosBones(0.000000f, 1.000000f, -1.000000f, -0.408246f, 0.816492f, -0.408246f, 0.000000f, 0.000000f, 1.000000f, 0, -1));
m_vertices3->push_back(VertexPosBones(2.000000f, 0.999999f, 1.000000f, 0.000000f, 0.799982f, 0.599994f, 0.000000f, 0.000000f, 1.000000f, 0, 1));
m_vertices3->push_back(VertexPosBones(0.000000f, 1.000000f, -1.000000f, -0.408246f, 0.816492f, -0.408246f, 0.000000f, 0.000000f, 1.000000f, 0, -1));
m_vertices3->push_back(VertexPosBones(0.000000f, 1.000000f, 1.000000f, -0.666646f, 0.333323f, 0.666646f, 0.000000f, 0.000000f, 1.000000f, 0, -1));
m_vertices3->push_back(VertexPosBones(-0.000000f, -1.000000f, -1.000000f, -0.577349f, -0.577349f, -0.577349f, 0.000000f, 0.000000f, 1.000000f, 0, -1));
m_vertices3->push_back(VertexPosBones(-0.000000f, -1.000000f, 1.000000f, -0.577349f, -0.577349f, 0.577349f, 0.000000f, 0.000000f, 1.000000f, 0, -1));
m_vertices3->push_back(VertexPosBones(0.000000f, 1.000000f, 1.000000f, -0.666646f, 0.333323f, 0.666646f, 0.000000f, 0.000000f, 1.000000f, 0, -1));
m_vertices3->push_back(VertexPosBones(-0.000000f, -1.000000f, -1.000000f, -0.577349f, -0.577349f, -0.577349f, 0.000000f, 0.000000f, 1.000000f, 0, -1));
m_vertices3->push_back(VertexPosBones(0.000000f, 1.000000f, 1.000000f, -0.666646f, 0.333323f, 0.666646f, 0.000000f, 0.000000f, 1.000000f, 0, -1));
m_vertices3->push_back(VertexPosBones(0.000000f, 1.000000f, -1.000000f, -0.408246f, 0.816492f, -0.408246f, 0.000000f, 0.000000f, 1.000000f, 0, -1));
m_vertices3->push_back(VertexPosBones(2.000000f, -1.000000f, -1.000000f, 0.000000f, -0.707083f, -0.707083f, 0.000000f, 0.000000f, 1.000000f, 0, 1));
m_vertices3->push_back(VertexPosBones(1.999999f, -1.000001f, 1.000000f, 0.000000f, -0.707083f, 0.707083f, 0.000000f, 0.000000f, 1.000000f, 0, 1));
m_vertices3->push_back(VertexPosBones(-0.000000f, -1.000000f, -1.000000f, -0.577349f, -0.577349f, -0.577349f, 0.000000f, 0.000000f, 1.000000f, 0, -1));
m_vertices3->push_back(VertexPosBones(1.999999f, -1.000001f, 1.000000f, 0.000000f, -0.707083f, 0.707083f, 0.000000f, 0.000000f, 1.000000f, 0, 1));
m_vertices3->push_back(VertexPosBones(-0.000000f, -1.000000f, 1.000000f, -0.577349f, -0.577349f, 0.577349f, 0.000000f, 0.000000f, 1.000000f, 0, -1));
m_vertices3->push_back(VertexPosBones(-0.000000f, -1.000000f, -1.000000f, -0.577349f, -0.577349f, -0.577349f, 0.000000f, 0.000000f, 1.000000f, 0, -1));
m_vertices3->push_back(VertexPosBones(2.000000f, 0.999999f, 1.000000f, 0.000000f, 0.799982f, 0.599994f, 0.000000f, 0.000000f, 1.000000f, 0, 1));
m_vertices3->push_back(VertexPosBones(0.000000f, 1.000000f, 1.000000f, -0.666646f, 0.333323f, 0.666646f, 0.000000f, 0.000000f, 1.000000f, 0, -1));
m_vertices3->push_back(VertexPosBones(1.999999f, -1.000001f, 1.000000f, 0.000000f, -0.707083f, 0.707083f, 0.000000f, 0.000000f, 1.000000f, 0, 1));
m_vertices3->push_back(VertexPosBones(0.000000f, 1.000000f, 1.000000f, -0.666646f, 0.333323f, 0.666646f, 0.000000f, 0.000000f, 1.000000f, 0, -1));
m_vertices3->push_back(VertexPosBones(-0.000000f, -1.000000f, 1.000000f, -0.577349f, -0.577349f, 0.577349f, 0.000000f, 0.000000f, 1.000000f, 0, -1));
m_vertices3->push_back(VertexPosBones(1.999999f, -1.000001f, 1.000000f, 0.000000f, -0.707083f, 0.707083f, 0.000000f, 0.000000f, 1.000000f, 0, 1));
m_vertices3->push_back(VertexPosBones(2.000000f, 1.000000f, -1.000000f, 0.000000f, 0.554674f, -0.832026f, 0.000000f, 0.000000f, 1.000000f, 0, 1));
m_vertices3->push_back(VertexPosBones(2.000000f, -1.000000f, -1.000000f, 0.000000f, -0.707083f, -0.707083f, 0.000000f, 0.000000f, 1.000000f, 0, 1));
m_vertices3->push_back(VertexPosBones(-0.000000f, -1.000000f, -1.000000f, -0.577349f, -0.577349f, -0.577349f, 0.000000f, 0.000000f, 1.000000f, 0, -1));
m_vertices3->push_back(VertexPosBones(2.000000f, 1.000000f, -1.000000f, 0.000000f, 0.554674f, -0.832026f, 0.000000f, 0.000000f, 1.000000f, 0, 1));
m_vertices3->push_back(VertexPosBones(-0.000000f, -1.000000f, -1.000000f, -0.577349f, -0.577349f, -0.577349f, 0.000000f, 0.000000f, 1.000000f, 0, -1));
m_vertices3->push_back(VertexPosBones(0.000000f, 1.000000f, -1.000000f, -0.408246f, 0.816492f, -0.408246f, 0.000000f, 0.000000f, 1.000000f, 0, -1));


m_indices->push_back(0);
m_indices->push_back(1);
m_indices->push_back(2);
m_indices->push_back(3);
m_indices->push_back(4);
m_indices->push_back(5);
m_indices->push_back(6);
m_indices->push_back(7);
m_indices->push_back(8);
m_indices->push_back(9);
m_indices->push_back(10);
m_indices->push_back(11);
m_indices->push_back(12);
m_indices->push_back(13);
m_indices->push_back(14);
m_indices->push_back(15);
m_indices->push_back(16);
m_indices->push_back(17);
m_indices->push_back(18);
m_indices->push_back(19);
m_indices->push_back(20);
m_indices->push_back(21);
m_indices->push_back(22);
m_indices->push_back(23);
m_indices->push_back(24);
m_indices->push_back(25);
m_indices->push_back(26);
m_indices->push_back(27);
m_indices->push_back(28);
m_indices->push_back(29);
m_indices->push_back(30);
m_indices->push_back(31);
m_indices->push_back(32);
m_indices->push_back(33);
m_indices->push_back(34);
m_indices->push_back(35);
m_indices->push_back(36);
m_indices->push_back(37);
m_indices->push_back(38);
m_indices->push_back(39);
m_indices->push_back(40);
m_indices->push_back(41);
m_indices->push_back(42);
m_indices->push_back(43);
m_indices->push_back(44);
m_indices->push_back(45);
m_indices->push_back(46);
m_indices->push_back(47);
m_indices->push_back(48);
m_indices->push_back(49);
m_indices->push_back(50);
m_indices->push_back(51);
m_indices->push_back(52);
m_indices->push_back(53);
m_indices->push_back(54);
m_indices->push_back(55);
m_indices->push_back(56);
m_indices->push_back(57);
m_indices->push_back(58);
m_indices->push_back(59);







	
	//LoadFromC3DEFile(ResourceManager::GetInstance()->GetMeshBuffer(0));

	//D3DImage * d3dImage = new D3DImage(ResourceManager::GetInstance()->GetTextureByID(IMAGE_PARTICLE_TORCH_ID));	
	//D3DImage * d3dImage = new D3DImage(ResourceManager::GetInstance()->GetTextureByID(IMAGE_SWIMMER_SKIN_ID));	
	D3DImage * d3dImage = new D3DImage(ResourceManager::GetInstance()->GetTextureByID(IMAGE_CRATE_ID));	
	AddTexture((Image *) d3dImage);

	Material *t_material = new Material(	D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),
										D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f), 16.0f);	

	AddMaterial(t_material);

	//CreateXMesh(D3DRenderer::GetDevice());



	IDirect3DDevice9 *t_device = D3DRenderer::GetDevice();
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
	HR(t_device->CreateVertexDeclaration(VertexPosElements, &VertexPosSkin::Decl));

	
	D3DVERTEXELEMENT9 elems[MAX_FVF_DECL_SIZE];
	UINT numElems = 0;
	HR(VertexPosSkin::Decl->GetDeclaration(elems, &numElems));

	//const int NUM_GRASS_BLOCKS = 5;
	HR(D3DXCreateMesh(m_indices->size() / 3, m_vertices3->size(), D3DXMESH_MANAGED, 
		elems, t_device, &m_xMesh));

	VertexPosBones* v = 0;
	WORD* k = 0;
	HR(m_xMesh->LockVertexBuffer(0, (void**)&v));
	HR(m_xMesh->LockIndexBuffer(0, (void**)&k));
	
	int indexOffset = 0;	

	int vertexSize = m_vertices3->size();
	for(int i = 0; i < vertexSize; ++i)
	{
		v[i] = m_vertices3->at(i);
	}

	int indicesSize = GetIndices()->size();

	for(int i = 0; i < indicesSize; i++)
	{
		k[i] = GetIndices()->at(i);
	}

	HR(m_xMesh->UnlockVertexBuffer());
	HR(m_xMesh->UnlockIndexBuffer());

	HR(m_xMesh->LockVertexBuffer(0, (void**)&v));
	
	D3DXVECTOR3 t_min;
	D3DXVECTOR3 t_max;

	
	HR(D3DXComputeBoundingBox(&v->pos, m_xMesh->GetNumVertices(),
			m_xMesh->GetNumBytesPerVertex(), &t_min, &t_max));	

	m_boundingBox = new AABB(t_min, t_max);
	HR(m_xMesh->UnlockVertexBuffer());


	// Fill in the attribute buffer (everything in subset 0)
	DWORD* attributeBufferPtr = 0;
	HR(m_xMesh->LockAttributeBuffer(0, &attributeBufferPtr));
	for(UINT i = 0; i < m_xMesh->GetNumFaces(); ++i)
		attributeBufferPtr[i] = 0;
	HR(m_xMesh->UnlockAttributeBuffer());


	DWORD* adj = new DWORD[m_xMesh->GetNumFaces()*3];
	HR(m_xMesh->GenerateAdjacency(EPSILON, adj));
	HR(m_xMesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT|D3DXMESHOPT_VERTEXCACHE,
		adj, 0, 0, 0));

	delete [] adj;





	m_effect = ShaderManager::GetInstance()->GetFXByID(SHADER_C3DE_SKINNED_MESH_FX_ID);

	C3DESkinnedMeshFX *t_effect = (C3DESkinnedMeshFX *) m_effect;
	t_effect->SetRootMatrices(m_roots, 2);
	
}
#endif
#if 0

C3DESkinnedMesh::C3DESkinnedMesh()
{
	
	m_vertices2 = new vector<VertexPosSkin>;
	m_vertices3 = new vector<VertexPosBones>;
	m_indices = new vector<int>;

	D3DXMATRIX t_matrixOffset1;
	D3DXMatrixIdentity(&t_matrixOffset1);

	D3DXMATRIX t_matrixOffset2;
	D3DXMatrixIdentity(&t_matrixOffset2);
	D3DXMatrixTranslation(&t_matrixOffset2, 5.0f, 0.0f, 0.0f);
	D3DXMatrixInverse(&t_matrixOffset2, 0, &t_matrixOffset2);

	D3DXMATRIX t_matrixToRoot1;
	D3DXMatrixIdentity(&t_matrixToRoot1);

	D3DXMATRIX t_matrixToRoot2;
	D3DXMatrixIdentity(&t_matrixToRoot2);
	D3DXMatrixTranslation(&t_matrixToRoot2, 4.1f, 2.5f, 0.0f);
	//D3DXMatrixScaling(&t_matrixToRoot2, 1.0f, 2.0f, 1.0f);
	
	D3DXMATRIX t_matrix1;
	D3DXMatrixIdentity(&t_matrix1);
	D3DXMatrixMultiply(&t_matrix1, &t_matrixOffset1, &t_matrixToRoot1);

	D3DXMATRIX t_matrix2;
	D3DXMatrixIdentity(&t_matrix2);
	D3DXMatrixMultiply(&t_matrix2, &t_matrixOffset2, &t_matrixToRoot2);

	m_matrices[0] = t_matrix1;
	m_matrices[1] = t_matrix2;

	





	D3DXMATRIX t_toRoot1;
	D3DXMatrixIdentity(&t_toRoot1);

	D3DXMATRIX t_toRoot2;
	D3DXMatrixIdentity(&t_toRoot2);
	D3DXMatrixTranslation(&t_toRoot2, 2.0f, 0.0f, 0.0f);

	D3DXMATRIX t_currentFrameToRoot1;
	D3DXMatrixIdentity(&t_currentFrameToRoot1);

	D3DXMATRIX t_currentFrameToRoot2;
	D3DXMatrixIdentity(&t_currentFrameToRoot2);
	D3DXMatrixTranslation(&t_currentFrameToRoot2, 0.0f, -2.0f, 0.0f);

	m_roots[0] = t_toRoot1;
	m_roots[1] = t_toRoot2;
	m_currentFrameToRoots[0] = t_currentFrameToRoot1;
	m_currentFrameToRoots[1] = t_currentFrameToRoot2;

	
	
	

	//vertices

m_vertices2->push_back(VertexPosSkin(5.000000f, 0.999999f, -1.000000f, 0.333323f, 0.666646f, -0.666646f, 0.0f, 0.0f, 1, 1));
m_vertices2->push_back(VertexPosSkin(5.000000f, 0.999999f, 1.000000f, 0.816492f, 0.408246f, 0.408246f, 0.0f, 0.0f, 1, 1));
m_vertices2->push_back(VertexPosSkin(5.000000f, -1.000001f, -1.000000f, 0.816492f, -0.408246f, -0.408246f, 0.0f, 0.0f, 1, 1));
m_vertices2->push_back(VertexPosSkin(5.000000f, 0.999999f, 1.000000f, 0.816492f, 0.408246f, 0.408246f, 0.0f, 0.0f, 1, 1));
m_vertices2->push_back(VertexPosSkin(4.999999f, -1.000001f, 1.000000f, 0.333323f, -0.666646f, 0.666646f, 0.0f, 0.0f, 1, 1));
m_vertices2->push_back(VertexPosSkin(5.000000f, -1.000001f, -1.000000f, 0.816492f, -0.408246f, -0.408246f, 0.0f, 0.0f, 1, 1));
m_vertices2->push_back(VertexPosSkin(2.000000f, -1.000000f, -1.000000f, 0.000000f, -0.707083f, -0.707083f, 0.0f, 0.0f, 1, 0));
m_vertices2->push_back(VertexPosSkin(2.000000f, 1.000000f, -1.000000f, 0.000000f, 0.554674f, -0.832026f, 0.0f, 0.0f));
m_vertices2->push_back(VertexPosSkin(5.000000f, 0.999999f, -1.000000f, 0.333323f, 0.666646f, -0.666646f, 0.0f, 0.0f, 1, 1));
m_vertices2->push_back(VertexPosSkin(2.000000f, -1.000000f, -1.000000f, 0.000000f, -0.707083f, -0.707083f, 0.0f, 0.0f));
m_vertices2->push_back(VertexPosSkin(5.000000f, 0.999999f, -1.000000f, 0.333323f, 0.666646f, -0.666646f, 0.0f, 0.0f, 1, 1));
m_vertices2->push_back(VertexPosSkin(5.000000f, -1.000001f, -1.000000f, 0.816492f, -0.408246f, -0.408246f, 0.0f, 0.0f, 1, 1));
m_vertices2->push_back(VertexPosSkin(2.000000f, 1.000000f, -1.000000f, 0.000000f, 0.554674f, -0.832026f, 0.0f, 0.0f, 1, 0));
m_vertices2->push_back(VertexPosSkin(2.000000f, 0.999999f, 1.000000f, 0.000000f, 0.799982f, 0.599994f, 0.0f, 0.0f));
m_vertices2->push_back(VertexPosSkin(5.000000f, 0.999999f, -1.000000f, 0.333323f, 0.666646f, -0.666646f, 0.0f, 0.0f, 1, 1));
m_vertices2->push_back(VertexPosSkin(2.000000f, 0.999999f, 1.000000f, 0.000000f, 0.799982f, 0.599994f, 0.0f, 0.0f));
m_vertices2->push_back(VertexPosSkin(5.000000f, 0.999999f, 1.000000f, 0.816492f, 0.408246f, 0.408246f, 0.0f, 0.0f, 1, 1));
m_vertices2->push_back(VertexPosSkin(5.000000f, 0.999999f, -1.000000f, 0.333323f, 0.666646f, -0.666646f, 0.0f, 0.0f, 1, 1));
m_vertices2->push_back(VertexPosSkin(1.999999f, -1.000001f, 1.000000f, 0.000000f, -0.707083f, 0.707083f, 0.0f, 0.0f, 1, 0));
m_vertices2->push_back(VertexPosSkin(2.000000f, -1.000000f, -1.000000f, 0.000000f, -0.707083f, -0.707083f, 0.0f, 0.0f));
m_vertices2->push_back(VertexPosSkin(4.999999f, -1.000001f, 1.000000f, 0.333323f, -0.666646f, 0.666646f, 0.0f, 0.0f, 1, 1));
m_vertices2->push_back(VertexPosSkin(2.000000f, -1.000000f, -1.000000f, 0.000000f, -0.707083f, -0.707083f, 0.0f, 0.0f));
m_vertices2->push_back(VertexPosSkin(5.000000f, -1.000001f, -1.000000f, 0.816492f, -0.408246f, -0.408246f, 0.0f, 0.0f, 1, 1));
m_vertices2->push_back(VertexPosSkin(4.999999f, -1.000001f, 1.000000f, 0.333323f, -0.666646f, 0.666646f, 0.0f, 0.0f, 1, 1));
m_vertices2->push_back(VertexPosSkin(2.000000f, 0.999999f, 1.000000f, 0.000000f, 0.799982f, 0.599994f, 0.0f, 0.0f, 1, 0));
m_vertices2->push_back(VertexPosSkin(1.999999f, -1.000001f, 1.000000f, 0.000000f, -0.707083f, 0.707083f, 0.0f, 0.0f));
m_vertices2->push_back(VertexPosSkin(4.999999f, -1.000001f, 1.000000f, 0.333323f, -0.666646f, 0.666646f, 0.0f, 0.0f, 1, 1));
m_vertices2->push_back(VertexPosSkin(2.000000f, 0.999999f, 1.000000f, 0.000000f, 0.799982f, 0.599994f, 0.0f, 0.0f));
m_vertices2->push_back(VertexPosSkin(4.999999f, -1.000001f, 1.000000f, 0.333323f, -0.666646f, 0.666646f, 0.0f, 0.0f, 1, 1));
m_vertices2->push_back(VertexPosSkin(5.000000f, 0.999999f, 1.000000f, 0.816492f, 0.408246f, 0.408246f, 0.0f, 0.0f, 1, 1));
m_vertices2->push_back(VertexPosSkin(2.000000f, 0.999999f, 1.000000f, 0.000000f, 0.799982f, 0.599994f, 0.0f, 0.0f, 1, 0));
m_vertices2->push_back(VertexPosSkin(2.000000f, 1.000000f, -1.000000f, 0.000000f, 0.554674f, -0.832026f, 0.0f, 0.0f));
m_vertices2->push_back(VertexPosSkin(0.000000f, 1.000000f, -1.000000f, -0.408246f, 0.816492f, -0.408246f, 0.0f, 0.0f, 1, 0));
m_vertices2->push_back(VertexPosSkin(2.000000f, 0.999999f, 1.000000f, 0.000000f, 0.799982f, 0.599994f, 0.0f, 0.0f));
m_vertices2->push_back(VertexPosSkin(0.000000f, 1.000000f, -1.000000f, -0.408246f, 0.816492f, -0.408246f, 0.0f, 0.0f, 1, 0));
m_vertices2->push_back(VertexPosSkin(0.000000f, 1.000000f, 1.000000f, -0.666646f, 0.333323f, 0.666646f, 0.0f, 0.0f));
m_vertices2->push_back(VertexPosSkin(-0.000000f, -1.000000f, -1.000000f, -0.577349f, -0.577349f, -0.577349f, 0.0f, 0.0f, 1, 0));
m_vertices2->push_back(VertexPosSkin(-0.000000f, -1.000000f, 1.000000f, -0.577349f, -0.577349f, 0.577349f, 0.0f, 0.0f));
m_vertices2->push_back(VertexPosSkin(0.000000f, 1.000000f, 1.000000f, -0.666646f, 0.333323f, 0.666646f, 0.0f, 0.0f, 1, 0));
m_vertices2->push_back(VertexPosSkin(-0.000000f, -1.000000f, -1.000000f, -0.577349f, -0.577349f, -0.577349f, 0.0f, 0.0f));
m_vertices2->push_back(VertexPosSkin(0.000000f, 1.000000f, 1.000000f, -0.666646f, 0.333323f, 0.666646f, 0.0f, 0.0f, 1, 0));
m_vertices2->push_back(VertexPosSkin(0.000000f, 1.000000f, -1.000000f, -0.408246f, 0.816492f, -0.408246f, 0.0f, 0.0f));
m_vertices2->push_back(VertexPosSkin(2.000000f, -1.000000f, -1.000000f, 0.000000f, -0.707083f, -0.707083f, 0.0f, 0.0f, 1, 0));
m_vertices2->push_back(VertexPosSkin(1.999999f, -1.000001f, 1.000000f, 0.000000f, -0.707083f, 0.707083f, 0.0f, 0.0f));
m_vertices2->push_back(VertexPosSkin(-0.000000f, -1.000000f, -1.000000f, -0.577349f, -0.577349f, -0.577349f, 0.0f, 0.0f, 1, 0));
m_vertices2->push_back(VertexPosSkin(1.999999f, -1.000001f, 1.000000f, 0.000000f, -0.707083f, 0.707083f, 0.0f, 0.0f));
m_vertices2->push_back(VertexPosSkin(-0.000000f, -1.000000f, 1.000000f, -0.577349f, -0.577349f, 0.577349f, 0.0f, 0.0f, 1, 0));
m_vertices2->push_back(VertexPosSkin(-0.000000f, -1.000000f, -1.000000f, -0.577349f, -0.577349f, -0.577349f, 0.0f, 0.0f));
m_vertices2->push_back(VertexPosSkin(2.000000f, 0.999999f, 1.000000f, 0.000000f, 0.799982f, 0.599994f, 0.0f, 0.0f, 1, 0));
m_vertices2->push_back(VertexPosSkin(0.000000f, 1.000000f, 1.000000f, -0.666646f, 0.333323f, 0.666646f, 0.0f, 0.0f));
m_vertices2->push_back(VertexPosSkin(1.999999f, -1.000001f, 1.000000f, 0.000000f, -0.707083f, 0.707083f, 0.0f, 0.0f, 1, 0));
m_vertices2->push_back(VertexPosSkin(0.000000f, 1.000000f, 1.000000f, -0.666646f, 0.333323f, 0.666646f, 0.0f, 0.0f));
m_vertices2->push_back(VertexPosSkin(-0.000000f, -1.000000f, 1.000000f, -0.577349f, -0.577349f, 0.577349f, 0.0f, 0.0f, 1, 0));
m_vertices2->push_back(VertexPosSkin(1.999999f, -1.000001f, 1.000000f, 0.000000f, -0.707083f, 0.707083f, 0.0f, 0.0f));
m_vertices2->push_back(VertexPosSkin(2.000000f, 1.000000f, -1.000000f, 0.000000f, 0.554674f, -0.832026f, 0.0f, 0.0f, 1, 0));
m_vertices2->push_back(VertexPosSkin(2.000000f, -1.000000f, -1.000000f, 0.000000f, -0.707083f, -0.707083f, 0.0f, 0.0f));
m_vertices2->push_back(VertexPosSkin(-0.000000f, -1.000000f, -1.000000f, -0.577349f, -0.577349f, -0.577349f, 0.0f, 0.0f, 1, 0));
m_vertices2->push_back(VertexPosSkin(2.000000f, 1.000000f, -1.000000f, 0.000000f, 0.554674f, -0.832026f, 0.0f, 0.0f));
m_vertices2->push_back(VertexPosSkin(-0.000000f, -1.000000f, -1.000000f, -0.577349f, -0.577349f, -0.577349f, 0.0f, 0.0f, 1, 0));
m_vertices2->push_back(VertexPosSkin(0.000000f, 1.000000f, -1.000000f, -0.408246f, 0.816492f, -0.408246f, 0.0f, 0.0f, 1, 0));
m_indices->push_back(0);
m_indices->push_back(1);
m_indices->push_back(2);
m_indices->push_back(3);
m_indices->push_back(4);
m_indices->push_back(5);
m_indices->push_back(6);
m_indices->push_back(7);
m_indices->push_back(8);
m_indices->push_back(9);
m_indices->push_back(10);
m_indices->push_back(11);
m_indices->push_back(12);
m_indices->push_back(13);
m_indices->push_back(14);
m_indices->push_back(15);
m_indices->push_back(16);
m_indices->push_back(17);
m_indices->push_back(18);
m_indices->push_back(19);
m_indices->push_back(20);
m_indices->push_back(21);
m_indices->push_back(22);
m_indices->push_back(23);
m_indices->push_back(24);
m_indices->push_back(25);
m_indices->push_back(26);
m_indices->push_back(27);
m_indices->push_back(28);
m_indices->push_back(29);
m_indices->push_back(30);
m_indices->push_back(31);
m_indices->push_back(32);
m_indices->push_back(33);
m_indices->push_back(34);
m_indices->push_back(35);
m_indices->push_back(36);
m_indices->push_back(37);
m_indices->push_back(38);
m_indices->push_back(39);
m_indices->push_back(40);
m_indices->push_back(41);
m_indices->push_back(42);
m_indices->push_back(43);
m_indices->push_back(44);
m_indices->push_back(45);
m_indices->push_back(46);
m_indices->push_back(47);
m_indices->push_back(48);
m_indices->push_back(49);
m_indices->push_back(50);
m_indices->push_back(51);
m_indices->push_back(52);
m_indices->push_back(53);
m_indices->push_back(54);
m_indices->push_back(55);
m_indices->push_back(56);
m_indices->push_back(57);
m_indices->push_back(58);
m_indices->push_back(59);







	
	//LoadFromC3DEFile(ResourceManager::GetInstance()->GetMeshBuffer(0));

	//D3DImage * d3dImage = new D3DImage(ResourceManager::GetInstance()->GetTextureByID(IMAGE_PARTICLE_TORCH_ID));	
	//D3DImage * d3dImage = new D3DImage(ResourceManager::GetInstance()->GetTextureByID(IMAGE_SWIMMER_SKIN_ID));	
	D3DImage * d3dImage = new D3DImage(ResourceManager::GetInstance()->GetTextureByID(IMAGE_CRATE_ID));	
	AddTexture((Image *) d3dImage);

	Material *t_material = new Material(	D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),
										D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f), 16.0f);	

	AddMaterial(t_material);

	//CreateXMesh(D3DRenderer::GetDevice());



	IDirect3DDevice9 *t_device = D3DRenderer::GetDevice();
	D3DVERTEXELEMENT9 VertexPosElements[] = 
	{
		{0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
		{0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
		{0, 32, D3DDECLTYPE_FLOAT1, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1},
		{0, 36, D3DDECLTYPE_UBYTE4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDINDICES, 0},
		D3DDECL_END()
	};	
	HR(t_device->CreateVertexDeclaration(VertexPosElements, &VertexPosSkin::Decl));

	
	D3DVERTEXELEMENT9 elems[MAX_FVF_DECL_SIZE];
	UINT numElems = 0;
	HR(VertexPosSkin::Decl->GetDeclaration(elems, &numElems));

	//const int NUM_GRASS_BLOCKS = 5;
	HR(D3DXCreateMesh(m_indices->size() / 3, m_vertices2->size(), D3DXMESH_MANAGED, 
		elems, t_device, &m_xMesh));

	VertexPosSkin* v = 0;
	WORD* k = 0;
	HR(m_xMesh->LockVertexBuffer(0, (void**)&v));
	HR(m_xMesh->LockIndexBuffer(0, (void**)&k));
	
	int indexOffset = 0;	

	int vertexSize = GetVertices2()->size();
	for(int i = 0; i < vertexSize; ++i)
	{
		v[i] = GetVertices2()->at(i);
	}

	int indicesSize = GetIndices()->size();

	for(int i = 0; i < indicesSize; i++)
	{
		k[i] = GetIndices()->at(i);
	}

	HR(m_xMesh->UnlockVertexBuffer());
	HR(m_xMesh->UnlockIndexBuffer());

	HR(m_xMesh->LockVertexBuffer(0, (void**)&v));
	
	D3DXVECTOR3 t_min;
	D3DXVECTOR3 t_max;

	
	HR(D3DXComputeBoundingBox(&v->pos, m_xMesh->GetNumVertices(),
			m_xMesh->GetNumBytesPerVertex(), &t_min, &t_max));	

	m_boundingBox = new AABB(t_min, t_max);
	HR(m_xMesh->UnlockVertexBuffer());


	// Fill in the attribute buffer (everything in subset 0)
	DWORD* attributeBufferPtr = 0;
	HR(m_xMesh->LockAttributeBuffer(0, &attributeBufferPtr));
	for(UINT i = 0; i < m_xMesh->GetNumFaces(); ++i)
		attributeBufferPtr[i] = 0;
	HR(m_xMesh->UnlockAttributeBuffer());



	DWORD* adj = new DWORD[m_xMesh->GetNumFaces()*3];
	HR(m_xMesh->GenerateAdjacency(EPSILON, adj));
	HR(m_xMesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT|D3DXMESHOPT_VERTEXCACHE,
		adj, 0, 0, 0));

	delete [] adj;





	m_effect = ShaderManager::GetInstance()->GetFXByID(SHADER_C3DE_SKINNED_MESH_FX_ID);

	C3DESkinnedMeshFX *t_effect = (C3DESkinnedMeshFX *) m_effect;
	t_effect->SetRootMatrices(m_roots, 2);
	
}

#endif

void C3DESkinnedMesh::SetShaderHandlers()
{
	
	
	C3DESkinnedMeshFX *t_effect = (C3DESkinnedMeshFX *) m_effect;
	
	t_effect->SetObjectMaterials(	m_currentMaterial->GetAmbient(), m_currentMaterial->GetDiffuse(),
									m_currentMaterial->GetSpecular(), m_currentMaterial->GetSpecularPower());

									
	
	D3DImage *t_d3dText = (D3DImage *) m_currentTexture;
	t_effect->SetObjectTexture(t_d3dText->GetTexture());

	t_effect->SetTransformMatrix(GetTransformMatrix());

	//t_effect->SetBoneMatrix(m_matrices, 2);

	t_effect->SetFrameRootMatrices(m_currentFrameToRoots, 2);

	//t_effect->SetAlpha(m_alpha);
	
}

C3DESkinnedMesh::~C3DESkinnedMesh()
{
	ReleaseCOM(m_vertexDeclaration);

	FreeTextures();
	//CRASH
	FreeMaterials();
	
}



