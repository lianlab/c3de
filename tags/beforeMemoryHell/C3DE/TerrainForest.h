#ifndef TERRAIN_FOREST_H
#define TERRAIN_FOREST_H

#include "TerrainFactory.h"

class TerrainForest : public Terrain
{
public:
	TerrainForest(IDirect3DDevice9 * a_device);
	~TerrainForest();
};
#endif