#ifndef BUTTON_LISTENER_H
#define BUTTON_LISTENER_H

class Button;

class ButtonListener
{
public:
	virtual void OnButtonDown(Button *button) = 0;
	virtual void OnButtonOver(Button *button) = 0;
	virtual void OnButtonUp(Button *button) = 0;
};

#endif
