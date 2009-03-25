#include "SupernovaFX.h"

SupernovaFX::SupernovaFX(ID3DXEffect * effect) : FX(effect)
{

	//m_shaderEyePosL = m_effect->GetParameterByName(0, "gEyePosL"); 
	m_shaderTex     = m_effect->GetParameterByName(0, "gTex");
	m_shaderTime    = m_effect->GetParameterByName(0, "gTime");
	m_shaderAccel   = m_effect->GetParameterByName(0, "gAccel");
	m_shaderViewportHeight = m_effect->GetParameterByName(0, "gViewportHeight");
}

SupernovaFX::~SupernovaFX()
{

}


void SupernovaFX::SetTexture(IDirect3DTexture9 *texture)
{
	HR(m_effect->SetTexture(m_shaderTex, texture));
}

void SupernovaFX::SetTime(float a_time)
{
	HR(m_effect->SetFloat(m_shaderTime, a_time));
}

void SupernovaFX::SetAcceleration(D3DXVECTOR3 a_acceleration)
{
	HR(m_effect->SetValue(m_shaderAccel, a_acceleration, sizeof(D3DXVECTOR3)));
	
}

void SupernovaFX::SetViewportHeight(int a_height)
{
	HR(m_effect->SetInt(m_shaderViewportHeight, a_height));
}