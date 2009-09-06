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
#include "LandscapeWall1.h"
#include "LandscapeWall2.h"
#include "LandscapeWall3.h"
#include "Skybox.h"
#include "Font.h"
#include "Text.h"
#include "FXManager.h"
#include "C3DETransform.h"
#include "BufferReader.h"
#include <iostream>

//THIS CLASS CAN'T OVERRIDE THE NEW OPERATOR OR IT WILL SCREW UP ALL DIRECTX DRAWING
//#include "DebugMemory.h"

#define CONST_RATIO 8

using namespace std;

Game::Game(Application * app)
{

	m_character0UpdateTime = 0;
	m_spiderUpdateTime = 0;
	m_dogUpdateTime = 0;
	m_ninjaUpdateTime = 0;
	int m_loadedObjects = 0;
	int m_totalObjects = 145;

	m_physPosX = 200;
	m_physPosY = 0;
	m_physSpeedX = 0;
	m_physSpeedY  = 0;
	m_gAcc = 10;

	hack = 0;

	m_application = app;

	IDirect3DTexture9 * t = ResourceManager::GetInstance()->GetTextureByID(IMAGE_EXPLOSION_ID);
	D3DImage *image = new D3DImage(t);				

	t = ResourceManager::GetInstance()->GetTextureByID(IMAGE_BUTTON_ID);
	D3DImage *image2 = new D3DImage(t);			
	m_sprite = new D3DSprite(image, 64, 64, 30, 6, 5, 50);

	m_sprite->SetX(50);
	m_sprite->SetY(50);

	m_speed = 1;
	m_yspeed = 1;

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

	
	m_button = new Button(image2, frames, r);
	m_button->SetX(50);
	m_button->SetY(340);

	m_button->AddListener(this);

	
	hx = 0;
	hy = 0;


	m_camRadius = 1.0f;

	m_cubeX = 0.0f;
	m_cubeY = -2.0f;
	m_cubeZ = 0.0f;

	m_camX = m_cubeX;
	m_camY = m_cubeY + 2.0f;
	m_camZ = m_cubeZ - 5.0f;
	

	m_camTargetX = m_cubeX;
	m_camTargetY = m_cubeY + 2.0f;
	m_camTargetZ = m_cubeZ - 4.0f;
	

	m_camUpX = 0.0f;
	m_camUpY = 1.0f;
	m_camUpZ = 0.0f;

	m_camYRotation = 0.0f;
	m_camZRotation = 0.0f;

	m_carDirection = D3DXVECTOR3(0.0f, 0.0f, 1.0f);


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
	m_inputer->AddMouseListener((MouseListener*)m_button);
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

int eita = 0;
void Game::Update(int deltaTime)
{		


	m_character0UpdateTime += deltaTime;
	m_spiderUpdateTime += (deltaTime);
	m_dogUpdateTime += (deltaTime);
	m_ninjaUpdateTime += (deltaTime);

	

	m_character0UpdateTime = m_character0UpdateTime % m_characterContainer0->GetTotalAnimationTime();
	m_spiderUpdateTime = m_spiderUpdateTime % m_spiderContainer->GetTotalAnimationTime();
	m_dogUpdateTime = m_dogUpdateTime % m_dogContainer->GetTotalAnimationTime();
	m_ninjaUpdateTime = m_ninjaUpdateTime % m_ninjaContainer->GetTotalAnimationTime();


	m_characterContainer0->SetAnimationTime(m_character0UpdateTime);
	m_spiderContainer->SetAnimationTime(m_spiderUpdateTime);
	m_dogContainer->SetAnimationTime(m_dogUpdateTime);
	m_ninjaContainer->SetAnimationTime(m_ninjaUpdateTime);

	int totalObjects = m_testScene->GetMeshesVector()->size();

	for(int i = 0 ; i< totalObjects; i++)
	{
		Mesh * t_target = (*m_testScene->GetMeshesVector())[i];
		D3DMesh *t_targetMesh = (D3DMesh *)t_target;

		if(t_targetMesh == m_woman || t_targetMesh == m_ground || t_target == m_skyBox)
		{
			continue;
		}
		
		bool ret = m_woman->Collides(t_targetMesh);
		if(ret)
		{
			printf("Collision%d\n", timeGetTime());
		}
	}
	
	UpdateInput(deltaTime);

	eita++;

	m_gAcc = 10;	
	//deltaTime = 1000;

	int t_timeRatio = 1;
	int t_spaceRatio = 50;
	
	int formula = (m_physSpeedY*deltaTime/t_timeRatio) + ((m_gAcc*deltaTime*deltaTime)/(2 * t_timeRatio));
	
	int maxInt = 2147483647;


	if(maxInt - formula < m_physPosY || maxInt - formula == m_physPosY)
	{
		int jhgfgf = 987;
	}

	int t_transformedFormula = formula / 10000;
	
	//m_physPosY = m_physPosY + formula;
	m_physPosY = m_physPosY + t_transformedFormula;

	int t_forReal = m_physPosY / 10000;

	m_sprite->SetY(t_forReal);

	m_physSpeedY = m_physSpeedY + ((deltaTime * m_gAcc));
	

	int fleps = 0;
	int t_accumulating = 0;
	int t_transformed = 0;
	while(false)
	{
		fleps++;
		if(fleps == maxInt)
		{	
			t_accumulating++;
			fleps= 0;
		}
		t_transformed = ((maxInt >> 8 )*t_accumulating) + (fleps >> 8 );
	}
	
	
	
	m_sprite->SetX(200);
	
	if(m_physPosY < 0)
	{
		int fkjdfds = 876;
	}


	
	m_sprite->Update(deltaTime);

	m_deltaTime = deltaTime;

	m_testScene->Update(deltaTime);

}


void Game::UpdateInput(int deltaTime)
{
	
	//Mesh * t_target = (Mesh*)m_woman;
	Mesh * t_target = (Mesh*)m_characterMesh;

	float f_deltaTime = deltaTime/1000.0f;

	float step = 17.0f;
	float t_fleps = 0.0f;

	float t_angle = 0.0f;
	const float angleStepNormal = 0.3f * f_deltaTime;
	const float angleStepFast = angleStepNormal * 5.0f;



	if(DirectInput::GetInstance()->IsKeyDown(1))
	{
		m_application->Quit();
		return;
		
	}

	bool isRunning = false;
	if(DirectInput::GetInstance()->IsKeyDown(42))
	{
		step *= 5.0f;
		isRunning = true;

		
		
	}
	
	
	//makes step a function of the deltaTime
	step = step * f_deltaTime;

	D3DXVECTOR3 newPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	bool upDown = false;
	bool downDown = false;
	bool leftDown = false;
	bool rightDown = false;


	if(DirectInput::GetInstance()->IsKeyDown(200))
	//UP
	{		
		//m_cubeZ += step;
		newPos = step*m_carDirection;
		upDown = true;

		
	}
	if(DirectInput::GetInstance()->IsKeyDown(208))
	{	
	//DOWN	
		
		//m_cubeZ -= step;
		newPos = -step*m_carDirection;
		downDown = true;

		
	}	
	if(DirectInput::GetInstance()->IsKeyDown(205))
	{
		//RIGHT		
		t_angle = (isRunning)?angleStepFast:angleStepNormal;	
		leftDown = true;
		//m_cube->Rotate(m_cube->GetRotationX(), m_cube->GetRotationY() + 0.1f, m_cube->GetRotationZ());
		//t_house->Scale(t_house->GetXScale() - 0.1f, t_house->GetYScale() - 0.1f, t_house->GetZScale() - 0.1f);
	}
	if(DirectInput::GetInstance()->IsKeyDown(203))
	{
		//LEFT		
		t_angle = (isRunning)?-angleStepFast:-angleStepNormal;
		rightDown = true;
		//m_cube->Rotate(m_cube->GetRotationX(), m_cube->GetRotationY() - 0.1f, m_cube->GetRotationZ());
		
	}

	

	//if(!upDown && !downDown && !leftDown && !rightDown && m_woman->GetAnimation() != WomanMesh::ANIMATION_IDLE)
	if(false)
	{
		//m_woman->SetAnimation(WomanMesh::ANIMATION_IDLE);
	}
	else
	{
		if(upDown)
		{
			if(isRunning)
			{
				//m_woman->SetAnimation(WomanMesh::ANIMATION_JOGGING);
			}
			else
			{
				//m_woman->SetAnimation(WomanMesh::ANIMATION_WALKING);
			}
		}
	}



	float t_dAngle = 57.29577951308232286465f * t_angle;
	D3DXMATRIX R;
	D3DXMatrixRotationY(&R, t_angle);
	D3DXVec3TransformCoord(&m_carDirection, &m_carDirection, &R);
	D3DXVec3Normalize(&m_carDirection, &m_carDirection);
	
	
	t_target->Rotate(t_target->GetRotationX(), t_target->GetRotationY() + t_dAngle, t_target->GetRotationZ());

	m_cubeX += newPos.x;
	//m_cubeY += newPos.y;
	m_cubeY = 0;
	m_cubeZ += newPos.z;

	hx = (int)m_cubeX ;
	//hy = (int)m_auei->GetHeight(m_cubeX, m_cubeZ);	
	hy = 0;	
	
	t_target->SetPosition(m_cubeX, m_cubeY, m_cubeZ);


	D3DXVECTOR3 t_camLook = m_carDirection * -15.0f;
	t_camLook.x = m_cubeX + t_camLook.x;
	t_camLook.y = m_cubeY + t_camLook.y;
	t_camLook.z = m_cubeZ + t_camLook.z;

	//m_cubeY = m_auei->GetHeight(m_cubeX, m_cubeZ) + 1.5f;
	m_cubeY = 1.5f;

	m_camX = t_camLook.x;
	m_camY = m_cubeY + 3.0f;
	m_camZ = t_camLook.z;

	D3DXVECTOR3 t_camTarget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	t_camTarget.x = m_camX + (m_carDirection*2.0f).x;
	t_camTarget.y = m_camY + (m_carDirection*2.0f).y;
	t_camTarget.z = m_camZ + (m_carDirection*2.0f).z;
	

	m_camTargetX = t_camTarget.x;
	m_camTargetY = t_camTarget.y;
	m_camTargetZ = t_camTarget.z;




}


void Game::Render(Renderer *renderer)
{
	
	D3DCamera * cam = (D3DCamera *)renderer->GetCamera();
	float x = m_cameraRadius * cosf(m_cameraRotation);
	float z =  m_cameraRadius * sinf(m_cameraRotation);

	cam->SetPosition(m_camX, m_camY, m_camZ);
	cam->SetUp(m_camUpX, m_camUpY, m_camUpZ);	
	cam->SetTarget(m_camTargetX, m_camTargetY, m_camTargetZ);
	
	m_testScene->ClearAllNodes();


	C3DETransform *t0 = new C3DETransform();	

	SceneNode *t_node0 = new SceneNode(m_ground, t0);
	m_testScene->AddNode(t_node0);	

	C3DETransform *t2 = new C3DETransform();		
	//t2->Translate(5.0f, 2.0f, 0.0f);

	SceneNode *t_node2 = new SceneNode(m_characterContainer0, t2);
	m_testScene->AddNode(t_node2);

	C3DETransform *t3 = new C3DETransform();
	t3->Translate(0.0f, 0.0f, 25.0f);
	SceneNode *t_node3 = new SceneNode(m_spiderContainer, t3);	
	m_testScene->AddNode(t_node3);

	C3DETransform *t4 = new C3DETransform();
	t4->Translate(25.0f, 0.0f, 25.0f);
	SceneNode *t_node4 = new SceneNode(m_dogContainer, t4);	
	m_testScene->AddNode(t_node4);

	C3DETransform *t5 = new C3DETransform();
	t5->Translate(50.0f, 0.0f, 25.0f);
	SceneNode *t_node5 = new SceneNode(m_ninjaContainer, t5);	
	m_testScene->AddNode(t_node5);

	for(int i = 0; i< m_sceneTotalObjects; i++)
	{
		Mesh * t_mesh = (*m_meshes)[m_sceneStaticObjectsList[i]];
		C3DETransform *t_transform = new C3DETransform();
		t_transform->Set(m_sceneStaticObjectsTransforms[i]->GetMatrix());
		SceneNode *t_node = new SceneNode(t_mesh, t_transform);
		m_testScene->AddNode(t_node);
	}	

	

	renderer->DrawScene2(m_testScene);


	//renderer->DrawScene(m_testScene);
	//renderer->DrawSprite(m_button);
	renderer->DrawSprite((Sprite *)m_sprite);



	//static_cast<D3DRenderer *>(renderer)->DrawText(m_text);
	//static_cast<D3DRenderer *>(renderer)->DrawAxis();
	
	
}

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
	return;
	D3DXVECTOR3 pos = D3DXVECTOR3(m_camX, m_camY, m_camZ);
	D3DXVECTOR3 target = D3DXVECTOR3(m_camTargetX, m_camTargetY, m_camTargetZ);
	D3DXVECTOR3 look = target - pos;
	D3DXVECTOR3 up = D3DXVECTOR3(m_camUpX, m_camUpY, m_camUpZ);;
	D3DXVECTOR3 right;
	D3DXVec3Cross(&right, &up, &look);
	D3DXVec3Normalize(&right, &right);		

	float yAngle = dx / 150.0f;
	float t_angle = yAngle * 57.29577951308232286465f;

	//m_cube->Rotate(m_cube->GetRotationX(), m_cube->GetRotationY() + t_angle, m_cube->GetRotationZ());
	
	// Rotate camera axes about the world's y-axis.
	D3DXMATRIX R;
	D3DXMatrixRotationY(&R, yAngle);
	D3DXVec3TransformCoord(&right, &right, &R);
	D3DXVec3TransformCoord(&up, &up, &R);
	D3DXVec3TransformCoord(&look, &look, &R);

	float pitch  = dy / 150.0f;
	
	
	// Rotate camera axes about the world's y-axis.
	
	D3DXMatrixRotationAxis(&R, &right, pitch);
	D3DXVec3TransformCoord(&look, &look, &R);
	D3DXVec3TransformCoord(&up, &up, &R);

	m_camTargetX = pos.x + look.x;
	m_camTargetY = pos.y + look.y;
	m_camTargetZ = pos.z + look.z;

	m_camUpX = up.x;
	m_camUpY = up.y;
	m_camUpZ = up.z;


}


