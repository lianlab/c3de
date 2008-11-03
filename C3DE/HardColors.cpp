#include "HardColors.h"


HardColors::HardColors(ID3DXEffect *effect):
FX(effect)
{
	
	
	m_shaderObjectAmbientMaterial = m_effect->GetParameterByName(0, "gAmbientMtrl");
	m_shaderObjectDiffuseMaterial = m_effect->GetParameterByName(0, "gDiffuseMtrl");
	m_shaderObjectSpecularMaterial = m_effect->GetParameterByName(0, "gSpecMtrl");
	m_shaderSpecularLightPower = m_effect->GetParameterByName(0, "gSpecPower");
	m_hTex = m_effect->GetParameterByName(0, "gTex");
	m_shaderTransformMatrix = m_effect->GetParameterByName(0, "gTransformMatrix");

	D3DXMATRIX M;
	
	D3DXMatrixIdentity(&M);		
	HR(m_effect->SetMatrix(m_shaderTransformMatrix, &M));	

	m_shaderLightPosition = m_effect->GetParameterByName(0, "gLightPosW");

	m_shaderSpecularLightMaterial = m_effect->GetParameterByName(0, "gSpecLight");

	m_shaderAlpha = m_effect->GetParameterByName(0, "gAlpha");

}

HardColors::~HardColors()
{

}

void HardColors::ResetHandlers()
{
	D3DXMATRIX T;
	D3DXMatrixIdentity(&T);
	SetTransformMatrix(T);
}

void HardColors::SetAlpha(float alpha)
{
	HR(m_effect->SetFloat(m_shaderAlpha, alpha));
}

void HardColors::SetObjectMaterials(D3DXCOLOR ambientMaterial, D3DXCOLOR diffuseMaterial,
							D3DXCOLOR specularMaterial, float specularPower)
{

	D3DXVECTOR3 t = D3DXVECTOR3(0.0f, 2.0f, 0.0f);
	HR(m_effect->SetValue(m_shaderLightPosition, &t, sizeof(D3DXVECTOR3)));
	
	HR(m_effect->SetValue(m_shaderObjectAmbientMaterial, &ambientMaterial,sizeof(D3DXCOLOR)));
	HR(m_effect->SetValue(m_shaderObjectDiffuseMaterial, &diffuseMaterial, sizeof(D3DXCOLOR)));
	HR(m_effect->SetValue(m_shaderObjectSpecularMaterial, &specularMaterial, sizeof(D3DXCOLOR)));
	HR(m_effect->SetFloat(m_shaderSpecularLightPower, specularPower));
	
}

void HardColors::SetObjectTexture(IDirect3DTexture9 *texture)
{
	HR(m_effect->SetTexture(m_hTex, texture));
}