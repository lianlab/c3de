#ifndef SUPERNOVA_PARTICLE_SYSTEM_H
#define SUPERNOVA_PARTICLE_SYSTEM_H

#include "ParticleSystem.h"
#include "Math.h"

class SupernovaParticleSystem : public ParticleSystem
{
public:
	SupernovaParticleSystem(IDirect3DTexture9 * a_texture,int a_maxNumParticles, D3DXVECTOR3 a_acceleration, bool a_isFinite = false);
	~SupernovaParticleSystem();

	void SetShaderHandlers();

	//void Update(int deltaTime);

protected:
	void InitParticle(VertexParticle& out);



	D3DXVECTOR3 m_acceleration;
};
#endif