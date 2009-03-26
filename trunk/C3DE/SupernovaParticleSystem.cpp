#include "SupernovaParticleSystem.h"
#include "SupernovaFX.h"

SupernovaParticleSystem::SupernovaParticleSystem(IDirect3DTexture9 * a_texture,int a_maxNumParticles, float a_timePerParticle, D3DXVECTOR3 a_acceleration, bool a_isFinite):
ParticleSystem(a_acceleration,a_maxNumParticles, a_timePerParticle, a_isFinite)
{
	m_acceleration = a_acceleration;

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