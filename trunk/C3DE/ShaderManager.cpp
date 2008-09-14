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

	ID3DXEffect * SHADER_BOOK_FIRST;

	ID3DXBuffer *errors = 0;
	
	HR(D3DXCreateEffectFromFile(m_device, "effects/transform.fx", 0, 0, D3DXSHADER_DEBUG, 0, &SHADER_BOOK_FIRST, &errors));
	
	m_effectResources[0] = SHADER_BOOK_FIRST;
	
}

ID3DXEffect * ShaderManager::GetEffectById(int id)
{
	ID3DXEffect* effect = m_effectResources[id];
	return effect; 
}
