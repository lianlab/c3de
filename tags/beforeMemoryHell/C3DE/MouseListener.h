#ifndef MOUSE_LISTENER_H
#define MOUSE_LISTENER_H


class MouseListener
{
public:
	virtual void OnMouseDown(int button, int x, int y) = 0;
	virtual void OnMouseMove(int mouseX, int mouseY, int dx, int dy) = 0;
	virtual void OnMouseUp(int button, int x, int y) = 0;
};


#endif