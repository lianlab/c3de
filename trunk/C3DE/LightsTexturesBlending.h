#ifndef LIGHTS_TEXTURES_BLENDING_H
#define LIGHTS_TEXTURES_BLENDING_H

#include "FX.h"

class LightsTexturesBlending : public FX
{
public:
	LightsTexturesBlending(ID3DXEffect * effect);
	~LightsTexturesBlending();
};
#endif