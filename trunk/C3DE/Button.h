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
private:
	RECT m_collisionBox;
	bool IsInRect(int x, int y);
	vector<ButtonListener *> *m_listeners;
};
#endif