void Game::OnKeyDown(int key)
{
	//float step = 0.1f;
	//Mesh * target = (Mesh*)m_cube;
	//Mesh * t_target = (Mesh*)m_castle;
	Mesh * t_target = (Mesh*)t_house;
	//Mesh * target = (Mesh*)m_skinMesh;
	float step = 0.1f;

	if(key == 1)
	{
		m_application->Quit();
	}

	if(DirectInput::GetInstance()->IsKeyDown(42))
	{
		step = 0.01f;
		
		
	}

	

	
	if(DirectInput::GetInstance()->IsKeyDown(200))
	//UP
	{		
		m_dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 pos = D3DXVECTOR3(m_camX, m_camY, m_camZ);
		D3DXVECTOR3 target = D3DXVECTOR3(m_camTargetX, m_camTargetY, m_camTargetZ);
		D3DXVECTOR3 look = target - pos;
		D3DXVECTOR3 up = D3DXVECTOR3(m_camUpX, m_camUpY, m_camUpZ);;
		D3DXVECTOR3 right;
		D3DXVec3Cross(&right, &up, &look);
		D3DXVec3Normalize(&right, &right);

		m_dir = look*step;

		m_camX += m_dir.x;
		m_camY += m_dir.y;
		m_camZ += m_dir.z;

		m_camTargetX += m_dir.x;
		m_camTargetY += m_dir.y;
		m_camTargetZ += m_dir.z;
	}
	else if(DirectInput::GetInstance()->IsKeyDown(208))
	{	
	//DOWN	
		m_dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 pos = D3DXVECTOR3(m_camX, m_camY, m_camZ);
		D3DXVECTOR3 target = D3DXVECTOR3(m_camTargetX, m_camTargetY, m_camTargetZ);
		D3DXVECTOR3 look = target - pos;
		D3DXVECTOR3 up = D3DXVECTOR3(m_camUpX, m_camUpY, m_camUpZ);;
		D3DXVECTOR3 right;
		D3DXVec3Cross(&right, &up, &look);
		D3DXVec3Normalize(&right, &right);

		m_dir = -look*step;

		m_camX += m_dir.x;
		m_camY += m_dir.y;
		m_camZ += m_dir.z;

		m_camTargetX += m_dir.x;
		m_camTargetY += m_dir.y;
		m_camTargetZ += m_dir.z;
		
	}	
	else if(DirectInput::GetInstance()->IsKeyDown(205))
	{
		//RIGHT
		m_dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 pos = D3DXVECTOR3(m_camX, m_camY, m_camZ);
		D3DXVECTOR3 target = D3DXVECTOR3(m_camTargetX, m_camTargetY, m_camTargetZ);
		D3DXVECTOR3 look = target - pos;
		D3DXVECTOR3 up = D3DXVECTOR3(m_camUpX, m_camUpY, m_camUpZ);;
		D3DXVECTOR3 right;
		D3DXVec3Cross(&right, &up, &look);
		D3DXVec3Normalize(&right, &right);

		m_dir = right*step;

		m_camX += m_dir.x;
		m_camY += m_dir.y;
		m_camZ += m_dir.z;

		m_camTargetX += m_dir.x;
		m_camTargetY += m_dir.y;
		m_camTargetZ += m_dir.z;
	}
	else if(DirectInput::GetInstance()->IsKeyDown(203))
	{
		//LEFT
		m_dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 pos = D3DXVECTOR3(m_camX, m_camY, m_camZ);
		D3DXVECTOR3 target = D3DXVECTOR3(m_camTargetX, m_camTargetY, m_camTargetZ);
		D3DXVECTOR3 look = target - pos;
		D3DXVECTOR3 up = D3DXVECTOR3(m_camUpX, m_camUpY, m_camUpZ);;
		D3DXVECTOR3 right;
		D3DXVec3Cross(&right, &up, &look);
		D3DXVec3Normalize(&right, &right);

		m_dir = -right*step;

		m_camX += m_dir.x;
		m_camY += m_dir.y;
		m_camZ += m_dir.z;

		m_camTargetX += m_dir.x;
		m_camTargetY += m_dir.y;
		m_camTargetZ += m_dir.z;
		
	}
	else if(DirectInput::GetInstance()->IsKeyDown(17))
	{
		//W
		t_target->SetPosition(t_target->GetX() , t_target->GetY(), t_target->GetZ() + step);

	}
	else if(DirectInput::GetInstance()->IsKeyDown(30))
	{
		//A
		t_target->SetPosition(t_target->GetX() -step , t_target->GetY(), t_target->GetZ());

	}
	else if(DirectInput::GetInstance()->IsKeyDown(31))
	{
		//S
		t_target->SetPosition(t_target->GetX() , t_target->GetY(), t_target->GetZ() -step);

	}
	else if(DirectInput::GetInstance()->IsKeyDown(32))
	{
		//D
		t_target->SetPosition(t_target->GetX() +step , t_target->GetY(), t_target->GetZ());

	}
	else if(DirectInput::GetInstance()->IsKeyDown(44))
	{
		//Z
		t_target->Scale(t_target->GetXScale() -step , t_target->GetYScale() - step, t_target->GetZScale() - step);

	}

	else if(DirectInput::GetInstance()->IsKeyDown(45))
	{
		//X
		t_target->Scale(t_target->GetXScale() +step , t_target->GetYScale() + step, t_target->GetZScale() + step);

	}
	else if(DirectInput::GetInstance()->IsKeyDown(49))
	{
		//N
		t_target->Rotate(t_target->GetRotationX(), t_target->GetRotationY() + step, t_target->GetRotationZ());

	}
	else if(DirectInput::GetInstance()->IsKeyDown(50))
	{
		//M
		t_target->Rotate(t_target->GetRotationX(), t_target->GetRotationY() - step, t_target->GetRotationZ());

	}

}

