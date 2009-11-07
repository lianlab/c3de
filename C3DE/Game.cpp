#include "Game.h"
#include "ShaderManager.h"
#include "D3DCamera.h"
#include "D3DRenderer.h"
#include "TerrainFactory.h"
#include "TerrainForest.h"
#include "DirectInput.h"
#include "Tree0.h"
#include "Tree1.h"
#include "Tree2.h"
#include "Tree3.h"
#include "Castle.h"
#include "Grass.h"
#include "GrassGrid.h"
#include "SupernovaParticleSystem.h"
#include "FireRingParticleSystem.h"
#include "Ground.h"
#include "LandscapeWall.h"


#include "Skybox.h"
#include "Font.h"
#include "Text.h"
#include "FXManager.h"
#include "C3DETransform.h"
#include "BufferReader.h"
#include <iostream>
#include "Physics.h"

//THIS CLASS CAN'T OVERRIDE THE NEW OPERATOR OR IT WILL SCREW UP PHYSICS
//#include "DebugMemory.h"

#define CONST_RATIO 8


using namespace std;



const float Game::m_camDistanceToCharacter = 19.699961f;
const float Game::m_camAngle = 0.18500003f;
const float Game::m_camYOffsetToCharacter = 5.5700326f;
const float Game::m_camZOffsetToCharacter = 0.0f;

#define BIT(x) (1<<(x))
enum collisiontypes 
{
	COL_NOTHING = 0, //<Collide with nothing
	COL_CHARACTER = BIT(1), //<Collide with character
	COL_OBJECTS = BIT(2), //<Collide with static objects
	
};
int characterCollidesWith = COL_OBJECTS;
int objectsCollidesWith = COL_NOTHING;


Game::Game(Application * app)
{
	m_characterCurrentRotation = 0.0f;
	m_tree0 = NULL;
	m_tree1 = NULL;
	m_tree2 = NULL;
	m_tree3 = NULL;

	m_wall1 = NULL;
	m_wall2 = NULL;
	m_wall2 = NULL;

	m_character0UpdateTime = 0;
	m_spiderUpdateTime = 0;
	m_dogUpdateTime = 0;
	m_ninjaUpdateTime = 0;
	int m_loadedObjects = 0;
	int m_totalObjects = 145;

	m_characterPhysicsTransform = new btTransform();

	


	m_application = app;

	IDirect3DTexture9 * t = ResourceManager::GetInstance()->GetTextureByID(IMAGE_EXPLOSION_ID);
	D3DImage *image = new D3DImage(t);				

	t = ResourceManager::GetInstance()->GetTextureByID(IMAGE_BUTTON_ID);
	D3DImage *image2 = new D3DImage(t);			
	//m_sprite = new D3DSprite(image, 64, 64, 30, 6, 5, 50);

	//m_sprite->SetX(50);
	//m_sprite->SetY(50);

	


	m_cameraRadius = 10.0f;
	m_cameraRotation = 1.2 * D3DX_PI;
	m_cameraHeight = 5.0f;

	m_cameraHeightIncrease = 0.0f;

	m_renderer = app->GetRenderer();

	vector<RECT> *frames = new vector<RECT>;
	RECT r;
	r.left = 0;
	r.right = 255;
	r.top = 0;
	r.bottom = 85;
	frames->push_back(r);
	r.left = 0;
	r.right = 256;
	r.top = 85;
	r.bottom = 170;
	frames->push_back(r);
	r.left = 0;
	r.right = 255;
	r.top = 170;
	r.bottom = 255;
	frames->push_back(r);

	
	r.left = 0;
	r.right = 256;
	r.top = 0;
	r.bottom = 85;

	m_camX = 0.0f;
	m_camY = 10.0f;
	m_camZ = -15.0f;
	

	m_camTargetX = 0.0f;
	m_camTargetY = 0.0f;
	m_camTargetZ = 0.0f;
	

	m_camUpX = 0.0f;
	m_camUpY = 1.0f;
	m_camUpZ = 0.0f;
		
	m_camAngleSin = sinf( m_camAngle  * (D3DX_PI * 2.0f));
	m_camAngleCos = cosf( m_camAngle  * (D3DX_PI * 2.0f));


	m_capsuleHeight = 1.75f;
	m_capsuleWidth = 1.75f;

	InitializeMeshes();

}

void Game::OnButtonDown(Button *down)
{
	int khgfd = 987;
}

void Game::OnButtonUp(Button *button)
{
	int otrte= 987;
}

void Game::OnButtonOver(Button *button)
{
	int hjsfs = 9874324;
}

void Game::SetInputer(DirectInput *inputer)
{
	m_inputer = inputer;
	//m_inputer->AddMouseListener((MouseListener*)m_button);
}

Game::~Game()
{
	delete m_testScene;	

	int totalMeshes = m_meshes->size();
	for(int i = 0; i< totalMeshes; i++)
	{
		Mesh *t_mesh = (*m_meshes)[i];
		delete t_mesh;
		t_mesh = NULL;
	}

	if(m_font)
	{
		delete m_font;
		m_font = NULL;
	}

	if(m_text)
	{
		delete m_text;
		m_text = NULL;
	}


	if(m_characterContainer0)
	{
		delete m_characterContainer0;
		m_characterContainer0 = 0;
	}



	for(int i = 0; i < m_sceneTotalObjects; i++)
	{
		delete m_sceneStaticObjectsTransforms[i];
		 m_sceneStaticObjectsTransforms[i] = NULL;
	}
	
	

	
}

