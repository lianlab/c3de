#ifndef AMBIENT_LIGHT_H
#define AMBIENT_LIGHT_H

#include "Light.h"
#include "Material.h"

class AmbientLight: public Light
{
public:
	AmbientLight();
	~AmbientLight();
	void SetColor(Material a_color){m_color = a_color;}
	Material GetColor(){return m_color;}
private:
	Material m_color;
};
#endif