#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#define MAX_SHADERS_RESOURCES 100


#include "CommonDefs.h"


#include <d3dx9.h>



enum ShaderIDs
{ 
	SHADER_BOOK_FIRST_ID, 
	
	TOTAL_SHADERS
};

class ShaderManager
{
public:
	static ShaderManager * GetInstance();
	
	~ShaderManager();

	//C3DESprite * GetSpriteByID(int id);
	//IDirect3DTexture9 * GetImageByID(int id);
	ID3DXEffect * GetEffectById(int id);


	
	
	//inline static void* m_resources[] = {1,2};

	void SetDevice(IDirect3DDevice9 *device);
	

private:
	ShaderManager();
	static ShaderManager *m_instance;	
	void InitializeResources();
	IDirect3DDevice9 *m_device;

	ID3DXEffect * m_effectResources[TOTAL_SHADERS];

	/*
	IDirect3DTexture9 * temp;

	IDirect3DTexture9 * m_imageResources[TOTAL_IMAGES];
	
	
*/
	

};
#endif