void Game::UpdateLoadingBar(int loadedObjects, int totalobjects)
{
	D3DRenderer *t_renderer = (D3DRenderer*) m_renderer;
	t_renderer->Clear();
	t_renderer->BeginRender();

	int rectHeight = 50;
	int rectOffset = 20;
	int rectWidth = SCREEN_WIDTH - (rectOffset *2);
	int y = ( SCREEN_HEIGHT >> 1) - (rectHeight >> 1);

	t_renderer->DrawText(m_text);
	

	t_renderer->DrawFillRect(rectOffset, y, rectWidth, rectHeight, 0xffff0000);
	float percentage = (float)((float)loadedObjects / (float)totalobjects);
	t_renderer->DrawFillRect(rectOffset, y , (int)(rectWidth * percentage), rectHeight, 0xffffffff);		

	t_renderer->EndRender();
}

void Game::Update(int deltaTime)
{		
	
	m_physicsWorld->stepSimulation(deltaTime);

	m_character0UpdateTime += deltaTime;
	m_spiderUpdateTime += (deltaTime);
	m_dogUpdateTime += (deltaTime);
	m_ninjaUpdateTime += (deltaTime);

	
	int animationTime = m_characterContainer0->GetTotalAnimationTime();
	m_character0UpdateTime = m_character0UpdateTime % animationTime;

#if 0
	m_spiderUpdateTime = m_spiderUpdateTime % m_spiderContainer->GetTotalAnimationTime();
	m_dogUpdateTime = m_dogUpdateTime % m_dogContainer->GetTotalAnimationTime();
	m_ninjaUpdateTime = m_ninjaUpdateTime % m_ninjaContainer->GetTotalAnimationTime();
#endif

	

	m_characterContainer0->SetAnimationTime(m_character0UpdateTime);
	//m_characterContainer0->SetAnimationTime(0);
	

#if 0
	m_spiderContainer->SetAnimationTime(m_spiderUpdateTime);
	m_dogContainer->SetAnimationTime(m_dogUpdateTime);
	m_ninjaContainer->SetAnimationTime(m_ninjaUpdateTime);
#endif

	int totalObjects = m_testScene->GetMeshesVector()->size();
		
	UpdateInput(deltaTime);
		
	//m_sprite->Update(deltaTime);

	m_deltaTime = deltaTime;

	//m_testScene->Update(deltaTime);

}

void Game::UpdateInput(int deltaTime)
{

	float t_time = deltaTime / 1000.0f;

	float posMultiplier = 1.0f;
	float fastPosMultiplier = 2.0f;


	float rotMultiplier = 0.5f;
	float fastRotMultiplier = 2.0f;

	D3DXVECTOR3 t_walkDirectionVector(0.0f, 0.0f, 1.0f);
	D3DXVECTOR3 t_walkVector(0.0f, 0.0f, 0.0f);	

	if(DirectInput::GetInstance()->IsKeyDown(1))
	{
		m_application->Quit();
		return;		
	}

	if(DirectInput::GetInstance()->IsKeyDown(42))
	{
		//SHIFT
		posMultiplier *= fastPosMultiplier;
		rotMultiplier *= fastRotMultiplier;
	}				

	if(DirectInput::GetInstance()->IsKeyDown(200))	
	{	
		m_characterCurrentRotation = 0.75f;
		m_characterContainer0->SetCurrentAnimation(0);
		//UP
		t_walkVector += t_walkDirectionVector * posMultiplier;
	}
	else if(DirectInput::GetInstance()->IsKeyDown(208))
	{	
		m_characterContainer0->SetCurrentAnimation(8);
		//DOWN			
		t_walkVector -= t_walkDirectionVector * posMultiplier;
	}	
	else
	{
		m_characterCurrentRotation = 0.0f;
		m_characterContainer0->SetCurrentAnimation(9);
	}
	if(DirectInput::GetInstance()->IsKeyDown(205))
	{
		//RIGHT				
		btMatrix3x3 orn = m_characterGhost->getWorldTransform().getBasis();
		orn *= btMatrix3x3(btQuaternion(btVector3(0,1,0),(rotMultiplier * t_time)));
		m_characterGhost->getWorldTransform ().setBasis(orn);
		
	}
	if(DirectInput::GetInstance()->IsKeyDown(203))
	{
		//LEFT			
		btMatrix3x3 orn = m_characterGhost->getWorldTransform().getBasis();
		orn *= btMatrix3x3(btQuaternion(btVector3(0,1,0),-(rotMultiplier * t_time)));
		m_characterGhost->getWorldTransform ().setBasis(orn);
		
	}	

	D3DXMATRIX t_characterTransform = BT2DX_MATRIX(m_characterGhost->getWorldTransform());
	float t_characterPosX = t_characterTransform._41;
	float t_characterPosY = t_characterTransform._42;
	float t_characterPosZ = t_characterTransform._43;

	t_characterTransform._41 = 0.0f;
	t_characterTransform._42 = 0.0f;
	t_characterTransform._43 = 0.0f;

	D3DXVECTOR4 t_walkVector4;
	D3DXVec3Transform(&t_walkVector4, &t_walkVector, &t_characterTransform);

	D3DXVECTOR3 t_walkVector3(t_walkVector4.x, t_walkVector4.y, t_walkVector4.z);

	btVector3 t_bulletVector(t_walkVector3.x, t_walkVector3.y, t_walkVector3.z);

	m_character->setWalkDirection(t_bulletVector);

	t_characterTransform._41 = t_characterPosX;
	t_characterTransform._42 = t_characterPosY;
	t_characterTransform._43 = t_characterPosZ;

	float zLength = m_camZOffsetToCharacter + m_camAngleSin * m_camDistanceToCharacter;

	D3DXVECTOR4 t_camVector4;
	D3DXVECTOR3 t_camVector3(0.0f, 0.0f, -zLength);
	D3DXVec3Transform(&t_camVector4, &t_camVector3, &t_characterTransform);

	m_camTargetX = t_characterPosX;
	m_camTargetY = t_characterPosY + m_camYOffsetToCharacter;
	m_camTargetZ = t_characterPosZ + m_camZOffsetToCharacter;

	m_camY = t_characterPosY + (m_camYOffsetToCharacter) + m_camAngleCos * m_camDistanceToCharacter;
	m_camX = t_camVector4.x;
	m_camZ = t_camVector4.z;

}


