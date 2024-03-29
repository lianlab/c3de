#ifndef RENDERER_H
#define RENDERER_H

#include "ApplicationWindow.h"
#include <stdlib.h>
#include <vector>
#include "RendererListener.h"
#include "Sprite.h"
#include "Mesh.h"
#include "Camera.h"
#include "Scene.h"

#define SCREEN_MODE_FULL 1
#define SCREEN_MODE_WINDOWED 2

using namespace std;

class Renderer
{
public:
	Renderer();
	virtual ~Renderer();
	virtual bool Init(ApplicationWindow *window){return true;};
	virtual void Reset() = 0;	
	virtual void Clear() = 0;
	virtual bool BeginRender() = 0;
	virtual void EndRender() = 0;

	void AddListener(RendererListener *listener);

	virtual void SetScreenMode(int newScreenMode) = 0;
	
	virtual void RenderText(char *text) = 0;

	virtual bool IsDeviceLost() = 0;

	void RemoveListener(RendererListener *listener);

	virtual void DrawSprite(Sprite *sprite) = 0;
	virtual void DrawMesh(Mesh *mesh) = 0;
	virtual void DrawScene(Scene *scene) = 0;
	virtual void DrawScene2(Scene *scene) = 0;
	virtual void DrawScene3(Scene *scene) = 0;
	virtual void DrawBox(float minX, float imnY, float inZ, float maxX, float maxY, float maxZ, D3DXMATRIX transform) = 0;
	Camera * GetCamera(){return m_camera;}

	virtual void EnableAlphaBlending(){}
	virtual void DisableAlphaBlending(){}
	
protected:
	ApplicationWindow *m_window;
	int m_currentScreenMode;
	//RendererListener *m_listener;
	vector <RendererListener *> *m_listeners;
	Camera *m_camera;

	

};

#endif
