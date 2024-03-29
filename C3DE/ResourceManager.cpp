#include "ResourceManager.h"
#include <fstream>
#include "D3DCommonDefs.h"
#include "DebugMemory.h"


using namespace std;

ResourceManager * ResourceManager::m_instance = NULL;

ResourceManager * ResourceManager::GetInstance()
{
	if(!m_instance)
	{
		m_instance = new ResourceManager();
	}

	return m_instance;
}
ResourceManager::ResourceManager()
{
	m_meshesFilenames[MESH_DWARF_ID] = "Meshes/Dwarf.x";
	m_meshesFilenames[MESH_WOLF_ID] = "Meshes/Wolf.x";
	m_meshesFilenames[MESH_TINY_ANIM_ID] = "Meshes/tiny.x";
	m_meshesFilenames[MESH_TIGER_ID] = "Meshes/tiger.x";
	m_meshesFilenames[MESH_SWIMMER_ID] = "Meshes/swimmer.x";
	m_meshesFilenames[MESH_TREE_0_ID] = "Meshes/tree0.x";
	m_meshesFilenames[MESH_TREE_1_ID] = "Meshes/tree1.x";
	m_meshesFilenames[MESH_TREE_2_ID] = "Meshes/tree2.x";
	m_meshesFilenames[MESH_TREE_3_ID] = "Meshes/tree3.x";
	m_meshesFilenames[MESH_CASTLE_ID] = "Meshes/castle.x";
	//LANDSCAPE
	m_meshesFilenames[MESH_CAFE_TABLE_ID] = "Meshes/landscape/cafeTable.x";
	m_meshesFilenames[MESH_GARDEN_BORDER_ID] = "Meshes/landscape/gardenBorder.x";
	m_meshesFilenames[MESH_MAILBOX01_ID] = "Meshes/landscape/mailbox01.x";
	m_meshesFilenames[MESH_MAILBOX02_ID] = "Meshes/landscape/mailbox02.x";
	m_meshesFilenames[MESH_MAILBOX03_ID] = "Meshes/landscape/mailbox03.x";
	m_meshesFilenames[MESH_PARKING_BARRIER_ID] = "Meshes/landscape/parkingBarrier.x";
	m_meshesFilenames[MESH_PALETTE_ID] = "Meshes/landscape/palette.x";
	m_meshesFilenames[MESH_PIPE_CAGE_ID] = "Meshes/landscape/pipeCage.x";
	m_meshesFilenames[MESH_SANDWICH_BOARD_ID] = "Meshes/landscape/sandwichBoard.x";
	m_meshesFilenames[MESH_SIDEWALK_BARRIER_ID] = "Meshes/landscape/sidewalkBarrier.x";
	m_meshesFilenames[MESH_SIGN01_ID] = "Meshes/landscape/sign01.x";
	m_meshesFilenames[MESH_SIGN02_ID] = "Meshes/landscape/sign02.x";
	m_meshesFilenames[MESH_SIGN03_ID] = "Meshes/landscape/sign03.x";
	m_meshesFilenames[MESH_SIGN04_ID] = "Meshes/landscape/sign04.x";
	m_meshesFilenames[MESH_SIGN05_ID] = "Meshes/landscape/sign05.x";
	m_meshesFilenames[MESH_SIGN06_ID] = "Meshes/landscape/sign06.x";
	m_meshesFilenames[MESH_SPRINKLER_ID] = "Meshes/landscape/sprinkler.x";
	m_meshesFilenames[MESH_BENCH_ID] = "Meshes/landscape/bench.x";
	m_meshesFilenames[MESH_STREET_LIGHT_01_ID] = "Meshes/landscape/streetLight01.x";
	m_meshesFilenames[MESH_STREET_LIGHT_02_ID] = "Meshes/landscape/streetLight02.x";	
	m_meshesFilenames[MESH_SWITCHBOX_ID] = "Meshes/landscape/switchBox.x";
	m_meshesFilenames[MESH_TRAFFIC_CONE_ID] = "Meshes/landscape/trafficCone.x";
	m_meshesFilenames[MESH_HOUSE_ID] = "Meshes/house.x";
	m_meshesFilenames[MESH_HOUSE_2_ID] = "Meshes/house2.x";
	m_meshesFilenames[MESH_HOUSE_3_ID] = "Meshes/house3.x";
	m_meshesFilenames[MESH_HOUSE_4_ID] = "Meshes/house4.x";
	m_meshesFilenames[MESH_HOUSE_5_ID] = "Meshes/house5.x";
	


}

ResourceManager::~ResourceManager()
{

	for(int i = 0; i < TOTAL_FONTS; i++)
	{
		delete m_fonts[i];
		m_fonts[i] = NULL;
	}

	for(int i = 0; i  < TOTAL_MESH_BUFFERS; i++)
	{
		free(m_meshBuffers[i]);
		m_meshBuffers[i] = NULL;
	}

	for(int i = 0; i < TOTAL_SCENES; i++)
	{
		free(m_sceneBuffers[i]);
		m_sceneBuffers[i] = NULL;
	}

	for(int i = 0; i < TOTAL_VIDEOS; i++)
	{
		delete m_videos[i]->m_frames;
		m_videos[i]->m_frames = NULL;
		delete m_videos[i]->m_stream;
		m_videos[i]->m_stream = NULL;
		delete m_videos[i];
		m_videos[i] = NULL;
	}

	

}

void ResourceManager::SetDevice(IDirect3DDevice9 *device)
{ 
	m_device = device;
	InitializeResources();
}

