#include "DirectionalLight.h"

DirectionalLight::DirectionalLight():Light()
{
	m_direction = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

DirectionalLight::~DirectionalLight()
{

}

void DirectionalLight::SetDirection(float x, float y, float z)
{
	D3DXVECTOR3 t_vector = D3DXVECTOR3(x, y, z);
	D3DXVec3Normalize(&t_vector, &t_vector);

	m_direction = t_vector;

}