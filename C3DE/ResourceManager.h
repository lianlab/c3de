#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#define MAX_RESOURCES 100


#include "CommonDefs.h"
#include <vector>
#include <d3dx9.h>

enum TexturesIDs
{ 
	IMAGE_SHIP_ID, 	
	IMAGE_BACKGROUND_ID,
	IMAGE_EXPLOSION_ID,
	IMAGE_BUTTON_ID,
	IMAGE_CRATE_ID,
	IMAGE_ABE_ID,
	//DWARF TEXTURES
	IMAGE_DWARF_WEAPONS_ID, 
	IMAGE_DWARF_PACK_ID,
	IMAGE_DWARF_BODY_ID,
	IMAGE_DWARF_ARMOR_ID,
	IMAGE_DWARF_HEADGEAR_ID,
	IMAGE_DWARF_HEAD_ID,
	///////////
	//TINY_ANIM TEXTURE
	IMAGE_TINY_ANIM_SKIN_ID,
	//TIGER
	IMAGE_TIGER_SKIN_ID,
	///////////////////////
	//SWIMMER
	IMAGE_SWIMMER_SKIN_ID,
	///////////////////////
	///////////////////////
	//TERRAIN
	IMAGE_TERRAIN_ID,
	//TERRAIN
	IMAGE_TERRAIN_FOREST_ID,
	///////////////////////
	//TERRAIN
	IMAGE_TERRAIN_NOISE_ID,
	///////////////////////

	
	TOTAL_IMAGES
};

enum FilesIDs
{ 	
	///////////////////////
	//TERRAIN
	FILE_TERRAIN_ID,
	///////////////////////
	TOTAL_FILES
};

enum MeshesIDs
{ 
	MESH_DWARF_ID,
	MESH_WOLF_ID,
	MESH_TINY_ANIM_ID,
	MESH_TIGER_ID,
	MESH_SWIMMER_ID,
	TOTAL_MESHES
};



class ResourceManager
{
public:
	static ResourceManager * GetInstance();
	
	~ResourceManager();

	//C3DESprite * GetSpriteByID(int id);
	IDirect3DTexture9 * GetTextureByID(int id);


	
	
	//inline static void* m_resources[] = {1,2};

	void SetDevice(IDirect3DDevice9 *device);
	
	std::string GetMeshFilenameByID(int a_ID);
	IDirect3DTexture9 * ResourceManager::GetTextureByFilename(std::string a_filename);

	

private:
	ResourceManager();
	static ResourceManager *m_instance;	
	void InitializeResources();
	IDirect3DDevice9 *m_device;

	IDirect3DTexture9 * temp;

	IDirect3DTexture9 * m_imageResources[TOTAL_IMAGES];	
	

	std::string m_meshesFilenames[TOTAL_MESHES];
	
	
};
#endif
