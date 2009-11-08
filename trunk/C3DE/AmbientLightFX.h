#ifndef AMBIENT_LIGHT_FX_H
#define AMBIENT_LIGHT_FX_H

#include "FX.h"

class AmbientLightFX : public FX
{
public:
	AmbientLightFX(ID3DXEffect * effect);
	~AmbientLightFX();

	void SetObjectMaterials(D3DXCOLOR ambientMaterial, D3DXCOLOR diffuseMaterial,
							D3DXCOLOR specularMaterial, float specularPower);
	void SetObjectTexture(IDirect3DTexture9 *texture);

	void SetAlpha(float alpha);

	void ResetHandlers();
protected:
	D3DXHANDLE m_shaderObjectAmbientMaterial;//gAmbientMtrl
	//D3DXHANDLE m_shaderObjectDiffuseMaterial;//gDiffuseMtrl
	//D3DXHANDLE m_shaderObjectSpecularMaterial;//gSpecMtrl
	//D3DXHANDLE m_shaderSpecularLightPower;//gSpecPower
	//D3DXHANDLE m_shaderAlpha;//gSpecPower
	D3DXHANDLE   m_hTex;
};
#endif