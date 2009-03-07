#ifndef GRASS_FX_H
#define GRASS_FX_H

#include "FX.h"

class GrassFX : public FX
{
public:
	GrassFX(ID3DXEffect * effect);
	~GrassFX();

	void SetObjectMaterials(D3DXCOLOR ambientMaterial, D3DXCOLOR diffuseMaterial,
							D3DXCOLOR specularMaterial, float specularPower);
	void SetObjectTexture(IDirect3DTexture9 *texture);

	void SetAlpha(float alpha);

	void SetTime(float a_time);

	void ResetHandlers();
protected:
	D3DXHANDLE m_shaderObjectAmbientMaterial;//gAmbientMtrl
	D3DXHANDLE m_shaderObjectDiffuseMaterial;//gDiffuseMtrl
	D3DXHANDLE m_shaderObjectSpecularMaterial;//gSpecMtrl
	D3DXHANDLE m_shaderSpecularLightPower;//gSpecPower
	D3DXHANDLE m_shaderAlpha;//gSpecPower
	D3DXHANDLE m_hTex;
	D3DXHANDLE m_shaderGrassTime;
	D3DXHANDLE m_shaderGrassDirToSunW;
};
#endif