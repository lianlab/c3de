#ifndef TERRAIN_H
#define TERRAIN_H

#include <d3dx9.h>
#include <vector>
#include "Heightmap.h"
#include "Patch.h"

class Terrain
{
public:
	Terrain();
	~Terrain();
	void Init(IDirect3DDevice9* Dev, IntPoint _size);
	void Release();
	void GenerateRandomTerrain(int numPatches);
	void CreatePatches(int numPatches);
	void Render();
	HeightMap * getHeightMap(){ return m_pHeightMap;}
private:
	IDirect3DDevice9 *m_pDevice;
	IntPoint m_size;
	HeightMap *m_pHeightMap;
	std::vector<Patch*> m_patches;
};
#endif