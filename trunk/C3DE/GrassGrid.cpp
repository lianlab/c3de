#include "GrassGrid.h"
#include "D3DRenderer.h"
#include "Math.h"
#include "GrassFX.h"
#include "ResourceManager.h"



GrassGrid::GrassGrid(int a_numBlockRows, int a_numBlocksCols, D3DXVECTOR3 a_blockOffset, D3DImage * a_texture, float a_randomPositionOffset, float a_randomScaleOffset) : D3DMesh()
{
	m_numBlocksRows = a_numBlockRows;
	m_numBlocksCols = a_numBlocksCols;

	m_randomPositionOffset = a_randomPositionOffset;
	m_randomScaleOffset = a_randomScaleOffset;

	m_blockOffset = a_blockOffset;
	BuildGrass();

	
	AddTexture((Image *) a_texture);

	Material *t_material = new Material(	D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),
										D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f), 16.0f);	

	AddMaterial(t_material);

	

	m_effect = ShaderManager::GetInstance()->GetFXByID(SHADER_GRASS_FX_ID);
}

GrassGrid::~GrassGrid() 
{

}

void GrassGrid::BuildGrass()
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

	//const int NUM_GRASS_BLOCKS = 5;
	int t_numBlocks = m_numBlocksRows*m_numBlocksCols;
	HR(D3DXCreateMesh(t_numBlocks*2, t_numBlocks*4, D3DXMESH_MANAGED, 
		elems, t_device, &m_xMesh));

	GrassVertex* v = 0;
	WORD* k = 0;
	HR(m_xMesh->LockVertexBuffer(0, (void**)&v));
	HR(m_xMesh->LockIndexBuffer(0, (void**)&k));
	
	int indexOffset = 0;

	


	// Randomly generate a grass block (three intersecting quads) around the 
	// terrain in the height range [35, 50] (similar to the trees).
	for(int i = 0; i < t_numBlocks; ++i)
	{
		//============================================
		// Construct vertices.

		// Generate random position in region.  Note that we also shift
		// this region to place it in the world.
		int t_col = i%m_numBlocksCols;
		int t_row = i/m_numBlocksCols;

		//float x = m_blockOffset.x*i;
		//float z = m_blockOffset.z*i;
		float t_positionOffset = 0.0f;		
		float t_scaleOffset = 1.0f;

		if(m_randomPositionOffset > 0 )
		{
			t_positionOffset = GetRandomFloat(-(m_randomPositionOffset/2), (m_randomPositionOffset/2));
		}
		if(m_randomScaleOffset > 0)
		{
			t_scaleOffset = GetRandomFloat(1.0f, m_randomScaleOffset);
		}
		
		float x = m_blockOffset.x*t_col + t_positionOffset;
		float z = m_blockOffset.z*t_row + t_positionOffset;
		//float y = m_blockOffset.y*i;		
		float y = m_blockOffset.y;		

		float sx = GetRandomFloat(0.75f, 1.25f); 
		float sy = GetRandomFloat(0.75f, 1.25f);
		float sz = GetRandomFloat(0.75f, 1.25f);

		
		D3DXVECTOR3 pos(x, y, z);
		D3DXVECTOR3 scale(sx, sy, sz);

		/////////////////////////
		float amp = GetRandomFloat(0.5f, 1.0f);


		float t_width = 2.0f;
		float t_height = 1.0f;
		float t_minX = -1.0f;
		float t_minY = -0.5f;
		float t_halfHeight = t_height/2.0f;
		float t_topLeft = (t_minY + t_height + y + t_halfHeight)*t_scaleOffset;
		float t_topRight = (t_minY + t_height + y + t_halfHeight)*t_scaleOffset;
		v[i*4]		= GrassVertex(D3DXVECTOR3(t_minX + x, t_minY + y + t_halfHeight, z), D3DXVECTOR2(0.0f, 1.0f), 0.0f);
		v[i*4 + 1]	= GrassVertex(D3DXVECTOR3(t_minX + x, t_topLeft , z), D3DXVECTOR2(0.0f, 0.0f), amp);
		v[i*4 + 2]	= GrassVertex(D3DXVECTOR3(t_minX + t_width + x, t_topRight , z), D3DXVECTOR2(1.0f, 0.0f), amp);
		v[i*4 + 3]	= GrassVertex(D3DXVECTOR3(t_minX + t_width + x, t_minY + y + t_halfHeight, z), D3DXVECTOR2(1.0f, 1.0f), 0.0f);

		k[i*6] = 0 + indexOffset;
		k[i*6 + 1] = 1 + indexOffset;
		k[i*6 + 2] = 2 + indexOffset;
		k[i*6 + 3] = 0 + indexOffset;
		k[i*6 + 4] = 2 + indexOffset;
		k[i*6 + 5] = 3 + indexOffset;

		indexOffset += 4;

		for(int j = 0; j < 4; ++j)
		{
			//v[i*4 + j].pos.x *= scale.x;
			//v[i*4 + j].pos.y *= scale.y;
			//v[i*4 + j].pos.z *= scale.z;			

			//v[i].colorOffset = D3DXCOLOR(GetRandomFloat(0.0f, 1.0f), GetRandomFloat(0.0f, 0.2f), GetRandomFloat(0.0f, 0.1f), 0.0f);
			v[i*4 + j].colorOffset = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		}

		float heightOver2 = (v[i*4 + 1].pos.y - v[i*4].pos.y) /2;
		pos.y += heightOver2;

		v[i*4].quadPos = pos;
		v[i*4 + 1].quadPos = pos;
		v[i*4 + 2].quadPos = pos;
		v[i*4 + 3].quadPos = pos;
//////////////////////////////
		//v += 4;
		//k += 6;
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


void GrassGrid::SetShaderHandlers()
{
	
	
	GrassFX *t_effect = (GrassFX *) m_effect;
	
	t_effect->SetObjectMaterials(	m_currentMaterial->GetAmbient(), m_currentMaterial->GetDiffuse(),
									m_currentMaterial->GetSpecular(), m_currentMaterial->GetSpecularPower());

									
	
	D3DImage *t_d3dText = (D3DImage *) m_currentTexture;
	t_effect->SetObjectTexture(t_d3dText->GetTexture());

	t_effect->SetTransformMatrix(GetTransformMatrix());
	//t_effect->SetAlpha(m_alpha);
	
}
