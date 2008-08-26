#include "DirectInput.h"
#include "DebugMemory.h"

DirectInput::DirectInput()
{
	POINT point;
	int ret = GetCursorPos(&point);
	m_mouseAbsX = (int)point.x;
	m_mouseAbsY = (int)point.y;
}

DirectInput::~DirectInput()
{
	ReleaseCOM(m_dInput);
	m_keyboard->Unacquire();
	m_mouse->Unacquire();
	ReleaseCOM(m_keyboard);
	ReleaseCOM(m_mouse);
}

void DirectInput::Update()
{
	HRESULT hr = m_keyboard->GetDeviceState(sizeof(m_keyboardState), (void**)&m_keyboardState);
	
	POINT point;
	int ret = GetCursorPos(&point);
	m_mouseAbsX = point.x;
	m_mouseAbsY = point.y;

	if(FAILED(hr))
	{
		ZeroMemory(m_keyboardState, sizeof(m_keyboardState));
		hr = m_keyboard->Acquire();
	}

	hr = m_mouse->GetDeviceState(sizeof(DIMOUSESTATE2), (void**)&m_mouseState);

	if(FAILED(hr))
	{
		ZeroMemory(&m_mouseState, sizeof(m_mouseState));
		hr = m_mouse->Acquire();
	}
	
	unsigned int i = 0;
	for(i = 0; i< m_keyboardListeners->size(); i++)
	{
		KeyboardListener *kbListener = m_keyboardListeners->at(i);

		for(int j = 0; j < 256; j++)
		{
			if(m_keyboardState[j] & 0x80)
			{
				kbListener->OnKeyDown(j);
				break;
			}
			else if(m_previousKeyboardState[j] & 0x80)
			{
				kbListener->OnKeyUp(j);
			}
		}	
		
	}

	

	for(i = 0; i< m_mouseListeners->size(); i++)
	{
		MouseListener *mouseListener = m_mouseListeners->at(i);

		for(int j = 0; j < 3; j++)
		{
			if(m_mouseState.rgbButtons[j] & 0x80)
			{
				mouseListener->OnMouseDown(j, m_mouseAbsX, m_mouseAbsY);				
			}
			else if(m_previousMouseState.rgbButtons[j] & 0x80)
			{
				mouseListener->OnMouseUp(j, m_mouseAbsX, m_mouseAbsY);
			}

		}		

		if(m_mouseState.lX || m_mouseState.lY)
		{
			
			
			mouseListener->OnMouseMove(m_mouseAbsX, m_mouseAbsY,m_mouseState.lX, m_mouseState.lY);
		}		
		
	}

	hr = m_keyboard->GetDeviceState(sizeof(m_previousKeyboardState), (void**)&m_previousKeyboardState);
	hr = m_mouse->GetDeviceState(sizeof(m_previousMouseState), (void**)&m_previousMouseState);


}



void DirectInput::Init(HINSTANCE hInstance, HWND hwnd)
{
	ZeroMemory(&m_previousKeyboardState, sizeof(m_previousKeyboardState));
	ZeroMemory(&m_previousMouseState, sizeof(m_previousMouseState));
	ZeroMemory(&m_keyboardState, sizeof(m_keyboardState));
	ZeroMemory(&m_mouseState, sizeof(m_mouseState));

	DWORD keyboardCoopFlags = DISCL_NONEXCLUSIVE | DISCL_FOREGROUND;
	DWORD mouseCoopFlags = DISCL_NONEXCLUSIVE | DISCL_FOREGROUND;
		
	DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_dInput, 0);

	HR(m_dInput->CreateDevice(GUID_SysKeyboard, &m_keyboard, 0));
	HR(m_dInput->CreateDevice(GUID_SysMouse, &m_mouse, 0));		

	DIPROPDWORD         dipdw;	
	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE;
	HR(m_keyboard->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph));	

	HR(m_keyboard->SetDataFormat(&c_dfDIKeyboard));
	HR(m_mouse->SetDataFormat(&c_dfDIMouse2));

	HR(m_keyboard->SetCooperativeLevel(hwnd, keyboardCoopFlags));
	HR(m_mouse->SetCooperativeLevel(hwnd, mouseCoopFlags));


	m_keyboard->Acquire();
	m_mouse->Acquire();

}



bool DirectInput::IsKeyDown(char key)
{
	return false;
}

bool DirectInput::IsMouseButtonDown(int button)
{
	return false;
}

