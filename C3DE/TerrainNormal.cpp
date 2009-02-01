#include "TerrainNormal.h"
#include "Material.h"
#include "D3DImage.h"
#include "ResourceManager.h"

TerrainNormal::TerrainNormal():
TerrainGrid(TERRAIN_NORMAL_ID, 10,10,ResourceManager::GetInstance()->GetTextureByID(IMAGE_TERRAIN_ID), 10.0f)
{
	Material *t_material = new Material(	D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),
										D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f), 16.0f);
	AddMaterial(t_material);
	D3DImage * d3dImage = new D3DImage(ResourceManager::GetInstance()->GetTextureByID(IMAGE_CRATE_ID));	
	AddTexture((Image *) d3dImage);
}

TerrainNormal::~TerrainNormal()
{

}