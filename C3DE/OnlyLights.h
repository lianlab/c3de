#ifndef ONLY_LIGHTS_H
#define ONLY_LIGHTS_H

#include "FX.h"

class OnlyLights : public FX
{
public:
	OnlyLights(ID3DXEffect * effect);
	~OnlyLights();
};
#endif