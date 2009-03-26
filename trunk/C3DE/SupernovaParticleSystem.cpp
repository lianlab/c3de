#include "SupernovaParticleSystem.h"
#include "SupernovaFX.h"

SupernovaParticleSystem::SupernovaParticleSystem(IDirect3DTexture9 * a_texture,int a_maxNumParticles, float a_timePerParticle, D3DXVECTOR3 a_acceleration, bool a_isFinite):
ParticleSystem(a_acceleration,a_maxNumParticles, a_timePerParticle, a_isFinite)
{
	m_acceleration = a_acceleration;

	m_acceleration = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_texture = a_texture;

	m_effect = ShaderManager::GetInstance()->GetFXByID(SHADER_SUPERNOVA_FX_ID);

	//HARD CODED
	RECT clientRect;	
	clientRect.left = 0;
	clientRect.top = 0;
	clientRect.bottom = 573;
	clientRect.right = 796;

	SupernovaFX *t_effect = (SupernovaFX*) m_effect;
	t_effect->SetViewportHeight(clientRect.bottom);

	m_timePerParticle = -1.0f;

		// They start off all dead.
	for(int i = 0; i < m_maxNumParticles; ++i)
	{
		float t_angle = (D3DX_PI*2 / m_maxNumParticles) * i;
		D3DXMATRIX R;
		D3DXMatrixRotationY(&R, t_angle);
		D3DXVECTOR3 t_speed = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		D3DXVec3TransformCoord(&t_speed, &t_speed, &R);
		//D3DXVec3Normalize(&m_carDirection, &m_carDirection);

		VertexParticle *t_particle;
		t_particle = (*m_particles)[i];
		delete t_particle;
		t_particle = NULL;

		t_particle = new VertexParticle();
		t_particle->lifeTime = 50.0f;
		t_particle->initialTime = 0.0f;
		t_particle->initialSize  = 10.0f;
		if(i%4 == 0)
		{
			t_particle->initialVelocity = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		}
		else if(i%4 == 1)
		{
			t_particle->initialVelocity = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		}
		else if(i%4 == 2)
		{
			t_particle->initialVelocity = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		}
		else if(i%4 == 3)
		{
			t_particle->initialVelocity = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
		}

		t_particle->initialVelocity = t_speed;
		
		t_particle->mass = 1.5f;
		t_particle->initialColor = D3DXCOLOR(0.75f, 0.75f, 0.75f, 0.75f);
		t_particle->initialPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//m_particles->push_back(t_particle);
		(*m_particles)[i] = t_particle;
		//m_deadParticles.push_back(t_particle);

		



	}

}

SupernovaParticleSystem::~SupernovaParticleSystem()
{

}

void SupernovaParticleSystem::InitParticle(VertexParticle& out)
{
	// Time particle is created relative to the global running
	// time of the particle system.
	out.initialTime = m_time;

	// Flare lives for 2-4 seconds.
	//out.lifeTime   = GetRandomFloat(2.0f, 4.0f);
	out.lifeTime = 4.0f;

	// Initial size in pixels.
	//out.initialSize  = GetRandomFloat(10.0f, 15.0f);
	out.initialSize  = 10.0f;

	// Give a very small initial velocity to give the flares
	// some randomness.
	//GetRandomVec(out.initialVelocity);
	out.initialVelocity = D3DXVECTOR3(0.0f, 0.0f, 15.0f);

	// Scalar value used in vertex shader as an amplitude factor.
	out.mass = GetRandomFloat(1.0f, 2.0f);

	// Start color at 50-100% intensity when born for variation.
	out.initialColor = D3DXCOLOR(GetRandomFloat(0.5f, 1.0f), GetRandomFloat(0.5f, 1.0f), GetRandomFloat(0.5f, 1.0f), GetRandomFloat(0.5f, 1.0f));

	// Generate random particle on the ring in polar coordinates:
	// random radius and random angle.
	float r = GetRandomFloat(10.0f, 14.0f);
	float t = GetRandomFloat(0, 2.0f*D3DX_PI);

	// Convert to Cartesian coordinates.
	//out.initialPos.x = r*cosf(t);
	//out.initialPos.y = r*sinf(t);
	out.initialPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// Random depth value in [-1, 1] (depth of the ring)
	//out.initialPos.z = GetRandomFloat(-1.0f, 1.0f);
}

void SupernovaParticleSystem::SetShaderHandlers()
{
	SupernovaFX *t_effect = (SupernovaFX*) m_effect;
	t_effect->SetTexture(m_texture);
	t_effect->SetAcceleration(m_acceleration);
	t_effect->SetTime(m_time);

	t_effect->SetTransformMatrix(GetTransformMatrix());

	
}

void SupernovaParticleSystem::Update(int deltaTime)
{
	if(m_isFinished && m_isFinite)
	{
		return;
	}

	float dt = deltaTime/1000.0f;
	m_time += dt;

	

	// Rebuild the dead and alive list.  Note that resize(0) does
	// not deallocate memory (i.e., the capacity of the vector does
	// not change).
	m_deadParticles->resize(0);
	m_aliveParticles->resize(0);

	// For each particle.

	for(int i = 0; i < m_maxNumParticles; ++i)
	{
		// Is the particle dead?
		//VertexParticle *t = m_particles->operator[i];
		if( (m_time - (*m_particles)[i]->initialTime) > (*m_particles)[i]->lifeTime)
		{
			m_deadParticles->push_back((*m_particles)[i]);
		}
		else
		{
			m_aliveParticles->push_back((*m_particles)[i]);
		}
	}




	// A negative or zero mTimePerParticle value denotes
	// not to emit any particles.
	if( m_timePerParticle > 0.0f )
	{
		// Emit particles.
		static float timeAccum = 0.0f;
		timeAccum += dt;
		while( timeAccum >= m_timePerParticle )
		{
			m_emmittedParticles++;

			if(m_isFinite)
			{
				if(m_emmittedParticles > m_maxNumParticles)
				{
					int t_deadParticlesCount = m_deadParticles->size();
					m_isFinished = t_deadParticlesCount == m_maxNumParticles;

					
					//return;
				}
				else
				{
					AddParticle();
				}
			}
			else
			{
				AddParticle();
			}
		
			
			
			
			timeAccum -= m_timePerParticle;
		}
	}
}