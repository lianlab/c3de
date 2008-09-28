#include "DefaultScene1.h"

DefaultScene1::DefaultScene1():D3DScene()
{
	m_ambientLight = new AmbientLight();
	m_ambientLight->SetColor(0.4f*D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	m_diffuseLight = new DiffuseLight();
	m_diffuseLight->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	m_specularLight = new SpecularLight();
	m_specularLight->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	m_lightAttenuation = new D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	m_pointLight = new PointLight(16.0f);
		

	

}

DefaultScene1::~DefaultScene1()
{

}

void DefaultScene1::Initialize()
{
	
	ID3DXEffect * effect = this->GetEffect();

	HR(effect->SetValue(this->GetShaderAmbientLightMaterial(), &this->GetAmbientLight()->GetColor(), sizeof(D3DXCOLOR)));
	HR(effect->SetValue(this->GetShaderDiffuseLightMaterial(), &this->GetDiffuseLight()->GetColor(), sizeof(D3DXCOLOR)));		
	HR(effect->SetValue(this->GetShaderSpecularLightMaterial(), &this->GetSpecularLight()->GetColor(), sizeof(D3DXCOLOR)));		
	HR(effect->SetValue(this->GetShaderLightAttenuation(), this->GetLightAttenuation(), sizeof(D3DXVECTOR3)));
	HR(effect->SetFloat(this->GetShaderSpotLightPower(), this->GetPointLight()->GetPower()));	
}