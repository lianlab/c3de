#include "D3DSprite.h"
#include "DebugMemory.h"

D3DSprite::D3DSprite(D3DImage *image, int frameWidth, int frameHeight, int numFrames, int numColumns, 
					int numRows, int frameDuration):
Sprite((Image *)image, frameWidth, frameHeight, numFrames, numColumns, numRows, frameDuration)
{
	D3DXMatrixIdentity(&m_transformationMatrix);
	D3DXMatrixIdentity(&m_translationMatrix);
	D3DXMatrixIdentity(&m_rotationMatrix);
	D3DXMatrixIdentity(&m_scalingMatrix);

	BuildFrameRects();
}

void D3DSprite::BuildFrameRects()
{
	m_frameRects = new vector<RECT>;
	
	for(int i = 0; i < m_numFrames; i++)
	{		
		int colIndex = i % m_numColumns;
		int rowIndex = i / m_numColumns;		
		
		RECT src;
		src.left = colIndex * m_frameWidth;
		src.right = (colIndex * m_frameWidth) + m_frameWidth;
		src.top = rowIndex * m_frameHeight;
		src.bottom = (rowIndex * m_frameHeight) + m_frameHeight;

		m_frameRects->push_back(src);
	}
}

D3DSprite::~D3DSprite()
{
	if(m_image)
	{
		delete m_image;
		m_image = NULL;
	}
	
	if(m_frameRects)
	{
		m_frameRects->clear();
		delete m_frameRects;
		m_frameRects = NULL;
	}
}

void D3DSprite::SetX(int x)
{	
	D3DXMatrixTranslation(&m_translationMatrix, float(x), float(m_y), 0.0f);
	m_transformationMatrix = m_translationMatrix * m_rotationMatrix * m_scalingMatrix;
	m_x = x;
}

void D3DSprite::SetY(int y)
{
	D3DXMatrixTranslation(&m_translationMatrix, float(m_x), float(y), 0.0f);
	m_transformationMatrix = m_translationMatrix * m_rotationMatrix * m_scalingMatrix;
	m_y = y;
}

void D3DSprite::SetXScale(float xScale)
{
	D3DXMatrixScaling(&m_scalingMatrix, xScale, m_yScale, 0.0f);
	m_transformationMatrix = m_translationMatrix * m_rotationMatrix * m_scalingMatrix;
	m_xScale = xScale;
}

void D3DSprite::SetYScale(float yScale)
{
	D3DXMatrixScaling(&m_scalingMatrix, m_xScale, yScale, 0.0f);
	m_transformationMatrix = m_translationMatrix * m_rotationMatrix * m_scalingMatrix;
	m_yScale = yScale;
}

void D3DSprite::SetRotation(float angle)
{
	D3DXMatrixRotationZ(&m_rotationMatrix, angle);
	m_transformationMatrix = m_translationMatrix * m_rotationMatrix * m_scalingMatrix;
	m_angle = angle;
}
