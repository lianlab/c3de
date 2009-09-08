#ifndef OBB_H
#define OBB_H

#include <d3dx9.h>

class OBB
{
public:
	
	OBB(D3DXVECTOR3 position, D3DXVECTOR3 size);
	~OBB();
	bool Intersect(D3DXVECTOR3 &point);
	bool Intersect( OBB &b);
	void SetPosition(float x, float y, float z);
	void SetRotation(float x, float y, float z, float w);
private:
	D3DXVECTOR3 m_size;
	D3DXVECTOR3 m_pos;
	D3DXQUATERNION m_rotation;
};
#endif