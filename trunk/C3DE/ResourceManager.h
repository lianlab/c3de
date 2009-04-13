#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#define MAX_RESOURCES 100


#include "CommonDefs.h"
#include <vector>
#include <d3dx9.h>
#include <vfw.h>

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
	//TREE 0
	IMAGE_TREE_0_BARK_ID,
	IMAGE_TREE_0_LEAVES_ID,

	//TREE 1
	IMAGE_TREE_1_BARK_ID,
	IMAGE_TREE_1_LEAVES_ID,

	//TREE 2
	IMAGE_TREE_2_BARK_ID,
	IMAGE_TREE_2_LEAVES_ID,

	//TREE 3
	IMAGE_TREE_3_BARK_ID,
	IMAGE_TREE_3_LEAVES_ID,

	//CASTLE
	IMAGE_CASTLE_BRICK_ID,
	IMAGE_CASTLE_STONE_FLOOR_ID, 
	IMAGE_CASTLE_MARBLE_ID,

	//GRASS PATTERN
	IMAGE_GRASS_PATTERN_ID,

	//GRASS BILLBOARD
	IMAGE_GRASS_BILLBOARD_ID,

	//PARTICLES
	IMAGE_PARTICLE_TORCH_ID,
	IMAGE_PARTICLE_BOLT_ID,

	//LANDSCAPE
	IMAGE_STREET_GROUND_ID,
	IMAGE_CAFE_TABLE_ID,
	IMAGE_GARDEN_BORDER_ID,
	IMAGE_MAILBOX01_ID,
	IMAGE_MAILBOX02_ID,
	IMAGE_MAILBOX03_ID,
	IMAGE_PARKING_BARRIER_ID,
	IMAGE_PALETTE_ID,
	IMAGE_PIPE_CAGE_ID,
	IMAGE_SANDWICH_BOARD_ID,
	IMAGE_SIDEWALK_BARRIER_ID,
	IMAGE_SIGN01_ID,
	IMAGE_SIGN02_ID,
	IMAGE_SIGN03_ID,
	IMAGE_SIGN04_ID,
	IMAGE_SIGN05_ID,
	IMAGE_SIGN06_ID,
	IMAGE_SPRINKLER_ID,
	IMAGE_BENCH_ID,
	IMAGE_STREET_LIGHT_01_ID,	
	IMAGE_STREET_LIGHT_02_ID,	
	IMAGE_SWITCHBOX_ID,
	IMAGE_TRAFFIC_CONE_ID,
	IMAGE_STREET_LIGHT_01_LIT_ID,
	IMAGE_STREET_LIGHT_02_LIT_ID,
	IMAGE_TOWNHALL_ID,
	IMAGE_BRICKS_ID,
	
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
	MESH_TREE_0_ID,
	MESH_TREE_1_ID,
	MESH_TREE_2_ID,
	MESH_TREE_3_ID,
	MESH_CASTLE_ID,

	//LANDSCAPE
	MESH_CAFE_TABLE_ID,
	MESH_GARDEN_BORDER_ID,
	MESH_MAILBOX01_ID,
	MESH_MAILBOX02_ID,
	MESH_MAILBOX03_ID,
	MESH_PARKING_BARRIER_ID,
	MESH_PALETTE_ID,
	MESH_PIPE_CAGE_ID,
	MESH_SANDWICH_BOARD_ID,
	MESH_SIDEWALK_BARRIER_ID,
	MESH_SIGN01_ID,
	MESH_SIGN02_ID,
	MESH_SIGN03_ID,
	MESH_SIGN04_ID,
	MESH_SIGN05_ID,
	MESH_SIGN06_ID,
	MESH_SPRINKLER_ID,
	MESH_BENCH_ID,
	MESH_STREET_LIGHT_01_ID,
	MESH_STREET_LIGHT_02_ID,	
	MESH_SWITCHBOX_ID,
	MESH_TRAFFIC_CONE_ID,
	MESH_TOWNHALL_ID,
	TOTAL_MESHES
};

struct VideoStructure
{
	PGETFRAME *m_frames;
	PAVISTREAM *m_stream;
	long m_totalTime;

};
enum Videos
{
	VIDEO_FIRST_ID,
	TOTAL_VIDEOS
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

	VideoStructure * GetVideoByID(int a_ID);

private:
	ResourceManager();
	static ResourceManager *m_instance;	
	void InitializeResources();
	IDirect3DDevice9 *m_device;

	IDirect3DTexture9 * temp;

	IDirect3DTexture9 * m_imageResources[TOTAL_IMAGES];	
	

	std::string m_meshesFilenames[TOTAL_MESHES];
	
	VideoStructure * m_videos[TOTAL_VIDEOS];

	void InitializeVideos();
};
#endif
