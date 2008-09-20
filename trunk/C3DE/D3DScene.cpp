#include "D3DScene.h"

D3DScene::D3DScene()
{

	m_lightAttenuation = new D3DXVECTOR3(1.0f, 0.0f, 0.0f);
}

D3DScene::~D3DScene()
{

}

void D3DScene::SetEffectHandles()
{ 
	if(m_effect)
	{
		m_shaderTechnique = m_effect->GetTechniqueByName("LightsTech");
		//m_shaderTechnique = m_effect->GetTechniqueByName("LightsTech");
		m_shaderViewMatrix  = m_effect->GetParameterByName(0, "gWVP");
		//m_shaderUpdateTime = m_effect->GetParameterByName(0, "gTime");

		m_shaderEyePosition= m_effect->GetParameterByName(0, "gEyePosW");
		m_shaderAmbientLightMaterial = m_effect->GetParameterByName(0, "gAmbientLight");
		m_shaderDiffuseLightMaterial = m_effect->GetParameterByName(0, "gDiffuseLight");
		m_shaderSpecularLightMaterial = m_effect->GetParameterByName(0, "gSpecLight");
		m_shaderLightPosition = m_effect->GetParameterByName(0, "gLightPosW");
		m_shaderLightDirection = m_effect->GetParameterByName(0, "gLightDirW");
		m_shaderLightAttenuation = m_effect->GetParameterByName(0, "gAttenuation012");
		m_shaderSpotLightPower = m_effect->GetParameterByName(0, "gSpotPower");

		m_shaderObjectAmbientMaterial = m_effect->GetParameterByName(0, "gAmbientMtrl");
		m_shaderObjectDiffuseMaterial = m_effect->GetParameterByName(0, "gDiffuseMtrl");
		m_shaderObjectSpecularMaterial = m_effect->GetParameterByName(0, "gSpecMtrl");
		m_shaderSpecularLightPower = m_effect->GetParameterByName(0, "gSpecPower");

		m_shaderWorldMatrix = m_effect->GetParameterByName(0, "gWorld");
		m_shaderWorldInverseTransposeMatrix = m_effect->GetParameterByName(0, "gWorldInvTrans");
	}	
}

	


D3DXHANDLE D3DScene::GetShaderWorldInverseTransposeMatrix()
{
	return m_shaderWorldInverseTransposeMatrix;
}

D3DXHANDLE D3DScene::GetShaderWorldMatrix()
{
	return m_shaderWorldMatrix;
}

D3DXHANDLE D3DScene::GetShaderEyePosition()
{
	return m_shaderEyePosition;
}

D3DXHANDLE D3DScene::GetShaderAmbientLightMaterial()
{
	return m_shaderAmbientLightMaterial;
}

D3DXHANDLE D3DScene::GetShaderDiffuseLightMaterial()
{
	return m_shaderDiffuseLightMaterial;
}

D3DXHANDLE D3DScene::GetShaderSpecularLightMaterial()
{
	return m_shaderSpecularLightMaterial;
}

D3DXHANDLE D3DScene::GetShaderLightPosition()
{
	return m_shaderLightPosition;
}

D3DXHANDLE D3DScene::GetShaderLightDirection()
{
	return m_shaderLightDirection;
}

D3DXHANDLE D3DScene::GetShaderLightAttenuation()
{
	return m_shaderLightAttenuation;
}

D3DXHANDLE D3DScene::GetShaderSpotLightPower()
{
	return m_shaderSpotLightPower;
}

D3DXHANDLE D3DScene::GetShaderObjectAmbientMaterial()
{
	return m_shaderObjectAmbientMaterial;
}

D3DXHANDLE D3DScene::GetShaderObjectDiffuseMaterial()
{
	return m_shaderObjectDiffuseMaterial;
}

D3DXHANDLE D3DScene::GetShaderObjectSpecularMaterial()
{
	return m_shaderObjectSpecularMaterial;
}

D3DXHANDLE D3DScene::GetShaderSpecularLightPower()
{
	return m_shaderSpecularLightPower;
}

D3DXHANDLE D3DScene::GetShaderViewMatrix()
{
	return m_shaderViewMatrix;
}

D3DXHANDLE D3DScene::GetShaderTechnique()
{
	return m_shaderTechnique;
}

