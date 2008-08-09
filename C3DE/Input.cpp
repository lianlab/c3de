#include "Input.h"
#include "DebugMemory.h"

Input::Input()
{
	m_keyboardListeners = new vector<KeyboardListener *>;
	m_mouseListeners = new vector<MouseListener *>;
}

Input::~Input()
{
	delete m_keyboardListeners;
	delete m_mouseListeners;
}

void Input::AddMouseListener(MouseListener *listener)
{
	m_mouseListeners->push_back(listener);
}

void Input::RemoveMouseListener(MouseListener *a_listener)
{
	MouseListener *listener;
	for(unsigned int i = 0; i < m_mouseListeners->size(); i++)
	{
		listener = m_mouseListeners->at(i);
		if(listener == a_listener)
		{
			//m_listeners.erase(str_Vector.begin()+i,str_Vector.begin()+2);
			m_mouseListeners->erase(m_mouseListeners->begin() + i);
		}
	}
	
}

void Input::AddKeyboardListener(KeyboardListener *listener)
{
	m_keyboardListeners->push_back(listener);
}

void Input::RemoveKeyboardListener(KeyboardListener *a_listener)
{
	KeyboardListener *listener;
	for(unsigned int i = 0; i < m_keyboardListeners->size(); i++)
	{
		listener = m_keyboardListeners->at(i);
		if(listener == a_listener)
		{
			//m_listeners.erase(str_Vector.begin()+i,str_Vector.begin()+2);
			m_keyboardListeners->erase(m_keyboardListeners->begin() + i);
		}
	}
	
}