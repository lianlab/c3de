#ifndef MOUSE_LISTENER_H
#define MOUSE_LISTENER_H

class MouseListener
{
public:
	virtual void OnMouseDown(int button) = 0;
	virtual void OnMouseMove(int mouseX, int mouseY) = 0;
	virtual void OnMouseUp(int button) = 0;
};

#endif