void ResourceManager::InitializeResources()
{
	IDirect3DTexture9 * TEX_SHIP;
	
	IDirect3DTexture9 * TEX_BG;
	IDirect3DTexture9 * TEX_EXPLOSION;
	IDirect3DTexture9 * TEX_BUTTON;
	IDirect3DTexture9 * TEX_CRATE;
	IDirect3DTexture9 * TEX_ABE;
	//DWARF
	IDirect3DTexture9 * TEX_DWARF_WEAPONS;
	IDirect3DTexture9 * TEX_DWARF_PACK;
	IDirect3DTexture9 * TEX_DWARF_BODY;
	IDirect3DTexture9 * TEX_DWARF_ARMOR;
	IDirect3DTexture9 * TEX_DWARF_HEADGEAR;
	IDirect3DTexture9 * TEX_DWARF_HEAD;
	////////////////////
	//TINY ANIM
	IDirect3DTexture9 * TEX_TINY_ANIM;
	//TIGER
	IDirect3DTexture9 * TEX_TIGER;
	//SWIMMER
	IDirect3DTexture9 * TEX_SWIMMER;
	//TERRAIN
	IDirect3DTexture9 * TEX_TERRAIN;
	//TERRAIN
	IDirect3DTexture9 * TEX_TERRAIN_FOREST;
	//TERRAIN
	IDirect3DTexture9 * TEX_TERRAIN_NOISE;
	//TREE 0
	IDirect3DTexture9 * TEX_TREE_0_BARK;
	IDirect3DTexture9 * TEX_TREE_0_LEAVES;

	//TREE 1
	IDirect3DTexture9 * TEX_TREE_1_BARK;
	IDirect3DTexture9 * TEX_TREE_1_LEAVES;

	//TREE 2
	IDirect3DTexture9 * TEX_TREE_2_BARK;
	IDirect3DTexture9 * TEX_TREE_2_LEAVES;

	//TREE 3
	IDirect3DTexture9 * TEX_TREE_3_BARK;
	IDirect3DTexture9 * TEX_TREE_3_LEAVES;

	//CASTLE
	IDirect3DTexture9 * TEX_CASTLE_BRICK;
	IDirect3DTexture9 * TEX_CASTLE_STONE_FLOOR;
	IDirect3DTexture9 * TEX_CASTLE_MARBLE;
	//GRASS PATTERN
	IDirect3DTexture9 * TEX_GRASS_PATTERN;

	//GRASS BILLBOARD
	IDirect3DTexture9 * TEX_GRASS_BILLBOARD;

	//PARTICLES

	//TORCH
	IDirect3DTexture9 * TEX_PARTICLES_TORCH;

	//BOLT
	IDirect3DTexture9 * TEX_PARTICLES_BOLT;


	//LANDSCAPE
	IDirect3DTexture9 * TEX_STREET_GROUND;
	IDirect3DTexture9 * TEX_CAFE_TABLE;
	IDirect3DTexture9 * TEX_GARDEN_BORDER;
	IDirect3DTexture9 * TEX_MAILBOX01;
	IDirect3DTexture9 * TEX_MAILBOX02;
	IDirect3DTexture9 * TEX_MAILBOX03;
	IDirect3DTexture9 * TEX_PARKING_BARRIER;
	IDirect3DTexture9 * TEX_PALETTE;
	IDirect3DTexture9 * TEX_PIPE_CAGE;
	IDirect3DTexture9 * TEX_SANDWICH_BOARD;
	IDirect3DTexture9 * TEX_SIDEWALK_BARRIER;
	IDirect3DTexture9 * TEX_SIGN01;
	IDirect3DTexture9 * TEX_SIGN02;
	IDirect3DTexture9 * TEX_SIGN03;
	IDirect3DTexture9 * TEX_SIGN04;
	IDirect3DTexture9 * TEX_SIGN05;
	IDirect3DTexture9 * TEX_SIGN06;
	IDirect3DTexture9 * TEX_SPRINKLER;
	IDirect3DTexture9 * TEX_BENCH;
	IDirect3DTexture9 * TEX_STREET_LIGHT_01;
	IDirect3DTexture9 * TEX_STREET_LIGHT_01_LIT;
	IDirect3DTexture9 * TEX_STREET_LIGHT_02;
	IDirect3DTexture9 * TEX_STREET_LIGHT_02_LIT;
	IDirect3DTexture9 * TEX_SWITCHBOX;
	IDirect3DTexture9 * TEX_TRAFFIC_CONE;						
	
	IDirect3DTexture9 * TEX_BRICKS;	
	IDirect3DTexture9 * TEX_WALL_GRASS;	
	IDirect3DTexture9 * TEX_WALL_WOOD;	

	IDirect3DTexture9 * TEX_SKYBOX;
	IDirect3DTexture9 * TEX_SKYBOX_UP;
	IDirect3DTexture9 * TEX_SKYBOX_DOWN;
	IDirect3DTexture9 * TEX_SKYBOX_LEFT;
	IDirect3DTexture9 * TEX_SKYBOX_RIGHT;
	IDirect3DTexture9 * TEX_SKYBOX_FRONT;
	IDirect3DTexture9 * TEX_SKYBOX_BACK;
	IDirect3DTexture9 * TEX_HOUSE;
	IDirect3DTexture9 * TEX_HOUSE_2;
	IDirect3DTexture9 * TEX_HOUSE_3;
	IDirect3DTexture9 * TEX_HOUSE_4;
	IDirect3DTexture9 * TEX_HOUSE_5;
	IDirect3DTexture9 * TEX_SPIDER;
	IDirect3DTexture9 * TEX_DOG;
	IDirect3DTexture9 * TEX_NINJA;
	IDirect3DTexture9 * TEX_BLACK_NINJA;

	IDirect3DTexture9 * TEX_FEMALE_SKIN;
	IDirect3DTexture9 * TEX_MALE_SKIN;

	IDirect3DTexture9 * TEX_HOUSE_0;

	IDirect3DTexture9 * TEX_LOW_HOUSE_0;
	IDirect3DTexture9 * TEX_LOW_HOUSE_1_MAIN;
	IDirect3DTexture9 * TEX_LOW_HOUSE_1_ROOF;
	IDirect3DTexture9 * TEX_LOW_HOUSE_1_GARAGE;
	IDirect3DTexture9 * TEX_STORAGE;
	

	IDirect3DTexture9 * TEX_FONT_VERDANA_36;

	IDirect3DTexture9 * TEX_TEST;
	
	
	


	HR(D3DXCreateTextureFromFile(m_device, "Images/alienship.bmp", &TEX_SHIP));
	
	
	HR(D3DXCreateTextureFromFile(m_device, "Images/bkgd1.bmp", &TEX_BG));	
	HR(D3DXCreateTextureFromFile(m_device, "Images/fireatlas.bmp", &TEX_EXPLOSION));
	HR(D3DXCreateTextureFromFile(m_device, "Images/button.bmp", &TEX_BUTTON));
	HR(D3DXCreateTextureFromFile(m_device, "Images/crate.jpg", &TEX_CRATE));
	HR(D3DXCreateTextureFromFile(m_device, "Images/abe.jpg", &TEX_ABE));
	
	//DWARF
	HR(D3DXCreateTextureFromFile(m_device, "Images/Dwarf/Weapons.dds", &TEX_DWARF_WEAPONS));
	HR(D3DXCreateTextureFromFile(m_device, "Images/Dwarf/Pack.dds", &TEX_DWARF_PACK));
	HR(D3DXCreateTextureFromFile(m_device, "Images/Dwarf/Body.dds", &TEX_DWARF_BODY));
	HR(D3DXCreateTextureFromFile(m_device, "Images/Dwarf/Armor.dds", &TEX_DWARF_ARMOR));
	HR(D3DXCreateTextureFromFile(m_device, "Images/Dwarf/Headgear.dds", &TEX_DWARF_HEADGEAR));
	HR(D3DXCreateTextureFromFile(m_device, "Images/Dwarf/DwarfHead.dds", &TEX_DWARF_HEAD));
	///////////

	//TINY_ANIM
	HR(D3DXCreateTextureFromFile(m_device, "Images/Tiny/Tiny_skin.dds", &TEX_TINY_ANIM));
	///////////////////
	//Tiger
	HR(D3DXCreateTextureFromFile(m_device, "Images/Tiger/tiger.bmp", &TEX_TIGER));
	///////////////////
	//Swimmer
	HR(D3DXCreateTextureFromFile(m_device, "Images/Swimmer/swimmer.bmp", &TEX_SWIMMER));
	///////////////////

	//TERRAIN
	//HR(D3DXCreateTextureFromFile(m_device, "Images/Terrain/terrain.bmp", &TEX_TERRAIN));
	
	D3DXCreateTextureFromFileEx(m_device, "Images/Terrain/noise128.jpg", 128, 128, 1, D3DUSAGE_DYNAMIC, 
											  D3DFMT_L8, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 
											  NULL, NULL, NULL, &TEX_TERRAIN);

	D3DXCreateTextureFromFileEx(m_device, "Images/Terrain/noise256.jpg", 256, 256, 1, D3DUSAGE_DYNAMIC, 
											  D3DFMT_L8, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 
											  NULL, NULL, NULL, &TEX_TERRAIN_FOREST);

	//D3DXCreateTextureFromFileEx(m_device, "Images/Terrain/noise512.jpg", 512, 512, 1, D3DUSAGE_DYNAMIC, 
	//										  D3DFMT_L8, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 
	//										  NULL, NULL, NULL, &TEX_TERRAIN_NOISE);

	D3DXCreateTextureFromFileEx(m_device, "Images/Terrain/noise.jpg", 512, 512, 1, D3DUSAGE_DYNAMIC, 
											  D3DFMT_L8, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 
											  NULL, NULL, NULL, &TEX_TERRAIN_NOISE);

	//TREE 0
	HR(D3DXCreateTextureFromFile(m_device, "Images/Tree0/tree0_bark.dds", &TEX_TREE_0_BARK));
	HR(D3DXCreateTextureFromFile(m_device, "Images/Tree0/tree0_leaf.dds", &TEX_TREE_0_LEAVES));

	//TREE 1
	HR(D3DXCreateTextureFromFile(m_device, "Images/Tree1/tree1_bark.dds", &TEX_TREE_1_BARK));
	HR(D3DXCreateTextureFromFile(m_device, "Images/Tree1/tree1_leaf.dds", &TEX_TREE_1_LEAVES));

	//TREE 2
	HR(D3DXCreateTextureFromFile(m_device, "Images/Tree2/tree2_bark.dds", &TEX_TREE_2_BARK));
	HR(D3DXCreateTextureFromFile(m_device, "Images/Tree2/tree2_leaf.dds", &TEX_TREE_2_LEAVES));

	//TREE 3
	HR(D3DXCreateTextureFromFile(m_device, "Images/Tree3/tree3_bark.dds", &TEX_TREE_3_BARK));
	HR(D3DXCreateTextureFromFile(m_device, "Images/Tree3/tree3_leaf.dds", &TEX_TREE_3_LEAVES));

	//CASTLE
	HR(D3DXCreateTextureFromFile(m_device, "Images/castle/darkbrick.bmp", &TEX_CASTLE_BRICK));
	HR(D3DXCreateTextureFromFile(m_device, "Images/castle/marble.bmp", &TEX_CASTLE_MARBLE));
	HR(D3DXCreateTextureFromFile(m_device, "Images/castle/stonefloor.bmp", &TEX_CASTLE_STONE_FLOOR));
		
	//GRASS PATTERN
	HR(D3DXCreateTextureFromFile(m_device, "Images/grass.dds", &TEX_GRASS_PATTERN));
	//HR(D3DXCreateTextureFromFile(m_device, "Images/Terrain/terrain.bmp", &TEX_TERRAIN));
	
	//GRASS BILLBOARD
	HR(D3DXCreateTextureFromFile(m_device, "Images/Grass/grassfin0.dds", &TEX_GRASS_BILLBOARD));


	//PARTICLES

	//TORCH
	HR(D3DXCreateTextureFromFile(m_device, "Images/Particles/torch.dds", &TEX_PARTICLES_TORCH));

	//BOLT
	HR(D3DXCreateTextureFromFile(m_device, "Images/Particles/bolt.dds", &TEX_PARTICLES_BOLT));
	///////////////////
	//LANDSCAPE
	HR(D3DXCreateTextureFromFile(m_device, "Images/landscape/streetGround.png", &TEX_STREET_GROUND));
	HR(D3DXCreateTextureFromFile(m_device, "Images/landscape/cafeTable.png", &TEX_CAFE_TABLE));
	HR(D3DXCreateTextureFromFile(m_device, "Images/landscape/gardenBorder.png", &TEX_GARDEN_BORDER));
	HR(D3DXCreateTextureFromFile(m_device, "Images/landscape/mailbox01.png", &TEX_MAILBOX01));
	HR(D3DXCreateTextureFromFile(m_device, "Images/landscape/mailbox02.png", &TEX_MAILBOX02));
	HR(D3DXCreateTextureFromFile(m_device, "Images/landscape/mailbox03.png", &TEX_MAILBOX03));
	HR(D3DXCreateTextureFromFile(m_device, "Images/landscape/parkingBarrier.png", &TEX_PARKING_BARRIER));
	HR(D3DXCreateTextureFromFile(m_device, "Images/landscape/palette.png", &TEX_PALETTE));
	HR(D3DXCreateTextureFromFile(m_device, "Images/landscape/pipeCage.png", &TEX_PIPE_CAGE));
	HR(D3DXCreateTextureFromFile(m_device, "Images/landscape/sandwichBoard.png", &TEX_SANDWICH_BOARD));
	HR(D3DXCreateTextureFromFile(m_device, "Images/landscape/sidewalkBarrier.png", &TEX_SIDEWALK_BARRIER));
	HR(D3DXCreateTextureFromFile(m_device, "Images/landscape/sign01.png", &TEX_SIGN01));
	HR(D3DXCreateTextureFromFile(m_device, "Images/landscape/sign02.png", &TEX_SIGN02));
	HR(D3DXCreateTextureFromFile(m_device, "Images/landscape/sign03.png", &TEX_SIGN03));
	HR(D3DXCreateTextureFromFile(m_device, "Images/landscape/sign04.png", &TEX_SIGN04));
	HR(D3DXCreateTextureFromFile(m_device, "Images/landscape/sign05.png", &TEX_SIGN05));
	HR(D3DXCreateTextureFromFile(m_device, "Images/landscape/sign06.png", &TEX_SIGN06));
	HR(D3DXCreateTextureFromFile(m_device, "Images/landscape/sprinkler.png", &TEX_SPRINKLER));
	HR(D3DXCreateTextureFromFile(m_device, "Images/landscape/bench.png", &TEX_BENCH));
	HR(D3DXCreateTextureFromFile(m_device, "Images/landscape/streetLight01.png", &TEX_STREET_LIGHT_01));
	HR(D3DXCreateTextureFromFile(m_device, "Images/landscape/streetLight01_lit.png", &TEX_STREET_LIGHT_01_LIT));
	HR(D3DXCreateTextureFromFile(m_device, "Images/landscape/streetLight02.png", &TEX_STREET_LIGHT_02));
	HR(D3DXCreateTextureFromFile(m_device, "Images/landscape/streetLight02_lit.png", &TEX_STREET_LIGHT_02_LIT));
	HR(D3DXCreateTextureFromFile(m_device, "Images/landscape/switchbox.png", &TEX_SWITCHBOX));
	HR(D3DXCreateTextureFromFile(m_device, "Images/landscape/trafficCone.png", &TEX_TRAFFIC_CONE));
	
	HR(D3DXCreateTextureFromFile(m_device, "Images/landscape/brick.jpg", &TEX_BRICKS));
	HR(D3DXCreateTextureFromFile(m_device, "Images/landscape/wall_grass.jpg", &TEX_WALL_GRASS));
	HR(D3DXCreateTextureFromFile(m_device, "Images/landscape/wall_wood.jpg", &TEX_WALL_WOOD));


	HR(D3DXCreateTextureFromFile(m_device, "Images/skybox/skybox.png", &TEX_SKYBOX));
	


	HR(D3DXCreateTextureFromFile(m_device, "Images/skybox/skybox_UP.jpg", &TEX_SKYBOX_UP));
	HR(D3DXCreateTextureFromFile(m_device, "Images/skybox/skybox_DN.jpg", &TEX_SKYBOX_DOWN));
	HR(D3DXCreateTextureFromFile(m_device, "Images/skybox/skybox_LF.jpg", &TEX_SKYBOX_LEFT));
	HR(D3DXCreateTextureFromFile(m_device, "Images/skybox/skybox_RT.jpg", &TEX_SKYBOX_RIGHT));
	HR(D3DXCreateTextureFromFile(m_device, "Images/skybox/skybox_FR.jpg", &TEX_SKYBOX_FRONT));
	HR(D3DXCreateTextureFromFile(m_device, "Images/skybox/skybox_BK.jpg", &TEX_SKYBOX_BACK));

	HR(D3DXCreateTextureFromFile(m_device, "Images/house/house.png", &TEX_HOUSE));
	HR(D3DXCreateTextureFromFile(m_device, "Images/house/house2.png", &TEX_HOUSE_2));
	HR(D3DXCreateTextureFromFile(m_device, "Images/house/house3.png", &TEX_HOUSE_3));
	HR(D3DXCreateTextureFromFile(m_device, "Images/house/house4.png", &TEX_HOUSE_4));
	HR(D3DXCreateTextureFromFile(m_device, "Images/house/house5.png", &TEX_HOUSE_5));

	HR(D3DXCreateTextureFromFile(m_device, "Images/house/house5.png", &TEX_HOUSE_5));
	HR(D3DXCreateTextureFromFile(m_device, "Images/spider.jpg", &TEX_SPIDER));
	HR(D3DXCreateTextureFromFile(m_device, "Images/dog.jpg", &TEX_DOG));
	HR(D3DXCreateTextureFromFile(m_device, "Images/ninja.jpg", &TEX_NINJA));
	HR(D3DXCreateTextureFromFile(m_device, "Images/blackNinja.jpg", &TEX_BLACK_NINJA));
	HR(D3DXCreateTextureFromFile(m_device, "Images/female/femaleSkin.png", &TEX_FEMALE_SKIN));
	HR(D3DXCreateTextureFromFile(m_device, "Images/male/maleSkin.png", &TEX_MALE_SKIN));
	HR(D3DXCreateTextureFromFile(m_device, "Images/landscape/house0.png", &TEX_HOUSE_0));

	HR(D3DXCreateTextureFromFile(m_device, "Images/landscape/lowHouse0.png", &TEX_LOW_HOUSE_0));

	HR(D3DXCreateTextureFromFile(m_device, "Images/landscape/lowHouse1Main.png", &TEX_LOW_HOUSE_1_MAIN));
	HR(D3DXCreateTextureFromFile(m_device, "Images/landscape/lowHouse1Roof.png", &TEX_LOW_HOUSE_1_ROOF));
	HR(D3DXCreateTextureFromFile(m_device, "Images/landscape/lowHouse1Garage.png", &TEX_LOW_HOUSE_1_GARAGE));

	HR(D3DXCreateTextureFromFile(m_device, "Images/landscape/storage.png", &TEX_STORAGE));


	//HR(D3DXCreateTextureFromFile(m_device, "Fonts/verdana36.bmp", &TEX_FONT_VERDANA_36));

	D3DXCreateTextureFromFileEx(m_device, "Fonts/verdana36.png", 2048, 64, 1, D3DUSAGE_DYNAMIC, 
											  D3DFMT_FROM_FILE, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 
											  0xFF000000, NULL, NULL, &TEX_FONT_VERDANA_36);

	HR(D3DXCreateTextureFromFile(m_device, "C:/Documents and Settings/csabino/Desktop/exportedMeshes/test.png", &TEX_TEST));





	

	m_imageResources[IMAGE_SHIP_ID] = TEX_SHIP;	
	m_imageResources[IMAGE_BACKGROUND_ID] = TEX_BG;
	m_imageResources[IMAGE_EXPLOSION_ID] = TEX_EXPLOSION;
	m_imageResources[IMAGE_BUTTON_ID] = TEX_BUTTON;
	m_imageResources[IMAGE_CRATE_ID] = TEX_CRATE;
	m_imageResources[IMAGE_ABE_ID] = TEX_ABE;
	
	//DWARF
	m_imageResources[IMAGE_DWARF_WEAPONS_ID] = TEX_DWARF_WEAPONS;
	m_imageResources[IMAGE_DWARF_PACK_ID] = TEX_DWARF_PACK;
	m_imageResources[IMAGE_DWARF_BODY_ID] = TEX_DWARF_BODY;
	m_imageResources[IMAGE_DWARF_ARMOR_ID] = TEX_DWARF_ARMOR;
	m_imageResources[IMAGE_DWARF_HEADGEAR_ID] = TEX_DWARF_HEADGEAR;
	m_imageResources[IMAGE_DWARF_HEAD_ID] = TEX_DWARF_HEAD;

	//TINY_ANIM
	m_imageResources[IMAGE_TINY_ANIM_SKIN_ID] = TEX_TINY_ANIM;

	//Tiger
	m_imageResources[IMAGE_TIGER_SKIN_ID] = TEX_TIGER;

	//Swimmer
	m_imageResources[IMAGE_SWIMMER_SKIN_ID] = TEX_SWIMMER;

	//Terrain
	m_imageResources[IMAGE_TERRAIN_ID] = TEX_TERRAIN;

	//Terrain
	m_imageResources[IMAGE_TERRAIN_FOREST_ID] = TEX_TERRAIN_FOREST;

	//Terrain
	m_imageResources[IMAGE_TERRAIN_NOISE_ID] = TEX_TERRAIN_NOISE;

	//Tree 0
	m_imageResources[IMAGE_TREE_0_BARK_ID] = TEX_TREE_0_BARK;
	m_imageResources[IMAGE_TREE_0_LEAVES_ID] = TEX_TREE_0_LEAVES;

	//Tree 1
	m_imageResources[IMAGE_TREE_1_BARK_ID] = TEX_TREE_1_BARK;
	m_imageResources[IMAGE_TREE_1_LEAVES_ID] = TEX_TREE_1_LEAVES;

	//Tree 2
	m_imageResources[IMAGE_TREE_2_BARK_ID] = TEX_TREE_2_BARK;
	m_imageResources[IMAGE_TREE_2_LEAVES_ID] = TEX_TREE_2_LEAVES;

	//Tree 3
	m_imageResources[IMAGE_TREE_3_BARK_ID] = TEX_TREE_3_BARK;
	m_imageResources[IMAGE_TREE_3_LEAVES_ID] = TEX_TREE_3_LEAVES;

	//CASTLE
	m_imageResources[IMAGE_CASTLE_STONE_FLOOR_ID] = TEX_CASTLE_STONE_FLOOR;
	m_imageResources[IMAGE_CASTLE_BRICK_ID] = TEX_CASTLE_BRICK;
	m_imageResources[IMAGE_CASTLE_MARBLE_ID] = TEX_CASTLE_MARBLE;

	//GRASS PATTERN
	m_imageResources[IMAGE_GRASS_PATTERN_ID] = TEX_GRASS_PATTERN;

	//GRASS BILLBOARD
	m_imageResources[IMAGE_GRASS_BILLBOARD_ID] = TEX_GRASS_BILLBOARD;

	//PARTICLES

	//TORCH
	m_imageResources[IMAGE_PARTICLE_TORCH_ID] = TEX_PARTICLES_TORCH;
	//BOLT
	m_imageResources[IMAGE_PARTICLE_BOLT_ID] = TEX_PARTICLES_BOLT;

	//LANDSCAPE
	m_imageResources[IMAGE_STREET_GROUND_ID] = TEX_STREET_GROUND;
	m_imageResources[IMAGE_CAFE_TABLE_ID] = TEX_CAFE_TABLE;
	m_imageResources[IMAGE_GARDEN_BORDER_ID] = TEX_GARDEN_BORDER;
	m_imageResources[IMAGE_MAILBOX01_ID] = TEX_MAILBOX01;
	m_imageResources[IMAGE_MAILBOX02_ID] = TEX_MAILBOX02;
	m_imageResources[IMAGE_MAILBOX03_ID] = TEX_MAILBOX03;
	m_imageResources[IMAGE_PARKING_BARRIER_ID] = TEX_PARKING_BARRIER;
	m_imageResources[IMAGE_PALETTE_ID] = TEX_PALETTE;
	m_imageResources[IMAGE_PIPE_CAGE_ID] = TEX_PIPE_CAGE;
	m_imageResources[IMAGE_SANDWICH_BOARD_ID] = TEX_SANDWICH_BOARD;
	m_imageResources[IMAGE_SIDEWALK_BARRIER_ID] = TEX_SIDEWALK_BARRIER;
	m_imageResources[IMAGE_SIGN01_ID] = TEX_SIGN01;
	m_imageResources[IMAGE_SIGN02_ID] = TEX_SIGN02;
	m_imageResources[IMAGE_SIGN03_ID] = TEX_SIGN03;
	m_imageResources[IMAGE_SIGN04_ID] = TEX_SIGN04;
	m_imageResources[IMAGE_SIGN05_ID] = TEX_SIGN05;
	m_imageResources[IMAGE_SIGN06_ID] = TEX_SIGN06;
	m_imageResources[IMAGE_SPRINKLER_ID] = TEX_SPRINKLER;
	m_imageResources[IMAGE_BENCH_ID] = TEX_BENCH;
	m_imageResources[IMAGE_STREET_LIGHT_01_ID] = TEX_STREET_LIGHT_01;
	m_imageResources[IMAGE_STREET_LIGHT_01_LIT_ID] = TEX_STREET_LIGHT_01_LIT;
	m_imageResources[IMAGE_STREET_LIGHT_02_ID] = TEX_STREET_LIGHT_02;
	m_imageResources[IMAGE_STREET_LIGHT_02_LIT_ID] = TEX_STREET_LIGHT_02_LIT;
	m_imageResources[IMAGE_SWITCHBOX_ID] = TEX_SWITCHBOX;
	m_imageResources[IMAGE_TRAFFIC_CONE_ID] = TEX_TRAFFIC_CONE;
	
	m_imageResources[IMAGE_BRICKS_ID] = TEX_BRICKS;
	m_imageResources[IMAGE_WALL_GRASS_ID] = TEX_WALL_GRASS;
	m_imageResources[IMAGE_WALL_WOOD_ID] = TEX_WALL_WOOD;

	m_imageResources[IMAGE_SKYBOX_ID] = TEX_SKYBOX;

	m_imageResources[IMAGE_SKYBOX_UP_ID] = TEX_SKYBOX_UP;
	m_imageResources[IMAGE_SKYBOX_DOWN_ID] = TEX_SKYBOX_DOWN;
	m_imageResources[IMAGE_SKYBOX_LEFT_ID] = TEX_SKYBOX_LEFT;
	m_imageResources[IMAGE_SKYBOX_RIGHT_ID] = TEX_SKYBOX_RIGHT;
	m_imageResources[IMAGE_SKYBOX_FRONT_ID] = TEX_SKYBOX_FRONT;
	m_imageResources[IMAGE_SKYBOX_BACK_ID] = TEX_SKYBOX_BACK;

	m_imageResources[IMAGE_HOUSE_ID] = TEX_HOUSE;
	m_imageResources[IMAGE_HOUSE_2_ID] = TEX_HOUSE_2;
	m_imageResources[IMAGE_HOUSE_3_ID] = TEX_HOUSE_3;
	m_imageResources[IMAGE_HOUSE_4_ID] = TEX_HOUSE_4;
	m_imageResources[IMAGE_HOUSE_5_ID] = TEX_HOUSE_5;
	m_imageResources[IMAGE_SPIDER_ID] = TEX_SPIDER;
	m_imageResources[IMAGE_DOG_ID] = TEX_DOG;
	m_imageResources[IMAGE_NINJA_ID] = TEX_NINJA;
	m_imageResources[IMAGE_BLACK_NINJA_ID] = TEX_BLACK_NINJA;

	m_imageResources[IMAGE_FEMALE_SKIN_ID] = TEX_FEMALE_SKIN;
	m_imageResources[IMAGE_MALE_SKIN_ID] = TEX_MALE_SKIN;

	m_imageResources[IMAGE_HOUSE_0_ID] = TEX_HOUSE_0;

	m_imageResources[IMAGE_LOW_HOUSE_0_ID] = TEX_LOW_HOUSE_0;
	m_imageResources[IMAGE_LOW_HOUSE_1_MAIN_ID] = TEX_LOW_HOUSE_1_MAIN;
	m_imageResources[IMAGE_LOW_HOUSE_1_ROOF_ID] = TEX_LOW_HOUSE_1_ROOF;
	m_imageResources[IMAGE_LOW_HOUSE_1_GARAGE_ID] = TEX_LOW_HOUSE_1_GARAGE;
	m_imageResources[IMAGE_STORAGE_ID] = TEX_STORAGE;

	m_imageResources[IMAGE_FONT_VERDANA_36_ID] = TEX_FONT_VERDANA_36;

	m_imageResources[IMAGE_TEST_ID] = TEX_TEST;

	InitializeVideos();

	InitializeFonts();

	InitializeMeshBuffers();

	InitializeSceneBuffers();
}