#if 1
void Game::Render(Renderer *renderer)
{	
	
	D3DCamera * cam = (D3DCamera *)renderer->GetCamera();

	cam->SetPosition(m_camX, m_camY, m_camZ);
	cam->SetUp(m_camUpX, m_camUpY, m_camUpZ);	
	cam->SetTarget(m_camTargetX, m_camTargetY, m_camTargetZ);
	
	m_testScene->ClearAllNodes();

	C3DETransform *t0 = new C3DETransform();	
	SceneNode *t_node0 = new SceneNode(m_ground, t0, EFFECT_PER_VERTEX_LIGHTING);	
	m_testScene->AddNode(t_node0);	



	btTransform t_characterTransform = m_characterGhost->getWorldTransform();
	D3DXMATRIX t_characterTransform2 = BT2DX_MATRIX(t_characterTransform);


	C3DETransform *t2 = new C3DETransform();
	t2->Set(&t_characterTransform2);
	//

	D3DXMATRIX *t_matrix = t2->GetMatrix();
	float tx = t_matrix->_41;
	float ty = t_matrix->_42;
	float tz = t_matrix->_43;

	t_matrix->_41 = 0.0f;
	t_matrix->_42 = 0.0f;
	t_matrix->_43 = 0.0f;

	t2->Rotate(m_characterCurrentRotation, &D3DXVECTOR3(0.0f, 1.0f, 0.0));

	t_matrix->_41 = tx;
	t_matrix->_42 = ty;
	t_matrix->_43 = tz;

	t2->Translate(0.0f, -m_capsuleHeight, 0.0f);
	SceneNode *t_node2 = new SceneNode(m_characterContainer0, t2, EFFECT_SKINNED_MESH);
	m_testScene->AddNode(t_node2);	




	C3DETransform *t5 = new C3DETransform();	
	t5->Translate(m_camX, m_camY, m_camZ);
	SceneNode *t_node5 = new SceneNode(m_skyBox, t5, EFFECT_PER_VERTEX_LIGHTING);	
	m_testScene->AddNode(t_node5);


	for(int i = 0; i< m_sceneTotalObjects; i++)	
	{
		Mesh * t_mesh = (*m_meshes)[m_sceneStaticObjectsList[i]];
		C3DETransform *t_transform = new C3DETransform();	
		D3DXMATRIX *t_matrix = m_sceneStaticObjectsTransforms[i]->GetMatrix();		
		t_transform->Set(t_matrix);

		int effect = EFFECT_TEXTURE_ONLY;

		if(t_mesh == m_wall1 || t_mesh == m_wall2 || t_mesh == m_wall3)
		{
			effect = EFFECT_WALL;

		}
		else if(t_mesh == m_tree0 || t_mesh == m_tree1 || t_mesh == m_tree2 || t_mesh == m_tree3)
		{
			effect = EFFECT_TREE;

		}


		SceneNode *t_node = new SceneNode(t_mesh, t_transform, effect);
		m_testScene->AddNode(t_node);
		
	}	

		
	int totalBodies = m_rigidBodies->size();
#if 0
	for(int i = 0; i < totalBodies; i++)
	{
		btRigidBody *t_body = (*m_rigidBodies)[i];
		btMotionState *t_motionState = t_body->getMotionState();		

		D3DXMATRIX t_matrix = BT2DX_MATRIX(*t_motionState);		

		

		btVector3 *t_size = (*m_rigidBodiesSizes)[i];

		
		renderer->DrawBox(-t_size->getX(), -t_size->getY(), -t_size->getZ(), t_size->getX(), t_size->getY(), t_size->getZ(), t_matrix);
	}

	
	btTransform t_transform2 = m_characterGhost->getWorldTransform();
	
	D3DXMATRIX t_matrix2 = BT2DX_MATRIX(t_transform2);		

	
	renderer->DrawBox(	-1.75f / 2.0f, 
						-1.75f / 2.0f, 
						-1.75f / 2.0f, 
						1.75f / 2.0f, 
						1.75f / 2.0f, 
						1.75f / 2.0f, t_matrix2);
	
#endif


	
	renderer->DrawScene3(m_testScene);



}
#else
void Game::Render(Renderer *renderer)
{
	

	D3DCamera * cam = (D3DCamera *)renderer->GetCamera();

	cam->SetPosition(m_camX, m_camY, m_camZ);
	cam->SetUp(m_camUpX, m_camUpY, m_camUpZ);	
	cam->SetTarget(m_camTargetX, m_camTargetY, m_camTargetZ);
	
	m_testScene->ClearAllNodes();

	C3DETransform *t0 = new C3DETransform();	
	SceneNode *t_node0 = new SceneNode(m_ground, t0, EFFECT_PER_VERTEX_LIGHTING);	
	m_testScene->AddNode(t_node0);	



	btTransform t_characterTransform = m_characterGhost->getWorldTransform();
	D3DXMATRIX t_characterTransform2 = BT2DX_MATRIX(t_characterTransform);

#if 1
	C3DETransform *t2 = new C3DETransform();
	t2->Set(&t_characterTransform2);
	t2->Translate(0.0f, -m_capsuleHeight, 0.0f);
	SceneNode *t_node2 = new SceneNode(m_characterContainer0, t2, EFFECT_SKINNED_MESH);
	m_testScene->AddNode(t_node2);	
#endif

#if 0
	C3DETransform *t4 = new C3DETransform();
	t4->Rotate(3.1415 / 2.0f, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	t4->Translate(25.0f, 0.0f, 25.0f);
	SceneNode *t_node4 = new SceneNode(m_dogContainer, t4);	
	m_testScene->AddNode(t_node4);
#endif



	C3DETransform *t5 = new C3DETransform();	
	t5->Translate(m_camX, m_camY, m_camZ);
	SceneNode *t_node5 = new SceneNode(m_skyBox, t5, EFFECT_PER_VERTEX_LIGHTING);	
	m_testScene->AddNode(t_node5);

	

#if 1
	for(int i = 0; i< m_sceneTotalObjects; i++)	
	{
		Mesh * t_mesh = (*m_meshes)[m_sceneStaticObjectsList[i]];
		C3DETransform *t_transform = new C3DETransform();	
		D3DXMATRIX *t_matrix = m_sceneStaticObjectsTransforms[i]->GetMatrix();		
		t_transform->Set(t_matrix);

		int effect = EFFECT_PER_VERTEX_LIGHTING;

		if(t_mesh == m_wall1 || t_mesh == m_wall2 || t_mesh == m_wall3)
		{
			effect = EFFECT_WALL;

		}
		else if(t_mesh == m_tree0 || t_mesh == m_tree1 || t_mesh == m_tree2 || t_mesh == m_tree3)
		{
			effect = EFFECT_TREE;

		}


		SceneNode *t_node = new SceneNode(t_mesh, t_transform, effect);
		m_testScene->AddNode(t_node);
		
	}	
#endif

	int totalBodies = m_rigidBodies->size();
	
#if 0
	for(int i = 0; i < totalBodies; i++)
	{
		btRigidBody *t_body = (*m_rigidBodies)[i];
		btMotionState *t_motionState = t_body->getMotionState();		

		D3DXMATRIX t_matrix = BT2DX_MATRIX(*t_motionState);		

		

		btVector3 *t_size = (*m_rigidBodiesSizes)[i];

		
		renderer->DrawBox(-t_size->getX(), -t_size->getY(), -t_size->getZ(), t_size->getX(), t_size->getY(), t_size->getZ(), t_matrix);
	}

	
	btTransform t_transform2 = m_characterGhost->getWorldTransform();
	
	D3DXMATRIX t_matrix = BT2DX_MATRIX(t_transform2);		

	
	renderer->DrawBox(	-1.75f / 2.0f, 
						-1.75f / 2.0f, 
						-1.75f / 2.0f, 
						1.75f / 2.0f, 
						1.75f / 2.0f, 
						1.75f / 2.0f, t_matrix);
	
#endif
	//renderer->DrawScene2(m_testScene);
	renderer->DrawScene3(m_testScene);


	//renderer->DrawScene(m_testScene);
	//renderer->DrawSprite(m_button);
	//renderer->DrawSprite((Sprite *)m_sprite);



	//static_cast<D3DRenderer *>(renderer)->DrawText(m_text);
	//static_cast<D3DRenderer *>(renderer)->DrawAxis();
	

}
#endif
void Game::OnMouseDown(int button, int x , int y)
{

}

void Game::OnMouseUp(int button, int x, int y)
{
	int moueskfd = button;
	int clickedX = 999999;
	int clickedY = 999999;
}


void Game::OnMouseMove(int x, int y, int dx, int dy)
{				

}

void Game::OnKeyDown(int key)
{	
	
}


#define USE_X_MODELS 0
#define ADD_TEST_MESH 0

void Game::InitializeMeshes()
{	

	m_groundShape = new btStaticPlaneShape(btVector3(0,1,0),-0.5);


	btDefaultCollisionConfiguration *cc;
	cc = new btDefaultCollisionConfiguration();
	btConstraintSolver *sl;
	sl = new btSequentialImpulseConstraintSolver();

	btVector3 worldAabbMin(-1000, -1000, -1000);
	btVector3 worldAabbMax(1000, 1000, 1000);
	const int maxProxies = 32766;
	btBroadphaseInterface *bp;

	bp = new btAxisSweep3(worldAabbMin, worldAabbMax, maxProxies);

	btCollisionDispatcher *dp;
	dp = new btCollisionDispatcher(cc);

	m_physicsWorld = new btDiscreteDynamicsWorld(dp, bp, sl, cc);







	







	m_rigidBodiesSizes = new vector<btVector3*>;
	m_rigidBodies = new vector<btRigidBody*>;

	btVector3 *t_size = new btVector3(1.0f, 1.0f, 1.0f);

	btRigidBody *floor = new btRigidBody(0.0f, new btDefaultMotionState(), m_groundShape);
	m_physicsWorld->addRigidBody(floor);

	btVector3 *t_size2 = new btVector3(1.0f, 1.0f, 1.0f);

	m_totalObjects = 38;
	m_loadedObjects = 0;

	IDirect3DTexture9 * t = ResourceManager::GetInstance()->GetTextureByID(IMAGE_FONT_VERDANA_36_ID);
	D3DImage *image = new D3DImage(t);		
	m_font = new Font(	image,ResourceManager::GetInstance()->GetFontDescriptor(FONT_VERDANA_36_ID));

	m_text = new Text("Loading Meshes...", m_font);
	m_text->SetX(200);
	m_text->SetY(150);
	m_text->SetColor(0xff000000);
	

	m_testScene = new DefaultScene1();	
	Material *t_material = new Material(	D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),
										D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f), 16.0f);		
	

	
	m_ground = new Ground();
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	

	
	D3DImage * characterTexture = new D3DImage(ResourceManager::GetInstance()->GetTextureByID(IMAGE_SWIMMER_SKIN_ID));	
	
	vector<char*> *animations = new vector<char*>;

	animations->push_back(ResourceManager::GetInstance()->GetMeshBuffer(MESH_BUFFER_SWIMMER_BONES_COOL_ID));
