#include "TerrainFactory.h"

TerrainFactory::TerrainFactory(int m, int n)
{

}
	
TerrainFactory::TerrainFactory(int m, int n, const std::string &filename, float heightScale, float heightOffset)
{

}

	
Mesh * TerrainFactory::getTerrainMesh(int m, int n, const std::string &filename, float heightScale, float heightOffset)
{
	return NULL;
}
	
	
bool TerrainFactory::inBounds(int i, int j)
{
	return true;
}
	
float TerrainFactory::sampleHeight3x3(int i, int j)
{
	return 0.0f;
}
	
void TerrainFactory::filter3x3()
{

}