void ResourceManager::InitializeMeshBuffers()
{	
	FILE * pFile;
	long lSize;
	size_t result;
	fpos_t position;

	//CAFE TABLE
	pFile = fopen ( "Meshes/landscape/cafeTable.c3d" , "rb" );	
	//pFile = fopen ( "C:/Documents and Settings/csabino/Desktop/exportedMeshes/out0.c3d" , "rb" );	
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferCafeTable = (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferCafeTable,lSize,1,pFile);

	m_meshBuffers[MESH_BUFFER_CAFE_TABLE_ID] = bufferCafeTable;

	


	//GARDEN BORDER
	pFile = fopen ( "Meshes/landscape/gardenBorder.c3d" , "rb" );
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferGardenBorder = (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferGardenBorder,lSize,1,pFile);

	m_meshBuffers[MESH_BUFFER_GARDEN_BORDER_ID] = bufferGardenBorder;

	//MAILBOX 1
	pFile = fopen ( "Meshes/landscape/mailbox01.c3d" , "rb" );
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferMailbox1 = (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferMailbox1,lSize,1,pFile);

	m_meshBuffers[MESH_BUFFER_MAILBOX01_ID] = bufferMailbox1;

	
	//MAILBOX 2
	pFile = fopen ( "Meshes/landscape/mailbox02.c3d" , "rb" );
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferMailbox2 = (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferMailbox2,lSize,1,pFile);

	m_meshBuffers[MESH_BUFFER_MAILBOX02_ID] = bufferMailbox2;


	//MAILBOX 3
	pFile = fopen ( "Meshes/landscape/mailbox03.c3d" , "rb" );
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferMailbox3 = (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferMailbox3,lSize,1,pFile);

	m_meshBuffers[MESH_BUFFER_MAILBOX03_ID] = bufferMailbox3;


	
	//PARKING BARRIER
	pFile = fopen ( "Meshes/landscape/parkingBarrier.c3d" , "rb" );
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferParkingBarrier = (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferParkingBarrier,lSize,1,pFile);

	m_meshBuffers[MESH_BUFFER_PARKING_BARRIER_ID] = bufferParkingBarrier;

	//PALETTE
	pFile = fopen ( "Meshes/landscape/palette.c3d" , "rb" );
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferPalette = (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferPalette,lSize,1,pFile);

	m_meshBuffers[MESH_BUFFER_PALETTE_ID] = bufferPalette;

	
	//PIPECAGE
	pFile = fopen ( "Meshes/landscape/pipeCage.c3d" , "rb" );
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferPipeCage = (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferPipeCage,lSize,1,pFile);

	m_meshBuffers[MESH_BUFFER_PIPE_CAGE_ID] = bufferPipeCage;

	//SANDWICH_BOARD
	pFile = fopen ( "Meshes/landscape/sandwichBoard.c3d" , "rb" );
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferSandwichBoard = (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferSandwichBoard,lSize,1,pFile);

	m_meshBuffers[MESH_BUFFER_SANDWICH_BOARD_ID] = bufferSandwichBoard;

	//MESH_BUFFER_SIDEWALK_BARRIER_ID
	pFile = fopen ( "Meshes/landscape/sidewalkBarrier.c3d" , "rb" );
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferSidewalkBarrier = (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferSidewalkBarrier,lSize,1,pFile);

	m_meshBuffers[MESH_BUFFER_SIDEWALK_BARRIER_ID] = bufferSidewalkBarrier;

	
	//MESH_BUFFER_SIGN01_ID
	pFile = fopen ( "Meshes/landscape/sign01.c3d" , "rb" );
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferSign01 = (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferSign01,lSize,1,pFile);

	m_meshBuffers[MESH_BUFFER_SIGN01_ID] = bufferSign01;

	
	//MESH_BUFFER_SIGN02_ID
	pFile = fopen ( "Meshes/landscape/sign02.c3d" , "rb" );
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferSign02 = (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferSign02,lSize,1,pFile);

	m_meshBuffers[MESH_BUFFER_SIGN02_ID] = bufferSign02;

	//MESH_BUFFER_SIGN03_ID
	pFile = fopen ( "Meshes/landscape/sign03.c3d" , "rb" );
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferSign03 = (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferSign03,lSize,1,pFile);

	m_meshBuffers[MESH_BUFFER_SIGN03_ID] = bufferSign03;

	//MESH_BUFFER_SIGN04_ID
	pFile = fopen ( "Meshes/landscape/sign04.c3d" , "rb" );
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferSign04 = (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferSign04,lSize,1,pFile);

	m_meshBuffers[MESH_BUFFER_SIGN04_ID] = bufferSign04;

	//MESH_BUFFER_SIGN05_ID
	pFile = fopen ( "Meshes/landscape/sign05.c3d" , "rb" );
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferSign05 = (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferSign05,lSize,1,pFile);

	m_meshBuffers[MESH_BUFFER_SIGN05_ID] = bufferSign05;

	//MESH_BUFFER_SIGN06_ID
	pFile = fopen ( "Meshes/landscape/sign06.c3d" , "rb" );
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferSign06 = (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferSign06,lSize,1,pFile);

	m_meshBuffers[MESH_BUFFER_SIGN06_ID] = bufferSign06;

	//MESH_BUFFER_SPRINKLER_ID
	pFile = fopen ( "Meshes/landscape/sprinkler.c3d" , "rb" );
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferSprinkler = (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferSprinkler,lSize,1,pFile);

	m_meshBuffers[MESH_BUFFER_SPRINKLER_ID] = bufferSprinkler;

	
	//MESH_BUFFER_BENCH_ID
	pFile = fopen ( "Meshes/landscape/bench.c3d" , "rb" );
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferBench = (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferBench,lSize,1,pFile);

	m_meshBuffers[MESH_BUFFER_BENCH_ID] = bufferBench;

	
	//MESH_BUFFER_STREET_LIGHT_01_ID
	pFile = fopen ( "Meshes/landscape/streetLight01.c3d" , "rb" );
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferStreetLight01= (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferStreetLight01,lSize,1,pFile);

	m_meshBuffers[MESH_BUFFER_STREET_LIGHT_01_ID] = bufferStreetLight01;

	//MESH_BUFFER_STREET_LIGHT_02_ID
	pFile = fopen ( "Meshes/landscape/streetLight02.c3d" , "rb" );
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferStreetLight02= (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferStreetLight02,lSize,1,pFile);

	m_meshBuffers[MESH_BUFFER_STREET_LIGHT_02_ID] = bufferStreetLight02;

	
	//MESH_BUFFER_SWITCHBOX_ID
	pFile = fopen ( "Meshes/landscape/switchBox.c3d" , "rb" );
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferSwitchbox= (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferSwitchbox,lSize,1,pFile);

	m_meshBuffers[MESH_BUFFER_SWITCHBOX_ID] = bufferSwitchbox;

	
	//MESH_BUFFER_TRAFFIC_CONE_ID
	pFile = fopen ( "Meshes/landscape/trafficCone.c3d" , "rb" );
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferTrafficCone= (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferTrafficCone,lSize,1,pFile);

	m_meshBuffers[MESH_BUFFER_TRAFFIC_CONE_ID] = bufferTrafficCone;

	//MESH_BUFFER_HOUSE_0_ID
	pFile = fopen ( "Meshes/landscape/house0.c3d" , "rb" );	
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferHouse0= (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferHouse0,lSize,1,pFile);

	m_meshBuffers[MESH_BUFFER_HOUSE_0_ID] = bufferHouse0;

	//MESH_BUFFER_HOUSE_0_ID
	pFile = fopen ( "Meshes/landscape/house1.c3d" , "rb" );
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferHouse1= (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferHouse1,lSize,1,pFile);

	m_meshBuffers[MESH_BUFFER_HOUSE_1_ID] = bufferHouse1;



	//MESH_BUFFER_HOUSE_ID
	pFile = fopen ( "Meshes/landscape/house.c3d" , "rb" );
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferHouse= (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferHouse,lSize,1,pFile);

	m_meshBuffers[MESH_BUFFER_HOUSE_ID] = bufferHouse;

	
	//MESH_BUFFER_HOUSE_2_ID
	pFile = fopen ( "Meshes/landscape/house_2.c3d" , "rb" );
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferHouse_2= (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferHouse_2,lSize,1,pFile);

	m_meshBuffers[MESH_BUFFER_HOUSE_2_ID] = bufferHouse_2;

	//MESH_BUFFER_HOUSE_3_ID
	pFile = fopen ( "Meshes/landscape/house_3.c3d" , "rb" );
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferHouse_3= (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferHouse_3,lSize,1,pFile);

	m_meshBuffers[MESH_BUFFER_HOUSE_3_ID] = bufferHouse_3;

	//MESH_BUFFER_HOUSE_4_ID
	pFile = fopen ( "Meshes/landscape/house_4.c3d" , "rb" );
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferHouse_4= (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferHouse_4,lSize,1,pFile);

	m_meshBuffers[MESH_BUFFER_HOUSE_4_ID] = bufferHouse_4;

	//MESH_BUFFER_HOUSE_5_ID
	pFile = fopen ( "Meshes/landscape/house_5.c3d" , "rb" );
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferHouse_5= (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferHouse_5,lSize,1,pFile);

	m_meshBuffers[MESH_BUFFER_HOUSE_5_ID] = bufferHouse_5;

	//MESH_BUFFER_LOW_HOUSE_0_ID
	pFile = fopen ( "Meshes/landscape/lowHouse0.c3d" , "rb" );	
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferLowHouse0= (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferLowHouse0,lSize,1,pFile);

	m_meshBuffers[MESH_BUFFER_LOW_HOUSE_0_ID] = bufferLowHouse0;

	//MESH_BUFFER_LOW_HOUSE_1_MAIN_ID
	pFile = fopen ( "Meshes/landscape/lowHouse1Main.c3d" , "rb" );	
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferLowHouse1Main= (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferLowHouse1Main,lSize,1,pFile);

	m_meshBuffers[MESH_BUFFER_LOW_HOUSE_1_MAIN_ID] = bufferLowHouse1Main;

	//MESH_BUFFER_LOW_HOUSE_1_ROOF_ID
	pFile = fopen ( "Meshes/landscape/lowHouse1Roof.c3d" , "rb" );	
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferLowHouse1Roof= (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferLowHouse1Roof,lSize,1,pFile);

	m_meshBuffers[MESH_BUFFER_LOW_HOUSE_1_ROOF_ID] = bufferLowHouse1Roof;

	//MESH_BUFFER_LOW_HOUSE_1_GARAGE_ID
	pFile = fopen ( "Meshes/landscape/lowHouse1Garage.c3d" , "rb" );	
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferLowHouse1Garage= (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferLowHouse1Garage,lSize,1,pFile);

	m_meshBuffers[MESH_BUFFER_LOW_HOUSE_1_GARAGE_ID] = bufferLowHouse1Garage;




	//MESH_BUFFER_SPIDER
	pFile = fopen ( "Meshes/skinned/spider.c3d" , "rb" );
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferSpider= (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferSpider,lSize,1,pFile);

	m_meshBuffers[MESH_BUFFER_SPIDER_ID] = bufferSpider;

	//MESH_BUFFER_SPIDER_BONES
	pFile = fopen ( "Meshes/skinned/spiderBones.c3d" , "rb" );
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferSpiderBones= (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferSpiderBones,lSize,1,pFile);

	m_meshBuffers[MESH_BUFFER_SPIDER_BONES_ID] = bufferSpiderBones;

	//MESH_BUFFER_DOG
	pFile = fopen ( "Meshes/skinned/dog.c3d" , "rb" );
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferDog= (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferDog,lSize,1,pFile);

	m_meshBuffers[MESH_BUFFER_DOG_ID] = bufferDog;

	//MESH_BUFFER_DOG_BONES
	pFile = fopen ( "Meshes/skinned/dogBones.c3d" , "rb" );
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferDogBones= (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferDogBones,lSize,1,pFile);

	m_meshBuffers[MESH_BUFFER_DOG_BONES_ID] = bufferDogBones;

	//MESH_BUFFER_NINJA
	pFile = fopen ( "Meshes/skinned/ninja.c3d" , "rb" );
	//pFile = fopen ( "C:/Documents and Settings/csabino/Desktop/exportedMeshes/SkinnedMeshOut0.c3d" , "rb" );
	
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferNinja= (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferNinja,lSize,1,pFile);

	m_meshBuffers[MESH_BUFFER_NINJA_ID] = bufferNinja;

	//MESH_BUFFER_NINJA_BONES
	pFile = fopen ( "Meshes/skinned/ninjaBones.c3d" , "rb" );
	//pFile = fopen ( "C:/Documents and Settings/csabino/Desktop/exportedMeshes/SkinnedMeshOutBones.c3d" , "rb" );
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferNinjaBones= (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferNinjaBones,lSize,1,pFile);

	m_meshBuffers[MESH_BUFFER_NINJA_BONES_ID] = bufferNinjaBones;

	//MESH_CHARACTER_MALE
	//pFile = fopen ( "C:/Documents and Settings/csabino/Desktop/exportedMeshes/SkinnedMeshOut0.c3d" , "rb" );
	pFile = fopen ( "Meshes/skinned/characterMale.c3d" , "rb" );
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferCharacterMale= (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferCharacterMale,lSize,1,pFile);

	m_meshBuffers[MESH_BUFFER_CHARACTER_MALE_ID] = bufferCharacterMale;

	//MESH_CHARACTER_MALE_BONES
	pFile = fopen ( "Meshes/skinned/characterMaleBones.c3d" , "rb" );
	//pFile = fopen ( "C:/Documents and Settings/csabino/Desktop/exportedMeshes/SkinnedMeshOutBones.c3d" , "rb" );
	//pFile = fopen ( "C:/Documents and Settings/csabino/Desktop/exportedMeshes/IdentityBones.c3d" , "rb" );
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferCharacterMaleBones= (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferCharacterMaleBones,lSize,1,pFile);

	m_meshBuffers[MESH_BUFFER_CHARACTER_MALE_BONES_ID] = bufferCharacterMaleBones;

	//MESH_CHARACTER_SWIMMER
	//pFile = fopen ( "C:/Documents and Settings/csabino/Desktop/exportedMeshes/SkinnedMeshOut0.c3d" , "rb" );
	pFile = fopen ( "Meshes/skinned/Swimmer.c3d" , "rb" );
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferSwimmer= (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferSwimmer,lSize,1,pFile);

	m_meshBuffers[MESH_BUFFER_SWIMMER_ID] = bufferSwimmer;

	//MESH_CHARACTER_MALE_BONES
	pFile = fopen ( "Meshes/skinned/SwimmerWalk.c3d" , "rb" );
	//pFile = fopen ( "C:/Documents and Settings/csabino/Desktop/exportedMeshes/SkinnedMeshOutBones.c3d" , "rb" );
	//pFile = fopen ( "C:/Documents and Settings/csabino/Desktop/exportedMeshes/IdentityBones.c3d" , "rb" );
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferSwimmerWalk= (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferSwimmerWalk,lSize,1,pFile);

	m_meshBuffers[MESH_BUFFER_SWIMMER_WALK_ID] = bufferSwimmerWalk;

	//MESH_CHARACTER_MALE_BONES
	pFile = fopen ( "Meshes/skinned/SwimmerBonesJumpKick.c3d" , "rb" );
	//pFile = fopen ( "C:/Documents and Settings/csabino/Desktop/exportedMeshes/SkinnedMeshOutBones.c3d" , "rb" );
	//pFile = fopen ( "C:/Documents and Settings/csabino/Desktop/exportedMeshes/IdentityBones.c3d" , "rb" );
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferSwimmerBonesJumpKick= (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferSwimmerBonesJumpKick,lSize,1,pFile);

	m_meshBuffers[MESH_BUFFER_SWIMMER_BONES_JUMP_KICK_ID] = bufferSwimmerBonesJumpKick;

	//MESH_CHARACTER_MALE_BONES
	pFile = fopen ( "Meshes/skinned/SwimmerCarry.c3d" , "rb" );
	//pFile = fopen ( "C:/Documents and Settings/csabino/Desktop/exportedMeshes/SkinnedMeshOutBones.c3d" , "rb" );
	//pFile = fopen ( "C:/Documents and Settings/csabino/Desktop/exportedMeshes/IdentityBones.c3d" , "rb" );
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferSwimmerCarry= (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferSwimmerCarry,lSize,1,pFile);

	m_meshBuffers[MESH_BUFFER_SWIMMER_BONES_CARRY_ID] = bufferSwimmerCarry;

	//MESH_CHARACTER_MALE_BONES
	pFile = fopen ( "Meshes/skinned/SwimmerCarry2.c3d" , "rb" );
	//pFile = fopen ( "C:/Documents and Settings/csabino/Desktop/exportedMeshes/SkinnedMeshOutBones.c3d" , "rb" );
	//pFile = fopen ( "C:/Documents and Settings/csabino/Desktop/exportedMeshes/IdentityBones.c3d" , "rb" );
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferSwimmerCarry2= (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferSwimmerCarry2,lSize,1,pFile);

	m_meshBuffers[MESH_BUFFER_SWIMMER_BONES_CARRY_2_ID] = bufferSwimmerCarry2;

	//MESH_CHARACTER_MALE_BONES
	pFile = fopen ( "Meshes/skinned/SwimmerCool.c3d" , "rb" );
	//pFile = fopen ( "C:/Documents and Settings/csabino/Desktop/exportedMeshes/SkinnedMeshOutBones.c3d" , "rb" );
	//pFile = fopen ( "C:/Documents and Settings/csabino/Desktop/exportedMeshes/IdentityBones.c3d" , "rb" );
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferSwimmerCool= (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferSwimmerCool,lSize,1,pFile);

	m_meshBuffers[MESH_BUFFER_SWIMMER_BONES_COOL_ID] = bufferSwimmerCool;

	//MESH_CHARACTER_MALE_BONES
	pFile = fopen ( "Meshes/skinned/SwimmerFastWalk.c3d" , "rb" );
	//pFile = fopen ( "C:/Documents and Settings/csabino/Desktop/exportedMeshes/SkinnedMeshOutBones.c3d" , "rb" );
	//pFile = fopen ( "C:/Documents and Settings/csabino/Desktop/exportedMeshes/IdentityBones.c3d" , "rb" );
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferSwimmerFastWalk= (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferSwimmerFastWalk,lSize,1,pFile);

	m_meshBuffers[MESH_BUFFER_SWIMMER_BONES_FAST_WALK_ID] = bufferSwimmerFastWalk;

	//MESH_CHARACTER_MALE_BONES
	pFile = fopen ( "Meshes/skinned/SwimmerKneeKick.c3d" , "rb" );
	//pFile = fopen ( "C:/Documents and Settings/csabino/Desktop/exportedMeshes/SkinnedMeshOutBones.c3d" , "rb" );
	//pFile = fopen ( "C:/Documents and Settings/csabino/Desktop/exportedMeshes/IdentityBones.c3d" , "rb" );
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferSwimmerKneeKick = (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferSwimmerKneeKick,lSize,1,pFile);

	m_meshBuffers[MESH_BUFFER_SWIMMER_BONES_KNEE_KICK_ID] = bufferSwimmerKneeKick;

	//MESH_CHARACTER_MALE_BONES
	pFile = fopen ( "Meshes/skinned/SwimmerMoonwalk.c3d" , "rb" );
	//pFile = fopen ( "C:/Documents and Settings/csabino/Desktop/exportedMeshes/SkinnedMeshOutBones.c3d" , "rb" );
	//pFile = fopen ( "C:/Documents and Settings/csabino/Desktop/exportedMeshes/IdentityBones.c3d" , "rb" );
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferSwimmerMoonwalk= (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferSwimmerMoonwalk,lSize,1,pFile);

	m_meshBuffers[MESH_BUFFER_SWIMMER_BONES_MOONWALK_ID] = bufferSwimmerMoonwalk;

	//MESH_CHARACTER_MALE_BONES
	pFile = fopen ( "Meshes/skinned/SwimmerRunLoop.c3d" , "rb" );
	//pFile = fopen ( "C:/Documents and Settings/csabino/Desktop/exportedMeshes/SkinnedMeshOutBones.c3d" , "rb" );
	//pFile = fopen ( "C:/Documents and Settings/csabino/Desktop/exportedMeshes/IdentityBones.c3d" , "rb" );
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferSwimmerRunLoop= (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferSwimmerRunLoop,lSize,1,pFile);

	m_meshBuffers[MESH_BUFFER_SWIMMER_BONES_RUN_LOOP_ID] = bufferSwimmerRunLoop;

	//MESH_CHARACTER_MALE_BONES
	pFile = fopen ( "Meshes/skinned/SwimmerWalkBackwards.c3d" , "rb" );
	//pFile = fopen ( "C:/Documents and Settings/csabino/Desktop/exportedMeshes/SkinnedMeshOutBones.c3d" , "rb" );
	//pFile = fopen ( "C:/Documents and Settings/csabino/Desktop/exportedMeshes/IdentityBones.c3d" , "rb" );
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferSwimmerWalkBackwards= (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferSwimmerWalkBackwards,lSize,1,pFile);

	m_meshBuffers[MESH_BUFFER_SWIMMER_BONES_WALK_BACKWARD_ID] = bufferSwimmerWalkBackwards;

	//MESH_CHARACTER_MALE_BONES
	pFile = fopen ( "Meshes/skinned/SwimmerIdle.c3d" , "rb" );
	//pFile = fopen ( "C:/Documents and Settings/csabino/Desktop/exportedMeshes/SkinnedMeshOutBones.c3d" , "rb" );
	//pFile = fopen ( "C:/Documents and Settings/csabino/Desktop/exportedMeshes/IdentityBones.c3d" , "rb" );
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferSwimmerIdle = (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferSwimmerIdle,lSize,1,pFile);

	m_meshBuffers[MESH_BUFFER_SWIMMER_BONES_IDLE_ID] = bufferSwimmerIdle;

	//MESH_TEST_ID
	pFile = fopen ( "C:/Documents and Settings/csabino/Desktop/exportedMeshes/out0.c3d" , "rb" );	
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferTest = (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferTest,lSize,1,pFile);

	m_meshBuffers[MESH_BUFFER_TEST_ID] = bufferTest;		

}