#if 1
	animations->push_back(ResourceManager::GetInstance()->GetMeshBuffer(MESH_BUFFER_SWIMMER_BONES_CARRY_2_ID));
	animations->push_back(ResourceManager::GetInstance()->GetMeshBuffer(MESH_BUFFER_SWIMMER_BONES_CARRY_ID));
	animations->push_back(ResourceManager::GetInstance()->GetMeshBuffer(MESH_BUFFER_SWIMMER_BONES_FAST_WALK_ID));
	animations->push_back(ResourceManager::GetInstance()->GetMeshBuffer(MESH_BUFFER_SWIMMER_BONES_JUMP_KICK_ID));
	animations->push_back(ResourceManager::GetInstance()->GetMeshBuffer(MESH_BUFFER_SWIMMER_BONES_KNEE_KICK_ID));
	animations->push_back(ResourceManager::GetInstance()->GetMeshBuffer(MESH_BUFFER_SWIMMER_BONES_MOONWALK_ID));
	animations->push_back(ResourceManager::GetInstance()->GetMeshBuffer(MESH_BUFFER_SWIMMER_BONES_RUN_LOOP_ID));
	animations->push_back(ResourceManager::GetInstance()->GetMeshBuffer(MESH_BUFFER_SWIMMER_BONES_WALK_BACKWARD_ID));
	animations->push_back(ResourceManager::GetInstance()->GetMeshBuffer(MESH_BUFFER_SWIMMER_BONES_IDLE_ID));

