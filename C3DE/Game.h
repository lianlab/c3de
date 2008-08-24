#ifndef GAME_H
#define GAME_H

#include "KeyboardListener.h"
#include "MouseListener.h"
#include "Application.h"
#include "ResourceManager.h"
#include "D3DImage.h"
#include "D3DSprite.h"
//#include <d3dx9.h>

//testing
//#include "Cube.h"

class Game : public KeyboardListener, MouseListener
{
public:
	Game(Application * app);
	~Game();
	void Update(int deltaTime);
	void Render(Renderer *renderer);

	void OnKeyDown(int key);
	void OnKeyUp(int key);

	void OnMouseDown(int button);
	void OnMouseUp(int button);
	void OnMouseMove(int x, int y);
	void CreateTestMesh();
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

	//Renderer *m_renderer;

	//testing
	//Cube *m_testMesh;
	

};
#endif