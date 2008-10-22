#ifndef FX_H
#define FX_H

#include "d3dx9.h"
#include "D3DCommonDefs.h"
class FX
{
public:
	FX(ID3DXEffect * effect);
	~FX();

	ID3DXEffect * GetEffect(){return m_effect;}

	virtual void SetWorldHandlers(D3DXVECTOR3 cameraPosition, D3DXMATRIX worldViewProjection);
	virtual void SetLightHandlers(	D3DXCOLOR ambientLightColor, D3DXCOLOR diffuseLightColor,
							D3DXCOLOR specularLightColor, D3DXVECTOR3 lightVector);
protected:
	ID3DXEffect * m_effect;

	D3DXHANDLE m_shaderWorldMatrix;//gWorld R
	D3DXHANDLE m_shaderWorldInverseTransposeMatrix;//gWorldInverseTranspose R
	D3DXHANDLE m_shaderEyePosition;//gEyePosW R
	D3DXHANDLE m_shaderViewMatrix;//gWVP	R
	D3DXHANDLE m_shaderTechnique; //R

	D3DXHANDLE m_shaderAmbientLightMaterial;//gAmbientLigh
	D3DXHANDLE m_shaderDiffuseLightMaterial;//gDiffuseLight
	D3DXHANDLE m_shaderSpecularLightMaterial;//gSpecularLight
	D3DXHANDLE m_shaderLightPosition;//gLightPosW R
};
#endif