#endif
	m_characterMesh = new C3DESkinnedMesh(	ResourceManager::GetInstance()->GetMeshBuffer(MESH_BUFFER_SWIMMER_ID),
											animations,
											characterTexture, 33);

	







	delete animations;
	animations = NULL;


	btVector3 characterPos(0.0f, 0.0f, 0.0f);
	btQuaternion characterRot(0.0f, 0.0f, 0.0f);
	btTransform characterTransform(characterRot, characterPos);
	

	m_characterGhost = new btPairCachingGhostObject();
	m_characterGhost->setWorldTransform(characterTransform);
	bp->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());
	//btScalar characterHeight= m_characterMesh->GetBoundingBox()->maxPoint.y - m_characterMesh->GetBoundingBox()->minPoint.y;
	//btScalar characterWidth = m_characterMesh->GetBoundingBox()->maxPoint.x - m_characterMesh->GetBoundingBox()->minPoint.x;
	btScalar characterHeight = m_capsuleHeight;
	btScalar characterWidth = m_capsuleWidth;
	btConvexShape* capsule = new btCapsuleShape(characterWidth,characterHeight);
	m_characterGhost->setCollisionShape (capsule);
	m_characterGhost->setCollisionFlags (btCollisionObject::CF_CHARACTER_OBJECT);

	btScalar stepHeight = btScalar(0.35);
	m_character = new btKinematicCharacterController (m_characterGhost,capsule,stepHeight);



	btQuaternion q(0.0f, 0.0f, 0.0f);
	btVector3 p(0.0f, 30.0f, 10.0f);
	btTransform startTrans(q,p);
	btMotionState * ms = new btDefaultMotionState(startTrans);

	btVector3 size(1.0f, 1.0f, 1.0f);
	btCollisionShape *cs = new btBoxShape(size);

	m_physicsWorld->addCollisionObject(m_characterGhost,btBroadphaseProxy::CharacterFilter, btBroadphaseProxy::StaticFilter|btBroadphaseProxy::DefaultFilter);

	m_physicsWorld->addAction(m_character);


	



	




