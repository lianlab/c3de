#include "OBB.h"
#include "DebugMemory.h"

OBB::OBB(D3DXVECTOR3 position, D3DXVECTOR3 size)
{
	m_pos = position;
	m_size = size;
	m_rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 0.0f);
	
}

OBB::~OBB()
{

}

void OBB::SetPosition(float x, float y, float z)
{
	m_pos.x = x;
	m_pos.y = y;
	m_pos.z = z;
	
}

void OBB::SetRotation(float x, float y, float z, float w)
{
	m_rotation.x = x;
	m_rotation.y = y;
	m_rotation.z = z;
	m_rotation.w = w;
}


bool OBB::Intersect(D3DXVECTOR3 &point)
{
	return false;
}

bool OBB::Intersect(OBB &b)
{
	return false;
}