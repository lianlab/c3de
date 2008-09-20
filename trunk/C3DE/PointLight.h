#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "Light.h"

class PointLight: public Light
{
public:
	PointLight(float power = 16.0f);
	~PointLight();
	float GetPower(){return m_power;}
protected:
	float m_power;
};

#endif