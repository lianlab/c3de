#ifndef D3D_SPRITE_H
#define D3D_SPRITE_H

#include "Sprite.h"
#include "D3DImage.h"

class D3DSprite : public Sprite
{
public:
	D3DSprite(D3DImage *image, int frameWidth, int frameHeight, int numFrames, int numColumns, int numRows,int frameDuration);
	~D3DSprite();
	D3DXMATRIX GetTransformationMatrix(){return m_transformationMatrix;}
	void SetX(int x);
	void SetY(int y);
	void SetXScale(float xscale);
	void SetYScale(float yscale);
	void SetRotation(float angle);
private:
	D3DXMATRIX m_transformationMatrix;
	D3DXMATRIX m_translationMatrix;
	D3DXMATRIX m_scalingMatrix;
	D3DXMATRIX m_rotationMatrix;

};
#endif
