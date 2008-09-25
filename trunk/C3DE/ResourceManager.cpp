#include "ResourceManager.h"
#include "DebugMemory.h"
#include "D3DCommonDefs.h"

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
	IDirect3DTexture9 * TEX_SHIP_BULLET;
	IDirect3DTexture9 * TEX_BG;
	IDirect3DTexture9 * TEX_EXPLOSION;
	IDirect3DTexture9 * TEX_BUTTON;
	IDirect3DTexture9 * TEX_CRATE;

	HR(D3DXCreateTextureFromFile(m_device, "Images/alienship.bmp", &TEX_SHIP));
	HR(D3DXCreateTextureFromFile(m_device, "Images/bullet.bmp", &TEX_SHIP_BULLET));
	HR(D3DXCreateTextureFromFile(m_device, "Images/bkgd1.bmp", &TEX_BG));	
	HR(D3DXCreateTextureFromFile(m_device, "Images/fireatlas.bmp", &TEX_EXPLOSION));
	HR(D3DXCreateTextureFromFile(m_device, "Images/button.bmp", &TEX_BUTTON));
	HR(D3DXCreateTextureFromFile(m_device, "Images/crate.jpg", &TEX_CRATE));

	m_imageResources[0] = TEX_SHIP;
	m_imageResources[1] = TEX_SHIP_BULLET;
	m_imageResources[2] = TEX_BG;
	m_imageResources[3] = TEX_EXPLOSION;
	m_imageResources[4] = TEX_BUTTON;
	m_imageResources[5] = TEX_CRATE;


}

IDirect3DTexture9 * ResourceManager::GetImageByID(int id)
{
	//return TEX_SHIP;
	//return temp;
	IDirect3DTexture9* tex = m_imageResources[id];
	return tex; 
}


//C3DESprite * ResourceManager::GetSpriteByID(int id)
//{
	//return (*((C3DESprite**)g_resources[id]));
	//return NULL;
//}