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


#include "SpecularLight.h"



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

	void DrawMirror(Mirror *mirror, Scene *scene);
	void EnableAlphaBlending();
	void DisableAlphaBlending();

	void CreateMeshBuffers(D3DMesh *mesh);

	void DrawPivot(Pivot *pivot);

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

#if 0
	void drawTeapot();
	ID3DXMesh*              mTeapot;
	IDirect3DTexture9*     mTeapotTex;
	ID3DXEffect* mFX;
	D3DXHANDLE   mhTech;
	D3DXHANDLE   mhWVP;
	D3DXHANDLE   mhWorldInvTrans;
	D3DXHANDLE   mhLightVecW;
	D3DXHANDLE   mhDiffuseMtrl;
	D3DXHANDLE   mhDiffuseLight;
	D3DXHANDLE   mhAmbientMtrl;
	D3DXHANDLE   mhAmbientLight;
	D3DXHANDLE   mhSpecularMtrl;
	D3DXHANDLE   mhSpecularLight;
	D3DXHANDLE   mhSpecularPower;
	D3DXHANDLE   mhEyePos;
	D3DXHANDLE   mhWorld;
	D3DXHANDLE   mhTex;
	D3DXMATRIX mTeapotWorld;
	D3DXMATRIX mView;
	D3DXMATRIX mProj;
	

	D3DXVECTOR3 mLightVecW;
	D3DXCOLOR   mAmbientLight;
	D3DXCOLOR   mDiffuseLight;
	D3DXCOLOR   mSpecularLight;

	void drawReflectedTeapot();

	void drawReflected(Scene *scene);
#endif

};


#endif
