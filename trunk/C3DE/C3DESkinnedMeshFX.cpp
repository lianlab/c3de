#include "C3DESkinnedMeshFX.h"
#include "DebugMemory.h"


C3DESkinnedMeshFX::C3DESkinnedMeshFX(ID3DXEffect *effect):
FX(effect)
{
	
	
	m_shaderObjectAmbientMaterial = m_effect->GetParameterByName(0, "gAmbientMtrl");
	m_shaderObjectDiffuseMaterial = m_effect->GetParameterByName(0, "gDiffuseMtrl");
	m_shaderObjectSpecularMaterial = m_effect->GetParameterByName(0, "gSpecularMtrl");
	m_shaderSpecularLightPower = m_effect->GetParameterByName(0, "gSpecularPower");
	m_shaderAlpha = m_effect->GetParameterByName(0, "gAlpha");
	mhFinalXForms = m_effect->GetParameterByName(0, "gFinalXForms");

	mhToRoot = m_effect->GetParameterByName(0, "gToRoot");
	mhCurrentFrameToRoot = m_effect->GetParameterByName(0, "gCurrentFrameToRoot");

	m_shaderHack = m_effect->GetParameterByName(0, "gHack");
	
	m_hTex = m_effect->GetParameterByName(0, "gTex");

	m_hack  = 0.0f;

	dir = 1.0f;
	
}

C3DESkinnedMeshFX::~C3DESkinnedMeshFX()
{

}

void C3DESkinnedMeshFX::ResetHandlers()
{
	D3DXMATRIX T;
	D3DXMatrixIdentity(&T);
	SetTransformMatrix(T);
}

void C3DESkinnedMeshFX::SetObjectMaterials(D3DXCOLOR ambientMaterial, D3DXCOLOR diffuseMaterial,
							D3DXCOLOR specularMaterial, float specularPower)
{

	
	HR(m_effect->SetValue(m_shaderObjectAmbientMaterial, &ambientMaterial,sizeof(D3DXCOLOR)));
	HR(m_effect->SetValue(m_shaderObjectDiffuseMaterial, &diffuseMaterial, sizeof(D3DXCOLOR)));
	HR(m_effect->SetValue(m_shaderObjectSpecularMaterial, &specularMaterial, sizeof(D3DXCOLOR)));
	HR(m_effect->SetFloat(m_shaderSpecularLightPower, specularPower));
	
}

void C3DESkinnedMeshFX::SetObjectTexture(IDirect3DTexture9 *texture)
{
	HR(m_effect->SetTexture(m_hTex, texture));
}

void C3DESkinnedMeshFX::SetAlpha(float alpha)
{
	HR(m_effect->SetFloat(m_shaderAlpha, alpha));
}

void C3DESkinnedMeshFX::SetBoneMatrix(const D3DXMATRIX *a_bones, UINT a_numBones)
{

	HR(m_effect->SetMatrixArray(mhFinalXForms, a_bones, a_numBones));
}


void C3DESkinnedMeshFX::SetRootMatrices(const D3DXMATRIX *a_toRoot, UINT totalToRoots)
{
	HR(m_effect->SetMatrixArray(mhToRoot, a_toRoot, totalToRoots));
	//HR(m_effect->SetMatrixArray(mhCurrentFrameToRoot, currentFrameToRoots, totalCurrentFrameToRoots));
}

void C3DESkinnedMeshFX::SetFrameRootMatrices(const D3DXMATRIX * currentFrameToRoots, UINT totalCurrentFrameToRoots)
{
	//HR(m_effect->SetMatrixArray(mhToRoot, a_toRoot, totalToRoots));
	HR(m_effect->SetMatrixArray(mhCurrentFrameToRoot, currentFrameToRoots, totalCurrentFrameToRoots));
}

void C3DESkinnedMeshFX::SetWorldHandlers(D3DXVECTOR3 cameraPosition, D3DXMATRIX worldViewProjection)
{
	if(m_hack > 1.0f || m_hack < 0.0f)
	{
		dir = 0 - dir;
	}

	m_hack += 0.01f * dir;
	D3DXMATRIX W;		
	D3DXMatrixIdentity(&W);			

	D3DXMATRIX WIT;
	D3DXMatrixInverse(&WIT, 0, &W);
	D3DXMatrixTranspose(&WIT, &WIT);														
	
	
	HR(m_effect->SetMatrix(m_shaderWorldMatrix, &W));	
	HR(m_effect->SetMatrix(m_shaderViewMatrix, &worldViewProjection));	
	HR(m_effect->SetMatrix(m_shaderWorldInverseTransposeMatrix, &WIT));												
	HR(m_effect->SetValue(m_shaderEyePosition, cameraPosition, sizeof(D3DXVECTOR3)));
	//HR(m_effect->SetFloat(m_shaderHack, m_hack));
	//HR(m_effect->SetFloat(m_shaderAlpha, m_hack));
}