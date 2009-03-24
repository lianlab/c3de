#ifndef FIRE_RING_FX_H
#define FIRE_RING_FX_H

#include "Fx.h"

class  FireRingFX : public FX
{
public:
	FireRingFX(ID3DXEffect * effect);
	~FireRingFX();

	//void SetWorldHandlers(D3DXVECTOR3 cameraPosition, D3DXMATRIX worldViewProjection);

	void SetTexture(IDirect3DTexture9 *texture);

	void SetTime(float a_time);
	void SetAcceleration(D3DXVECTOR3 a_acceleration);
	void SetViewportHeight(int a_height);
private:
	D3DXHANDLE m_shaderEyePosL;
	D3DXHANDLE m_shaderTex;
	D3DXHANDLE m_shaderTime;
	D3DXHANDLE m_shaderAccel;
	D3DXHANDLE m_shaderViewportHeight;
};
#endif