void ResourceManager::InitializeSceneBuffers()
{	
	FILE * pFile;
	long lSize;
	size_t result;
	fpos_t position;

	//Scene0
	pFile = fopen ( "Meshes/scenes/scene0.c3d" , "rb" );	
	//pFile = fopen ( "C:/Documents and Settings/csabino/Desktop/exportedMeshes/outScene.c3d" , "rb" );
	
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	char *bufferScene0 = (char*)malloc(lSize);
	fsetpos(pFile, &position);
	result = fread (bufferScene0,lSize,1,pFile);

	m_sceneBuffers[SCENE_BUFFER_SCENE_0_ID] = bufferScene0;	
	
}

char * ResourceManager::GetMeshBuffer(int meshBufferID)
{
	return m_meshBuffers[meshBufferID];
}

char * ResourceManager::GetSceneBuffer(int sceneBufferID)
{
	return m_sceneBuffers[sceneBufferID];
}

void ResourceManager::InitializeVideos()
{
	AVIFileInit();
	IAVIFile *t_aviFile = NULL;

	if(AVIFileOpen(&t_aviFile, "Videos/intro.avi", OF_READ, NULL) != 0)
	{
		
	}

	PAVISTREAM *t_stream = new PAVISTREAM();
	PGETFRAME *t_getFrame = new PGETFRAME();
	AVIFileGetStream(t_aviFile, t_stream, streamtypeVIDEO, 0);
	*t_getFrame = AVIStreamGetFrameOpen(*t_stream, NULL);
	long t_time = AVIStreamEndTime(*t_stream);
	VideoStructure *t_structure = new VideoStructure();
	t_structure->m_frames = t_getFrame;
	t_structure->m_stream = t_stream;
	t_structure->m_totalTime = t_time;

	m_videos[VIDEO_FIRST_ID] = t_structure;


	m_videos[VIDEO_FIRST_ID] = t_structure;


	AVIFileInit();
	t_aviFile = NULL;

	if(AVIFileOpen(&t_aviFile, "Videos/intro.avi", OF_READ, NULL) != 0)
	{
		
	}

	PAVISTREAM *t_stream2 = new PAVISTREAM();
	PGETFRAME *t_getFrame2 = new PGETFRAME();
	AVIFileGetStream(t_aviFile, t_stream2, streamtypeVIDEO, 0);
	*t_getFrame2 = AVIStreamGetFrameOpen(*t_stream2, NULL);
	t_time = AVIStreamEndTime(*t_stream2);
	VideoStructure *t_structure2 = new VideoStructure();
	t_structure2->m_frames = t_getFrame2;
	t_structure2->m_stream = t_stream2;
	t_structure2->m_totalTime = t_time;

	

	m_videos[VIDEO_SECOND_ID] = t_structure2;
	//AVIFileExit();
}

