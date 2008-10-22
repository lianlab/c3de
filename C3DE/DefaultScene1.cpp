#include "DefaultScene1.h"
#include "FXManager.h"
#include "DebugMemory.h"

DefaultScene1::DefaultScene1():D3DScene()
{

	
	AmbientLight * t_ambientLight = new AmbientLight();
	t_ambientLight->SetColor(0.4f*D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	DiffuseLight * t_diffuseLight = new DiffuseLight();
	m_diffuseLight->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	SpecularLight *t_specularLight = new SpecularLight();
	t_specularLight->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	D3DXVECTOR3 *t_lightAttenuation = new D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	PointLight *t_pointLight = new PointLight(16.0f);	

	SetAmbientLight(t_ambientLight);
	SetDiffuseLight(t_diffuseLight);
	SetSpecularLight(t_specularLight);
	SetPointLight(t_pointLight);
	SetLightAttenuation(t_lightAttenuation);
	
	

}

DefaultScene1::~DefaultScene1()
{

}

