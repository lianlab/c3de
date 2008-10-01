#include "ShaderManager.h"
#include "DebugMemory.h"
#include "D3DCommonDefs.h"

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
	HR(D3DXCreateEffectFromFile(m_device, "effects/lights.fx", 0, 0, D3DXSHADER_DEBUG, 0, &SHADER_BOOK_LIGHTS, &errors));	
	m_effectResources[SHADER_BOOK_LIGHTS_ID] = SHADER_BOOK_LIGHTS;

	ID3DXEffect * SHADER_LIGHTS_AND_TEXTURES;
	errors = 0;	
	HR(D3DXCreateEffectFromFile(m_device, "effects/lightsAndTextures.fx", 0, 0, D3DXSHADER_DEBUG, 0, &SHADER_LIGHTS_AND_TEXTURES, &errors));	
	m_effectResources[SHADER_LIGHTS_AND_TEXTURES_ID] = SHADER_LIGHTS_AND_TEXTURES;

	ID3DXEffect * SHADER_ONLY_LIGHTS;
	errors = 0;	
	HR(D3DXCreateEffectFromFile(m_device, "effects/onlyLights.fx", 0, 0, D3DXSHADER_DEBUG, 0, &SHADER_ONLY_LIGHTS, &errors));	
	m_effectResources[SHADER_ONLY_LIGHTS_ID] = SHADER_ONLY_LIGHTS;
	
}

ID3DXEffect * ShaderManager::GetEffectById(int id)
{
	ID3DXEffect* effect = m_effectResources[id];
	return effect; 
}
