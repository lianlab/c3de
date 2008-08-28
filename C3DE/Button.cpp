#include "Button.h"

Button::Button(D3DImage *image, vector<RECT> *frames, RECT collisionBox):
D3DSprite(image,0, 0, 0, 0, 0, 0)
{
	m_frameRects = frames;
	m_collisionBox = collisionBox;
	m_listeners = new vector<ButtonListener *>;

	m_frameWidth = collisionBox.right - collisionBox.left;
	m_frameHeight = collisionBox.bottom - collisionBox.top;

	m_currentState = Button::STATE_OUT;
}

Button::~Button()
{

}

void Button::OnMouseDown(int button, int x, int y)
{
	Update(Button::MOUSE_EVENT_DOWN, x, y);

}

void Button::Update(int mouseEvent, int mouseX, int mouseY)
{
	bool isInRect = IsInRect(mouseX, mouseY);

	if(mouseEvent == Button::MOUSE_EVENT_DOWN)
	{
		switch(m_currentState)
		{
			case Button::STATE_OUT:
					if(isInRect)
					{
						m_currentFrame = 2;
						NotifyButtonDown();
						m_currentState = Button::STATE_DOWN;
						return;
					}
				break;

			case Button::STATE_DOWN:
					//impossible
				break;

			case Button::STATE_OVER:
					m_currentFrame = 2;
					NotifyButtonDown();
					m_currentState = Button::STATE_DOWN;
					return;
				break;

			case Button::STATE_UP:
					if(isInRect)
					{
						m_currentFrame = 2;
						NotifyButtonDown();
						m_currentState = Button::STATE_DOWN;
						return;
					}
					else
					{
						m_currentFrame = 0;
						m_currentState = Button::STATE_OUT;
						return;
					}
				break;
		}
	}
	else if(mouseEvent == Button::MOUSE_EVENT_MOVE)
	{
		switch(m_currentState)
		{
			case Button::STATE_OUT:
					if(isInRect)
					{
						m_currentFrame = 1;
						NotifyButtonOver();
						m_currentState = Button::STATE_OVER;
						return;
					}
				break;

			case Button::STATE_DOWN:					
					if(!isInRect)
					{
						m_currentFrame = 0;						
						m_currentState = Button::STATE_OUT;
						return;
					}
				break;

			case Button::STATE_OVER:
					if(!isInRect)
					{
						m_currentFrame = 0;						
						m_currentState = Button::STATE_OUT;
						return;
					}
					
					return;
				break;

			case Button::STATE_UP:
					if(isInRect)
					{
						m_currentFrame = 1;
						NotifyButtonOver();
						m_currentState = Button::STATE_OVER;
						return;
					}
					else
					{
						m_currentFrame = 0;
						m_currentState = Button::STATE_OUT;
						return;
					}
				break;
		}
	}
	//mouseEvent == MOUSE_EVENT_UP
	else
	{
		if(isInRect)
		{
			m_currentFrame = 1;			
			m_currentState = Button::STATE_OVER;
			
		}
		else
		{
			m_currentFrame = 0;
			m_currentState = Button::STATE_OUT;
			
		}

		NotifyButtonUp();
	}
}

void Button::NotifyButtonDown()
{
	for(int i = 0; i< m_listeners->size(); i++)
	{
		ButtonListener *listener = m_listeners->at(i);
		listener->OnButtonDown(this);			
	}
}

void Button::NotifyButtonOver()
{
	for(int i = 0; i< m_listeners->size(); i++)
	{
		ButtonListener *listener = m_listeners->at(i);
		listener->OnButtonOver(this);			
	}
}

void Button::NotifyButtonUp()
{
	for(int i = 0; i< m_listeners->size(); i++)
	{
		ButtonListener *listener = m_listeners->at(i);
		listener->OnButtonUp(this);			
	}
}
void Button::OnMouseMove(int x, int y, int dx, int dy)
{
	Update(Button::MOUSE_EVENT_MOVE, x, y);
}

void Button::OnMouseUp(int button, int x, int y)
{
	Update(Button::MOUSE_EVENT_UP, x, y);
}

bool Button::IsInRect(int x, int y)
{
	int absLeft = m_x + m_collisionBox.left;
	int absRight = m_x + m_collisionBox.right;
	int absTop = m_y + m_collisionBox.top;
	int absBottom = m_y + m_collisionBox.bottom;
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