#if 0

	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	D3DImage * spiderTexture = new D3DImage(ResourceManager::GetInstance()->GetTextureByID(IMAGE_SPIDER_ID));	
	m_spiderMesh = new C3DESkinnedMesh(	ResourceManager::GetInstance()->GetMeshBuffer(MESH_BUFFER_SPIDER_ID),
										ResourceManager::GetInstance()->GetMeshBuffer(MESH_BUFFER_SPIDER_BONES_ID),
										spiderTexture, 33);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	D3DImage * ninjaTexture = new D3DImage(ResourceManager::GetInstance()->GetTextureByID(IMAGE_NINJA_ID));	
	m_ninjaMesh = new C3DESkinnedMesh(	ResourceManager::GetInstance()->GetMeshBuffer(MESH_BUFFER_NINJA_ID),
										ResourceManager::GetInstance()->GetMeshBuffer(MESH_BUFFER_NINJA_BONES_ID),
										ninjaTexture, 66);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	D3DImage * dogTexture = new D3DImage(ResourceManager::GetInstance()->GetTextureByID(IMAGE_DOG_ID));	
	m_dogMesh = new C3DESkinnedMesh(	ResourceManager::GetInstance()->GetMeshBuffer(MESH_BUFFER_DOG_ID),
										ResourceManager::GetInstance()->GetMeshBuffer(MESH_BUFFER_DOG_BONES_ID),
										dogTexture, 33);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);
#endif

	m_tree0 = new Tree0();
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	m_tree1 = new Tree1();
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	m_tree2 = new Tree2();
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	m_tree3 = new Tree3();
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	m_wall1 = new LandscapeWall(IMAGE_BRICKS_ID);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	m_wall2 = new LandscapeWall(IMAGE_WALL_GRASS_ID);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	m_wall3 = new LandscapeWall(IMAGE_WALL_WOOD_ID);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

#if USE_X_MODELS
	LandscapeMesh *m_streetLight02 = new LandscapeMesh(MESH_STREET_LIGHT_02_ID,IMAGE_STREET_LIGHT_02_ID);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);
	
	LandscapeMesh *m_streetLight01 = new LandscapeMesh(MESH_STREET_LIGHT_01_ID,IMAGE_STREET_LIGHT_01_ID);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	LandscapeMesh *m_house5 = new LandscapeMesh(MESH_HOUSE_5_ID,IMAGE_HOUSE_5_ID);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	LandscapeMesh *m_house4 = new LandscapeMesh(MESH_HOUSE_4_ID,IMAGE_HOUSE_4_ID);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	LandscapeMesh *m_house3 = new LandscapeMesh(MESH_HOUSE_3_ID,IMAGE_HOUSE_3_ID);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	LandscapeMesh *m_house2 = new LandscapeMesh(MESH_HOUSE_2_ID,IMAGE_HOUSE_2_ID);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	LandscapeMesh *m_house = new LandscapeMesh(MESH_HOUSE_ID,IMAGE_HOUSE_ID);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	LandscapeMesh *m_bench = new LandscapeMesh(MESH_BENCH_ID,IMAGE_BENCH_ID);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	LandscapeMesh *m_sign3 = new LandscapeMesh(MESH_SIGN03_ID,IMAGE_SIGN03_ID);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	LandscapeMesh *m_sign2 = new LandscapeMesh(MESH_SIGN02_ID,IMAGE_SIGN02_ID);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	LandscapeMesh *m_sign = new LandscapeMesh(MESH_SIGN01_ID,IMAGE_SIGN01_ID);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	LandscapeMesh *m_sidewalkBarrier = new LandscapeMesh(MESH_SIDEWALK_BARRIER_ID,IMAGE_SIDEWALK_BARRIER_ID);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	LandscapeMesh *m_mailbox = new LandscapeMesh(MESH_MAILBOX01_ID,IMAGE_MAILBOX01_ID);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	LandscapeMesh *m_mailbox2 = new LandscapeMesh(MESH_MAILBOX02_ID,IMAGE_MAILBOX02_ID);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	LandscapeMesh *m_gardenBorder = new LandscapeMesh(MESH_GARDEN_BORDER_ID,IMAGE_GARDEN_BORDER_ID);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	LandscapeMesh *m_cafeTable = new LandscapeMesh(MESH_CAFE_TABLE_ID,IMAGE_CAFE_TABLE_ID);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	LandscapeMesh *m_parkingBarrier = new LandscapeMesh(MESH_PARKING_BARRIER_ID,IMAGE_PARKING_BARRIER_ID);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	LandscapeMesh *m_trafficCone = new LandscapeMesh(MESH_TRAFFIC_CONE_ID,IMAGE_TRAFFIC_CONE_ID);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);
