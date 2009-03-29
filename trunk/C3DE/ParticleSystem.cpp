#include "ParticleSystem.h"
#include "D3DRenderer.h"

IDirect3DVertexDeclaration9* VertexParticle::Decl  = 0;

ParticleSystem::ParticleSystem(const D3DXVECTOR3& accel,
		        // const AABB& box,
				 int maxNumParticles,
				 float timePerParticle, bool a_isFinite) : D3DMesh()
	 
{
	m_isFinite = a_isFinite;
	m_isFinished = false;
	m_emmittedParticles = 0;
	//m_device = a_device;
	m_accel = accel;
	m_time = 0.0f;
	m_maxNumParticles = maxNumParticles;
	m_timePerParticle = timePerParticle;

	// Allocate memory for maximum number of particles.
	m_particles = new std::vector<VertexParticle*>;
	m_aliveParticles = new std::vector<VertexParticle*>;
	m_deadParticles = new std::vector<VertexParticle*>;

	//m_particles->resize(m_maxNumParticles);
	m_aliveParticles->reserve(m_maxNumParticles);
	m_deadParticles->reserve(m_maxNumParticles);

	// They start off all dead.
	for(int i = 0; i < m_maxNumParticles; ++i)
	{
#if 1
		VertexParticle *t_particle = new VertexParticle();
		t_particle->lifeTime = -1.0f;
		t_particle->initialTime = 0.0f;

		m_particles->push_back(t_particle);
		//m_deadParticles.push_back(t_particle);
#endif


	}

	IDirect3DDevice9 *t_device = D3DRenderer::GetDevice();

	HR(t_device->CreateVertexBuffer(m_maxNumParticles*sizeof(VertexParticle),
		D3DUSAGE_DYNAMIC|D3DUSAGE_WRITEONLY|D3DUSAGE_POINTS,
		0, D3DPOOL_DEFAULT, &m_vertexBuffer, 0));
}

ParticleSystem::~ParticleSystem()
{

}

void ParticleSystem::AddParticle()
{
	
	if( m_deadParticles->size() > 0)
	{
		// Reinitialize a particle.
		VertexParticle* p = m_deadParticles->back();
		InitParticle(*p);

		// No longer dead.
		m_deadParticles->pop_back();
		m_aliveParticles->push_back(p);
	}
}

bool ParticleSystem::GetIsFinished()
{
	return m_isFinished;
}
	
void ParticleSystem::Update(int deltaTime)
{
	if(m_isFinished && m_isFinite)
	{
		return;
	}

	float dt = deltaTime/1000.0f;
	//dt = 0.0001f;
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

bool ParticleSystem::GetIsFinite()
{
	return m_isFinite;
}