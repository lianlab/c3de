#ifndef TERRAIN_NORMAL_H
#define TERRAIN_NORMAL_H

#include "TerrainFactory.h"

class TerrainNormal : public Terrain
{
public:
	TerrainNormal(IDirect3DDevice9 * a_device);
	~TerrainNormal();
};
#endif