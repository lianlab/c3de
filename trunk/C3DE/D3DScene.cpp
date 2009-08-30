#include "D3DScene.h"
#include "FXManager.h"
#include "DebugMemory.h"

D3DScene::D3DScene()
{
	m_lightAttenuation = new D3DXVECTOR3(1.0f, 0.0f, 0.0f);
}

D3DScene::~D3DScene()
{
	if(m_lightAttenuation)
	{
		delete m_lightAttenuation;
		m_lightAttenuation = NULL;
	}
}



void D3DScene::SetLightAttenuation(D3DXVECTOR3 *attenuation)
{
	if(m_lightAttenuation)
	{
		delete m_lightAttenuation;
		m_lightAttenuation = NULL;
	}

	m_lightAttenuation = attenuation;
}

void D3DScene::Initialize()
{
	FXManager::GetInstance()->SetSceneEffects(this);
	
}


