#include "TerrainForest.h"
#include "ResourceManager.h"

TerrainForest::TerrainForest():
TerrainGrid(TERRAIN_FOREST_ID, 100,100,ResourceManager::GetInstance()->GetTextureByID(IMAGE_TERRAIN_FOREST_ID), 10.0f)
{
	Material *t_material = new Material(	D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),
										D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f), 16.0f);
	AddMaterial(t_material);
	D3DImage * d3dImage = new D3DImage(ResourceManager::GetInstance()->GetTextureByID(IMAGE_TIGER_SKIN_ID));	
	AddTexture((Image *) d3dImage);
}

TerrainForest::~TerrainForest()
{

}