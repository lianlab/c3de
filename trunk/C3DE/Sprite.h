#ifndef SPRITE_H
#define SPRITE_H

#include "Image.h"

class Sprite
{
public:
	Sprite(Image *image, int frameWidth, int frameHeight, int numFrames, int numColumns, int numRows, int frameDuration);
	~Sprite();
	Image * GetImage(){ return m_image;}
	
	void Update(int deltaTime);
	void SetX(int x);
	void SetY(int y);
	void SetXScale(float xscale);
	void SetYScale(float yscale);
	void SetRotation(float angle);

	int GetX(){ return m_x;}
	int GetY(){ return m_y;}
	float GetXScale(){ return m_xScale;}
	float GetYScale(){ return m_yScale;}
	float GetRotation(){ return m_angle;}

	int GetFrameWidth(){return m_frameWidth;}
	int GetFrameHeight(){return m_frameHeight;}
	int GetCurrentFrame(){return m_currentFrame;}
	int GetNumFrames(){return m_numFrames;}
	int GetNumColumns(){return m_numColumns;}
	int getNumRows(){return m_numRows;}

protected:
	int m_frameWidth;
	int m_frameHeight;
	int m_numFrames;
	int m_frameDuration;
	int m_currentFrameTime;
	int m_currentFrame;
	Image *m_image;

	int m_numColumns;
	int m_numRows;

	int m_x;
	int m_y;
	float m_xScale;
	float m_yScale;
	float m_angle;
};
#endif
