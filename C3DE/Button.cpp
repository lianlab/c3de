#include "Button.h"

Button::Button(D3DImage *image, vector<RECT> *frames, RECT collisionBox):
D3DSprite(image,0, 0, 0, 0, 0, 0)
{
	m_frameRects = frames;
	m_collisionBox = collisionBox;
	m_listeners = new vector<ButtonListener *>;

	m_frameWidth = collisionBox.right - collisionBox.left;
	m_frameHeight = collisionBox.bottom - collisionBox.top;
}

Button::~Button()
{

}

void Button::OnMouseDown(int button, int x, int y)
{
	if(IsInRect(x, y))
	{
		m_currentFrame = 2;
		for(int i = 0; i< m_listeners->size(); i++)
		{
			ButtonListener *listener = m_listeners->at(i);
			listener->OnButtonDown(this);			
		}
	}
}

void Button::OnMouseMove(int x, int y, int dx, int dy)
{
	if(IsInRect(x, y))
	{
		m_currentFrame = 1;
		for(int i = 0; i< m_listeners->size(); i++)
		{
			ButtonListener *listener = m_listeners->at(i);
			listener->OnButtonOver(this);			
		}
	}
	else
	{
		m_currentFrame = 0;
		for(int i = 0; i< m_listeners->size(); i++)
		{
			ButtonListener *listener = m_listeners->at(i);
			listener->OnButtonUp(this);			
		}
	}
}

void Button::OnMouseUp(int button, int x, int y)
{
	if(IsInRect(x, y))
	{
		m_currentFrame = 1;
		for(int i = 0; i< m_listeners->size(); i++)
		{
			ButtonListener *listener = m_listeners->at(i);
			listener->OnButtonOver(this);			
		}
	}
	else
	{
		m_currentFrame = 0;
		for(int i = 0; i< m_listeners->size(); i++)
		{
			ButtonListener *listener = m_listeners->at(i);
			listener->OnButtonUp(this);			
		}
	}
}

bool Button::IsInRect(int x, int y)
{
	int absLeft = m_x + m_collisionBox.left;
	int absRight = m_x + m_frameWidth + m_collisionBox.right;
	int absTop = m_y + m_collisionBox.top;
	int absBottom = m_y + m_frameHeight + m_collisionBox.bottom;
	return (x > absLeft) && (x < absRight) &&
		(y > absTop) && (y < absBottom);
}

void Button::AddListener(ButtonListener *listener)
{
	m_listeners->push_back(listener);
}

void Button::RemoveListener(ButtonListener *a_listener)
{
	ButtonListener *listener;
	for(unsigned int i = 0; i < m_listeners->size(); i++)
	{
		listener = m_listeners->at(i);
		if(listener == a_listener)
		{
			//m_listeners.erase(str_Vector.begin()+i,str_Vector.begin()+2);
			m_listeners->erase(m_listeners->begin() + i);
		}
	}
	
}