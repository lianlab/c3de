#ifndef LIGHT_MESH_H
#define LIGHT_MESH_H

#include "D3DMesh.h"

class LightMesh: public D3DMesh
{
public:
	LightMesh();
	~LightMesh();	

	virtual D3DXHANDLE *GetShaderAmbientLightMaterial() = 0;
	virtual D3DXHANDLE *GetShaderDiffuseLightMaterial() = 0;
	virtual D3DXHANDLE *GetShaderSpecularLightMaterial() = 0;
	virtual D3DXHANDLE *GetShaderLightPosition() = 0;
	virtual D3DXHANDLE *GetShaderLightDirection() = 0;
	virtual D3DXHANDLE *GetShaderLightAttenuation() = 0;
	virtual D3DXHANDLE *GetShaderSpotLightPower() = 0;
protected:
	D3DXHANDLE *m_shaderObjectAmbientMaterial;//gAmbientMtrl
	D3DXHANDLE *m_shaderObjectDiffuseMaterial;//gDiffuseMtrl
	D3DXHANDLE *m_shaderObjectSpecularMaterial;//gSpecMtrl
	D3DXHANDLE *m_shaderSpecularLightPower;//gSpecPower

	D3DXHANDLE *m_shaderObjectAmbientMaterial;//gAmbientMtrl
	D3DXHANDLE *m_shaderObjectDiffuseMaterial;//gDiffuseMtrl
	D3DXHANDLE *m_shaderObjectSpecularMaterial;//gSpecMtrl
	D3DXHANDLE *m_shaderSpecularLightPower;//gSpecPower


};
#endif