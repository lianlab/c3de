#include "SkinnedMeshBookFX.h"


SkinnedMeshBookFX::SkinnedMeshBookFX(ID3DXEffect *effect):
FX(effect)
{
	
	
	m_shaderObjectAmbientMaterial = m_effect->GetParameterByName(0, "gAmbientMtrl");
	m_shaderObjectDiffuseMaterial = m_effect->GetParameterByName(0, "gDiffuseMtrl");
	m_shaderObjectSpecularMaterial = m_effect->GetParameterByName(0, "gSpecularMtrl");
	m_shaderSpecularLightPower = m_effect->GetParameterByName(0, "gSpecularPower");
	m_shaderAlpha = m_effect->GetParameterByName(0, "gAlpha");

	mhTech = m_effect->GetParameterByName(0, "gAmbientMtrl");
	mhWVP = m_effect->GetParameterByName(0, "gWVP");
	mhWorldInvTrans = m_effect->GetParameterByName(0, "gWorldInvTrans");
	mhFinalXForms = m_effect->GetParameterByName(0, "gFinalXForms");
	mhEyePos = m_effect->GetParameterByName(0, "gEyePosW");
	mhWorld = m_effect->GetParameterByName(0, "gWorld");
	mhTex = m_effect->GetParameterByName(0, "gTex");
	//mhMtrl = m_effect->GetParameterByName(0, "gAmbientMtrl");
	//mhLight = m_effect->GetParameterByName(0, "gAmbientMtrl");


	

	
	
	m_hTex = m_effect->GetParameterByName(0, "gTex");

	
	dir = 1.0f;
	
}

SkinnedMeshBookFX::~SkinnedMeshBookFX()
{

}

void SkinnedMeshBookFX::ResetHandlers()
{
	D3DXMATRIX T;
	D3DXMatrixIdentity(&T);
	SetTransformMatrix(T);
}

void SkinnedMeshBookFX::SetObjectMaterials(D3DXCOLOR ambientMaterial, D3DXCOLOR diffuseMaterial,
							D3DXCOLOR specularMaterial, float specularPower)
{

	
	HR(m_effect->SetValue(m_shaderObjectAmbientMaterial, &ambientMaterial,sizeof(D3DXCOLOR)));
	HR(m_effect->SetValue(m_shaderObjectDiffuseMaterial, &diffuseMaterial, sizeof(D3DXCOLOR)));
	HR(m_effect->SetValue(m_shaderObjectSpecularMaterial, &specularMaterial, sizeof(D3DXCOLOR)));
	HR(m_effect->SetFloat(m_shaderSpecularLightPower, specularPower));
	
}

void SkinnedMeshBookFX::SetObjectTexture(IDirect3DTexture9 *texture)
{
	HR(m_effect->SetTexture(m_hTex, texture));
	HR(m_effect->SetTexture(mhTex, texture));
}

void SkinnedMeshBookFX::SetAlpha(float alpha)
{
	HR(m_effect->SetFloat(m_shaderAlpha, alpha));
}

void SkinnedMeshBookFX::SetBoneMatrix(const D3DXMATRIX *a_bones, UINT a_numBones)
{

	HR(m_effect->SetMatrixArray(mhFinalXForms, a_bones, a_numBones));
}

void SkinnedMeshBookFX::SetWorldHandlers(D3DXVECTOR3 cameraPosition, D3DXMATRIX worldViewProjection)
{
	
	D3DXMATRIX W;		
	D3DXMatrixIdentity(&W);			

	D3DXMATRIX WIT;
	D3DXMatrixInverse(&WIT, 0, &W);
	D3DXMatrixTranspose(&WIT, &WIT);														
	
	
	HR(m_effect->SetMatrix(m_shaderWorldMatrix, &W));	
	HR(m_effect->SetMatrix(m_shaderViewMatrix, &worldViewProjection));	
	HR(m_effect->SetMatrix(m_shaderWorldInverseTransposeMatrix, &WIT));												
	HR(m_effect->SetValue(m_shaderEyePosition, cameraPosition, sizeof(D3DXVECTOR3)));
	











	HR(m_effect->SetValue(mhEyePos, &cameraPosition, sizeof(D3DXVECTOR3)));
	//HR(m_effect->SetMatrixArray(mhFinalXForms, a_mesh->getFinalXFormArray(), a_mesh->numBones()));			
	HR(m_effect->SetMatrix(mhWVP, &(worldViewProjection)));		
	HR(m_effect->SetMatrix(mhWorld, &WIT));


	
	

}