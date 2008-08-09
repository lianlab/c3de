#ifndef D3D_SPRITE_H
#define D3D_SPRITE_H

#include "C3DESprite.h"
#include "D3DImage.h"

class D3DSprite : public C3DESprite
{
public:
	D3DSprite(D3DImage *image, int imageWidth, int imageHeight, int numFrames);
	~D3DSprite();

};
#endif
