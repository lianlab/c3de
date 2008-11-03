#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#define MAX_SHADERS_RESOURCES 100


#include "CommonDefs.h"

#include "FX.h"
#include <d3dx9.h>



enum ShaderIDs
{ 	
	SHADER_BOOK_LIGHTS_ID, 
	SHADER_LIGHTS_AND_TEXTURES_ID, 	
	SHADER_ONLY_LIGHTS_ID, 	
	SHADER_LIGHTS_TEXTURES_BLENDING_ID, 
	SHADER_LIGHTS_PER_VERTEX_TEXTURES_ID, 
	SHADER_LIGHTS_PER_PIXEL_TEXTURES_ID, 
	SHADER_HARD_COLORS_ID, 
	TOTAL_SHADERS
};

class ShaderManager
{
public:
	static ShaderManager * GetInstance();
	
	~ShaderManager();
	ID3DXEffect * GetEffectById(int id);
	FX * GetFXByID(int id);
	void SetDevice(IDirect3DDevice9 *device);
	

private:
	ShaderManager();
	static ShaderManager *m_instance;	
	void InitializeResources();
	IDirect3DDevice9 *m_device;

	ID3DXEffect * m_effectResources[TOTAL_SHADERS];	

	FX * m_effects[TOTAL_SHADERS];
};
#endif