#else
	GameMesh *m_streetLight02 = new GameMesh(MESH_BUFFER_STREET_LIGHT_02_ID,IMAGE_STREET_LIGHT_02_ID, false);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);
	
	GameMesh *m_streetLight01 = new GameMesh(MESH_BUFFER_STREET_LIGHT_01_ID,IMAGE_STREET_LIGHT_01_ID, false);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	GameMesh *m_house5 = new GameMesh(MESH_BUFFER_HOUSE_5_ID,IMAGE_HOUSE_5_ID);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	GameMesh *m_house4 = new GameMesh(MESH_BUFFER_HOUSE_4_ID,IMAGE_HOUSE_4_ID);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	GameMesh *m_house3 = new GameMesh(MESH_BUFFER_HOUSE_3_ID,IMAGE_HOUSE_3_ID);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	GameMesh *m_house2 = new GameMesh(MESH_BUFFER_HOUSE_2_ID,IMAGE_HOUSE_2_ID);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	GameMesh *m_house = new GameMesh(MESH_BUFFER_HOUSE_ID,IMAGE_HOUSE_ID);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	GameMesh *m_house0 = new GameMesh(MESH_BUFFER_HOUSE_0_ID,IMAGE_HOUSE_0_ID);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	GameMesh *m_house1 = new GameMesh(MESH_BUFFER_HOUSE_1_ID,IMAGE_STORAGE_ID);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	GameMesh *m_bench = new GameMesh(MESH_BUFFER_BENCH_ID,IMAGE_BENCH_ID);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	GameMesh *m_sign3 = new GameMesh(MESH_BUFFER_SIGN03_ID,IMAGE_SIGN03_ID);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	GameMesh *m_sign2 = new GameMesh(MESH_BUFFER_SIGN02_ID,IMAGE_SIGN02_ID);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	GameMesh *m_sign = new GameMesh(MESH_BUFFER_SIGN01_ID,IMAGE_SIGN01_ID);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	GameMesh *m_sidewalkBarrier = new GameMesh(MESH_BUFFER_SIDEWALK_BARRIER_ID,IMAGE_SIDEWALK_BARRIER_ID);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	GameMesh *m_mailbox = new GameMesh(MESH_BUFFER_MAILBOX01_ID,IMAGE_MAILBOX01_ID);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	GameMesh *m_mailbox2 = new GameMesh(MESH_BUFFER_MAILBOX02_ID,IMAGE_MAILBOX02_ID);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	GameMesh *m_gardenBorder = new GameMesh(MESH_BUFFER_GARDEN_BORDER_ID,IMAGE_GARDEN_BORDER_ID);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	GameMesh *m_cafeTable = new GameMesh(MESH_BUFFER_CAFE_TABLE_ID,IMAGE_CAFE_TABLE_ID, false);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	GameMesh *m_parkingBarrier = new GameMesh(MESH_BUFFER_PARKING_BARRIER_ID,IMAGE_PARKING_BARRIER_ID);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	GameMesh *m_trafficCone = new GameMesh(MESH_BUFFER_TRAFFIC_CONE_ID,IMAGE_TRAFFIC_CONE_ID);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	GameMesh *m_lowHouse1Main = new GameMesh(MESH_BUFFER_LOW_HOUSE_1_MAIN_ID,IMAGE_LOW_HOUSE_1_MAIN_ID);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	GameMesh *m_lowHouse1Roof = new GameMesh(MESH_BUFFER_LOW_HOUSE_1_ROOF_ID,IMAGE_LOW_HOUSE_1_ROOF_ID);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	GameMesh *m_lowHouse1Garage = new GameMesh(MESH_BUFFER_LOW_HOUSE_1_GARAGE_ID,IMAGE_LOW_HOUSE_1_GARAGE_ID);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	GameMesh *m_lowHouse0 = new GameMesh(MESH_BUFFER_LOW_HOUSE_0_ID,IMAGE_LOW_HOUSE_0_ID);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	GameMesh *m_test = new GameMesh(MESH_BUFFER_TEST_ID,IMAGE_TEST_ID);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);


	
#endif
	m_skyBox = new Skybox(1000);	
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);
	
	m_testScene->Initialize();

	m_meshes = new vector<Mesh*>;
	m_meshes->push_back(m_characterMesh);
	//m_meshes->push_back(NULL);
	m_meshes->push_back(m_ground);
	m_meshes->push_back(m_skyBox);
	m_meshes->push_back(m_tree0);
	m_meshes->push_back(m_tree1);
	m_meshes->push_back(m_tree2);
	m_meshes->push_back(m_tree3);
	m_meshes->push_back(m_wall1);
	m_meshes->push_back(m_wall2);
	m_meshes->push_back(m_wall3);
	m_meshes->push_back(m_streetLight01);
	m_meshes->push_back(m_streetLight02);
	m_meshes->push_back(m_house);
	m_meshes->push_back(m_house2);
	m_meshes->push_back(m_house3);
	m_meshes->push_back(m_house4);
	m_meshes->push_back(m_house5);
	m_meshes->push_back(m_house0);
	m_meshes->push_back(m_house1);
	m_meshes->push_back(m_bench);
	m_meshes->push_back(m_sign);
	m_meshes->push_back(m_sign2);
	m_meshes->push_back(m_sign3);
	m_meshes->push_back(m_sidewalkBarrier);
	m_meshes->push_back(m_mailbox);
	m_meshes->push_back(m_mailbox2);
	m_meshes->push_back(m_gardenBorder);
	m_meshes->push_back(m_cafeTable);
	m_meshes->push_back(m_parkingBarrier);
	m_meshes->push_back(m_trafficCone);	
	m_meshes->push_back(m_lowHouse1Main);	
	m_meshes->push_back(m_lowHouse1Roof);	
	m_meshes->push_back(m_lowHouse1Garage);	
	m_meshes->push_back(m_lowHouse0);	
	m_meshes->push_back(m_test);	
	

	//#include "C:\documents and Settings\csabino\Desktop\exportedMeshes\outWorld.c3d"
	BufferReader *t_scene = new BufferReader(ResourceManager::GetInstance()->GetSceneBuffer(SCENE_BUFFER_SCENE_0_ID));

#if ADD_TEST_MESH
	m_sceneTotalObjects = t_scene->ReadNextInt() + 1;	
#else
	m_sceneTotalObjects = t_scene->ReadNextInt();	
#endif
	
	m_sceneStaticObjectsList = (int*)malloc(sizeof(int) * (m_sceneTotalObjects));
	m_sceneStaticObjectsTransforms = (C3DETransform**)malloc(sizeof(C3DETransform) * (m_sceneTotalObjects));
	D3DXMATRIX *t_matrix = new D3DXMATRIX();

