#ifndef DIRECT_INPUT_H
#define DIRECT_INPUT_H

#define DIRECTINPUT_VERSION 0x0800
#define KEYBOARD_BUFFER_SIZE 10

#include "Input.h"
#include <dinput.h>
#include "D3DCommonDefs.h"

class DirectInput : public Input
{
public:
	DirectInput();
	~DirectInput();
	void Update();
	void Init(HINSTANCE hInstance, HWND hwnd);
	bool IsKeyDown(char key);
	bool IsMouseButtonDown(int button);
private:
	IDirectInput8 *m_dInput;
	IDirectInputDevice8 *m_keyboard;
	char m_keyboardState[256];
	char m_previousKeyboardState[256];
	IDirectInputDevice8 *m_mouse;
	DIMOUSESTATE2 m_mouseState;
	DIMOUSESTATE2 m_previousMouseState;
	

};
#endif
