#ifndef D3DCAMERA_H
#define D3DCAMERA_H

#include "Camera.h"
#include <d3dx9.h>
class D3DCamera : public Camera
{
public:
	D3DCamera();
	~D3DCamera();
	
	D3DXVECTOR3 GetPosition(){return m_pos;}
	D3DXVECTOR3 GetTarget(){return m_target;}
	D3DXVECTOR3 GetUp(){return m_up;}
	D3DXMATRIX GetMatrix();
private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_target;
	D3DXVECTOR3 m_up;
	D3DXMATRIX m_matrix;

	

};
#endif