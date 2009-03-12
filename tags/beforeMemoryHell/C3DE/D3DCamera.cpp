#include "D3DCamera.h"
#include "DebugMemory.h"

D3DCamera::D3DCamera()
{
	m_pos = D3DXVECTOR3(0, 0, 0);
	m_target = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	m_upX = 0.0f;
	m_upY = 1.0f;
	m_upZ = 0.0f;
}

D3DCamera::~D3DCamera()
{

}

D3DXMATRIX D3DCamera::GetMatrix()
{
#define USE_HELPER_FUCTIONS 1
#if USE_HELPER_FUCTIONS
	m_pos = D3DXVECTOR3(m_x, m_y, m_z);
	m_target = D3DXVECTOR3(m_targetX, m_targetY, m_targetZ);
	m_up = D3DXVECTOR3(m_upX, m_upY, m_upZ);

	D3DXMatrixLookAtLH(&m_matrix, &m_pos, &m_target, &m_up);		

	return m_matrix;

#else
	m_target = D3DXVECTOR3(m_targetX, m_targetY, m_targetZ);
	m_pos = D3DXVECTOR3(m_x, m_y, m_z);
	m_up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	D3DXVECTOR3 L = m_target - m_pos;
	D3DXVec3Normalize(&L, &L);

	D3DXVECTOR3 R;
	D3DXVec3Cross(&R, &m_up, &L);
	D3DXVec3Normalize(&R, &R);

	D3DXVECTOR3 U;
	D3DXVec3Cross(&U, &L, &R);
	D3DXVec3Normalize(&U, &U);		

	D3DXMATRIX tView;					

	// Fill in the view matrix entries.

	float x = -D3DXVec3Dot(&m_pos, &R);
	float y = -D3DXVec3Dot(&m_pos, &U);	
	float z = -D3DXVec3Dot(&m_pos, &L);

	tView(0,0) = R.x; 
	tView(1,0) = R.y; 
	tView(2,0) = R.z; 
	tView(3,0) = x;   

	tView(0,1) = U.x;
	tView(1,1) = U.y;
	tView(2,1) = U.z;
	tView(3,1) = y;  
	
	tView(0,2) = L.x; 
	tView(1,2) = L.y; 
	tView(2,2) = L.z; 
	tView(3,2) = z;   

	tView(0,3) = 0.0f;
	tView(1,3) = 0.0f;
	tView(2,3) = 0.0f;
	tView(3,3) = 1.0f;

	return tView;
#endif
}