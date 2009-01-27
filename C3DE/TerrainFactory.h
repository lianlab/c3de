#ifndef TERRAIN_FACTORY_H
#define TERRAIN_FACTORY_H

#include "CommonDefs.h"
#include "Mesh.h"
#include <string>



class TerrainFactory
{
public:
	TerrainFactory(int m, int n);
	TerrainFactory(int m, int n, const std::string &filename, float heightScale, float heightOffset);

	Mesh * getTerrainMesh(int m, int n, const std::string &filename, float heightScale, float heightOffset);
	int getTotalRows(){return m_totalRows;}
	int getTotalCols(){return m_totalCols;}

private :
	bool inBounds(int i, int j);
	float sampleHeight3x3(int i, int j);
	void filter3x3();

	std::string m_heightMapFile;
	//Table<float> m_heightMap;
	float m_heightScale;
	float m_heightOffset;

	int m_totalRows;
	int m_totalCols;
};
#endif