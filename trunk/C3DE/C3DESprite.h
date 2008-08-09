#ifndef SPRITE_H
#define SPRITE_H

#include "Image.h"

class C3DESprite
{
public:
	C3DESprite(Image *image, int imageWidth, int imageHeight, int numFrames);
	~C3DESprite();
	Image * GetImage(){ return m_image;}
	int GetImageWidth(){ return m_imageWidth;}
	int GetImageHeight(){ return m_imageHeight;}
	int GetNumFrames() { return m_numFrames;}
protected:
	int m_imageWidth;
	int m_imageHeight;
	int m_numFrames;
	Image *m_image;
};
#endif
