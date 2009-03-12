#include "DirectionalLight.h"
#include "DebugMemory.h"

DirectionalLight::DirectionalLight():Light()
{
	m_direction = new D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

DirectionalLight::~DirectionalLight()
{
	if(m_direction)
	{
		delete m_direction;
		m_direction = NULL;
	}
}

void DirectionalLight::SetDirection(float x, float y, float z)
{
	D3DXVECTOR3 t_vector = D3DXVECTOR3(x, y, z);
	D3DXVec3Normalize(&t_vector, &t_vector);

	m_direction->x = t_vector.x;
	m_direction->y = t_vector.y;
	m_direction->z = t_vector.z;

}