#ifndef PLANAR_MIRROR_H
#define PLANAR_MIRROR_H

#include "D3DMirror.h"

class PlanarMirror : public D3DMirror
{
public:
	PlanarMirror();
	~PlanarMirror();
	
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
						
	void PreRender(Renderer *a_renderer);
	void PosRender(Renderer *a_renderer);

protected:

	void InitializeEffectHandles(/*ID3DXEffect* fx*/);
	D3DXHANDLE   m_hTex;
	D3DXHANDLE	m_shaderAlpha;//galpha
	
};
#endif

