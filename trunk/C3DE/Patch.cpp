#include "Patch.h"

Patch::Patch()
{
	m_pDevice = NULL;
	m_pMesh = NULL;
}

Patch::~Patch()
{
	Release();
}

void Patch::Release()
{
	if(m_pMesh != NULL)
		m_pMesh->Release();
	m_pMesh = NULL;
}

void Patch::Render()
{
	//Draw mesh
	if(m_pMesh != NULL)
		m_pMesh->DrawSubset(0);
}

HRESULT Patch::CreateMesh(HeightMap &hm, RECT source, IDirect3DDevice9 *Dev, int index)
{
	m_pDevice = Dev;
	int width = source.right - source.left;
	int height = source.bottom - source.top;
	int nrVert = (width + 1) * (height + 1);
	int nrTri = width * height * 2;

	D3DXCreateMeshFVF( nrTri, nrVert, D3DXMESH_MANAGED, TerrainVertex::FVF, m_pDevice, &m_pMesh);

	TerrainVertex * ver = NULL;
	m_pMesh->LockVertexBuffer(0, (void**)&ver);

	for(int z = source.top, z0 = 0;  z <= source.bottom; z++, z0++)
	{
		for(int x = source.left, x0 = 0; x <= source.right; x++, x0++)
		{
			//Calculate vertex color
			float prc = hm.m_pHeightMap[x + z * hm.m_size.x] / hm.m_maxHeight;
			int red =  255 * prc;
			int green = 255 * (1.0f - prc);

			D3DCOLOR col;

			if(index % 2 == 0)		//Invert color depending on what patch it is...
				col = D3DCOLOR_ARGB(255, red, green, 0);
			else col = D3DCOLOR_ARGB(255, green, red, 0);


			//position
			D3DXVECTOR3 pos;
			pos = D3DXVECTOR3(x, hm.m_pHeightMap[x+z*hm.m_size.x], -z);

			ver[z0*(width+1)+x0] = TerrainVertex(pos, col);
		}
	}

	m_pMesh->UnlockVertexBuffer();

	//calculate indices
	WORD *ind = 0;
	m_pMesh->LockIndexBuffer(0, (void**)&ind);
	
	index = 0;

	for(int z = source.top, z0 = 0; z < source.bottom; z++, z0++)
	{
		for(int x = source.left, x0 = 0; x < source.right; x++, x0++)
		{
			//Triangle 1
			ind[index++] = z0 * (width+1) + x0;
			ind[index++] = z0 * (width+1) +x0 + 1;
			ind[index++] = (z0+1) * (width + 1) + x0;

			//Triangle 2
			ind[index++] = (z0+1) * (width + 1) + x0;
			ind[index++] = z0 * (width+1) +x0 + 1;
			ind[index++] = (z0+1) * (width + 1) + x0 +1;
		}
	}

	m_pMesh->UnlockIndexBuffer();

	DWORD *att = 0;
	m_pMesh->LockAttributeBuffer(0, &att);
	memset(att, 0, sizeof(DWORD)*nrTri);
	m_pMesh->UnlockAttributeBuffer();

	//normals
	D3DXComputeNormals(m_pMesh, NULL);

	return 0;
}