#ifndef BUTTON_H
#define BUTTON_H

#include "D3DSprite.h"
#include "MouseListener.h"
#include "ButtonListener.h"
#include <vector>

using namespace std;

class Button : public D3DSprite, MouseListener
{
public:
	Button(D3DImage *image, vector<RECT> *frames, RECT collisionBox);
	~Button();
	void OnMouseDown(int button, int x, int y);
	void OnMouseMove(int mouseX, int mouseY, int dx, int dy);
	void OnMouseUp(int button, int x, int y);	
	RECT GetCollisionBox(){return m_collisionBox;}
	void AddListener(ButtonListener *listener);
	void RemoveListener(ButtonListener *);

	
	static const int STATE_OUT = 0;
	static const int STATE_DOWN = 1;
	static const int STATE_OVER = 2;
	static const int STATE_UP = 3;
	
private:
	RECT m_collisionBox;
	bool IsInRect(int x, int y);
	vector<ButtonListener *> *m_listeners;

	int m_currentState;

	
	static const int MOUSE_EVENT_MOVE = 0;
	static const int MOUSE_EVENT_DOWN = 1;
	static const int MOUSE_EVENT_UP = 2;

	void NotifyButtonDown();
	void NotifyButtonOver();
	void NotifyButtonUp();

	void Update(int mouseEvent, int mouseX, int mouseY);

};
#endif
