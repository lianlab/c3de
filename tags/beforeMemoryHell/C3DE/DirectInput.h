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
	static DirectInput * GetInstance();
	~DirectInput();
	void Update();
	void Init(HINSTANCE hInstance, HWND hwnd);
	bool IsKeyDown(int key);
	bool IsMouseButtonDown(int button);
	void SetKeyDown(int key, bool a_isDown);

	void ClearAllKeys();

	static const int MAX_DOWN_KEYS_AT_A_TIME = 4;

	

	int * GetKeysDown();
private:
	DirectInput();
	IDirectInput8 *m_dInput;
	IDirectInputDevice8 *m_keyboard;
	char m_keyboardState[256];
	char m_previousKeyboardState[256];
	IDirectInputDevice8 *m_mouse;
	DIMOUSESTATE2 m_mouseState;
	DIMOUSESTATE2 m_previousMouseState;

	int m_downKeys[MAX_DOWN_KEYS_AT_A_TIME];

	

	int m_mouseAbsX;
	int m_mouseAbsY;

	static DirectInput *m_instance;
	

};
#endif
