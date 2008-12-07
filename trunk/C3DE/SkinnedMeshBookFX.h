#ifndef SKINNED_MESH_BOOK_FX_H
#define SKINNED_MESH_BOOK_FX_H

#include "FX.h"



class SkinnedMeshBookFX : public FX
{
public:
	SkinnedMeshBookFX(ID3DXEffect * effect);
	~SkinnedMeshBookFX();

	void SetObjectMaterials(D3DXCOLOR ambientMaterial, D3DXCOLOR diffuseMaterial,
							D3DXCOLOR specularMaterial, float specularPower);
	void SetObjectTexture(IDirect3DTexture9 *texture);

	void SetBoneMatrix(const D3DXMATRIX *a_bones, UINT a_numBones);


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

	
	D3DXHANDLE   mhTech;
	D3DXHANDLE   mhWVP;
	D3DXHANDLE   mhWorldInvTrans;
	D3DXHANDLE   mhFinalXForms;
	D3DXHANDLE   mhEyePos;
	D3DXHANDLE   mhWorld;
	D3DXHANDLE   mhTex;
	D3DXHANDLE   mhMtrl;
	D3DXHANDLE   mhLight;

	
	D3DXMATRIX mWorld;

	float m_hack;
	float dir;
};
#endif