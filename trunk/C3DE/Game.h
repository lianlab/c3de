#ifndef GAME_H
#define GAME_H

#include "KeyboardListener.h"
#include "MouseListener.h"
#include "Application.h"
#include "ResourceManager.h"
#include "D3DImage.h"
#include "D3DSprite.h"
//#include <d3dx9.h>
#include "Button.h"
#include "DirectInput.h"
#include "PlanarMirror.h"

#include "Wall.h"
#include "Pivot.h"



//testing
#include "DefaultScene1.h"
#include "Cube.h"
#include "Cube2.h"
#include "Plane.h"
#include "PlanarShadowSurface.h"
#include "Dwarf.h"
#include "SkinnedCube.h"
#include "D3DSkinnedMesh.h"
#include "WomanMesh.h"
#include "VideoMesh.h"
#include "Billboard.h"
#include "CubeMovie.h"
#include "BillboardMesh.h"



#include "Grid.h"

class Game : public KeyboardListener, MouseListener, ButtonListener
{
public:
	Game(Application * app);
	~Game();
	void Update(int deltaTime);
	void Render(Renderer *renderer);

	void OnKeyDown(int key);
	void OnKeyUp(int key);

	void OnMouseDown(int button, int x, int y);
	void OnMouseUp(int button, int x, int y);
	void OnMouseMove(int x, int y, int dx, int dy);
	
	void SetInputer(DirectInput *inputer);

	void OnButtonDown(Button *button);
	void OnButtonUp(Button *button);
	void OnButtonOver(Button * button);
	
	int hx;
	int hy;
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

	Renderer *m_renderer;

	//testing
	Cube *m_testMesh;

	Cube *m_cube;


	Plane *m_plane;

	void UpdateInput();
	

	Pivot *m_pivot;
	Grid *m_grid;

	PlanarMirror *m_mirror;

	Wall *m_wall;

	PlanarShadowSurface *m_shadowSurface;


	Dwarf *m_dwarf;


	Button *m_button;

	DirectInput *m_inputer;

	void CreateMeshBuffers(D3DMesh *mesh);
	void InitializeMeshes();

	DefaultScene1 *m_testScene;
	//SkinnedCube *m_skinnedCube;

	WomanMesh *m_skinMesh;

#if 1
	float m_camX;
	float m_camY;
	float m_camZ;

	float m_camTargetX;
	float m_camTargetY;
	float m_camTargetZ;

	float m_camUpX;
	float m_camUpY;
	float m_camUpZ;

	float m_camRadius;

	float m_camYRotation;
	float m_camZRotation;

	D3DXVECTOR3 m_dir;

	Terrain* m_auei;

	Billboard *m_videoMesh;

	CubeMovie *m_cubeMovie;

	float m_cubeX;
	float m_cubeY;
	float m_cubeZ;

	WomanMesh *m_woman;

	D3DXVECTOR3 m_carDirection;

	BillboardMesh * m_billboard;

	int * m_hack;

	int m_physPosX;
	int m_physPosY;
	int m_physSpeedX;
	int m_physSpeedY;
	int m_gAcc;

	int hack;
#endif	
};
#endif