void ResourceManager::InitializeFonts()
{
	FILE * pFile;
	long lSize;
	size_t result;
	fpos_t position;

	pFile = fopen ( "Fonts/verdana36.bin", "rb" );	

	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	fgetpos(pFile, &position);

	// allocate memory to contain the whole file:
	int *buffer = (int*)malloc((int)lSize);

	int totalCharacters;

	fsetpos(pFile, &position);

	//bool *t_buffer = (bool*)malloc(sizeof(bool)*32);
	result = fread(buffer,sizeof(int), lSize/sizeof(int),pFile);
	//result = fread(t_buffer,1,sizeof(int),pFile);
	
	totalCharacters = buffer[0];
	fclose(pFile);

	m_fonts[FONT_VERDANA_36_ID] = buffer;
	
	
}

VideoStructure * ResourceManager::GetVideoByID(int a_ID)
{
	return m_videos[a_ID];
}

IDirect3DTexture9 * ResourceManager::GetTextureByID(int id)
{
	//return TEX_SHIP;
	//return temp;
	IDirect3DTexture9* tex = m_imageResources[id];
	return tex; 
}

IDirect3DTexture9 * ResourceManager::GetTextureByFilename(std::string a_filename)
{
	if(strcmp(a_filename.c_str(), "alienship.bmp") == 0)	
	{
		return m_imageResources[IMAGE_SHIP_ID];
	}	
	
	else if(strcmp(a_filename.c_str(), "bkgd1.bmp") == 0)
	{
		return m_imageResources[IMAGE_BACKGROUND_ID];
	}
	else if(strcmp(a_filename.c_str(), "fireatlas.bmp") == 0)
	{
		return m_imageResources[IMAGE_EXPLOSION_ID];
	}
	else if(strcmp(a_filename.c_str(), "button.bmp") == 0)
	{
		return m_imageResources[IMAGE_BUTTON_ID];
	}
	else if(strcmp(a_filename.c_str(), "crate.jpg") == 0)
	{
		return m_imageResources[IMAGE_CRATE_ID];
	}
	else if(strcmp(a_filename.c_str(), "abe.jpg") == 0)
	{
		return m_imageResources[IMAGE_ABE_ID];
	}	
	//DWARF
	else if(strcmp(a_filename.c_str(), "Weapons.dds") == 0)
	{
		return m_imageResources[IMAGE_DWARF_WEAPONS_ID];
	}	
	else if(strcmp(a_filename.c_str(), "Pack.dds") == 0)
	{
		return m_imageResources[IMAGE_DWARF_PACK_ID];
	}	
	else if(strcmp(a_filename.c_str(), "Body.dds") == 0)
	{
		return m_imageResources[IMAGE_DWARF_BODY_ID];
	}	
	else if(strcmp(a_filename.c_str(), "Armor.dds") == 0)
	{
		return m_imageResources[IMAGE_DWARF_ARMOR_ID];
	}	
	else if(strcmp(a_filename.c_str(), "Headgear.dds") == 0)
	{
		return m_imageResources[IMAGE_DWARF_HEADGEAR_ID];
	}	
	else if(strcmp(a_filename.c_str(), "DwarfHead.dds") == 0)
	{
		return m_imageResources[IMAGE_DWARF_HEAD_ID];
	}	
	//TINY ANIM
	else if(strcmp(a_filename.c_str(), "Tiny_skin.dds") == 0)
	{
		return m_imageResources[IMAGE_TINY_ANIM_SKIN_ID];
	}	
	//TIGER
	else if(strcmp(a_filename.c_str(), "tiger.bmp") == 0)
	{
		return m_imageResources[IMAGE_TIGER_SKIN_ID];
	}	
	//Swimmer
	else if(strcmp(a_filename.c_str(), "swimmer.bmp") == 0)
	{
		return m_imageResources[IMAGE_SWIMMER_SKIN_ID];
	}	
	//Terrain
	else if(strcmp(a_filename.c_str(), "terrain.bmp") == 0)
	{
		return m_imageResources[IMAGE_TERRAIN_ID];
	}
	//tree 0
	else if(strcmp(a_filename.c_str(), "tree0_bark.dds") == 0)
	{
		return m_imageResources[IMAGE_TREE_0_BARK_ID];
	}
	else if(strcmp(a_filename.c_str(), "tree0_leaf.dds") == 0)
	{
		return m_imageResources[IMAGE_TREE_0_LEAVES_ID];
	}
	//tree 1
	else if(strcmp(a_filename.c_str(), "tree1_bark.dds") == 0)
	{
		return m_imageResources[IMAGE_TREE_1_BARK_ID];
	}
	else if(strcmp(a_filename.c_str(), "tree1_leaf.dds") == 0)
	{
		return m_imageResources[IMAGE_TREE_1_LEAVES_ID];
	}
	//tree 2
	else if(strcmp(a_filename.c_str(), "tree2_bark.dds") == 0)
	{
		return m_imageResources[IMAGE_TREE_2_BARK_ID];
	}
	else if(strcmp(a_filename.c_str(), "tree2_leaf.dds") == 0)
	{
		return m_imageResources[IMAGE_TREE_2_LEAVES_ID];
	}
	//tree 3
	else if(strcmp(a_filename.c_str(), "tree3_bark.dds") == 0)
	{
		return m_imageResources[IMAGE_TREE_3_BARK_ID];
	}
	else if(strcmp(a_filename.c_str(), "tree3_leaf.dds") == 0)
	{
		return m_imageResources[IMAGE_TREE_3_LEAVES_ID];
	}
	//castle
	else if(strcmp(a_filename.c_str(), "marble.bmp") == 0)
	{
		return m_imageResources[IMAGE_CASTLE_MARBLE_ID];
	}
	else if(strcmp(a_filename.c_str(), "stonefloor.bmp") == 0)
	{
		return m_imageResources[IMAGE_CASTLE_STONE_FLOOR_ID];
	}
	else if(strcmp(a_filename.c_str(), "darkbrick.bmp") == 0)
	{
		return m_imageResources[IMAGE_CASTLE_BRICK_ID];
	}
	//grass pattern
	else if(strcmp(a_filename.c_str(), "grass.dds") == 0)
	{
		return m_imageResources[IMAGE_GRASS_PATTERN_ID];
	}
	//grass billboard
	else if(strcmp(a_filename.c_str(), "grassfin0.dds") == 0)
	{
		return m_imageResources[IMAGE_GRASS_BILLBOARD_ID];
	}

	//PARTICLES

	//TORCH
	else if(strcmp(a_filename.c_str(), "torch.dds") == 0)
	{
		return m_imageResources[IMAGE_PARTICLE_TORCH_ID];
	}
	else if(strcmp(a_filename.c_str(), "bolt.dds") == 0)
	{
		return m_imageResources[IMAGE_PARTICLE_BOLT_ID];
	}		
	else if(strcmp(a_filename.c_str(), "brick.jpg") == 0)
	{
		return m_imageResources[IMAGE_BRICKS_ID];
	}	
	else if(strcmp(a_filename.c_str(), "wall_grass.jpg") == 0)
	{
		return m_imageResources[IMAGE_WALL_GRASS_ID];
	}	
	else if(strcmp(a_filename.c_str(), "wall_wood.jpg") == 0)
	{
		return m_imageResources[IMAGE_WALL_WOOD_ID];
	}	
	else if(strcmp(a_filename.c_str(), "skybox.jpg") == 0)
	{
		return m_imageResources[IMAGE_SKYBOX_ID];
	}	
	else if(strcmp(a_filename.c_str(), "house.png") == 0)
	{
		return m_imageResources[IMAGE_HOUSE_ID];
	}	
	else if(strcmp(a_filename.c_str(), "house2.png") == 0)
	{
		return m_imageResources[IMAGE_HOUSE_2_ID];
	}	
	else if(strcmp(a_filename.c_str(), "house3.png") == 0)
	{
		return m_imageResources[IMAGE_HOUSE_3_ID];
	}	
	else if(strcmp(a_filename.c_str(), "house4.png") == 0)
	{
		return m_imageResources[IMAGE_HOUSE_4_ID];
	}	
	else if(strcmp(a_filename.c_str(), "house5.png") == 0)
	{
		return m_imageResources[IMAGE_HOUSE_5_ID];
	}	
	else
	{
		return NULL;
	}
}

std::string ResourceManager::GetMeshFilenameByID(int a_ID)
{
	return m_meshesFilenames[a_ID];
}

int * ResourceManager::GetFontDescriptor(int a_fontId)
{
	return m_fonts[a_fontId];
}



//C3DESprite * ResourceManager::GetSpriteByID(int id)
//{
	//return (*((C3DESprite**)g_resources[id]));
	//return NULL;
//}