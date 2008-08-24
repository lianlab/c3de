#ifndef D3DAPPLICATION_H
#define D3DAPPLICATION_H

#include <windows.h>

#include "Application.h"
#include "D3DRenderer.h"
#include "DirectInput.h"
#include "KeyboardListener.h"
#include "MouseListener.h"
#include "D3DSprite.h"
#include "Game.h"


class D3DApplication : public Application
{
public:
	D3DApplication();
	~D3DApplication();

	bool Init(HINSTANCE hInstance, int width, int height, bool windowed);
	bool Update(int deltaTime);
	bool Render();
	bool Cleanup();
	bool Quit();
	void OnLostDevice();
	void OnResetDevice();

	void drawScene();


	
private:
	void SetupRenderer();
	void SetupWindow();
	HINSTANCE m_hInstance;
	HWND m_mainWindow;
	D3DRenderer *m_renderer;
	DirectInput *m_input;

	D3DImage * image;
	Game *m_game;	
	
};

#endif