#ifndef GRID_H
#define GRID_H

#include "D3DMesh.h"

class Grid : public D3DMesh
{
public:
	Grid(int numRows, int numCols, float dx, float dz/*, std::vector<D3DXVECTOR3>& verts, std::vector<DWORD>& indices*/);
	~Grid();

	void SetShaderHandlers();

#if 0
	void SetPreRenderEffectHandles();
	

	virtual void SetLightParameters(D3DXCOLOR ambientLightColor, D3DXCOLOR diffuseLightColor,
							D3DXCOLOR specularLightColor, D3DXVECTOR3 lightPosition, 
							D3DXVECTOR3 lightDirection, D3DXVECTOR3 lightAttenuation,
							float spotLightPower);
	
	virtual void SetWorldParameters(D3DXMATRIX worldMatrix, D3DXMATRIX worldViewProjection,
									D3DXMATRIX worldInverseTranspose, D3DXVECTOR3 eyePosition);


	void BeginShaderPass(int pass){m_effect->BeginPass(pass);}
	void EndShaderPass(int pass){m_effect->EndPass();}
	void BeginShader(){m_effect->Begin(&m_numShaderPasses,0);}
	void EndShader(){m_effect->End();}
	void CommitEffectHandles(){m_effect->CommitChanges();}

#endif
private:

	//D3DXHANDLE   m_hTex;

protected:
	void InitializeEffectHandles();

};

#endif