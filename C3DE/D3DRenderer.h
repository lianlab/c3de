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
#include "Text.h"

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

enum
{
	EFFECT_PER_VERTEX_LIGHTING,
	EFFECT_SKINNED_MESH,
	EFFECT_WALL,
	EFFECT_TREE,
	EFFECT_TEXTURE_ONLY,
	EFFECT_MOVING_LIGHT,
	EFFECT_DIFFUSE_STATIC_LIGHT,
	EFFECT_AMBIENT_LIGHT,
	EFFECT_SPECULAR_LIGHT,
	TOTAL_EFFECTS
};
class D3DRenderer : public Renderer
{
public:
	
	~D3DRenderer();	
	bool Init(WindowsApplicationWindow *window, bool windowed);
	void Reset();
	void Clear();
	bool BeginRender();
	void EndRender();
	void RenderText(char *text);

	bool IsDeviceLost();

	void DrawText(Text *a_text);

	void DrawSprite(Sprite *sprite);

	void DrawMesh(Mesh *mesh);//{DrawMesh(mesh,NULL);}
	void DrawMesh(Mesh *mesh, FX *fx);
	//void DrawMesh(Mesh *mesh, ID3DXEffect * effect);

	void DrawScene(Scene *scene);
	void DrawScene2(Scene *scene);
	void DrawScene3(Scene *scene);

	void SetScreenMode(int newScreenMode);

	//IDirect3DDevice9* GetDevice(){ return m_device;}

	static IDirect3DDevice9* GetDevice(){return m_device;}

	void DrawMirror(Mirror *mirror, Scene *scene);
	void DrawShadowSurface(ShadowSurface *shadowSurface, Scene *scene);
	void EnableAlphaBlending(bool enable);
	

	void CreateMeshBuffers(D3DMesh *mesh);

	void DrawAxis();

	void GetPickingRay(const D3DXMATRIX *worldMatrix, D3DXVECTOR3 *pOutOrigin, D3DXVECTOR3 *pOutDir, int mouseX, int mouseY);

	bool IsMousePicked(D3DMesh *a_mesh, int mouseX, int mouseY);

	static D3DRenderer * GetInstance();

	void DrawLine(int aX, int aY, int bX, int bY, int color);
	void DrawRect(int x, int y, int w, int h, int color);
	void DrawFillRect(int x, int y, int w, int h, int color);

	void DrawBox(float minX, float minY, float minZ, float maxX, float maxY, float maxZ, D3DXMATRIX transform);
private:



	D3DRenderer();
	static D3DRenderer *m_instance;
	void DrawParticleSystem(ParticleSystem *a_particleSystem);
	void DrawTerrainSubMesh(D3DMesh * a_parentMesh, D3DMesh *t_subMesh);
	static IDirect3DDevice9* m_device; 
	D3DPRESENT_PARAMETERS m_d3dpp;
	HINSTANCE m_hInstance;
	HWND m_mainWindow;

	void DrawAABB(D3DMesh * a_mesh);
	
	void DrawOBB(D3DMesh * a_mesh, D3DXMATRIX a_matrix);
	
	ID3DXFont *m_font;
	ID3DXSprite *m_sprite;

	void BuildProjMtx();
	
	D3DXMATRIX m_proj;	

	ShadowFX *m_shadowEffect;

	void DrawXMesh(D3DMesh * a_xMesh);
	void DrawXMesh2(D3DMesh * a_xMesh, D3DXMATRIX *a_matrix);
	void DrawXMesh3(D3DMesh * a_xMesh, D3DXMATRIX *a_matrix,  int effect, Material * a_material);

	void ApplyEffect(int effect, D3DMesh * a_mesh, D3DXMATRIX *a_transform, int subset, Material * a_material);

	void CreateAxis();

	IDirect3DVertexBuffer9 * m_axisBuffer;
	IDirect3DVertexDeclaration9 *m_axisDeclaration;

	IDirect3DVertexBuffer9 * m_aabbBuffer;
	IDirect3DVertexDeclaration9 *m_aabbDeclaration;

	D3DXPLANE m_frustumPlane[6];

	void CalculateFrustumPlanes();

	bool IsAABBWithinView(D3DXMATRIX a_matrix,AABB *a_box);
	bool IsMeshWithinView(D3DMesh *a_mesh, D3DXMATRIX a_matrix);
	bool IsMeshWithinView(D3DMesh *a_mesh);

	
	bool IsPointWithinView(D3DXVECTOR3 aPoint);

	LPD3DXLINE lpLine;	
	D3DXVECTOR2 t_lineVertices[2];	


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

	void CreateAABB();

	int hidden;
	int shown;

	IDirect3DVertexBuffer9* mVB2;


};


#endif
