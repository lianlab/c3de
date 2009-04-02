#include "SupernovaParticleSystem.h"
#include "SupernovaFX.h"
#include "DebugMemory.h"

SupernovaParticleSystem::SupernovaParticleSystem(IDirect3DTexture9 * a_texture,int a_maxNumParticles, D3DXVECTOR3 a_acceleration, bool a_isFinite):
ParticleSystem(a_acceleration,a_maxNumParticles, -1.0f, a_isFinite)
{
	m_acceleration = a_acceleration;

	//m_acceleration = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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

	// They start off all dead.
	for(int i = 0; i < m_maxNumParticles; ++i)
	{
		float t_angle = (D3DX_PI*2 / m_maxNumParticles) * i;
		D3DXMATRIX R;
		D3DXMATRIX R2;
		//D3DXMatrixRotationY(&R, t_angle);
		D3DXMatrixRotationAxis(&R, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), t_angle);
		D3DXMatrixRotationAxis(&R2, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DX_PI / 6.0f);

		D3DXMatrixMultiply(&R, &R2, &R);
		
		//D3DXMatrixRotationX(&R, -D3DX_PI/6.0f);


		float t_tspeed = 10.05f;
		//D3DXVECTOR3 t_speed = D3DXVECTOR3(t_tspeed, 0.0f, 0.0f);
		D3DXVECTOR3 t_speed;
		GetRandomVec(t_speed);
		t_speed *= t_tspeed;
		D3DXVec3TransformCoord(&t_speed, &t_speed, &R);
		//D3DXVec3Normalize(&m_carDirection, &m_carDirection);

		VertexParticle *t_particle;
		t_particle = (*m_particles)[i];
		//delete t_particle;
		//t_particle = NULL;

		//t_particle = new VertexParticle();
		t_particle->lifeTime = 5.0f;
		t_particle->initialTime = 0.0f;
		t_particle->initialSize  = 10.0f;		
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

void SupernovaParticleSystem::SetShaderHandlers()
{
	SupernovaFX *t_effect = (SupernovaFX*) m_effect;
	t_effect->SetTexture(m_texture);
	t_effect->SetAcceleration(m_acceleration);
	t_effect->SetTime(m_time);

	t_effect->SetTransformMatrix(GetTransformMatrix());

	
}

void SupernovaParticleSystem::InitParticle(VertexParticle& out)
{
	// Generate about the origin.
	out.initialPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	out.initialTime     = m_time;
	out.lifeTime        = GetRandomFloat(4.0f, 5.0f);
	out.initialColor    = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	out.initialSize     = GetRandomFloat(8.0f, 12.0f);
	out.mass            = GetRandomFloat(0.8f, 1.2f);

	out.initialVelocity.x = GetRandomFloat(-2.5f, 2.5f);
	out.initialVelocity.y = GetRandomFloat(15.0f, 25.0f);
	out.initialVelocity.z = GetRandomFloat(-2.5f, 2.5f);
}

