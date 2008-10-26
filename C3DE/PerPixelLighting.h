#ifndef PER_PIXEL_LIGHTING_H
#define PER_PIXEL_LIGHTING_H

#include "FX.h"

class PerPixelLighting : public FX
{
public:
	PerPixelLighting(ID3DXEffect * effect);
	~PerPixelLighting();

	void SetObjectMaterials(D3DXCOLOR ambientMaterial, D3DXCOLOR diffuseMaterial,
							D3DXCOLOR specularMaterial, float specularPower);
	void SetObjectTexture(IDirect3DTexture9 *texture);

	void SetAlpha(float alpha);
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