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
#include "Castle.h"
#include "LandscapeMesh.h"

#include "Text.h"
#include "Font.h"
#include "Grid.h"
#include "Ground.h"
#include "Skybox.h"
#include "C3DESkinnedMesh.h"
#include "C3DESkinnedMeshContainer.h"
#include "GameMesh.h"



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

	//for loading
	int m_loadedObjects;
	int m_totalObjects;

	void UpdateLoadingBar(int loadedObjects, int totalobjects);
	Application * m_application;

	D3DSprite *m_sprite;	

	int m_speed;
	int m_yspeed;

	float m_cameraRadius;
	float m_cameraRotation;
	float m_cameraHeight;

	float m_cameraHeightIncrease;

	int m_deltaTime;

	//Renderer *m_renderer;

	//testing
	Cube *m_testMesh;

	Cube *m_cube;


	Plane *m_plane;

	void UpdateInput(int deltaTime);
	

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

	int GetMeshIndex(Mesh*);

	
	//Mesh * m_sceneStaticObjectsMeshes;

	int *m_sceneStaticObjectsList;
	C3DETransform **m_sceneStaticObjectsTransforms;
	int m_sceneTotalObjects;
	

#if 1

	Text * m_text;
	Font *m_font;
	LandscapeMesh *m_castle;
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

	Ground *m_ground;
	Skybox *m_skyBox;

	D3DXVECTOR3 m_carDirection;

	BillboardMesh * m_billboard;

	int * m_hack;

	int m_physPosX;
	int m_physPosY;
	int m_physSpeedX;
	int m_physSpeedY;
	int m_gAcc;

	LandscapeMesh *t_house;

	Renderer *m_renderer;

	vector<Mesh *> *m_meshes;

	int m_character0UpdateTime;
	int m_spiderUpdateTime;

	C3DESkinnedMesh *m_characterMesh;	
	C3DESkinnedMeshContainer *m_characterContainer0;
	
	C3DESkinnedMesh *m_spiderMesh;
	C3DESkinnedMeshContainer *m_spiderContainer;

	

	int hack;
#endif	
};
#endif