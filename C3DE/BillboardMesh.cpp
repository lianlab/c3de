#include "BillboardMesh.h"
#include "D3DRenderer.h"
#include "Math.h"
#include "BillboardFX.h"
#include "ResourceManager.h"


IDirect3DVertexDeclaration9* BillboardVertex::Decl = 0;

BillboardMesh::BillboardMesh(D3DImage *a_texture) : D3DMesh()
{
	
	m_blockOffset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_vertices = new vector<VertexPos>;
	m_indices = new vector<int>;

	

	m_vertices->push_back(VertexPos(-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f));
	m_vertices->push_back(VertexPos(-1.0f,  1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f));
	m_vertices->push_back(VertexPos( 1.0f,  1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f));
	m_vertices->push_back(VertexPos( 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f));

	m_indices->push_back(0);
	m_indices->push_back(1);
	m_indices->push_back(2);
	m_indices->push_back(0);
	m_indices->push_back(2);
	m_indices->push_back(3);

	BuildBillboard();

	//D3DImage * d3dImage = new D3DImage(ResourceManager::GetInstance()->GetTextureByID(IMAGE_GRASS_BILLBOARD_ID));	
	AddTexture((Image *) a_texture);

	Material *t_material = new Material(	D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),
										D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f), 16.0f);	

	AddMaterial(t_material);

	

	m_effect = ShaderManager::GetInstance()->GetFXByID(SHADER_BILLBOARD_FX_ID);
}

BillboardMesh::~BillboardMesh() 
{

}

void BillboardMesh::BuildBillboard()
{
	IDirect3DDevice9 *t_device = D3DRenderer::GetDevice();
	D3DVERTEXELEMENT9 BillboardVertexElements[] = 
	{
		{0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
		{0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1},
		{0, 32, D3DDECLTYPE_FLOAT1, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 2},
		{0, 36, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0},
		D3DDECL_END()
	};	
	HR(t_device->CreateVertexDeclaration(BillboardVertexElements, &BillboardVertex::Decl));

	D3DVERTEXELEMENT9 elems[MAX_FVF_DECL_SIZE];
	UINT numElems = 0;
	HR(BillboardVertex::Decl->GetDeclaration(elems, &numElems));

	//const int NUM_GRASS_BLOCKS = 5;
	int t_numVertices = m_vertices->size();
	HR(D3DXCreateMesh(t_numVertices/2, t_numVertices, D3DXMESH_MANAGED, 
		elems, t_device, &m_xMesh));

	BillboardVertex* v = 0;
	WORD* k = 0;
	HR(m_xMesh->LockVertexBuffer(0, (void**)&v));
	HR(m_xMesh->LockIndexBuffer(0, (void**)&k));
	
	int indexOffset = 0;	

	// Randomly generate a grass block (three intersecting quads) around the 
	// terrain in the height range [35, 50] (similar to the trees).
#if 0
	for(int i = 0; i < m_numBlocks; ++i)
	{
		//============================================
		// Construct vertices.

		// Generate random position in region.  Note that we also shift
		// this region to place it in the world.
		float x = m_blockOffset.x*i;
		float z = m_blockOffset.z* i;
		float y = m_blockOffset.y*i;				
		
		D3DXVECTOR3 pos(x, y, z);
		

		/////////////////////////
		float amp = GetRandomFloat(0.5f, 1.0f);

		

		float t_width = 2.0f;
		float t_height = 1.0f;
		float t_minX = -1.0f;
		float t_minY = -0.5f;
		float t_halfHeight = t_height/2.0f;

		v[i*4]		= BillboardVertex(D3DXVECTOR3(-1.0f, -1.0f, -1.0f), D3DXVECTOR2(0.0f, 1.0f), 0.0f);
		v[i*4 + 1]	= BillboardVertex(D3DXVECTOR3(-1.0f, 1.0f, -1.0f), D3DXVECTOR2(0.0f, 0.0f), 0.0f);
		v[i*4 + 2]	= BillboardVertex(D3DXVECTOR3(1.0f, 1.0f, -1.0f), D3DXVECTOR2(1.0f, 0.0f), 0.0f);
		v[i*4 + 3]	= BillboardVertex(D3DXVECTOR3(1.0f, -1.0f, -1.0f), D3DXVECTOR2(1.0f, 1.0f), 0.0f);

		k[i*6] = 0 + indexOffset;
		k[i*6 + 1] = 1 + indexOffset;
		k[i*6 + 2] = 2 + indexOffset;
		k[i*6 + 3] = 0 + indexOffset;
		k[i*6 + 4] = 2 + indexOffset;
		k[i*6 + 5] = 3 + indexOffset;

		indexOffset += 4;

		for(int j = 0; j < 4; ++j)
		{
			
			v[i*4 + j].colorOffset = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		}

		

		v[i*4].quadPos = pos;
		v[i*4 + 1].quadPos = pos;
		v[i*4 + 2].quadPos = pos;
		v[i*4 + 3].quadPos = pos;

	}
#endif
	for(int i = 0; i < t_numVertices; ++i)
	{
		D3DXVECTOR3 t_vertex = m_vertices->at(i).pos;
		D3DXVECTOR2 t_uv = m_vertices->at(i).tex0;

		v[i]		= BillboardVertex(t_vertex, t_uv, 0.0f);
		v[i].colorOffset = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);								

		v[i].quadPos = m_blockOffset;		

	}

	int t_numIndices = m_indices->size();
	for(int j = 0; j < t_numIndices; j++)
	{
		k[j] = m_indices->at(j);		
	}

	HR(m_xMesh->UnlockVertexBuffer());
	HR(m_xMesh->UnlockIndexBuffer());

	HR(m_xMesh->LockVertexBuffer(0, (void**)&v));
	
	D3DXVECTOR3 t_min;
	D3DXVECTOR3 t_max;

	
	HR(D3DXComputeBoundingBox(&v->pos, m_xMesh->GetNumVertices(),
			m_xMesh->GetNumBytesPerVertex(), &t_min, &t_max));	

	//t_min = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
	//t_max = D3DXVECTOR3(21.0f, 1.0f, 4.0f);
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
}


void BillboardMesh::SetShaderHandlers()
{
	
	
	BillboardFX *t_effect = (BillboardFX *) m_effect;
	
	t_effect->SetObjectMaterials(	m_currentMaterial->GetAmbient(), m_currentMaterial->GetDiffuse(),
									m_currentMaterial->GetSpecular(), m_currentMaterial->GetSpecularPower());

									
	
	D3DImage *t_d3dText = (D3DImage *) m_currentTexture;
	t_effect->SetObjectTexture(t_d3dText->GetTexture());

	t_effect->SetTransformMatrix(GetTransformMatrix());
	//t_effect->SetAlpha(m_alpha);
	
}
