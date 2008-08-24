#include "D3DCamera.h"

D3DCamera::D3DCamera()
{
	m_pos = D3DXVECTOR3(0, 0, 0);
	m_target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
}

D3DCamera::~D3DCamera()
{

}

D3DXMATRIX D3DCamera::GetMatrix()
{
	m_pos = D3DXVECTOR3(m_x, m_y, m_z);
	m_target = D3DXVECTOR3(m_targetX, m_targetY, m_targetZ);
	m_up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&m_matrix, &m_pos, &m_target, &m_up);
	return m_matrix;
}