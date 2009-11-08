#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#define MAX_SHADERS_RESOURCES 100


#include "CommonDefs.h"

#include "FX.h"
#include "ShadowFX.h"
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
	SHADER_SHADOW_FX_ID, 
	SHADER_SKINNED_MESH_FX_ID, 
	SHADER_SKINNED_MESH_BOOK_FX_ID, 
	SHADER_BILLBOARD_FX_ID, 
	SHADER_GRASS_FX_ID, 
	SHADER_FIRE_RING_FX_ID, 
	SHADER_SUPERNOVA_FX_ID, 
	SHADER_LIGHTS_PER_VERTEX_TEXTURES_NO_FOG_ID, 
	SHADER_LIGHTS_PER_VERTEX_TEXTURES_WALL_NO_FOG_ID, 
	SHADER_C3DE_SKINNED_MESH_FX_ID, 
	SHADER_TEXTURE_ONLY_ID, 
	SHADER_DIFFUSE_STATIC_LIGHT_ID,
	SHADER_AMBIENT_LIGHT_ID,
	SHADER_SPECULAR_LIGHT_ID,
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
	ShadowFX * GetDefaultShadowFX();
	

private:
	ShaderManager();
	static ShaderManager *m_instance;	
	void InitializeResources();
	IDirect3DDevice9 *m_device;

	ID3DXEffect * m_effectResources[TOTAL_SHADERS];	

	FX * m_effects[TOTAL_SHADERS];
};
#endif
