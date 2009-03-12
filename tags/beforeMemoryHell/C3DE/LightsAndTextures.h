#ifndef LIGHTS_AND_TEXTURES_H
#define LIGHTS_AND_TEXTURES_H

#include "FX.h"

class LightsAndTextures : public FX
{
public:
	LightsAndTextures(ID3DXEffect * effect);
	~LightsAndTextures();
};
#endif