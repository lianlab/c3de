#ifndef TERRAIN_NOISE_H
#define TERRAIN_NOISE_H

#include "TerrainFactory.h"

class TerrainNoise : public Terrain
{
public:
	TerrainNoise(IDirect3DDevice9 * a_device);
	~TerrainNoise();
};
#endif