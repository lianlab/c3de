#ifndef GAME_H
#define GAME_H

#include "KeyboardListener.h"
#include "MouseListener.h"
#include "Application.h"
#include "ResourceManager.h"
#include "D3DImage.h"
#include "D3DSprite.h"
//#include <d3dx9.h>
#include "Button.h"
#include "DirectInput.h"


//testing
#include "Cube.h"

class Game : public KeyboardListener, MouseListener, ButtonListener
{
public:
	Game(Application * app);
	~Game();
	void Update(int deltaTime);
	void Render(Renderer *renderer);

	void OnKeyDown(int key);
	void OnKeyUp(int key);

	void OnMouseDown(int button, int x, int y);
	void OnMouseUp(int button, int x, int y);
	void OnMouseMove(int x, int y, int dx, int dy);
	void CreateTestMesh();
	void SetInputer(DirectInput *inputer);

	void OnButtonDown(Button *button);
	void OnButtonUp(Button *button);
	void OnButtonOver(Button * button);
	
	int hx;
	int hy;
private:
	Application * m_application;

	D3DSprite *m_sprite;	

	int m_speed;
	int m_yspeed;

	float m_cameraRadius;
	float m_cameraRotation;
	float m_cameraHeight;

	float m_cameraHeightIncrease;

	int m_deltaTime;

	Renderer *m_renderer;

	//testing
	Cube *m_testMesh;

	Button *m_button;

	DirectInput *m_inputer;

};
#endif