#include "WindowsApplicationWindow.h"

WindowsApplicationWindow::WindowsApplicationWindow(HINSTANCE instance, HWND handle, int width, int height):ApplicationWindow(width,height)

{
	m_hInstance = instance;
	m_handle = handle;

}

WindowsApplicationWindow::~WindowsApplicationWindow()
{

}
