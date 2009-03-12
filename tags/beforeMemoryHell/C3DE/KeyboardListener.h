#ifndef KEYBOARD_LISTENER_H
#define KEYBOARD_LISTENER_H

class KeyboardListener
{
public:
	virtual void OnKeyDown(int key) = 0;
	virtual void OnKeyUp(int key) = 0;
};
#endif