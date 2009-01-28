#include "ResourceManager.h"
#include <fstream>
#include "DebugMemory.h"
#include "D3DCommonDefs.h"

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


}

ResourceManager::~ResourceManager()
{

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
	HR(D3DXCreateTextureFromFile(m_device, "Images/Terrain/terrain.bmp", &TEX_TERRAIN));
	///////////////////

	

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


#if 0
	

	// Open the file.
	std::ifstream t_inFile;

	//TERRAIN 1
	// A height for each vertex
	std::vector<unsigned char> t_in( 129 * 129 );	
	t_inFile.open("Images/Terrain/terrain.raw", ios_base::binary);
	// Read the RAW bytes.
	t_inFile.read((char*)&t_in[0], (streamsize)t_in.size());
	// Done with file.
	t_inFile.close();
	m_fileBytes[0] = &t_in;





	float *m_pHeightMap = new float[128 * 128];
	memset(m_pHeightMap, 0, sizeof(float)  * 128 * 128);
	IDirect3DTexture9 *heightMapTexture =  NULL;

	D3DXCreateTextureFromFile(m_device, "Images/Terrain/terrain.bmp", &heightMapTexture);
	D3DLOCKED_RECT sRect;
	heightMapTexture->LockRect(0, &sRect, NULL, NULL);
	BYTE *bytes = (BYTE*)sRect.pBits;

	for(int y=0; y<128;y++)
	{
		for (int x = 0; x <128; x++)
		{
			BYTE *b = bytes + y*sRect.Pitch + x;
			m_pHeightMap[x+y*128] = ((*b /255.0f) * 5.0f);
		}

	}

	heightMapTexture->UnlockRect(0);

#endif
}

void poxa()
{
	
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
	else
	{
		return NULL;
	}
}

std::string ResourceManager::GetMeshFilenameByID(int a_ID)
{
	return m_meshesFilenames[a_ID];
}



//C3DESprite * ResourceManager::GetSpriteByID(int id)
//{
	//return (*((C3DESprite**)g_resources[id]));
	//return NULL;
//}