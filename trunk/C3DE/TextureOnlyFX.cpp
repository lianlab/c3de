#include "TextureOnlyFX.h"
#include "DebugMemory.h"


TextureOnlyFX::TextureOnlyFX(ID3DXEffect *effect):
FX(effect)
{

	m_hTex = m_effect->GetParameterByName(0, "gTex");

	
}

TextureOnlyFX::~TextureOnlyFX()
{

}

void TextureOnlyFX::ResetHandlers()
{
	D3DXMATRIX T;
	D3DXMatrixIdentity(&T);
	SetTransformMatrix(T);
}

void TextureOnlyFX::SetObjectMaterials(D3DXCOLOR ambientMaterial, D3DXCOLOR diffuseMaterial,
							D3DXCOLOR specularMaterial, float specularPower)
{
	
}

void TextureOnlyFX::SetLightHandlers(	D3DXCOLOR ambientLightColor, D3DXCOLOR diffuseLightColor,
							D3DXCOLOR specularLightColor, D3DXVECTOR3 lightVector)
{

}

void TextureOnlyFX::SetObjectTexture(IDirect3DTexture9 *texture)
{
	if(texture)
	{
		HR(m_effect->SetTexture(m_hTex, texture));

	}
	
}

void TextureOnlyFX::SetWorldHandlers(D3DXVECTOR3 cameraPosition, D3DXMATRIX worldViewProjection)
{
	
	D3DXMATRIX W;		
	D3DXMatrixIdentity(&W);			

	D3DXMATRIX WIT;
	D3DXMatrixInverse(&WIT, 0, &W);
	D3DXMatrixTranspose(&WIT, &WIT);														
	
	
	HR(m_effect->SetMatrix(m_shaderWorldMatrix, &W));	
	HR(m_effect->SetMatrix(m_shaderViewMatrix, &worldViewProjection));	
	HR(m_effect->SetMatrix(m_shaderWorldInverseTransposeMatrix, &WIT));												
	//HR(m_effect->SetValue(m_shaderEyePosition, cameraPosition, sizeof(D3DXVECTOR3)));
	
}

void TextureOnlyFX::SetAlpha(float alpha)
{
	//HR(m_effect->SetFloat(m_shaderAlpha, alpha));
}