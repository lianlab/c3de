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


#include "SpecularLight.h"

#if 1

#include "AmbientLight.h"
#include "DiffuseLight.h"
#include "SpecularLight.h"
#include "PointLight.h"
#include "Material.h"
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

	void EnableAlphaBlending();
	void DisableAlphaBlending();

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

	/*
	void SetMeshLights(Scene * scene, Mesh *d3dmesh);

	void SetMeshWorldHandlers(Scene *scene, Mesh *d3dmesh);

	*/
	
#if 0
	void hackTheKasbah();
	void group1();
	void group2();
	void group3();


	ID3DXEffect * m_effect;

	D3DXHANDLE m_shaderWorldMatrix;//gWorld R
	D3DXHANDLE m_shaderWorldInverseTransposeMatrix;//gWorldInverseTranspose R
	D3DXHANDLE m_shaderEyePosition;//gEyePosW R
	D3DXHANDLE m_shaderViewMatrix;//gWVP	R
	D3DXHANDLE m_shaderTransformMatrix;//gSpotPower
	D3DXHANDLE m_shaderTechnique; //R

	D3DXHANDLE m_shaderAmbientLightMaterial;//gAmbientLigh
	D3DXHANDLE m_shaderDiffuseLightMaterial;//gDiffuseLight
	D3DXHANDLE m_shaderSpecularLightMaterial;//gSpecularLight
	D3DXHANDLE m_shaderLightPosition;//gLightPosW R
	D3DXHANDLE m_shaderLightDirection;//gLightDirW R
	D3DXHANDLE m_shaderLightAttenuation;//gAttenuation012
	D3DXHANDLE m_shaderSpotLightPower;//gSpotPower



	D3DXHANDLE m_shaderObjectAmbientMaterial;//gAmbientMtrl
	D3DXHANDLE m_shaderObjectDiffuseMaterial;//gDiffuseMtrl
	D3DXHANDLE m_shaderObjectSpecularMaterial;//gSpecMtrl
	D3DXHANDLE m_shaderSpecularLightPower;//gSpecPower

	D3DXHANDLE m_hTex;//gSpecPower

	AmbientLight * t_ambientLight;
	DiffuseLight * t_diffuseLight;
	SpecularLight *t_specularLight;
	D3DXVECTOR3 *t_lightAttenuation;
	PointLight *t_pointLight;

	Material *m_material;
#endif

};


#endif
