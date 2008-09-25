#ifndef D3DRENDERER_H
#define D3DRENDERER_H

#include "Renderer.h"
#include "WindowsApplicationWindow.h"
#include <d3dx9.h>
#include <windows.h>
#include "D3DCommonDefs.h"
#include "D3DImage.h"
#include "D3DCamera.h"
#include "D3DScene.h"

#if 1
#include "SpecularLight.h"
#endif

class D3DRenderer : public Renderer
{
public:
	D3DRenderer();
	~D3DRenderer();	
	bool Init(WindowsApplicationWindow *window, bool windowed);
	void Reset();
	void Clear();
	bool BeginRender();
	void EndRender();
	void RenderText(char *text);

	bool IsDeviceLost();

	void DrawSprite(Sprite *sprite);

	void DrawMesh(Mesh *mesh);//{DrawMesh(mesh,NULL);}
	//void DrawMesh(Mesh *mesh, ID3DXEffect * effect);

	void DrawScene(Scene *scene);

	void SetScreenMode(int newScreenMode);

	IDirect3DDevice9* GetDevice(){ return m_device;}
	
private:
	IDirect3DDevice9* m_device; 
	D3DPRESENT_PARAMETERS m_d3dpp;
	HINSTANCE m_hInstance;
	HWND m_mainWindow;
	
	ID3DXFont *m_font;
	ID3DXSprite *m_sprite;

	void BuildProjMtx();
	
	D3DXMATRIX m_proj;

	//sets all shader handlers relative to a specific mesh's material for every drawScene pass
	void SetMeshMaterialShaderHandlers(Scene *scene, Mesh *mesh);
	//sets all shader handlers for every drawScene pass
	void SetSceneStepShaderHandlers(Scene *scene);

};
#endif


