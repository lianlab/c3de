#ifndef WINDOWS_APPLICATION_WINDOW_H
#define WINDOWS_APPLICATION_WINDOW_H

#include "ApplicationWindow.h"
#include <windows.h>

class WindowsApplicationWindow : public ApplicationWindow
{
public:
	WindowsApplicationWindow(HINSTANCE instance, HWND handle, int width, int height);
	~WindowsApplicationWindow();
	HINSTANCE getHInstance(){return m_hInstance;};
	HWND getHandle(){return m_handle;};
private:
	HINSTANCE m_hInstance;
	HWND m_handle;
};

#endif
