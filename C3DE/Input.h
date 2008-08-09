#ifndef INPUT_H
#define INPUT_H

#include "MouseListener.h"
#include "KeyboardListener.h"
#include <vector>

using namespace std;

class Input
{
public:
	Input();
	virtual ~Input();
	virtual void Update() = 0;
	virtual void Init(){};
	virtual bool IsKeyDown(char key) = 0;
	virtual bool IsMouseButtonDown(int button) = 0;
	float GetMouseDX() { return m_mouseDX;}
	float GetMouseDY() { return m_mouseDY;}
	float GetMouseDZ() { return m_mouseDZ;}
	void AddMouseListener(MouseListener *listener);
	void RemoveMouseListener(MouseListener *listener);
	void AddKeyboardListener(KeyboardListener *listener);
	void RemoveKeyboardListener(KeyboardListener *listener);


protected:
	float m_mouseDX;
	float m_mouseDY;
	float m_mouseDZ;
	vector<KeyboardListener *> *m_keyboardListeners;
	vector<MouseListener *> *m_mouseListeners;
};
#endif