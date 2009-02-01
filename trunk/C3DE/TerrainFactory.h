#ifndef TERRAIN_FACTORY_H
#define TERRAIN_FACTORY_H

#include "CommonDefs.h"
#include "Mesh.h"
#include "TerrainGrid.h"
#include <string>

enum TERRAINS
{
	TERRAIN_NORMAL_ID, 
	TERRAIN_FOREST_ID, 
	TOTAL_TERRAINS
};

class TerrainFactory
{
public:
	//TerrainFactory(int m, int n);
	//TerrainFactory(int m, int n, const std::string &filename, float heightScale, float heightOffset);

	static TerrainFactory * GetInstance();

	//Mesh * GetTerrainMesh(int m, int n, IDirect3DTexture9 *a_texture, float maxHeight);
	Mesh * GetTerrainMesh(int a_id);
	int GetTotalRows(){return m_totalRows;}
	int GetTotalCols(){return m_totalCols;}

	~TerrainFactory();

private :
	bool InBounds(int i, int j);
	float SampleHeight3x3(int i, int j);
	void Filter3x3();

	std::string m_heightMapFile;
	//Table<float> m_heightMap;
	float m_heightScale;
	float m_heightOffset;

	int m_totalRows;
	int m_totalCols;

	TerrainFactory();
	static TerrainFactory * m_instance;

	(TerrainGrid *)m_terrains[TOTAL_TERRAINS];
};
#endif