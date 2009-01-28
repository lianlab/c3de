#include "TerrainFactory.h"
#include "Grid.h"

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

}

TerrainFactory::~TerrainFactory()
{

}

/*
TerrainFactory::TerrainFactory(int m, int n)
{

}

	
TerrainFactory::TerrainFactory(int m, int n, const std::string &filename, float heightScale, float heightOffset)
{

}
*/
	
Mesh * TerrainFactory::GetTerrainMesh(int m, int n, IDirect3DTexture9 *a_texture, float heightScale, float heightOffset)
{
	Grid *t_grid = new Grid(m, n, 5.0f, 5.0f);
	
	return t_grid;
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