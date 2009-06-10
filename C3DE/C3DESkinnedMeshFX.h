#ifndef C3DE_SKINNED_MESH_FX_H
#define C3DE_SKINNED_MESH_FX_H

#include "FX.h"



class C3DESkinnedMeshFX : public FX
{
public:
	C3DESkinnedMeshFX(ID3DXEffect * effect);
	~C3DESkinnedMeshFX();

	void SetObjectMaterials(D3DXCOLOR ambientMaterial, D3DXCOLOR diffuseMaterial,
							D3DXCOLOR specularMaterial, float specularPower);
	void SetObjectTexture(IDirect3DTexture9 *texture);

	void SetWorldHandlers(D3DXVECTOR3 cameraPosition, D3DXMATRIX worldViewProjection);

	void SetBoneMatrix(const D3DXMATRIX *a_bones, UINT a_numBones);

	void SetRootMatrices(const D3DXMATRIX *a_toRoot, UINT totalToRoots);
	void SetFrameRootMatrices(const D3DXMATRIX * currentFrameToRoots, UINT totalCurrentFrameToRoots);

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
	D3DXHANDLE   mhFinalXForms;

	D3DXHANDLE   mhToRoot;
	D3DXHANDLE   mhCurrentFrameToRoot;

	float m_hack;
	float dir;
};
#endif