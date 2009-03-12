#ifndef DIFFUSE_LIGHT_H
#define DIFFUSE_LIGHT_H

#include "DirectionalLight.h"

class DiffuseLight : public DirectionalLight
{
public:
	DiffuseLight();
	~DiffuseLight();
};


#endif