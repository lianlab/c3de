#include "GrassFX.h"
#include "DebugMemory.h"


GrassFX::GrassFX(ID3DXEffect *effect):
FX(effect)
{
	//mhGrassTech     = mGrassFX->GetTechniqueByName("GrassTech");
	//mhGrassViewProj = mGrassFX->GetParameterByName(0, "gViewProj");
	//mhGrassTex      = mGrassFX->GetParameterByName(0, "gTex");
	m_shaderGrassTime     = m_effect->GetParameterByName(0, "gTime");
	//mhGrassEyePosW  = mGrassFX->GetParameterByName(0, "gEyePosW");
	m_shaderGrassDirToSunW= m_effect->GetParameterByName(0, "gDirToSunW");

	//HR(mGrassFX->SetTechnique(mhGrassTech));

	//HR(mGrassFX->SetTexture(mhGrassTex, mGrassTex));
	






















	
	m_shaderObjectAmbientMaterial = m_effect->GetParameterByName(0, "gAmbientMtrl");
	m_shaderObjectDiffuseMaterial = m_effect->GetParameterByName(0, "gDiffuseMtrl");
	m_shaderObjectSpecularMaterial = m_effect->GetParameterByName(0, "gSpecularMtrl");
	m_shaderSpecularLightPower = m_effect->GetParameterByName(0, "gSpecularPower");
	m_shaderAlpha = m_effect->GetParameterByName(0, "gAlpha");
	
	m_hTex = m_effect->GetParameterByName(0, "gTex");

	//HR(m_effect->SetTexture(mhGrassTex, mGrassTex));

	
}

void GrassFX::SetTime(float a_time)
{
	HR(m_effect->SetValue(m_shaderGrassTime, &a_time,sizeof(float)));
}

GrassFX::~GrassFX()
{

}



void GrassFX::ResetHandlers()
{
	D3DXMATRIX T;
	D3DXMatrixIdentity(&T);
	SetTransformMatrix(T);
}

void GrassFX::SetObjectMaterials(D3DXCOLOR ambientMaterial, D3DXCOLOR diffuseMaterial,
							D3DXCOLOR specularMaterial, float specularPower)
{

	
	HR(m_effect->SetValue(m_shaderObjectAmbientMaterial, &ambientMaterial,sizeof(D3DXCOLOR)));
	HR(m_effect->SetValue(m_shaderObjectDiffuseMaterial, &diffuseMaterial, sizeof(D3DXCOLOR)));
	HR(m_effect->SetValue(m_shaderObjectSpecularMaterial, &specularMaterial, sizeof(D3DXCOLOR)));
	HR(m_effect->SetFloat(m_shaderSpecularLightPower, specularPower));
	
}

void GrassFX::SetObjectTexture(IDirect3DTexture9 *texture)
{
	if(texture)
	{
		HR(m_effect->SetTexture(m_hTex, texture));

	}
	
}

void GrassFX::SetAlpha(float alpha)
{
	HR(m_effect->SetFloat(m_shaderAlpha, alpha));
}