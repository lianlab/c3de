#ifndef SPECULAR_LIGHT_H
#define SPECULAR_LIGHT_H


#include "DirectionalLight.h"

class SpecularLight : public DirectionalLight
{
public:
	SpecularLight();
	~SpecularLight();
};


#endif