#include "ShaderManager.h"

#include "D3DCommonDefs.h"

#include "BookLights.h"
#include "LightsAndTextures.h"
#include "LightsTexturesBlending.h"
#include "OnlyLights.h"
#include "PerVertexLighting.h"
#include "PerPixelLighting.h"
#include "HardColors.h"
#include "ShadowFX.h"
#include "SkinnedMeshFX.h"
#include "SkinnedMeshBookFX.h"
#include "BillboardFX.h"
#include "GrassFX.h"
#include "FireRingFx.h"
#include "PerVertexLightingNoFog.h"
#include "C3DESkinnedMeshFX.h"
#include "C3DESkinnedMeshClean.h"
#include "DebugMemory.h"



ShaderManager * ShaderManager::m_instance = NULL;

ShaderManager * ShaderManager::GetInstance()
{
	if(!m_instance)
	{
		m_instance = new ShaderManager();
	}

	return m_instance;
}
ShaderManager::ShaderManager()
{
	
}

ShaderManager::~ShaderManager()
{
	int totalEffects = TOTAL_SHADERS;
	for(int i = 0; i< totalEffects; i++)
	{
		FX *t_fx = m_effects[i];
		delete t_fx;
		t_fx = NULL;
	}
}

void ShaderManager::SetDevice(IDirect3DDevice9 *device)
{ 
	m_device = device;
	InitializeResources();
}

