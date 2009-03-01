#include "TerrainNoise.h"
#include "Material.h"
#include "D3DImage.h"
#include "ResourceManager.h"

TerrainNoise::TerrainNoise(IDirect3DDevice9 * a_device):
Terrain(TERRAIN_NOISE_ID, 512, 512, a_device,ResourceManager::GetInstance()->GetTextureByID(IMAGE_TERRAIN_NOISE_ID), 10.0f, 1.0f)
{
	Material *t_material = new Material(	D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),
										D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f), 16.0f);
	AddMaterial(t_material);
	D3DImage * d3dImage = new D3DImage(ResourceManager::GetInstance()->GetTextureByID(IMAGE_GRASS_PATTERN_ID));	
	AddTexture((Image *) d3dImage);
}

TerrainNoise::~TerrainNoise()
{

}