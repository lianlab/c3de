#ifndef SKINNED_MESH_FX_H
#define SKINNED_MESH_FX_H

#include "FX.h"



class SkinnedMeshFX : public FX
{
public:
	SkinnedMeshFX(ID3DXEffect * effect);
	~SkinnedMeshFX();

	void SetObjectMaterials(D3DXCOLOR ambientMaterial, D3DXCOLOR diffuseMaterial,
							D3DXCOLOR specularMaterial, float specularPower);
	void SetObjectTexture(IDirect3DTexture9 *texture);

	void SetWorldHandlers(D3DXVECTOR3 cameraPosition, D3DXMATRIX worldViewProjection);

	void SetAlpha(float alpha);

	void ResetHandlers();
protected:
	D3DXHANDLE m_shaderObjectAmbientMaterial;//gAmbientMtrl
	D3DXHANDLE m_shaderObjectDiffuseMaterial;//gDiffuseMtrl
	D3DXHANDLE m_shaderObjectSpecularMaterial;//gSpecMtrl
	D3DXHANDLE m_shaderSpecularLightPower;//gSpecPower
	D3DXHANDLE m_shaderAlpha;//gSpecPower
	D3DXHANDLE m_shaderHack;//gSpecPower
	D3DXHANDLE   m_hTex;

	float m_hack;
	float dir;
};
#endif