#include "C3DESprite.h"
#include "DebugMemory.h"

C3DESprite::C3DESprite(Image *image, int imageWidth, int imageHeight, int numFrames)
{
	m_image = image;
	m_imageWidth = imageWidth;
	m_imageHeight =  imageHeight;
	m_numFrames = numFrames;
}

C3DESprite::~C3DESprite()
{

}