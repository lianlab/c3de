#include "D3DSprite.h"
#include "DebugMemory.h"

D3DSprite::D3DSprite(D3DImage *image, int imageWidth, int imageHeight, int numFrames):
C3DESprite((Image *)image, imageWidth, imageHeight, numFrames)
{

}

D3DSprite::~D3DSprite()
{

}