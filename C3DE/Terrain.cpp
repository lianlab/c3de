#include "Terrain.h"

Terrain::Terrain()
{

}

Terrain::~Terrain()
{

}

void Terrain::Init(IDirect3DDevice9 *Dev, IntPoint size)
{
	m_pDevice = Dev;
	m_size = size;
	m_pHeightMap = NULL;
	GenerateRandomTerrain(3);	
}

void Terrain::Release()
{
	for(int i=0;i<m_patches.size();i++)
		if(m_patches[i] != NULL)
			m_patches[i]->Release();

	m_patches.clear();

	if(m_pHeightMap != NULL)
	{
		m_pHeightMap->Release();
		delete m_pHeightMap;
		m_pHeightMap = NULL;
	}
}

void Terrain::GenerateRandomTerrain(int numPatches)
{
	try
	{
		Release();

		//Create two heightmaps and multiply them
		m_pHeightMap = new HeightMap(m_size, 15.0f);
		HeightMap hm2(m_size, 30.0f);

		m_pHeightMap->CreateRandomHeightMap(rand()%2000, 2.5f, 0.5f, 8);
		hm2.CreateRandomHeightMap(rand()%2000, 2.5f, 0.7f, 3);
		hm2.Cap(hm2.m_maxHeight * 0.4f);

		*m_pHeightMap *= hm2;
		hm2.Release();

		CreatePatches(numPatches);
	}
	catch(...)
	{
		debug.Print("Error in TERRAIN::GenerateRandomTerrain()");
	}
}

void Terrain::CreatePatches(int numPatches)
{
	try
	{
		//Clear any old m_patches
		for(int i=0;i<m_patches.size();i++)
			if(m_patches[i] != NULL)
				m_patches[i]->Release();
		m_patches.clear();

		if(m_pHeightMap == NULL)return;

		//Create new patches
		for(int y=0;y<numPatches;y++)
			for(int x=0;x<numPatches;x++)
			{
				RECT r = {x * (m_size.x - 1) / (float)numPatches, 
						y * (m_size.y - 1) / (float)numPatches, 
						(x+1) * (m_size.x - 1) / (float)numPatches,
						(y+1) * (m_size.y - 1) / (float)numPatches};
						
				Patch *p = new Patch();
				p->CreateMesh(*m_pHeightMap, r, m_pDevice, x + y);
				m_patches.push_back(p);
			}
	}
	catch(...)
	{
		debug.Print("Error in TERRAIN::CreatePatches()");
	}
}

void Terrain::Render()
{
	//Set render states
	m_pDevice->SetRenderState(D3DRS_LIGHTING, true);
	m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);

	//Render Patches
	for(int i=0;i<m_patches.size();i++)
		m_patches[i]->Render();
}