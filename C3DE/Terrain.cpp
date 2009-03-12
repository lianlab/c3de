#include "Terrain.h"
#include "PerVertexLighting.h"
#include "SkinnedMeshFX.h"

#include "ResourceManager.h"
#include "CommonDefs.h"

//#include "DebugMemory.h"

Terrain::Terrain(int a_ID, int a_rows, int a_cols, IDirect3DDevice9*a_device,IDirect3DTexture9 *a_texture, float maxHeight, float cellSize)
{	
	//a_rows = 128;
	//a_cols = 128;
	m_device = a_device;
	//m_subMeshes = new vector<Mesh *>;
	m_id = a_ID;

	m_boundingBoxes = new vector<AABB*>;

	m_cellSize = cellSize;

	m_subMeshes = new vector<D3DMesh*>;

	m_numCols = a_cols;
	m_numRows = a_rows;

	m_heights = new float[(a_rows+1)*(a_cols+1)];

	

	//m_ambientMaterial = Material(0.0f, 0.0f, 1.0f, 1.0f);
	int numVertices = (a_rows +1)*(a_cols + 1);
	
	int numTris = a_rows*a_cols*2;

	float width = (float)a_cols*cellSize;
	float depth = (float)a_rows*cellSize;

	float xOffset = -width * 0.5f;
	float zOffset = depth * 0.5f;
	

	m_vertices = new vector<VertexPos>;
	m_indices = new vector<int>;

	D3DLOCKED_RECT sRect;
	a_texture->LockRect(0, &sRect, NULL, NULL);
	BYTE *bytes = (BYTE*)sRect.pBits;

	D3DSURFACE_DESC desc;
	a_texture->GetLevelDesc(0, &desc);	



	float t_ratio = (float)desc.Width / a_rows;

	
		
	int t_ratioInt = ROUND_FLOAT(t_ratio);	
	//int t_ratioInt = (int)t_ratio;	

	/*
	if(t_ratio < 1.0f)
	{
		t_ratioInt = (int)(t_ratio + 0.5f);	
	}
	*/

	if(m_xMesh)
	{
		delete m_xMesh;
		m_xMesh = NULL;
	}

	D3DVERTEXELEMENT9 VertexPosElements[] = 
	{
		{0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
		{0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
		D3DDECL_END()
	};	

	int totalVertices = (a_rows + 1) * (a_cols + 1);
	int totalIndices = (a_rows)*(a_cols)*6;
	DWORD indices = (a_rows)*(a_cols)*2;
	DWORD vertices = totalVertices;
	
	HRESULT err = D3DXCreateMesh(indices, vertices, D3DXMESH_SYSTEMMEM | D3DXMESH_32BIT, VertexPosElements, a_device, &m_xMesh);
	//HRESULT err = D3DXCreateMesh(indices, vertices, D3DXMESH_MANAGED, VertexPosElements, a_device, &m_xMesh);

	VertexPos *v2 = NULL;
	m_xMesh->LockVertexBuffer(0, (void**)&v2);

	int t_iterator = 0;	



	//buildVertex
	for(int i = 0; i < (a_rows + 1); i++)
	{
		for(int j = 0; j < (a_cols + 1); j++)
		{
					
			//int t_index = (int)(i * (sRect.Pitch) + j)*t_ratioInt;
			int t_j;
			int t_i;
			if(j == a_cols) 
			{
				t_j = a_cols -1;
			}
			else
			{
				t_j = j;
			}

			if(i == a_rows) 
			{
				t_i = a_rows -1;
			}
			else
			{
				t_i = i;
			}

			int t_index = (int)   (   (t_i *    sRect.Pitch    + t_j)    * t_ratio );
			float tx = j*cellSize + xOffset;
			float tz = -i*cellSize + zOffset;		
			
			BYTE *b = bytes  + t_index;
			float ty = (*b/255.0f)*maxHeight;
			//float ty = 0.0f;

			m_heights[t_iterator] = ty;			
		
			float u = (float(j) / a_cols);
			float v = (float(i) / a_rows);						
				
			v2[t_iterator] = VertexPos(tx, ty, tz, 0.0f, 1.0f, 0.0f, u , v);
			t_iterator++;
#if HACK_FROM_SCRATCH
			m_vertices->push_back(VertexPos(tx, ty, tz, 0.0f, 1.0f, 0.0f, u , v));
#endif
		}
	}

	m_xMesh->UnlockVertexBuffer();	

	t_iterator = 0;

	WORD *k2 = NULL;

	m_xMesh->LockIndexBuffer(0, (void**)&k2);

	//build indices
	for(int i = 0; i < (a_rows); i++)
	{
		for(int j = 0; j < (a_cols); j++)
		{
			

			int index1 = (i+1)*(a_cols+1) + j;
			int index2 = i*(a_cols+1) + j;
			int index3 = i*(a_cols+1) + j + 1;
			int index4 = (i+1)*(a_cols+1) + j;
			int index5 = i*(a_cols+1) + j + 1;
			int index6 = (i+1)*(a_cols+1) + j + 1;
			
			k2[t_iterator] = index1;
			t_iterator++;
			k2[t_iterator] = index2;
			t_iterator++;
			k2[t_iterator] = index3;
			t_iterator++;
			k2[t_iterator] = index4;
			t_iterator++;
			k2[t_iterator] = index5;
			t_iterator++;
			k2[t_iterator] = index6;
			t_iterator++;

#if HACK_FROM_SCRATCH
			m_indices->push_back(index1);
			m_indices->push_back(index2);
			m_indices->push_back(index3);
			m_indices->push_back(index4);
			m_indices->push_back(index5);
			m_indices->push_back(index6);
#endif
			
		}

	}

	m_xMesh->UnlockIndexBuffer();	


#if 1


	//===============================================================
	// Now break the grid up into subgrid meshes.
	m_xMesh->LockVertexBuffer(0, (void**)&v2);

	// Find out the number of subgrids we'll have.  For example, if
	// m = 513, n = 257, SUBGRID_VERT_ROWS = SUBGRID_VERT_COLS = 33,
	// then subGridRows = 512/32 = 16 and sibGridCols = 256/32 = 8.
	int subGridRows = (a_rows) / (SubGrid::NUM_ROWS-1);
	int subGridCols = (a_cols) / (SubGrid::NUM_COLS-1);


	for(int r = 0; r < subGridRows; ++r)
	{
		for(int c = 0; c < subGridCols; ++c)
		{
			
			// Rectangle that indicates (via matrix indices ij) the
			// portion of global grid vertices to use for this subgrid.
			RECT R = 
			{
					c * (SubGrid::NUM_COLS-1),
					r * (SubGrid::NUM_ROWS-1),
				(c+1) * (SubGrid::NUM_COLS-1),
				(r+1) * (SubGrid::NUM_ROWS-1)
			};

			BuildSubGridMesh(R, v2); 
		}
	}
#endif
	m_effect = ShaderManager::GetInstance()->GetFXByID(SHADER_LIGHTS_PER_VERTEX_TEXTURES_ID);
	PerVertexLighting *t_effect = (PerVertexLighting *) m_effect;
	t_effect->SetAlpha(1.0f);

}


D3DXVECTOR2 Terrain::GetCoords(float x, float z)
{
	

	int t_cols = m_numCols - 1;
	int t_rows = m_numRows - 1;	

	float width = (float)t_cols*m_cellSize;
	float depth = (float)t_rows*m_cellSize;

	float t_localX = x - m_x;
	float t_localZ = z - m_z;

	float t_transformedX = width/2 + t_localX;
	float t_transformedZ = depth/2 + t_localZ;

	int t_row = (int)t_transformedX/m_cellSize;
	int t_col = (int)t_transformedZ/m_cellSize;

	D3DXVECTOR2 t_ret = D3DXVECTOR2(t_row, t_col);

	return t_ret;
}

float Terrain::GetHeight(float x, float z)
{
	int t_cols = m_numCols +1;
	int t_rows = m_numRows + 1;	

	float width = (float)t_cols*m_cellSize;
	float depth = (float)t_rows*m_cellSize;

	float t_localX = x - m_x;
	float t_localZ = z - m_z;

	float t_transformedX = width/2 + t_localX;
	float t_transformedZ = depth/2 - t_localZ;

	int t_row = (int)t_transformedX/m_cellSize;
	int t_col = (int)t_transformedZ/m_cellSize;

	return m_heights[t_col*t_cols + t_row];
}

void Terrain::BuildSubGridMesh(RECT& R, VertexPos* gridVerts)
{

#if 1
	//===============================================================
	// Create the subgrid mesh.
	ID3DXMesh* subMesh = 0;
	

	D3DVERTEXELEMENT9 VertexPosElements[] = 
	{
		{0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
		{0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
		D3DDECL_END()
	};	



	HR(D3DXCreateMesh(SubGrid::NUM_TRIS, SubGrid::NUM_VERTS, 
		D3DXMESH_MANAGED, VertexPosElements, m_device, &subMesh));

	


	//===============================================================
	// Build Vertex Buffer.  Copy rectangle of vertices from the
	// grid into the subgrid structure.
	VertexPos* v = 0;
	HR(subMesh->LockVertexBuffer(0, (void**)&v));
	int k = 0;
	for(int i = R.top; i <= R.bottom; i++)
	{
		for(int j = R.left; j <= R.right; j++)
		{
			int value = i*(m_numCols+1)+j;
			v[k++] = gridVerts[value];
		}
	}

	//===============================================================
	// Compute the bounding box before unlocking the vertex buffer.
	//AABB bndBox;
	//HR(D3DXComputeBoundingBox((D3DXVECTOR3*)v, subMesh->GetNumVertices(), 
	//	sizeof(VertexPos), &bndBox.minPt, &bndBox.maxPt));

	// Compute the bounding box before unlocking the vertex buffer.
	
	D3DXVECTOR3 t_min;
	D3DXVECTOR3 t_max;

	HR(D3DXComputeBoundingBox((D3DXVECTOR3*)v, subMesh->GetNumVertices(), 
		sizeof(VertexPos), &t_min, &t_max));

	AABB *t_boundingBox = new AABB(t_min, t_max);
	//AABB *t_boundingBox = new AABB();

	//m_boundingBoxes->push_back(t_boundingBox);

	HR(subMesh->UnlockVertexBuffer());


	

	WORD* indices  = 0;
	DWORD* attBuff = 0;
	HR(subMesh->LockIndexBuffer(0, (void**)&indices));
	HR(subMesh->LockAttributeBuffer(0, &attBuff));
	

	int t_iterator = 0;

	for(int i = 0; i < (SubGrid::NUM_ROWS-1); i++)
	{
		for(int j = 0; j < (SubGrid::NUM_COLS-1); j++)
		{
			
			int index1 = i*(SubGrid::NUM_ROWS) + j;
			int index2 = i*(SubGrid::NUM_ROWS) + j + 1;
			int index3 = (i+1)*(SubGrid::NUM_ROWS) + j;
			
			int index4 = (i+1)*(SubGrid::NUM_ROWS) + j;
			int index5 = i*(SubGrid::NUM_ROWS) + j + 1;
			int index6 = (i+1)*(SubGrid::NUM_ROWS) + j + 1;
			
			
			
			indices[t_iterator] = index1;
			t_iterator++;
			indices[t_iterator] = index2;
			t_iterator++;
			indices[t_iterator] = index3;
			t_iterator++;
			indices[t_iterator] = index4;
			t_iterator++;
			indices[t_iterator] = index5;
			t_iterator++;
			indices[t_iterator] = index6;
			t_iterator++;

#if HACK_FROM_SCRATCH
			m_indices->push_back(index1);
			m_indices->push_back(index2);
			m_indices->push_back(index3);
			m_indices->push_back(index4);
			m_indices->push_back(index5);
			m_indices->push_back(index6);
#endif
			
		}

	}


	HR(subMesh->UnlockIndexBuffer());
	HR(subMesh->UnlockAttributeBuffer());

	
	int t_numFaces = subMesh->GetNumFaces();

	//===============================================================
	// Optimize for the vertex cache and build attribute table.
#if 1
	
	DWORD* adj = new DWORD[t_numFaces*3];
	HR(subMesh->GenerateAdjacency(EPSILON, adj));
	HR(subMesh->OptimizeInplace(D3DXMESHOPT_VERTEXCACHE|D3DXMESHOPT_ATTRSORT,
		adj, 0, 0, 0));
	delete[] adj;

#endif
	//===============================================================
	// Save the mesh and bounding box.
	//mSubGridMeshes.push_back(subMesh);
	D3DMesh *t_mesh = new D3DMesh();
	t_mesh->SetXMesh(subMesh);
	t_mesh->SetBoundingBox(t_boundingBox);
	
	m_subMeshes->push_back(t_mesh);
	//mSubGridBndBoxes.push_back(bndBox);
#endif
}


Terrain::~Terrain()
{
	//FREE SUBGRIDS
	if(m_subMeshes)
	{
		int t_totalSubmeshes = m_subMeshes->size();
		for(int i = 0; i < t_totalSubmeshes; i++)
		{
			D3DMesh * t_subMesh = m_subMeshes->at(i);
			delete t_subMesh;
			t_subMesh = NULL;
		}

		delete m_subMeshes;
		m_subMeshes = NULL;
	}
	ReleaseCOM(m_vertexDeclaration);
	delete [] m_heights;
}

void Terrain::SetShaderHandlers()
{		

	PerVertexLighting *t_effect = (PerVertexLighting *) m_effect;
	
	t_effect->SetObjectMaterials(	m_currentMaterial->GetAmbient(), m_currentMaterial->GetDiffuse(),
									m_currentMaterial->GetSpecular(), m_currentMaterial->GetSpecularPower());

									
	
	D3DImage *t_d3dText = (D3DImage *) m_currentTexture;
	//t_effect->SetObjectTexture(t_d3dText->GetTexture());
	
	t_effect->SetObjectTexture(t_d3dText->GetTexture());
	

	t_effect->SetTransformMatrix(GetTransformMatrix());
	t_effect->SetAlpha(m_alpha);
	
}
