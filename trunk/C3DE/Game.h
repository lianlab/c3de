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
#include "btBulletDynamicsCommon.h"
#include "BulletCollision/CollisionDispatch/btGhostObject.h"
#include "BulletDynamics/Character/btKinematicCharacterController.h"
#include "LandscapeWall.h"
#include "Tree0.h"
#include "Tree1.h"
#include "Tree2.h"
#include "Tree3.h"



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

private:

	btDynamicsWorld *m_physicsWorld;

	vector<btRigidBody*> *m_rigidBodies;
	vector<btVector3*> *m_rigidBodiesSizes;


	//for loading
	int m_loadedObjects;
	int m_totalObjects;

	void UpdateLoadingBar(int loadedObjects, int totalobjects);
	Application * m_application;

	//D3DSprite *m_sprite;

	

	
	float m_cameraRadius;
	float m_cameraRotation;
	float m_cameraHeight;

	float m_cameraHeightIncrease;

	int m_deltaTime;

	void UpdateInput(int deltaTime);	

	DirectInput *m_inputer;

	void CreateMeshBuffers(D3DMesh *mesh);
	void InitializeMeshes();

	DefaultScene1 *m_testScene;

	int GetMeshIndex(Mesh*);

	int *m_sceneStaticObjectsList;
	C3DETransform **m_sceneStaticObjectsTransforms;
	int m_sceneTotalObjects;


	Text * m_text;
	Font *m_font;
	

	float m_camX;
	float m_camY;
	float m_camZ;

	float m_camTargetX;
	float m_camTargetY;
	float m_camTargetZ;

	float m_camUpX;
	float m_camUpY;
	float m_camUpZ;

	//float m_camRadius;

	//float m_camYRotation;
	//float m_camZRotation;


	Ground *m_ground;
	Skybox *m_skyBox;	

	Renderer *m_renderer;

	vector<Mesh *> *m_meshes;

	int m_character0UpdateTime;
	int m_spiderUpdateTime;
	int m_dogUpdateTime;
	int m_ninjaUpdateTime;

	C3DESkinnedMesh *m_characterMesh;	
	C3DESkinnedMeshContainer *m_characterContainer0;
	
	C3DESkinnedMesh *m_spiderMesh;
	C3DESkinnedMeshContainer *m_spiderContainer;

	C3DESkinnedMesh *m_dogMesh;
	C3DESkinnedMeshContainer *m_dogContainer;

	C3DESkinnedMesh *m_ninjaMesh;
	C3DESkinnedMeshContainer *m_ninjaContainer;



	btTransform *m_characterPhysicsTransform;

	float m_capsuleHeight;
	float m_capsuleWidth;

	D3DXVECTOR3 m_characterAABBMin;
	D3DXVECTOR3 m_characterAABBMax;

	

	static const float m_camDistanceToCharacter;

	static const float m_camAngle;
	float m_camAngleSin;
	float m_camAngleCos;

	static const float m_camYOffsetToCharacter;
	static const float m_camZOffsetToCharacter;

	void RenderTest(Renderer *renderer);

	Cube * m_cube;



	btCollisionShape* m_groundShape;
	btPairCachingGhostObject* m_characterGhost;
	btKinematicCharacterController *m_character;

	LandscapeWall *m_wall1;
	LandscapeWall *m_wall2;
	LandscapeWall *m_wall3;

	Tree0 * m_tree0;
	Tree1 * m_tree1;
	Tree2 * m_tree2;
	Tree3 * m_tree3;

	float m_characterCurrentRotation;

};

#endif