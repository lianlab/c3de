#ifndef D3D_SPRITE_H
#define D3D_SPRITE_H

#include "Sprite.h"
#include "D3DImage.h"
#include <vector>

using namespace std;

class D3DSprite : public Sprite
{
public:
	D3DSprite(D3DImage *image, int frameWidth, int frameHeight, int numFrames, int numColumns, int numRows,int frameDuration);
	virtual ~D3DSprite();
	D3DXMATRIX GetTransformationMatrix(){return m_transformationMatrix;}
	void SetX(int x);
	void SetY(int y);
	void SetXScale(float xscale);
	void SetYScale(float yscale);
	void SetRotation(float angle);
	vector<RECT> *GetFrameRects(){return m_frameRects;}
	void SetFrameRects(vector<RECT> * frameRects){m_frameRects = frameRects;}
private:
	D3DXMATRIX m_transformationMatrix;
	D3DXMATRIX m_translationMatrix;
	D3DXMATRIX m_scalingMatrix;
	D3DXMATRIX m_rotationMatrix;

	void BuildFrameRects();

protected:
	vector<RECT> *m_frameRects;

};
#endif
