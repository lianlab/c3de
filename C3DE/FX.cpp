#include "FX.h"
#include "DebugMemory.h"

FX::FX(ID3DXEffect * effect)
{
	m_effect = effect;

	m_shaderTechnique = m_effect->GetTechniqueByName("ShaderTech");	
	m_shaderViewMatrix  = m_effect->GetParameterByName(0, "gWVP");	
	m_shaderEyePosition= m_effect->GetParameterByName(0, "gEyePosW");
	m_shaderWorldMatrix = m_effect->GetParameterByName(0, "gWorld");
	m_shaderWorldInverseTransposeMatrix = m_effect->GetParameterByName(0, "gWorldInvTrans");

	m_shaderAmbientLightMaterial = m_effect->GetParameterByName(0, "gAmbientLight");
	m_shaderDiffuseLightMaterial = m_effect->GetParameterByName(0, "gDiffuseLight");
	m_shaderSpecularLightMaterial = m_effect->GetParameterByName(0, "gSpecularLight");
	
	m_shaderLightPosition = m_effect->GetParameterByName(0, "gLightVecW");
	
	m_shaderTransformMatrix = m_effect->GetParameterByName(0, "gTransformMatrix");
	
	D3DXMATRIX T;
	D3DXMatrixIdentity(&T);
	SetTransformMatrix(T);
}

FX::~FX()
{


}

void FX::SetTransformMatrix(D3DXMATRIX matrix)
{
	if(m_shaderTransformMatrix)
	{	
		HR(m_effect->SetValue(m_shaderTransformMatrix, &matrix, sizeof(D3DXMATRIX)));
	}

}

void FX::SetLightHandlers(	D3DXCOLOR ambientLightColor, D3DXCOLOR diffuseLightColor,
							D3DXCOLOR specularLightColor, D3DXVECTOR3 lightVector)
{
	if(m_shaderLightPosition)
	{
		HR(m_effect->SetValue(m_shaderLightPosition, &lightVector, sizeof(D3DXVECTOR3)));	
	}

	if(m_shaderAmbientLightMaterial)
	{
		HR(m_effect->SetValue(m_shaderAmbientLightMaterial, &ambientLightColor, sizeof(D3DXCOLOR)));
	}

	if(m_shaderDiffuseLightMaterial)
	{
		HR(m_effect->SetValue(m_shaderDiffuseLightMaterial, &diffuseLightColor, sizeof(D3DXCOLOR)));		
	}

	if(m_shaderSpecularLightMaterial)
	{
		HR(m_effect->SetValue(m_shaderSpecularLightMaterial, &specularLightColor, sizeof(D3DXCOLOR)));
	}
	
	
	
	
	
}

	
void FX::SetWorldHandlers(D3DXVECTOR3 cameraPosition, D3DXMATRIX worldViewProjection)
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
	
}