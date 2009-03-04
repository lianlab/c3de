#include "Grass.h"
#include "D3DRenderer.h"
#include "Math.h"
#include "GrassFX.h"
#include "ResourceManager.h"


IDirect3DVertexDeclaration9* GrassVertex::Decl = 0;

Grass::Grass() : D3DMesh()
{
	BuildGrass();

	D3DImage * d3dImage = new D3DImage(ResourceManager::GetInstance()->GetTextureByID(IMAGE_GRASS_BILLBOARD_ID));	
	AddTexture((Image *) d3dImage);

	Material *t_material = new Material(	D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),
										D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f), 16.0f);	

	AddMaterial(t_material);

	

	m_effect = ShaderManager::GetInstance()->GetFXByID(SHADER_GRASS_FX_ID);
}

Grass::~Grass() 
{

}

void Grass::BuildGrass()
{
	IDirect3DDevice9 *t_device = D3DRenderer::GetDevice();
	D3DVERTEXELEMENT9 GrassVertexElements[] = 
	{
		{0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
		{0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1},
		{0, 32, D3DDECLTYPE_FLOAT1, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 2},
		{0, 36, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0},
		D3DDECL_END()
	};	
	HR(t_device->CreateVertexDeclaration(GrassVertexElements, &GrassVertex::Decl));

	D3DVERTEXELEMENT9 elems[MAX_FVF_DECL_SIZE];
	UINT numElems = 0;
	HR(GrassVertex::Decl->GetDeclaration(elems, &numElems));

	const int NUM_GRASS_BLOCKS = 1;
	HR(D3DXCreateMesh(NUM_GRASS_BLOCKS*2, NUM_GRASS_BLOCKS*4, D3DXMESH_MANAGED, 
		elems, t_device, &m_xMesh));

	GrassVertex* v = 0;
	WORD* k = 0;
	HR(m_xMesh->LockVertexBuffer(0, (void**)&v));
	HR(m_xMesh->LockIndexBuffer(0, (void**)&k));
	
	int indexOffset = 0;

	// Scale down the region in which we generate grass.
	int w = 1;
	int d = 1;

	// Randomly generate a grass block (three intersecting quads) around the 
	// terrain in the height range [35, 50] (similar to the trees).
	for(int i = 0; i < NUM_GRASS_BLOCKS; ++i)
	{
		//============================================
		// Construct vertices.

		// Generate random position in region.  Note that we also shift
		// this region to place it in the world.
		float x = 0.0f;
		float z = 5.0f;
		float y = 0.0f;		

		float sx = GetRandomFloat(0.75f, 1.25f); 
		float sy = GetRandomFloat(0.75f, 1.25f);
		float sz = GetRandomFloat(0.75f, 1.25f);
		D3DXVECTOR3 pos(x, y, z);
		D3DXVECTOR3 scale(sx, sy, sz);

		BuildGrassFin(v, k, indexOffset, pos, scale);
		v += 4;
		k += 6;
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
}


void Grass::SetShaderHandlers()
{
	
	
	GrassFX *t_effect = (GrassFX *) m_effect;
	
	t_effect->SetObjectMaterials(	m_currentMaterial->GetAmbient(), m_currentMaterial->GetDiffuse(),
									m_currentMaterial->GetSpecular(), m_currentMaterial->GetSpecularPower());

									
	
	D3DImage *t_d3dText = (D3DImage *) m_currentTexture;
	t_effect->SetObjectTexture(t_d3dText->GetTexture());

	t_effect->SetTransformMatrix(GetTransformMatrix());
	//t_effect->SetAlpha(m_alpha);
	
}

void Grass::BuildGrassFin(GrassVertex *v, WORD *k, int & indexOffset, D3DXVECTOR3 &worldPos, D3DXVECTOR3 &scale)
{
	float amp = GetRandomFloat(0.5f, 1.0f);

	v[0] = GrassVertex(D3DXVECTOR3(-1.0f, -0.5f, 0.0f), D3DXVECTOR2(0.0f, 1.0f), 0.0f);
	v[1] = GrassVertex(D3DXVECTOR3(-1.0f, 0.5f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), amp);
	v[2] = GrassVertex(D3DXVECTOR3(1.0f, 0.5f, 0.0f), D3DXVECTOR2(1.0f, 0.0f), amp);
	v[3] = GrassVertex(D3DXVECTOR3(1.0f, -0.5f, 0.0f), D3DXVECTOR2(1.0f, 1.0f), 0.0f);

	k[0] = 0 + indexOffset;
	k[1] = 1 + indexOffset;
	k[2] = 2 + indexOffset;
	k[3] = 0 + indexOffset;
	k[4] = 2 + indexOffset;
	k[5] = 3 + indexOffset;

	indexOffset += 4;

	for(int i = 0; i < 4; ++i)
	{
		v[i].pos.x *= scale.x;
		v[i].pos.y *= scale.y;
		v[i].pos.z *= scale.z;

		v[i].colorOffset = D3DXCOLOR(GetRandomFloat(0.0f, 1.0f), GetRandomFloat(0.0f, 0.2f), GetRandomFloat(0.0f, 0.1f), 0.0f);
	}

	float heightOver2 = (v[1].pos.y - v[0].pos.y) /2;
	worldPos.y += heightOver2;

	v[0].quadPos = worldPos;
	v[1].quadPos = worldPos;
	v[2].quadPos = worldPos;
	v[3].quadPos = worldPos;

	
}