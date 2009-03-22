#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include "D3DMesh.h"

struct VertexParticle
{
	D3DXVECTOR3 initialPos;
	D3DXVECTOR3 initialVelocity;
	float       initialSize; // In pixels.
	float       initialTime;
	float       lifeTime;
	float       mass;
	D3DCOLOR    initialColor;

	static IDirect3DVertexDeclaration9* Decl;
};

class ParticleSystem : public D3DMesh
{
public:
	ParticleSystem(const D3DXVECTOR3& accel, 
		//const AABB& box,
		int maxNumParticles,
		float timePerParticle);

	virtual ~ParticleSystem();
	void AddParticle();


	virtual void InitParticle(VertexParticle& out) = 0;
	virtual void Update(float dt);
	std::vector<VertexParticle*> GetAliveParticles(){return m_aliveParticles;}
	

protected:


	IDirect3DTexture9* m_texture;
	IDirect3DVertexBuffer9* mVB;
	

	float m_time;
	D3DXVECTOR3 m_accel;
	int m_maxNumParticles;
	float m_timePerParticle;

	std::vector<VertexParticle*> m_particles;
	std::vector<VertexParticle*> m_aliveParticles;
	std::vector<VertexParticle*> *m_deadParticles; 

};
#endif