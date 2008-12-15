#ifndef EMPTY_FX_H
#define EMPTY_FX_H

#include "FX.h"

class EmptyFX : public FX
{
public:
	EmptyFX();
	~EmptyFX();

	void SetObjectMaterials(D3DXCOLOR ambientMaterial, D3DXCOLOR diffuseMaterial,
							D3DXCOLOR specularMaterial, float specularPower);
	void SetObjectTexture(IDirect3DTexture9 *texture);

	void SetWorldHandlers(D3DXVECTOR3 cameraPosition, D3DXMATRIX worldViewProjection);
	void SetLightHandlers(	D3DXCOLOR ambientLightColor, D3DXCOLOR diffuseLightColor,
							D3DXCOLOR specularLightColor, D3DXVECTOR3 lightVector);

	void SetTransformMatrix(D3DXMATRIX matrix);
	void ResetHandlers();
protected:
	D3DXHANDLE m_shaderObjectAmbientMaterial;//gAmbientMtrl
	D3DXHANDLE m_shaderObjectDiffuseMaterial;//gDiffuseMtrl
	D3DXHANDLE m_shaderObjectSpecularMaterial;//gSpecMtrl
	D3DXHANDLE m_shaderSpecularLightPower;//gSpecPower
	D3DXHANDLE m_shaderTransformMatrix;//
	D3DXHANDLE m_shaderLightPos;//
	D3DXHANDLE m_shaderAlpha;//
	D3DXHANDLE   m_hTex;
};

#endif