#if ADD_TEST_MESH
	for(int i = 0; i < m_sceneTotalObjects - 1; i++)
#else
	for(int i = 0; i < m_sceneTotalObjects; i++)
#endif	
	{
		m_sceneStaticObjectsList[i] = t_scene->ReadNextInt();
		m_sceneStaticObjectsTransforms[i] = new C3DETransform();
				
		t_matrix->_11 = t_scene->ReadNextFloat();
		t_matrix->_12 = t_scene->ReadNextFloat();
		t_matrix->_13 = t_scene->ReadNextFloat();
		t_matrix->_14 = t_scene->ReadNextFloat();
		t_matrix->_21 = t_scene->ReadNextFloat();
		t_matrix->_22 = t_scene->ReadNextFloat();
		t_matrix->_23 = t_scene->ReadNextFloat();
		t_matrix->_24 = t_scene->ReadNextFloat();
		t_matrix->_31 = t_scene->ReadNextFloat();
		t_matrix->_32 = t_scene->ReadNextFloat();
		t_matrix->_33 = t_scene->ReadNextFloat();
		t_matrix->_34 = t_scene->ReadNextFloat();
		t_matrix->_41 = t_scene->ReadNextFloat();
		t_matrix->_42 = t_scene->ReadNextFloat();
		//t_matrix->_42 = 0.0f;
		t_matrix->_43 = t_scene->ReadNextFloat();
		t_matrix->_44 = t_scene->ReadNextFloat();
		m_sceneStaticObjectsTransforms[i]->Set(t_matrix);

		float scaleX = t_scene->ReadNextFloat();
		float scaleY = t_scene->ReadNextFloat();
		float scaleZ = t_scene->ReadNextFloat();

		float rotX = t_scene->ReadNextFloat();
		float rotY = t_scene->ReadNextFloat();
		float rotZ = t_scene->ReadNextFloat();




		D3DMesh *t_mesh = (D3DMesh*)(*m_meshes)[m_sceneStaticObjectsList[i]];
		AABB *t_aabb = t_mesh->GetBoundingBox();
		D3DXVECTOR3 t_sizeVector = (t_aabb->maxPoint - t_aabb->minPoint) * 0.5f;
		
		t_sizeVector.x *= scaleX;		
		t_sizeVector.y *= scaleY;		
		t_sizeVector.z *= scaleZ;

		btQuaternion rotation(rotY, rotX, rotZ);
		btVector3 position(t_matrix->_41, t_matrix->_42 + t_sizeVector.y, t_matrix->_43);
		btTransform transform(rotation, position);
		btMotionState * motionState = new btDefaultMotionState(transform);

		btVector3 colliderSize(t_sizeVector.x, t_sizeVector.y,t_sizeVector.z);
		btVector3 *t_size = new btVector3(t_sizeVector.x, t_sizeVector.y,t_sizeVector.z);

		m_rigidBodiesSizes->push_back(t_size);
		btCollisionShape *collisionShape = new btBoxShape(colliderSize);

		float objectMass = 0.0f;
		btVector3 objectLocalInertia(0,0,0);
		//btRigidBody *objectBody  = new btRigidBody(objectMass, motionState,collisionShape, objectLocalInertia);
		btRigidBody::btRigidBodyConstructionInfo cInfo(objectMass,motionState,collisionShape,objectLocalInertia);
		
		btRigidBody *objectBody  = new btRigidBody(cInfo);
		m_physicsWorld->addRigidBody(objectBody);
		m_rigidBodies->push_back(objectBody);

	}	

#if ADD_TEST_MESH
	m_sceneStaticObjectsList[m_sceneTotalObjects-1] = GetMeshIndex(m_test);
	m_sceneStaticObjectsTransforms[m_sceneTotalObjects-1] = new C3DETransform();
#endif			

	
	//FXManager::GetInstance()->AddMeshesEffects(m_testScene, m_meshes);

	FXManager::GetInstance()->AddEffect2(m_testScene, ShaderManager::GetInstance()->GetFXByID(SHADER_TEXTURE_ONLY_ID));
	FXManager::GetInstance()->AddEffect2(m_testScene, ShaderManager::GetInstance()->GetFXByID(SHADER_C3DE_SKINNED_MESH_FX_ID));
	FXManager::GetInstance()->AddEffect2(m_testScene, ShaderManager::GetInstance()->GetFXByID(SHADER_LIGHTS_PER_VERTEX_TEXTURES_WALL_NO_FOG_ID));
	FXManager::GetInstance()->AddEffect2(m_testScene, ShaderManager::GetInstance()->GetFXByID(SHADER_LIGHTS_PER_VERTEX_TEXTURES_NO_FOG_ID));

	m_characterContainer0 = new C3DESkinnedMeshContainer(m_characterMesh);
	
	m_characterContainer0->SetCurrentAnimation(9);

	
#if 0
	m_spiderContainer = new C3DESkinnedMeshContainer(m_spiderMesh);
	m_dogContainer = new C3DESkinnedMeshContainer(m_dogMesh);
	m_ninjaContainer = new C3DESkinnedMeshContainer(m_ninjaMesh);

	m_ninjaContainer->SetCurrentAnimation(0);
#endif
	
}



int Game::GetMeshIndex(Mesh*a_mesh)
{
	int total = m_meshes->size();
	for(int i = 0; i < total; i++)
	{
		if((*m_meshes)[i] == a_mesh)
		{
			return i;
		}
	}

	return -1;
}

void Game::OnKeyUp(int key)
{
	
}
