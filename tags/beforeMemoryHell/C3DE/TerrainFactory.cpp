#include "TerrainFactory.h"
#include "PerVertexLighting.h"
#include "ShaderManager.h"
#include "Terrain.h"
#include "TerrainNormal.h"
#include "TerrainForest.h"
#include "TerrainNoise.h"
#include "D3DRenderer.h"
#include "DebugMemory.h"

TerrainFactory * TerrainFactory::m_instance = NULL;

TerrainFactory * TerrainFactory::GetInstance()
{
	if(!m_instance)
	{
		m_instance = new TerrainFactory();
	}

	return m_instance;
}

TerrainFactory::TerrainFactory()
{
	m_terrains[TERRAIN_NORMAL_ID] = new TerrainNormal(D3DRenderer::GetDevice());
	m_terrains[TERRAIN_FOREST_ID] = new TerrainForest(D3DRenderer::GetDevice());
	m_terrains[TERRAIN_NOISE_ID] = new TerrainNoise(D3DRenderer::GetDevice());
}

TerrainFactory::~TerrainFactory()
{
	
	for(int i = 0; i < TOTAL_TERRAINS; i++)
	{
		Terrain *t_terrain = m_terrains[i];
		delete t_terrain;
		t_terrain = NULL;
	}
	


}
	
Mesh * TerrainFactory::GetTerrainMesh(int a_ID)
{	
	return m_terrains[a_ID];	
}	
	
bool TerrainFactory::InBounds(int i, int j)
{
	return true;
}
	
float TerrainFactory::SampleHeight3x3(int i, int j)
{
	return 0.0f;
}
	
void TerrainFactory::Filter3x3()
{

}