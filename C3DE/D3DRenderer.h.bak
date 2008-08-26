#ifndef D3DRENDERER_H
#define D3DRENDERER_H

#include "Renderer.h"
#include "WindowsApplicationWindow.h"
#include <d3dx9.h>
#include <windows.h>
#include "D3DCommonDefs.h"
#include "D3DImage.h"

//BOOK
struct VertexPos
{
	VertexPos():pos(0.0f, 0.0f, 0.0f){}
	VertexPos(float x, float y, float z):pos(x,y,z){}
	VertexPos(const D3DXVECTOR3 &v):pos(v){}

	D3DXVECTOR3 pos;
	static IDirect3DVertexDeclaration9 *Decl;
};

class D3DRenderer : public Renderer
{
public:
	D3DRenderer();
	~D3DRenderer();	
	bool Init(WindowsApplicationWindow *window);
	void Reset();
	void Clear();
	bool BeginRender();
	void EndRender();
	void RenderText(char *text);

	bool IsDeviceLost();

	void DrawSprite(Sprite *sprite);

	void DrawMesh(Mesh *mesh);

	void SetScreenMode(int newScreenMode);

	IDirect3DDevice9* GetDevice(){ return m_device;}
	
private:
	IDirect3DDevice9* m_device; 
	D3DPRESENT_PARAMETERS m_d3dpp;
	HINSTANCE m_hInstance;
	HWND m_mainWindow;
	bool m_windowed;
	ID3DXFont *m_font;
	ID3DXSprite *m_sprite;

	//BOOK

	void InitAllVertexDeclarations();
	void InitAllVertexDeclarations2(IDirect3DVertexDeclaration9 * a);
	void DestroyAllVertexDeclarations();
	void BuildVertexBuffer();
	void BuildIndexBuffer();
	void BuildProjMtx();
	void BuildViewMtx();
	
	IDirect3DVertexBuffer9 * m_vb;
	IDirect3DIndexBuffer9 * m_ib;
	float m_cameraRotationY;
	float m_cameraRadius;
	float m_cameraHeight;
	D3DXMATRIX m_view;
	D3DXMATRIX m_proj;



};
#endif


