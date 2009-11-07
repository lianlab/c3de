#ifndef TEXTURE_ONLY_FX_H
#define TEXTURE_ONLY_FX_H

#include "FX.h"

class TextureOnlyFX : public FX
{
public:
	TextureOnlyFX(ID3DXEffect * effect);
	~TextureOnlyFX();

	void SetObjectMaterials(D3DXCOLOR ambientMaterial, D3DXCOLOR diffuseMaterial,
							D3DXCOLOR specularMaterial, float specularPower);
	void SetObjectTexture(IDirect3DTexture9 *texture);

	void SetLightHandlers(	D3DXCOLOR ambientLightColor, D3DXCOLOR diffuseLightColor,
							D3DXCOLOR specularLightColor, D3DXVECTOR3 lightVector);

	void SetWorldHandlers(D3DXVECTOR3 cameraPosition, D3DXMATRIX worldViewProjection);

	void SetAlpha(float alpha);

	void ResetHandlers();
protected:
	
	D3DXHANDLE   m_hTex;
};
#endif