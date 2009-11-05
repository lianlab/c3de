#include "FireRingFX.h"


FireRingFX::FireRingFX(ID3DXEffect * effect) : FX(effect)
{

	//m_shaderEyePosL = m_effect->GetParameterByName(0, "gEyePosL"); 
	m_shaderTex     = m_effect->GetParameterByName(0, "gTex");
	m_shaderTime    = m_effect->GetParameterByName(0, "gTime");
	m_shaderAccel   = m_effect->GetParameterByName(0, "gAccel");
	m_shaderViewportHeight = m_effect->GetParameterByName(0, "gViewportHeight");
}

FireRingFX::~FireRingFX()
{

}


//USE THE BASE ONE
#if 0
void FireRingFX::SetWorldHandlers(D3DXVECTOR3 cameraPosition, D3DXMATRIX worldViewProjection)
{
	D3DXMATRIX viewProj = worldViewProjection;
	D3DXMATRIX mWorld;
	D3DXMATRIX mInvWorld;

	D3DXMATRIX world;
	D3DXMatrixTranslation(&world, 0.0f, 0.0f, 5.0f);

	mWorld = world;

	// Compute the change of coordinates matrix that changes coordinates 
	// relative to world space so that they are relative to the particle
	// system's local space.
	D3DXMatrixInverse(&mInvWorld, 0, &mWorld);

	D3DXVECTOR3 eyePosW = cameraPosition;
	D3DXVECTOR3 eyePosL;
	D3DXVec3TransformCoord(&eyePosL, &eyePosW, &mInvWorld);

	// Set FX parameters.
	HR(m_effect->SetValue(m_shaderEyePosL, &cameraPosition, sizeof(D3DXVECTOR3)));
	
	//D3DXMATRIX fleps = (mWorld*viewProj);
	//HR(m_effect->SetMatrix(m_shaderViewMatrix, &fleps));
	HR(m_effect->SetMatrix(m_shaderViewMatrix, &worldViewProjection));
}
#endif

void FireRingFX::SetTexture(IDirect3DTexture9 *texture)
{
	HR(m_effect->SetTexture(m_shaderTex, texture));
}

void FireRingFX::SetTime(float a_time)
{
	HR(m_effect->SetFloat(m_shaderTime, a_time));
}

void FireRingFX::SetAcceleration(D3DXVECTOR3 a_acceleration)
{
	HR(m_effect->SetValue(m_shaderAccel, a_acceleration, sizeof(D3DXVECTOR3)));
	
}

void FireRingFX::SetViewportHeight(int a_height)
{
	HR(m_effect->SetInt(m_shaderViewportHeight, a_height));
}