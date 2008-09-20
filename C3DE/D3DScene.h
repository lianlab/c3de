#ifndef D3DSCENE_H
#define D3DSCENE_H

#include "Scene.h"

class D3DScene : public Scene
{
public:
	D3DScene();
	~D3DScene();

	void SetEffect(ID3DXEffect * effect){m_effect = effect;SetEffectHandles();}
	ID3DXEffect * GetEffect(){return m_effect;}

	virtual void SetEffectHandles();

	virtual D3DXHANDLE GetShaderViewMatrix();
	virtual D3DXHANDLE GetShaderTechnique();
	virtual D3DXHANDLE GetShaderWorldMatrix();
	virtual D3DXHANDLE GetShaderWorldInverseTransposeMatrix();
	virtual D3DXHANDLE GetShaderEyePosition();
	virtual D3DXHANDLE GetShaderAmbientLightMaterial();
	virtual D3DXHANDLE GetShaderDiffuseLightMaterial();
	virtual D3DXHANDLE GetShaderSpecularLightMaterial();
	virtual D3DXHANDLE GetShaderLightPosition();
	virtual D3DXHANDLE GetShaderLightDirection();
	virtual D3DXHANDLE GetShaderLightAttenuation();
	virtual D3DXHANDLE GetShaderSpotLightPower();

	virtual D3DXHANDLE GetShaderObjectAmbientMaterial();
	virtual D3DXHANDLE GetShaderObjectDiffuseMaterial();
	virtual D3DXHANDLE GetShaderObjectSpecularMaterial();
	virtual D3DXHANDLE GetShaderSpecularLightPower();

	D3DXVECTOR3 * GetLightAttenuation(){return m_lightAttenuation;}
	void SetLightAttenuation(D3DXVECTOR3 *attenuation){m_lightAttenuation = attenuation;}

protected:
	ID3DXEffect *m_effect;

	D3DXHANDLE m_shaderWorldMatrix;//gWorld
	D3DXHANDLE m_shaderWorldInverseTransposeMatrix;//gWorldInverseTranspose
	D3DXHANDLE m_shaderEyePosition;//gEyePosW
	D3DXHANDLE m_shaderAmbientLightMaterial;//gAmbientLigh
	D3DXHANDLE m_shaderDiffuseLightMaterial;//gDiffuseLight
	D3DXHANDLE m_shaderSpecularLightMaterial;//gSpecularLight
	D3DXHANDLE m_shaderLightPosition;//gLightPosW
	D3DXHANDLE m_shaderLightDirection;//gLightDirW
	D3DXHANDLE m_shaderLightAttenuation;//gAttenuation012
	D3DXHANDLE m_shaderSpotLightPower;//gSpotPower

	D3DXHANDLE m_shaderObjectAmbientMaterial;//gAmbientMtrl
	D3DXHANDLE m_shaderObjectDiffuseMaterial;//gDiffuseMtrl
	D3DXHANDLE m_shaderObjectSpecularMaterial;//gSpecMtrl
	D3DXHANDLE m_shaderSpecularLightPower;//gSpecPower

	D3DXHANDLE m_shaderViewMatrix;//gWVP	
	D3DXHANDLE m_shaderTechnique;

	D3DXVECTOR3 *m_lightAttenuation;
};
#endif