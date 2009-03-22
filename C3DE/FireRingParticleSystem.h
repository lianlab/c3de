#ifndef FIRE_RING_PARTICLE_SYSTEM_H
#define FIRE_RING_PARTICLE_SYSTEM_H

#include "ParticleSystem.h"
#include "Math.h"

class FireRingParticleSystem : public ParticleSystem
{
public:
	FireRingParticleSystem(IDirect3DTexture9 * a_texture,int a_maxNumParticles, float a_timePerParticle, D3DXVECTOR3 a_acceleration);
	~FireRingParticleSystem();

	void SetShaderHandlers();

protected:
	void InitParticle(VertexParticle& out);

	D3DXVECTOR3 m_acceleration;
};
#endif