void ShaderManager::InitializeResources()
{

	ID3DXBuffer *errors = 0;	

	ID3DXEffect * SHADER_BOOK_LIGHTS;	
	D3DXCreateEffectFromFile(m_device, "effects/lights.fx", 0, 0, D3DXSHADER_DEBUG, 0, &SHADER_BOOK_LIGHTS, &errors);	
	if(errors)
		MessageBox(0, (char*) errors->GetBufferPointer(), 0, 0);
	m_effectResources[SHADER_BOOK_LIGHTS_ID] = SHADER_BOOK_LIGHTS;

	ID3DXEffect * SHADER_LIGHTS_AND_TEXTURES;
	errors = 0;	
	D3DXCreateEffectFromFile(m_device, "effects/lightsAndTextures.fx", 0, 0, D3DXSHADER_DEBUG, 0, &SHADER_LIGHTS_AND_TEXTURES, &errors);	
	if(errors)
		MessageBox(0, (char*) errors->GetBufferPointer(), 0, 0);
	m_effectResources[SHADER_LIGHTS_AND_TEXTURES_ID] = SHADER_LIGHTS_AND_TEXTURES;

	ID3DXEffect * SHADER_ONLY_LIGHTS;
	errors = 0;	
	D3DXCreateEffectFromFile(m_device, "effects/onlyLights.fx", 0, 0, D3DXSHADER_DEBUG, 0, &SHADER_ONLY_LIGHTS, &errors);	
	if(errors)
		MessageBox(0, (char*) errors->GetBufferPointer(), 0, 0);
	m_effectResources[SHADER_ONLY_LIGHTS_ID] = SHADER_ONLY_LIGHTS;

	ID3DXEffect * SHADER_LIGHTS_TEXTURES_BLENDING;
	errors = 0;	
	D3DXCreateEffectFromFile(m_device, "effects/lightsAndTexturesAlphaBlending.fx", 0, 0, D3DXSHADER_DEBUG, 0, &SHADER_LIGHTS_TEXTURES_BLENDING, &errors);	
	if(errors)
		MessageBox(0, (char*) errors->GetBufferPointer(), 0, 0);
	m_effectResources[SHADER_LIGHTS_TEXTURES_BLENDING_ID] = SHADER_LIGHTS_TEXTURES_BLENDING;

	ID3DXEffect * SHADER_LIGHTS_PER_VERTEX_TEXTURES;
	errors = 0;	
	D3DXCreateEffectFromFile(m_device, "effects/PerVertexLighting.fx", 0, 0, D3DXSHADER_DEBUG, 0, &SHADER_LIGHTS_PER_VERTEX_TEXTURES, &errors);	
	if(errors)
		MessageBox(0, (char*) errors->GetBufferPointer(), 0, 0);
	m_effectResources[SHADER_LIGHTS_PER_VERTEX_TEXTURES_ID] = SHADER_LIGHTS_PER_VERTEX_TEXTURES;

	ID3DXEffect * SHADER_LIGHTS_PER_PIXEL_TEXTURES;
	errors = 0;	
	D3DXCreateEffectFromFile(m_device, "effects/PerPixelLighting.fx", 0, 0, D3DXSHADER_DEBUG, 0, &SHADER_LIGHTS_PER_PIXEL_TEXTURES, &errors);	
	if(errors)
		MessageBox(0, (char*) errors->GetBufferPointer(), 0, 0);
	m_effectResources[SHADER_LIGHTS_PER_PIXEL_TEXTURES_ID] = SHADER_LIGHTS_PER_PIXEL_TEXTURES;

	ID3DXEffect * SHADER_HARD_COLORS;
	errors = 0;	
	D3DXCreateEffectFromFile(m_device, "effects/hardColors.fx", 0, 0, D3DXSHADER_DEBUG, 0, &SHADER_HARD_COLORS, &errors);	
	if(errors)
		MessageBox(0, (char*) errors->GetBufferPointer(), 0, 0);
	m_effectResources[SHADER_HARD_COLORS_ID] = SHADER_HARD_COLORS;

	ID3DXEffect * SHADER_SHADOW_FX;
	errors = 0;	
	D3DXCreateEffectFromFile(m_device, "effects/Shadow.fx", 0, 0, D3DXSHADER_DEBUG, 0, &SHADER_SHADOW_FX, &errors);	
	if(errors)
		MessageBox(0, (char*) errors->GetBufferPointer(), 0, 0);
	m_effectResources[SHADER_SHADOW_FX_ID] = SHADER_SHADOW_FX;

	ID3DXEffect * SHADER_SKINNED_MESH_FX;
	errors = 0;	
	D3DXCreateEffectFromFile(m_device, "effects/SkinnedMesh.fx", 0, 0, D3DXSHADER_DEBUG, 0, &SHADER_SKINNED_MESH_FX, &errors);
	if(errors)
		MessageBox(0, (char*) errors->GetBufferPointer(), 0, 0);;	
	m_effectResources[SHADER_SKINNED_MESH_FX_ID] = SHADER_SKINNED_MESH_FX;

	ID3DXEffect * SHADER_SKINNED_MESH_BOOK_FX;
	errors = 0;	
	D3DXCreateEffectFromFile(m_device, "effects/vblend2.fx", 0, 0, D3DXSHADER_DEBUG, 0, &SHADER_SKINNED_MESH_BOOK_FX, &errors);	
	if(errors)
		MessageBox(0, (char*) errors->GetBufferPointer(), 0, 0);
	m_effectResources[SHADER_SKINNED_MESH_BOOK_FX_ID] = SHADER_SKINNED_MESH_BOOK_FX;

	ID3DXEffect * SHADER_BILLBOARD_FX;
	errors = 0;	
	D3DXCreateEffectFromFile(m_device, "effects/billboard.fx", 0, 0, D3DXSHADER_DEBUG, 0, &SHADER_BILLBOARD_FX, &errors);
	if(errors)
		MessageBox(0, (char*) errors->GetBufferPointer(), 0, 0);;	
	m_effectResources[SHADER_BILLBOARD_FX_ID] = SHADER_BILLBOARD_FX;

	ID3DXEffect * SHADER_GRASS_FX;
	errors = 0;	
	D3DXCreateEffectFromFile(m_device, "effects/grass.fx", 0, 0, D3DXSHADER_DEBUG, 0, &SHADER_GRASS_FX, &errors);
	if(errors)
		MessageBox(0, (char*) errors->GetBufferPointer(), 0, 0);;	
	m_effectResources[SHADER_GRASS_FX_ID] = SHADER_GRASS_FX;

	ID3DXEffect * SHADER_FIRE_RING_FX;
	errors = 0;	
	D3DXCreateEffectFromFile(m_device, "effects/firering.fx", 0, 0, D3DXSHADER_DEBUG, 0, &SHADER_FIRE_RING_FX, &errors);	
	if(errors)
		MessageBox(0, (char*) errors->GetBufferPointer(), 0, 0);
	m_effectResources[SHADER_FIRE_RING_FX_ID] = SHADER_FIRE_RING_FX;

	ID3DXEffect * SHADER_SUPERNOVA_FX;
	errors = 0;	
	D3DXCreateEffectFromFile(m_device, "effects/supernova.fx", 0, 0, D3DXSHADER_DEBUG, 0, &SHADER_SUPERNOVA_FX, &errors);	
	if(errors)
		MessageBox(0, (char*) errors->GetBufferPointer(), 0, 0);
	m_effectResources[SHADER_SUPERNOVA_FX_ID] = SHADER_SUPERNOVA_FX;

	ID3DXEffect * SHADER_LIGHTS_PER_VERTEX_TEXTURES_NO_FOG;
	errors = 0;	
	D3DXCreateEffectFromFile(m_device, "effects/PerVertexLightingNoFog.fx", 0, 0, D3DXSHADER_DEBUG, 0, &SHADER_LIGHTS_PER_VERTEX_TEXTURES_NO_FOG, &errors);	
	if(errors)
		MessageBox(0, (char*) errors->GetBufferPointer(), 0, 0);
	m_effectResources[SHADER_LIGHTS_PER_VERTEX_TEXTURES_NO_FOG_ID] = SHADER_LIGHTS_PER_VERTEX_TEXTURES_NO_FOG;

	ID3DXEffect * SHADER_C3DE_SKINNED_MESH_FX;
	errors = 0;	
	D3DXCreateEffectFromFile(m_device, "effects/C3DESkinnedMeshNoLights.fx", 0, 0, D3DXSHADER_DEBUG, 0, &SHADER_C3DE_SKINNED_MESH_FX, &errors);	
	m_effectResources[SHADER_C3DE_SKINNED_MESH_FX_ID] = SHADER_C3DE_SKINNED_MESH_FX;

	ID3DXEffect * SHADER_C3DE_SKINNED_MESH_CLEAN_FX;
	errors = 0;	
	D3DXCreateEffectFromFile(m_device, "effects/C3DESkinnedMeshClean.fx", 0, 0, D3DXSHADER_DEBUG, 0, &SHADER_C3DE_SKINNED_MESH_CLEAN_FX, &errors);	
	m_effectResources[SHADER_C3DE_SKINNED_MESH_CLEAN_FX_ID] = SHADER_C3DE_SKINNED_MESH_CLEAN_FX;


	if(errors)
		MessageBox(0, (char*) errors->GetBufferPointer(), 0, 0);
	
	m_effects[SHADER_BOOK_LIGHTS_ID] = new BookLights(SHADER_BOOK_LIGHTS);
	m_effects[SHADER_LIGHTS_AND_TEXTURES_ID] = new LightsAndTextures(SHADER_LIGHTS_AND_TEXTURES);
	m_effects[SHADER_LIGHTS_TEXTURES_BLENDING_ID] = new LightsTexturesBlending(SHADER_LIGHTS_TEXTURES_BLENDING);
	m_effects[SHADER_ONLY_LIGHTS_ID] = new OnlyLights(SHADER_ONLY_LIGHTS);
	m_effects[SHADER_LIGHTS_PER_VERTEX_TEXTURES_ID] = new PerVertexLighting(SHADER_LIGHTS_PER_VERTEX_TEXTURES);
	m_effects[SHADER_LIGHTS_PER_PIXEL_TEXTURES_ID] = new PerPixelLighting(SHADER_LIGHTS_PER_PIXEL_TEXTURES);
	m_effects[SHADER_HARD_COLORS_ID] = new HardColors(SHADER_HARD_COLORS);
	m_effects[SHADER_SHADOW_FX_ID] = new ShadowFX(SHADER_SHADOW_FX);
	m_effects[SHADER_SKINNED_MESH_FX_ID] = new SkinnedMeshFX(SHADER_SKINNED_MESH_FX);
	m_effects[SHADER_SKINNED_MESH_BOOK_FX_ID] = new SkinnedMeshBookFX(SHADER_SKINNED_MESH_BOOK_FX);
	m_effects[SHADER_BILLBOARD_FX_ID] = new BillboardFX(SHADER_BILLBOARD_FX);
	m_effects[SHADER_GRASS_FX_ID] = new GrassFX(SHADER_GRASS_FX);
	m_effects[SHADER_FIRE_RING_FX_ID] = new FireRingFX(SHADER_FIRE_RING_FX);
	m_effects[SHADER_SUPERNOVA_FX_ID] = new FireRingFX(SHADER_SUPERNOVA_FX);
	m_effects[SHADER_LIGHTS_PER_VERTEX_TEXTURES_NO_FOG_ID] = new PerVertexLightingNoFog(SHADER_LIGHTS_PER_VERTEX_TEXTURES_NO_FOG);
	m_effects[SHADER_C3DE_SKINNED_MESH_FX_ID] = new C3DESkinnedMeshFX(SHADER_C3DE_SKINNED_MESH_FX);
	m_effects[SHADER_C3DE_SKINNED_MESH_CLEAN_FX_ID] = new C3DESkinnedMeshClean(SHADER_C3DE_SKINNED_MESH_CLEAN_FX);
}

ShadowFX * ShaderManager::GetDefaultShadowFX()
{
	ShadowFX *shadowFX = (ShadowFX *)m_effects[SHADER_SHADOW_FX_ID];
	return shadowFX;
}

ID3DXEffect * ShaderManager::GetEffectById(int id)
{
	ID3DXEffect* effect = m_effectResources[id];
	return effect; 
}

FX * ShaderManager::GetFXByID(int id)
{
	FX* effect = m_effects[id];
	return effect; 
}
