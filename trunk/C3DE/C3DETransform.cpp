#include "C3DETransform.h"
#include "DebugMemory.h"

C3DETransform::C3DETransform()
{
	m_matrix = new D3DXMATRIX();
	D3DXMatrixIdentity(m_matrix);
}

C3DETransform::~C3DETransform()
{
	delete m_matrix;
	m_matrix = NULL;
}



void C3DETransform::Set(D3DXMATRIX *a_matrix)
{
	//if(m_matrix != NULL)
	//{
	//	delete m_matrix;
	//	m_matrix =NULL;
	//}



	//m_matrix = new D3DXMATRIX();
	m_matrix->_11 = a_matrix->_11;
	m_matrix->_12 = a_matrix->_12;
	m_matrix->_13 = a_matrix->_13;
	m_matrix->_14 = a_matrix->_14;
	m_matrix->_21 = a_matrix->_21;
	m_matrix->_22 = a_matrix->_22;
	m_matrix->_23 = a_matrix->_23;
	m_matrix->_24 = a_matrix->_24;
	m_matrix->_31 = a_matrix->_31;
	m_matrix->_32 = a_matrix->_32;
	m_matrix->_33 = a_matrix->_33;
	m_matrix->_34 = a_matrix->_34;
	m_matrix->_41 = a_matrix->_41;
	m_matrix->_42 = a_matrix->_42;
	m_matrix->_43 = a_matrix->_43;
	m_matrix->_44 = a_matrix->_44;
}
void C3DETransform::Translate(float x, float y, float z)
{
	D3DXMATRIX *tempMatrix = new D3DXMATRIX();
	D3DXMatrixTranslation(tempMatrix, x, y, z);
	D3DXMatrixMultiply(m_matrix, m_matrix, tempMatrix);
	delete tempMatrix;
	tempMatrix = NULL;
}

void C3DETransform::Scale(float x, float y, float z)
{
	D3DXMATRIX *tempMatrix = new D3DXMATRIX();
	D3DXMatrixScaling(tempMatrix, x, y, z);
	D3DXMatrixMultiply(m_matrix, m_matrix, tempMatrix);
	delete tempMatrix;
	tempMatrix = NULL;
}

//angle from 0 to 1
void C3DETransform::Rotate(float angle, D3DXVECTOR3 * t_axis)
{
	float t_angle = angle * (2.0f * D3DX_PI);
	D3DXMATRIX *tempMatrix = new D3DXMATRIX();
	D3DXMatrixRotationAxis(tempMatrix, t_axis, t_angle);
	D3DXMatrixMultiply(m_matrix, m_matrix, tempMatrix);
	delete tempMatrix;
	tempMatrix = NULL;
}

D3DXMATRIX * C3DETransform::GetMatrix()
{
	return m_matrix;
}