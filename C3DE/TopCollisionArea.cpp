#include "TopCollisionArea.h"
#include "DebugMemory.h"

TopCollisionArea::TopCollisionArea(D3DXVECTOR3 upLeft, D3DXVECTOR3 upRight, D3DXVECTOR3 downLeft, D3DXVECTOR3 downRight)
{
	m_upLeft = upLeft;
	m_upRight = upRight;
	m_downLeft = downLeft;
	m_downRight = downRight;
}
	
TopCollisionArea::~TopCollisionArea()
{

}

D3DXVECTOR3 TopCollisionArea::GetUpLeft()
{
	return m_upLeft;
}

D3DXVECTOR3 TopCollisionArea::GetUpRight()
{
	return m_upRight;
}

D3DXVECTOR3 TopCollisionArea::GetDownLeft()
{
	return m_downLeft;
}

D3DXVECTOR3 TopCollisionArea::GetDownRight()
{
	return m_downRight;
}

	