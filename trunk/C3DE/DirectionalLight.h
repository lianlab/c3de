#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include "Light.h"


class DirectionalLight: public Light
{
public:
	DirectionalLight();
	~DirectionalLight();

	void SetDirection(float x, float y, float z);
	D3DXVECTOR3 *GetDirection(){return m_direction;}
	
protected:
	D3DXVECTOR3 *m_direction;
};
#endif