#define USE_X_MODELS 0

void Game::InitializeMeshes()
{	

	m_totalObjects = 31;
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

	
	D3DImage * characterTexture = new D3DImage(ResourceManager::GetInstance()->GetTextureByID(IMAGE_MALE_SKIN_ID));	
	
	m_characterMesh = new C3DESkinnedMesh(	ResourceManager::GetInstance()->GetMeshBuffer(MESH_BUFFER_CHARACTER_MALE_ID),
											ResourceManager::GetInstance()->GetMeshBuffer(MESH_BUFFER_CHARACTER_MALE_BONES_ID),
											characterTexture);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	D3DImage * spiderTexture = new D3DImage(ResourceManager::GetInstance()->GetTextureByID(IMAGE_SPIDER_ID));	
	m_spiderMesh = new C3DESkinnedMesh(	ResourceManager::GetInstance()->GetMeshBuffer(MESH_BUFFER_SPIDER_ID),
										ResourceManager::GetInstance()->GetMeshBuffer(MESH_BUFFER_SPIDER_BONES_ID),
										spiderTexture);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	D3DImage * ninjaTexture = new D3DImage(ResourceManager::GetInstance()->GetTextureByID(IMAGE_NINJA_ID));	
	m_ninjaMesh = new C3DESkinnedMesh(	ResourceManager::GetInstance()->GetMeshBuffer(MESH_BUFFER_NINJA_ID),
										ResourceManager::GetInstance()->GetMeshBuffer(MESH_BUFFER_NINJA_BONES_ID),
										ninjaTexture);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	D3DImage * dogTexture = new D3DImage(ResourceManager::GetInstance()->GetTextureByID(IMAGE_DOG_ID));	
	m_dogMesh = new C3DESkinnedMesh(	ResourceManager::GetInstance()->GetMeshBuffer(MESH_BUFFER_DOG_ID),
										ResourceManager::GetInstance()->GetMeshBuffer(MESH_BUFFER_DOG_BONES_ID),
										dogTexture);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);
	

	Tree0 *m_tree0 = new Tree0();
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	Tree1 *m_tree1 = new Tree1();
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	Tree2 *m_tree2 = new Tree2();
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	Tree3 *m_tree3 = new Tree3();
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	LandscapeWall1 *m_wall1 = new LandscapeWall1();
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	LandscapeWall2 *m_wall2 = new LandscapeWall2();
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	LandscapeWall3 *m_wall3 = new LandscapeWall3();
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
	GameMesh *m_streetLight02 = new GameMesh(MESH_BUFFER_STREET_LIGHT_02_ID,IMAGE_STREET_LIGHT_02_ID);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);
	
	GameMesh *m_streetLight01 = new GameMesh(MESH_BUFFER_STREET_LIGHT_01_ID,IMAGE_STREET_LIGHT_01_ID);
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

	GameMesh *m_cafeTable = new GameMesh(MESH_BUFFER_CAFE_TABLE_ID,IMAGE_CAFE_TABLE_ID);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	GameMesh *m_parkingBarrier = new GameMesh(MESH_BUFFER_PARKING_BARRIER_ID,IMAGE_PARKING_BARRIER_ID);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	GameMesh *m_trafficCone = new GameMesh(MESH_BUFFER_TRAFFIC_CONE_ID,IMAGE_TRAFFIC_CONE_ID);
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);

	
#endif
	m_skyBox = new Skybox(1000);	
	m_loadedObjects++;
	UpdateLoadingBar(m_loadedObjects, m_totalObjects);
	
	m_testScene->Initialize();

	m_meshes = new vector<Mesh*>;
	m_meshes->push_back(m_characterMesh);
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
	

	//#include "C:\documents and Settings\csabino\Desktop\exportedMeshes\outWorld.c3d"
	BufferReader *t_scene = new BufferReader(ResourceManager::GetInstance()->GetSceneBuffer(SCENE_BUFFER_SCENE_0_ID));

	m_sceneTotalObjects = t_scene->ReadNextInt();	
	m_sceneStaticObjectsList = (int*)malloc(sizeof(int) * (m_sceneTotalObjects));
	m_sceneStaticObjectsTransforms = (C3DETransform**)malloc(sizeof(C3DETransform) * (m_sceneTotalObjects));
	D3DXMATRIX *t_matrix = new D3DXMATRIX();

	for(int i = 0; i < m_sceneTotalObjects; i++)
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
		t_matrix->_43 = t_scene->ReadNextFloat();
		t_matrix->_44 = t_scene->ReadNextFloat();
		m_sceneStaticObjectsTransforms[i]->Set(t_matrix);
	}		

	
	
	FXManager::GetInstance()->AddMeshesEffects(m_testScene, m_meshes);

	m_characterContainer0 = new C3DESkinnedMeshContainer(m_characterMesh);
	m_spiderContainer = new C3DESkinnedMeshContainer(m_spiderMesh);
	m_dogContainer = new C3DESkinnedMeshContainer(m_dogMesh);
	m_ninjaContainer = new C3DESkinnedMeshContainer(m_ninjaMesh);
	
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
