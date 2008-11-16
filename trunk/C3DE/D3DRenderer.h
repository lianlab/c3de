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

#include "D3DMesh.h"
#include "Pivot.h"

/*
#include "SpecularLight.h"

*/

#if 1
#include <vector>
#include "PerVertexLighting.h"
#include "Cube.h"
#endif
#include "FX.h"
#include "ShadowFX.h"

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
	void DrawMesh(Mesh *mesh, FX *fx);
	//void DrawMesh(Mesh *mesh, ID3DXEffect * effect);

	void DrawScene(Scene *scene);

	void SetScreenMode(int newScreenMode);

	IDirect3DDevice9* GetDevice(){ return m_device;}

	void DrawMirror(Mirror *mirror, Scene *scene);
	void DrawShadowSurface(ShadowSurface *shadowSurface, Scene *scene);
	void EnableAlphaBlending(bool enable);
	

	void CreateMeshBuffers(D3DMesh *mesh);

	void DrawPivot(Pivot *pivot);

	void fleps(Mesh *mesh);

	
	//void InitializeScene(Scene *scene);

private:
	IDirect3DDevice9* m_device; 
	D3DPRESENT_PARAMETERS m_d3dpp;
	HINSTANCE m_hInstance;
	HWND m_mainWindow;
	
	ID3DXFont *m_font;
	ID3DXSprite *m_sprite;

	void BuildProjMtx();
	
	D3DXMATRIX m_proj;	

	Pivot *m_pivot;

	ShadowFX *m_shadowEffect;

	void DrawXMesh(D3DMesh * a_xMesh);



};


#endif
