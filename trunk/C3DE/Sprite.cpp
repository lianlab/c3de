#include "Sprite.h"
#include "DebugMemory.h"

Sprite::Sprite(Image *image, int frameWidth, int frameHeight, int numFrames, int numColumns, int numRows, int frameDuration)
{
	m_image = image;
	m_frameWidth = frameWidth;
	m_frameHeight =  frameHeight;
	m_numFrames = numFrames;
	m_frameDuration = frameDuration;

	m_angle = 0;
	m_x = 0;
	m_y = 0;
	m_xScale = 1.0f;
	m_yScale = 1.0f;
	m_angle = 0.0f;

	m_numColumns = numColumns;
	m_numRows = numRows;

	m_currentFrameTime = 0;
	m_currentFrame = 0;

}

void Sprite::Update(int deltaTime)
{
	m_currentFrameTime += deltaTime;

	int framesToAdvance = m_currentFrameTime / m_frameDuration;

	m_currentFrame = ((m_currentFrame + framesToAdvance) % m_numFrames);	

	m_currentFrameTime = (m_currentFrameTime % m_frameDuration);

}

void Sprite::SetX(int x)
{
	m_x = x;
}

void Sprite::SetY(int y)
{
	m_y = y;
}

void Sprite::SetXScale(float xScale)
{
	m_xScale = xScale;
}

void Sprite::SetYScale(float yScale)
{
	m_yScale = yScale;
}

void Sprite::SetRotation(float angle)
{
	m_angle = angle;
}

Sprite::~Sprite()
{

}