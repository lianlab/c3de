#ifndef TOP_COLLISION_AREA
#define TOP_COLLISION_AREA

#include <d3dx9.h>

class TopCollisionArea
{
public:
	TopCollisionArea(D3DXVECTOR3 upLeft, D3DXVECTOR3 upRight, D3DXVECTOR3 downLeft, D3DXVECTOR3 downRight);
	~TopCollisionArea();

	D3DXVECTOR3 GetUpLeft();
	D3DXVECTOR3 GetUpRight();
	D3DXVECTOR3 GetDownLeft();
	D3DXVECTOR3 GetDownRight();

private:
	D3DXVECTOR3 m_upLeft;
	D3DXVECTOR3 m_upRight;
	D3DXVECTOR3 m_downLeft;
	D3DXVECTOR3 m_downRight;
};
#endif