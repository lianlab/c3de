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


#include "D3DSkinnedMesh.h"
#include "FX.h"
#include "ShadowFX.h"

//#define HACK_FROM_SCRATCH 1
#include "CommonDefs.h"


#if HACK_FROM_SCRATCH
	struct VertexPosHACK
	{
		VertexPosHACK():pos(0.0f, 0.0f, 0.0f){}
		VertexPosHACK(float x, float y, float z):pos(x,y,z){}
		VertexPosHACK(const D3DXVECTOR3& v):pos(v){}

		D3DXVECTOR3 pos;
		static IDirect3DVertexDeclaration9* Decl;
	};
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
	void DrawMesh(Mesh *mesh, FX *fx);
	//void DrawMesh(Mesh *mesh, ID3DXEffect * effect);

	void DrawScene(Scene *scene);

	void SetScreenMode(int newScreenMode);

	//IDirect3DDevice9* GetDevice(){ return m_device;}

	static IDirect3DDevice9* GetDevice(){return m_device;}

	void DrawMirror(Mirror *mirror, Scene *scene);
	void DrawShadowSurface(ShadowSurface *shadowSurface, Scene *scene);
	void EnableAlphaBlending(bool enable);
	

	void CreateMeshBuffers(D3DMesh *mesh);

	void DrawAxis();

	

private:
	static IDirect3DDevice9* m_device; 
	D3DPRESENT_PARAMETERS m_d3dpp;
	HINSTANCE m_hInstance;
	HWND m_mainWindow;
	
	ID3DXFont *m_font;
	ID3DXSprite *m_sprite;

	void BuildProjMtx();
	
	D3DXMATRIX m_proj;	

	ShadowFX *m_shadowEffect;

	void DrawXMesh(D3DMesh * a_xMesh);

	void CreateAxis();

	IDirect3DVertexBuffer9 * m_axisBuffer;
	IDirect3DVertexDeclaration9 *m_axisDeclaration;


#if HACK_FROM_SCRATCH
	IDirect3DVertexBuffer9* mVB;
	IDirect3DIndexBuffer9*  mIB;
	

	void buildIndexBuffer();
	void buildVertexBuffer();
	void buildProjMatrix();
	void buildViewMtx();

	D3DXMATRIX mView;
	D3DXMATRIX mProj;

	float mCameraRotationY;
	float mCameraRadius;
	float mCameraHeight;

	
#endif

	

};


#endif
