#include "ShadowFX.h"
#include "DebugMemory.h"


ShadowFX::ShadowFX(ID3DXEffect *effect):
FX(effect)
{
	
	
	m_shaderObjectAmbientMaterial = m_effect->GetParameterByName(0, "gAmbientMtrl");
	m_shaderObjectDiffuseMaterial = m_effect->GetParameterByName(0, "gDiffuseMtrl");
	m_shaderObjectSpecularMaterial = m_effect->GetParameterByName(0, "gSpecularMtrl");
	m_shaderSpecularLightPower = m_effect->GetParameterByName(0, "gSpecularPower");
	
	m_hTex = m_effect->GetParameterByName(0, "gTex");

	
}

ShadowFX::~ShadowFX()
{

}

void ShadowFX::ResetHandlers()
{
	D3DXMATRIX T;
	D3DXMatrixIdentity(&T);
	SetTransformMatrix(T);
}

void ShadowFX::SetObjectMaterials(D3DXCOLOR ambientMaterial, D3DXCOLOR diffuseMaterial,
							D3DXCOLOR specularMaterial, float specularPower)
{

	
	HR(m_effect->SetValue(m_shaderObjectAmbientMaterial, &ambientMaterial,sizeof(D3DXCOLOR)));
	HR(m_effect->SetValue(m_shaderObjectDiffuseMaterial, &diffuseMaterial, sizeof(D3DXCOLOR)));
	HR(m_effect->SetValue(m_shaderObjectSpecularMaterial, &specularMaterial, sizeof(D3DXCOLOR)));
	HR(m_effect->SetFloat(m_shaderSpecularLightPower, specularPower));
	
}

void ShadowFX::SetObjectTexture(IDirect3DTexture9 *texture)
{
	HR(m_effect->SetTexture(m_hTex, texture));
}