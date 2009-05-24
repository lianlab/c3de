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
//#include "Townhall.h"
#include "LandscapeWall1.h"
#include "LandscapeWall2.h"
#include "LandscapeWall3.h"
#include "Skybox.h"
#include "Font.h"
#include "Text.h"


#include <iostream>



//THIS CLASS CAN'T OVERRIDE THE NEW OPERATOR OR IT WILL SCREW UP ALL DIRECTX DRAWING
//#include "DebugMemory.h"

#define CONST_RATIO 8

#define CAMERA_ON_TOP 0

#define DISABLE_CAMERA_MOUSE 1


using namespace std;

Game::Game(Application * app)
{
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

	//CreateTestMesh();
	

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

	

#if 0
	m_camX = 0.0f;
	m_camY = 0.0f;
	m_camZ = 0.0f;

	m_camRadius = 1.0f;

	m_camTargetX = 0.0f;
	m_camTargetY = 0.0f;
	m_camTargetZ = 1.0f;

	m_camUpX = 0.0f;
	m_camUpY = 1.0f;
	m_camUpZ = 0.0f;

	m_camYRotation = 0.0f;
	m_camZRotation = 0.0f;

	
#endif

#if 1
	

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

	
#endif

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
	//delete m_sprite;
	//delete m_button;


#if 1
	//delete m_testMesh;
	
	//delete m_grid;

	
	//delete m_plane ;

	//delete m_pivot;
	
	

	//delete m_wall;

	//delete m_mirror;
	
	
	
	//delete m_shadowSurface;
#endif
}

int eita = 0;
void Game::Update(int deltaTime)
{		
	//deltaTime = 1000;
	
	UpdateInput(deltaTime);

	eita++;
	
#if 0
	///////////////////////////////////////////////
	m_gAcc = 1;	
	deltaTime = 1;
	int const_ratio = 1000;
	int t_formula = m_physPosY+ m_physSpeedY *deltaTime* const_ratio + (deltaTime * deltaTime*m_gAcc*const_ratio)/2;
	m_physPosY = t_formula;	
	m_physSpeedY = m_physSpeedY + deltaTime*m_gAcc;
	///////////////////////////////////////////////
#endif
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
	//int screenY = m_physPosY / 10000000;
	//m_sprite->SetY(screenY);
	
	if(m_physPosY < 0)
	{
		int fkjdfds = 876;
	}


	
	m_sprite->Update(deltaTime);

	//m_font->SetX(300);
	//m_font->SetY(300);
	//m_font->Update(deltaTime);

	m_deltaTime = deltaTime;

	m_testScene->Update(deltaTime);

	

	//m_videoMesh->Update(deltaTime);

	//m_testMesh->Update(1);

	//m_grid->Update(10);
	
}


#if CAMERA_ON_TOP


void Game::UpdateInput(int deltaTime)
{
	
	Mesh * t_target = (Mesh*)m_woman;

	
	float f_deltaTime = deltaTime/1000.0f;

	float step = 17.0f;
	float t_fleps = 0.0f;

	float t_angle = 0.0f;
	const float angleStepNormal = 1.5f * f_deltaTime;
	const float angleStepFast = angleStepNormal * 3.0f;


	if(DirectInput::GetInstance()->IsKeyDown(1))
	{
		m_application->Quit();
		return;
		
	}

	bool isRunning = false;
	if(DirectInput::GetInstance()->IsKeyDown(42))
	{
		step *= 3.0f;
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
		
	}
	if(DirectInput::GetInstance()->IsKeyDown(203))
	{
		//LEFT		
		t_angle = (isRunning)?-angleStepFast:-angleStepNormal;
		rightDown = true;
		//m_cube->Rotate(m_cube->GetRotationX(), m_cube->GetRotationY() - 0.1f, m_cube->GetRotationZ());
		
	}

	

	if(!upDown && !downDown && !leftDown && !rightDown && m_woman->GetAnimation() != WomanMesh::ANIMATION_IDLE)
	{
		m_woman->SetAnimation(WomanMesh::ANIMATION_IDLE);
	}
	else
	{
		if(upDown)
		{
			if(isRunning)
			{
				m_woman->SetAnimation(WomanMesh::ANIMATION_JOGGING);
			}
			else
			{
				m_woman->SetAnimation(WomanMesh::ANIMATION_WALKING);
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

	
	m_cubeY = 1.5f;

	//m_camX = m_cubeX;
	m_camX = 0.0f;
	m_camY = 250.0f;
	//m_camZ = m_cubeZ;
	m_camZ = 0.0f;

	D3DXVECTOR3 t_camTarget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	t_camTarget.x = m_camX + (m_carDirection*2.0f).x;
	t_camTarget.y = m_camY + (m_carDirection*2.0f).y;
	t_camTarget.z = m_camZ + (m_carDirection*2.0f).z;
	
	m_camUpX = 0.0f;
	m_camUpY = 0.0f;
	m_camUpZ = 1.0f;

	//m_camTargetX = m_cubeX;
	m_camTargetX = 0.0f;
	m_camTargetY = 0.0f;
	//m_camTargetZ = m_cubeZ;
	m_camTargetZ = 0.0f;


}


#else
void Game::UpdateInput(int deltaTime)
{
	
	Mesh * t_target = (Mesh*)m_woman;


#define USE_RELATIVE_SPEED 1
#if USER_RELATIVE_SPEED
	
	float f_deltaTime = deltaTime/1000.0f;

	float step = 17.0f;
	float t_fleps = 0.0f;

	float t_angle = 0.0f;
	const float angleStepNormal = 0.3f * f_deltaTime;
	const float angleStepFast = angleStepNormal * 5.0f;
#else
	float f_deltaTime = deltaTime/1000.0f;

	float step = 17.0f;
	float t_fleps = 0.0f;

	float t_angle = 0.0f;
	const float angleStepNormal = 0.3f * f_deltaTime;
	const float angleStepFast = angleStepNormal * 5.0f;

#endif

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

#if 1
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

	

	if(!upDown && !downDown && !leftDown && !rightDown && m_woman->GetAnimation() != WomanMesh::ANIMATION_IDLE)
	{
		m_woman->SetAnimation(WomanMesh::ANIMATION_IDLE);
	}
	else
	{
		if(upDown)
		{
			if(isRunning)
			{
				m_woman->SetAnimation(WomanMesh::ANIMATION_JOGGING);
			}
			else
			{
				m_woman->SetAnimation(WomanMesh::ANIMATION_WALKING);
			}
		}
	}

#endif

#if 0
	if(DirectInput::GetInstance()->IsKeyDown(200))
	//UP
	{	
		m_cube->Scale(m_cube->GetXScale() + step, m_cube->GetYScale(), m_cube->GetZScale());
		
	}
	if(DirectInput::GetInstance()->IsKeyDown(208))
	{	
	//DOWN	
		m_cube->Scale(m_cube->GetXScale() - step, m_cube->GetYScale(), m_cube->GetZScale());
		
	}	
	if(DirectInput::GetInstance()->IsKeyDown(205))
	{
		m_cube->Scale(m_cube->GetXScale(), m_cube->GetYScale() + step, m_cube->GetZScale());
		
	}
	if(DirectInput::GetInstance()->IsKeyDown(203))
	{
		m_cube->Scale(m_cube->GetXScale(), m_cube->GetYScale() - step, m_cube->GetZScale());
		
	}

#endif

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


#endif

#if 0
void Game::UpdateInput()
{
	return;
	Mesh * t_target = (Mesh*)m_cube;


	float step = 1.1f;
	float t_fleps = 0.0f;

	float t_angle = 0.0f;

	if(DirectInput::GetInstance()->IsKeyDown(1))
	{
		m_application->Quit();
		return;
		//step = 0.1f;
	}

	if(DirectInput::GetInstance()->IsKeyDown(16))
	{
		step = 0.1f;
	}

	D3DXVECTOR3 newPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	
	if(DirectInput::GetInstance()->IsKeyDown(200))
	//UP
	{		
		//m_cubeZ += step;
		newPos = step*m_carDirection;

	}
	if(DirectInput::GetInstance()->IsKeyDown(208))
	{	
	//DOWN	
		
		//m_cubeZ -= step;
		newPos = -step*m_carDirection;
	}	
	if(DirectInput::GetInstance()->IsKeyDown(205))
	{
		//RIGHT		
		t_angle = 0.01f;				
	}
	if(DirectInput::GetInstance()->IsKeyDown(203))
	{
		//LEFT		
		t_angle = -0.01f;	

		
	}

	float t_dAngle = 57.29577951308232286465f * t_angle;
	D3DXMATRIX R;
	D3DXMatrixRotationY(&R, t_angle);
	D3DXVec3TransformCoord(&m_carDirection, &m_carDirection, &R);
	D3DXVec3Normalize(&m_carDirection, &m_carDirection);
	
	//m_cube->Rotate(m_cube->GetRotationX(), m_cube->GetRotationY() + t_dAngle, m_cube->GetRotationZ());
	//m_woman->Rotate(m_woman->GetRotationX(), m_woman->GetRotationY() + t_dAngle, m_woman->GetRotationZ());
	t_target->Rotate(t_target->GetRotationX(), t_target->GetRotationY() + t_dAngle, t_target->GetRotationZ());

	m_cubeX += newPos.x;
	m_cubeY += newPos.y;
	m_cubeZ += newPos.z;

	//hx = m_auei->GetCoords(m_cubeX, m_cubeZ).x;
	hx = (int)m_cubeX ;
	hy = (int)m_auei->GetHeight(m_cubeX, m_cubeZ);
	//hy = (int)m_cubeZ;

	//m_cube->SetPosition(m_cubeX, m_cubeY, m_cubeZ);
	//m_woman->SetPosition(m_cubeX, m_cubeY, m_cubeZ);
	t_target->SetPosition(m_cubeX, m_cubeY, m_cubeZ);

#define LOCK_CAMERA 1
#define FIXED_CAMERA !LOCK_CAMERA
#if LOCK_CAMERA
	D3DXVECTOR3 t_camLook = m_carDirection * -15.0f;
	t_camLook.x = m_cubeX + t_camLook.x;
	t_camLook.y = m_cubeY + t_camLook.y;
	t_camLook.z = m_cubeZ + t_camLook.z;

	m_cubeY = m_auei->GetHeight(m_cubeX, m_cubeZ) + 1.5f;

	m_camX = t_camLook.x;
	m_camY = m_cubeY + 3.0f;
	m_camZ = t_camLook.z;

	D3DXVECTOR3 t_camTarget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	t_camTarget.x = m_camX + (m_carDirection*2.0f).x;
	t_camTarget.y = m_camY + (m_carDirection*2.0f).y;
	t_camTarget.z = m_camZ + (m_carDirection*2.0f).z;
	//m_camTargetX = m_camX

	m_camTargetX = t_camTarget.x;
	m_camTargetY = t_camTarget.y;
	m_camTargetZ = t_camTarget.z;
#endif

#if FIXED_CAMERA
	m_camX = 0.0f;
	m_camY = m_cubeY + 250.0f;
	m_camZ = 0.0f;

	m_camTargetX = 0.0f;
	m_camTargetY = 0.0f;
	m_camTargetZ = 0.0f;

	m_camUpX = 1.0f;
	m_camUpY = 0.0f;
	m_camUpZ = 0.0f;
#endif


}
#endif

#if 0
void Game::UpdateInput()
{

	float step = 0.1f;	

	if(DirectInput::GetInstance()->IsKeyDown(1))
	{
		m_application->Quit();
		return;
	}

	D3DXVECTOR3 newPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	
	if(DirectInput::GetInstance()->IsKeyDown(200))
	//UP
	{		
		
		m_auei->SetPosition(m_auei->GetX() + step, m_auei->GetY(), m_auei->GetZ());

	}
	if(DirectInput::GetInstance()->IsKeyDown(208))
	{	
	//DOWN	
		
		

	}	
	if(DirectInput::GetInstance()->IsKeyDown(205))
	{
		

	}
	if(DirectInput::GetInstance()->IsKeyDown(203))
	{
		

	}

	



}
#endif



int clickedX = 999999;
int clickedY = 999999;

void Game::Render(Renderer *renderer)
{
	//
	//m_camX = 0.0f;
	//m_camY = 0.0f;
	//m_camZ = -20.0f;
	D3DCamera * cam = (D3DCamera *)renderer->GetCamera();
	float x = m_cameraRadius * cosf(m_cameraRotation);
	float z =  m_cameraRadius * sinf(m_cameraRotation);

	cam->SetPosition(m_camX, m_camY, m_camZ);
	cam->SetUp(m_camUpX, m_camUpY, m_camUpZ);	
	cam->SetTarget(m_camTargetX, m_camTargetY, m_camTargetZ);
	
	renderer->DrawScene(m_testScene);
	//renderer->DrawSprite(m_button);
	renderer->DrawSprite((Sprite *)m_sprite);
	//renderer->DrawSprite((Sprite*)m_font);
	static_cast<D3DRenderer *>(renderer)->DrawText(m_text);
	static_cast<D3DRenderer *>(renderer)->DrawAxis();
	//bool ret = static_cast<D3DRenderer *>(renderer)->slig(m_woman, t_house);
	bool ret = m_woman->Collides(t_house);
	if(ret)
	{
		printf("Collision%d\n", timeGetTime());
	}

	

	
}

void Game::OnMouseDown(int button, int x , int y)
{
#if 0
	

	clickedX = x;
	clickedY = y;

	D3DRenderer * t_renderer = D3DRenderer::GetInstance();
	if(t_renderer->IsMousePicked(m_woman, x, y))
	{
		int gfdgfd= 8787;
	}
#endif
}

void Game::OnMouseUp(int button, int x, int y)
{
	int moueskfd = button;
	int clickedX = 999999;
	int clickedY = 999999;
}

#if 1
void Game::OnMouseMove(int x, int y, int dx, int dy)
{		
#if DISABLE_CAMERA_MOUSE
	return;
#endif
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
#else
void Game::OnMouseMove(int x, int y, int dx, int dy)
{		
	
	D3DXVECTOR3 pos = D3DXVECTOR3(m_camX, m_camY, m_camZ);
	D3DXVECTOR3 target = D3DXVECTOR3(m_camTargetX, m_camTargetY, m_camTargetZ);
	D3DXVECTOR3 look = target - pos;
	D3DXVECTOR3 up = D3DXVECTOR3(m_camUpX, m_camUpY, m_camUpZ);;
	D3DXVECTOR3 right;
	D3DXVec3Cross(&right, &up, &look);
	D3DXVec3Normalize(&right, &right);		

	float yAngle = dx / 150.0f;
	// Rotate camera axes about the world's y-axis.
	D3DXMATRIX R;
	D3DXMatrixRotationY(&R, yAngle);
	D3DXVec3TransformCoord(&right, &right, &R);
	D3DXVec3TransformCoord(&up, &up, &R);
	D3DXVec3TransformCoord(&look, &look, &R);

	

	m_camTargetX = pos.x + look.x;
	m_camTargetY = pos.y + look.y;
	m_camTargetZ = pos.z + look.z;

	m_camUpX = up.x;
	m_camUpY = up.y;
	m_camUpZ = up.z;


}
#endif

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

#if 0
void Game::OnKeyDown(int key)
{
	
	
	//float step = 0.1f;
	//Mesh * target = (Mesh*)m_cube;
	Mesh * target = (Mesh*)m_castle;
	//Mesh * target = (Mesh*)m_skinMesh;
	float step = 0.1f;

	if(key == 1)
	{
		m_application->Quit();
	}

	
	

#if 1
	else if(key == 200)
	{		
		target->Scale(target->GetXScale() - step, target->GetYScale() - step, target->GetZScale() - step);		
		
		
	}
	else if(key == 208)
	{		
		target->Scale(target->GetXScale()+ step, target->GetYScale()+ step, target->GetZScale() + step);		
	}	
	else if(key == 205)
	{
		target->Scale(target->GetXScale(), target->GetYScale() - step, target->GetZScale());
	}
	else if(key == 203)
	{
		target->Scale(target->GetXScale(), target->GetYScale() + step, target->GetZScale());
	}
	else if(key == 17)
	{
		target->Scale(target->GetXScale() + step, target->GetYScale(), target->GetZScale());
	}
	else if(key == 31)
	{
		target->Scale(target->GetXScale() - step, target->GetYScale(), target->GetZScale());
	}
#endif
#if 0
else if(key == 200)
	{		
		target->Scale(target->GetXScale()-step, target->GetYScale()-step, target->GetZScale() - step);		
		
		
	}
	else if(key == 208)
	{		
		target->Scale(target->GetXScale() + step, target->GetYScale() + step, target->GetZScale() + step);		
	}	
	
#endif
#if 0
	else if(key == 200)
	{		
		target->SetPosition(target->GetX(), target->GetY(), target->GetZ() - step);		
		
		
	}
	else if(key == 208)
	{		
		target->SetPosition(target->GetX(), target->GetY(), target->GetZ() + step);		
	}	
	else if(key == 205)
	{
		target->SetPosition(target->GetX(), target->GetY() - step, target->GetZ());
	}
	else if(key == 203)
	{
		target->SetPosition(target->GetX(), target->GetY() + step, target->GetZ());
	}
	else if(key == 17)
	{
		target->SetPosition(target->GetX() + step, target->GetY(), target->GetZ());
	}
	else if(key == 31)
	{
		target->SetPosition(target->GetX() - step, target->GetY(), target->GetZ());
	}
#endif
#if 0
	else if(key == 200)
	{		
		target->Rotate(target->GetRotationX(), target->GetRotationY(), target->GetRotationZ() - step);				
		
	}
	else if(key == 208)
	{		
		target->Rotate(target->GetRotationX(), target->GetRotationY(), target->GetRotationZ() + step);		
	}	
	else if(key == 205)
	{
		target->Rotate(target->GetRotationX(), target->GetRotationY() - step, target->GetRotationZ());
	}
	else if(key == 203)
	{
		target->Rotate(target->GetRotationX(), target->GetRotationY() + step, target->GetRotationZ());
	}
	else if(key == 17)
	{
		target->Rotate(target->GetRotationX() + step, target->GetRotationY(), target->GetRotationZ());
	}
	else if(key == 31)
	{
		target->Rotate(target->GetRotationX() - step, target->GetRotationY(), target->GetRotationZ());
	}
#endif

#if 0
		

	else if(key == 200)
		//UP
	{		
		//target->Rotate(target->GetRotationX(), target->GetRotationY(), target->GetRotationZ() - step);				
		m_camX += 0.1f;
		m_camTargetX += 0.1f;
	}
	else if(key == 208)
	{	//DOWN	
		
		//target->Rotate(target->GetRotationX(), target->GetRotationY(), target->GetRotationZ() + step);		
		m_camX -= 0.1f;
		m_camTargetX -= 0.1f;
	}	
	else if(key == 205)
	{
		//RIGHT
		//target->Rotate(target->GetRotationX(), target->GetRotationY() - step, target->GetRotationZ());
		m_camZ += 0.1f;
		m_camTargetZ += 0.1f;
	}
	else if(key == 203)
	{
		//LEFT
		//target->Rotate(target->GetRotationX(), target->GetRotationY() + step, target->GetRotationZ());
		m_camZ -= 0.1f;
		m_camTargetZ -= 0.1f;
	}
	else if(key == 17)
	{
		
		float yAngle = 1 / 150.0f;
		D3DXMATRIX matrix;

		D3DXVECTOR3 t_target = D3DXVECTOR3(m_camTargetX, m_camTargetY, m_camTargetZ);
		D3DXVECTOR3 t_pos = D3DXVECTOR3(m_camX, m_camY, m_camZ);	

		D3DXVECTOR3 L = t_target - t_pos;
		D3DXVec3Normalize(&L, &L);

		D3DXMatrixRotationY(&matrix, yAngle);
		D3DXVec3TransformCoord(&L, &L, &matrix);

		m_camTargetX = m_camX + L.x;
		m_camTargetY = m_camY + L.y;
		m_camTargetZ = m_camZ + L.z;
	}
	else if(key == 31)
	{		
		float yAngle = -1 / 150.0f;
		D3DXMATRIX matrix;

		D3DXVECTOR3 t_target = D3DXVECTOR3(m_camTargetX, m_camTargetY, m_camTargetZ);
		D3DXVECTOR3 t_pos = D3DXVECTOR3(m_camX, m_camY, m_camZ);					
		

		D3DXVECTOR3 L = t_target - t_pos;
		D3DXVec3Normalize(&L, &L);				

		D3DXMatrixRotationY(&matrix, yAngle);
		D3DXVec3TransformCoord(&L, &L, &matrix);

		m_camTargetX = m_camX + L.x;
		m_camTargetY = m_camY + L.y;
		m_camTargetZ = m_camZ + L.z;
	}
	
	else if(key == 30)
	{
		float zAngle = -1 / 150.0f;
		D3DXMATRIX matrix;

		D3DXVECTOR3 t_target = D3DXVECTOR3(m_camTargetX, m_camTargetY, m_camTargetZ);
		D3DXVECTOR3 t_pos = D3DXVECTOR3(m_camX, m_camY, m_camZ);					
		D3DXVECTOR3 t_up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		D3DXVECTOR3 L = t_target - t_pos;
		D3DXVec3Normalize(&L, &L);

		D3DXVECTOR3 R;
		D3DXVec3Cross(&R, &t_up, &L);
		D3DXVec3Normalize(&R, &R);

		D3DXVECTOR3 U;
		D3DXVec3Cross(&U, &L, &R);
		D3DXVec3Normalize(&U, &U);	


		D3DXMatrixRotationZ(&matrix, zAngle);
		D3DXVec3TransformCoord(&R, &R, &matrix);
		D3DXVec3TransformCoord(&U, &U, &matrix);
		D3DXVec3TransformCoord(&L, &L, &matrix);

		m_camTargetX = m_camX + L.x;
		m_camTargetY = m_camY + L.y;
		m_camTargetZ = m_camZ + L.z;
	}
	else if(key == 32)
	{
		float zAngle = 1 / 150.0f;
		D3DXMATRIX matrix;

		D3DXVECTOR3 t_target = D3DXVECTOR3(m_camTargetX, m_camTargetY, m_camTargetZ);
		D3DXVECTOR3 t_pos = D3DXVECTOR3(m_camX, m_camY, m_camZ);					
		D3DXVECTOR3 t_up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		D3DXVECTOR3 L = t_target - t_pos;
		D3DXVec3Normalize(&L, &L);

		D3DXVECTOR3 R;
		D3DXVec3Cross(&R, &t_up, &L);
		D3DXVec3Normalize(&R, &R);

		D3DXVECTOR3 U;
		D3DXVec3Cross(&U, &L, &R);
		D3DXVec3Normalize(&U, &U);	


		D3DXMatrixRotationZ(&matrix, zAngle);
		D3DXVec3TransformCoord(&R, &R, &matrix);
		D3DXVec3TransformCoord(&U, &U, &matrix);
		D3DXVec3TransformCoord(&L, &L, &matrix);

		m_camTargetX = m_camX + L.x;
		m_camTargetY = m_camY + L.y;
		m_camTargetZ = m_camZ + L.z;
	}
	
#endif

#if 0
	
	else if(key == 200)
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
	else if(key == 208)
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
	else if(key == 205)
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
	else if(key == 203)
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
#endif
#if 0
	else if(key == 200)
	//UP
	{		
		m_cubeZ += step;
	}
	else if(key == 208)
	{	
	//DOWN	
		
		m_cubeZ -= step;
	}	
	else if(key == 205)
	{
		//RIGHT
		m_cubeX += step;
	}
	else if(key == 203)
	{
		//LEFT
		
		m_cubeX -= step;
	}

	m_cube->SetPosition(m_cubeX, m_cubeY, m_cubeZ);

	
	m_camX = m_cubeX;
	m_camY = m_cubeY + 2.0f;
	m_camZ = m_cubeZ - 5.0f;

	m_camTargetX = m_cubeX;
	m_camTargetY = m_cubeY + 2.0f;
	m_camTargetZ = m_cubeZ - 4.0f;

	
#endif
}
#endif

void Game::CreateMeshBuffers(D3DMesh *mesh)
{
	
	
	D3DRenderer *renderer = (D3DRenderer *) m_renderer;
	
	//indices
	IDirect3DIndexBuffer9 *ib;

	int indicesSize = mesh->GetIndices()->size();
	
	HR(renderer->GetDevice()->CreateIndexBuffer(indicesSize * sizeof(WORD), D3DUSAGE_WRITEONLY,
	D3DFMT_INDEX16, D3DPOOL_MANAGED, &ib, 0));
	WORD *k = 0;

	HR(ib->Lock(0,0,(void**)&k, 0));

	for(int i = 0; i < indicesSize; i++)
	{
		k[i] = mesh->GetIndices()->at(i);
	}

	HR(ib->Unlock());

	//vertices
	IDirect3DVertexBuffer9 * vb;
	int vertexSize = mesh->GetVertices()->size();
	HR(renderer->GetDevice()->CreateVertexBuffer(vertexSize * mesh->GetVertexSize(), D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED, &vb, 0));
	VertexPos *v = 0;
	HR(vb->Lock(0,0,(void**)&v,0));

	for(int i = 0; i < vertexSize; i++)
	{
		v[i] = mesh->GetVertices()->at(i);
	}
	
	HR(vb->Unlock());

	//vertexDeclaration
#if 0
	D3DVERTEXELEMENT9 VertexPosElements[] =
	{
		{0,0,D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
		D3DDECL_END()
	};
#endif

	D3DVERTEXELEMENT9 VertexPosElements[] = 
	{
		{0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
		{0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
		D3DDECL_END()
	};	

	

	IDirect3DVertexDeclaration9 *Decl;
	HR(renderer->GetDevice()->CreateVertexDeclaration(VertexPosElements, &Decl));

	mesh->SetBuffers(vb, ib);
	mesh->SetVertexDeclaration(Decl);

	//mesh->Translate(0.0f, 0.0f, 0.0f);
	mesh->CreateXMesh(((D3DRenderer *)m_renderer)->GetDevice());
}
#if 0

void Game::InitializeMeshes()
{	


	m_testScene = new DefaultScene1();	
	Material *t_material = new Material(	D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),
										D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f), 16.0f);		
	
	//m_auei = (Terrain*)TerrainFactory::GetInstance()->GetTerrainMesh(TERRAIN_NOISE_ID);	

	


	//m_testScene->AddTerrain(m_auei);

	


	m_cube = new Cube();
	m_cube->AddMaterial(t_material);
	//CreateMeshBuffers(m_cube);

	//m_cube->SetPosition(0.0f, m_auei->GetHeight(0.0f, 0.0f), 0.0f);
	m_cube->SetPosition(5.0f, 5.0f, 5.0f);

	//m_cube->SetPosition(0.0f, 0.0f,5.0f);
	m_testScene->AddMesh(m_cube);
	


	

	//m_cubeMovie = new CubeMovie();
	//m_cubeMovie->SetPosition(0.0f, 0.0f, 15.0f);
	//m_testScene->AddMesh(m_cubeMovie);
	//m_cubeMovie->CreateXMesh(D3DRenderer::GetDevice());
	
#if 0

	Tree0 *t_tree0 = new Tree0();
	t_tree0->Scale(0.2f, 0.2f, 0.2f);
	//

	t_tree0->SetPosition(5.0f, m_auei->GetHeight(5.0f, 10.0f), 10.0f);
	//t_tree0->SetPosition(5.0f, 0.0f, 10.0f);

	Tree1 *t_tree1 = new Tree1();
	t_tree1->Scale(0.2f, 0.2f, 0.2f);
	t_tree1->SetPosition(10.0f, m_auei->GetHeight(10.0f, 10.0f), 10.0f);
	//t_tree1->SetPosition(10.0f, 0.0f, 10.0f);

	Tree2 *t_tree2 = new Tree2();
	t_tree2->Scale(0.2f, 0.2f, 0.2f);
	t_tree2->SetPosition(15.0f, m_auei->GetHeight(15.0f, 10.0f), 10.0f);
	//t_tree2->SetPosition(15.0f, 0.0f, 10.0f);

	Tree3 *t_tree3 = new Tree3();
	t_tree3->Scale(0.2f, 0.2f, 0.2f);
	t_tree3->SetPosition(20.0f, m_auei->GetHeight(20.0f, 10.0f), 10.0f);
	//t_tree3->SetPosition(20.0f, 0.0f, 10.0f);

#endif
	
	//Castle *t_castle = new Castle();
	

	D3DImage * d3dImage = new D3DImage(ResourceManager::GetInstance()->GetTextureByID(IMAGE_TIGER_SKIN_ID));	
	
	//Grass *t_grass = new Grass(25, D3DXVECTOR3(1.0f, 0.0f, 0.0f));
	//t_grass->SetPosition(0.0f,0.0f, 0.0f);
	//m_testScene->AddMesh(t_grass);
	D3DImage * t_d3dImage = new D3DImage(ResourceManager::GetInstance()->GetTextureByID(IMAGE_GRASS_BILLBOARD_ID));	
	GrassGrid *t_grassGrid = new GrassGrid(5, 5, D3DXVECTOR3(0.5f, 0.0f, 0.5f), t_d3dImage, 2.0f, 2.0f);
	//t_grassGrid->SetPosition(0.0f, m_auei->GetHeight(0.0f, 0.0f), 0.0f);
	//t_grassGrid->SetPosition(0.0f, 0.0f, 0.0f);
	//m_testScene->AddMesh(t_grassGrid);

	
	//m_billboard = new BillboardMesh(d3dImage);
	//m_billboard->AddMaterial(t_material);
	//m_billboard->SetPosition(5.0f, 5.0f, 5.0f);
	//CreateMeshBuffers(m_billboard);
	//m_testScene->AddMesh(m_billboard);
	
	

	//m_woman = new WomanMesh();
	//m_woman->Scale(0.01f, 0.01f, 0.01f);
	//m_woman->Rotate(-81.0f, 0.0f, 0.0f);
	//m_woman->SetPosition(0.0f, m_auei->GetHeight(0.0f, 0.0f), 0.0f);
	//m_testScene->AddMesh(m_woman);
	

	
	
	//m_testScene->AddMesh(t_tree0);
	//m_testScene->AddMesh(t_tree1);
	//m_testScene->AddMesh(t_tree2);
	//m_testScene->AddMesh(t_tree3);

	
	m_testScene->Initialize();
	
}

#endif

#if 0
void Game::InitializeMeshes()
{	
	

	
	IDirect3DTexture9 * t_texture = ResourceManager::GetInstance()->GetTextureByID(IMAGE_PARTICLE_BOLT_ID);
	
	
	//SupernovaParticleSystem *t_fireRing = new SupernovaParticleSystem(t_texture, 1500, D3DXVECTOR3(0.0f, -9.8f, 0.0f), true);
	//SupernovaParticleSystem *t_fireRing = new SupernovaParticleSystem(t_texture, 500, D3DXVECTOR3(0.0f, -9.8f, 0.0f), true);
	//SupernovaParticleSystem *t_fireRing = new SupernovaParticleSystem(t_texture, 2000, 0.003f, D3DXVECTOR3(-3.0f, -9.8f, 0.0f), false);
	
	FireRingParticleSystem *t_fireRing = new FireRingParticleSystem(t_texture, 1500, 0.0025f, D3DXVECTOR3(0.0f, 0.9f, 0.0f), true);

	t_fireRing->SetPosition(0.0f, 0.0f, 150.0f);
	m_testScene = new DefaultScene1();	
	
	m_cube = new Cube();

	
	
	
	m_testScene->AddMesh(m_cube);	
	m_testScene->AddParticleSystem((ParticleSystem*)t_fireRing);
	
	m_testScene->Initialize();
	
}
#endif

#if 0

void Game::InitializeMeshes()
{	
	m_testScene = new DefaultScene1();	
	Material *t_material = new Material(	D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),
										D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f), 16.0f);		
	

	m_cube = new Cube();
	
	CreateMeshBuffers(m_cube);
	m_testScene->AddMesh(m_cube);	
	
	D3DImage * t_d3dImage = new D3DImage(ResourceManager::GetInstance()->GetTextureByID(IMAGE_GRASS_BILLBOARD_ID));	
	Wall *t_grid = new Wall();
	t_grid->AddMaterial(t_material);
	t_grid->AddTexture((Image*)t_d3dImage);
	m_testScene->AddMesh(t_grid);
	

	m_testScene->Initialize();
	
}

#endif

int GetCorrespondingTextID(int meshID);
float GetCorrespondingScale(int meshID);
D3DXVECTOR2 GetPlanePositions(float x, float y);
float GetRelativeScale(float a_mapScale);

void Game::InitializeMeshes()
{	


	m_testScene = new DefaultScene1();	
	Material *t_material = new Material(	D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),
										D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f), 16.0f);		
	

	//m_auei = (Terrain*)TerrainFactory::GetInstance()->GetTerrainMesh(TERRAIN_NOISE_ID);
	//m_testScene->AddTerrain(m_auei);



	m_woman = new WomanMesh();
	m_woman->SetPosition(0.0f, 0.0f, 0.0f);
	m_woman->Scale(0.01f, 0.01f, 0.01f);
	m_woman->Rotate(-90.0f, 0.0f, 0.0f);
	m_woman->SetAnimation(WomanMesh::ANIMATION_IDLE);
	m_woman->SetBoundingBox(D3DXVECTOR3(-126.0f, 80.0f, 0.0f), D3DXVECTOR3(101.0f, -88.0f, 520.0f));
	m_woman->SetTopCollisionArea(D3DXVECTOR3(-126.0f, -88.0f, 520.0f), D3DXVECTOR3(101.0f, -88.0f, 520.0f), D3DXVECTOR3(-126.0f, 80.0f, 520.0f), D3DXVECTOR3(101.0f, 80.0f, 520.0f));
	
	

	Ground *t_ground = new Ground();

	
	
#if 0

	LandscapeWall3 *t_wall = new LandscapeWall3();
	t_wall->Scale(15.0f, 0.0f, 0.0f);
	
	t_wall->Rotate(0.0f, 90.0f, 0.0f);
	m_testScene->AddMesh(t_wall);

	Cube *t_cube = new Cube();
	t_cube->SetPosition(5.0f, 5.0f, 5.0f);
	m_testScene->AddMesh(t_cube);
#endif

#if 1
	//GENERATED CODE		
	//#include "Tools/Map/mapPositions.h"

	
	IDirect3DTexture9 * t = ResourceManager::GetInstance()->GetTextureByID(IMAGE_FONT_VERDANA_36_ID);
	D3DImage *image = new D3DImage(t);		
	m_font = new Font(	image,ResourceManager::GetInstance()->GetFontDescriptor(FONT_VERDANA_36_ID));

	t_house = new LandscapeMesh(MESH_HOUSE_2_ID, IMAGE_HOUSE_2_ID);

	m_testScene->AddMesh(t_house);
	m_text = new Text("QWERTY UI", m_font);
	m_text->SetX(250);
	m_text->SetY(250);
	m_text->SetColor(0xffff0000);
	
	m_testScene->AddMesh(t_ground);

	m_testScene->AddMesh(m_woman);	
	

	Skybox *t_skybox = new Skybox(1000);
	t_skybox->SetPosition(0.0f, 200, 0.0f);

	m_testScene->AddMesh(t_skybox);	
#endif
	m_testScene->Initialize();
	
}



int GetCorrespondingTextID(int meshID)
{
	int t[27];
	t[MESH_CAFE_TABLE_ID - MESH_CAFE_TABLE_ID] = IMAGE_CAFE_TABLE_ID;
	t[MESH_GARDEN_BORDER_ID - MESH_CAFE_TABLE_ID] = IMAGE_GARDEN_BORDER_ID;
	t[MESH_MAILBOX01_ID - MESH_CAFE_TABLE_ID] = IMAGE_MAILBOX01_ID;
	t[MESH_MAILBOX02_ID - MESH_CAFE_TABLE_ID] = IMAGE_MAILBOX02_ID;
	t[MESH_MAILBOX03_ID - MESH_CAFE_TABLE_ID] = IMAGE_MAILBOX03_ID;
	t[MESH_PARKING_BARRIER_ID - MESH_CAFE_TABLE_ID] = IMAGE_PARKING_BARRIER_ID;
	t[MESH_PALETTE_ID - MESH_CAFE_TABLE_ID] = IMAGE_PALETTE_ID;
	t[MESH_PIPE_CAGE_ID - MESH_CAFE_TABLE_ID] = IMAGE_PIPE_CAGE_ID;
	t[MESH_SANDWICH_BOARD_ID - MESH_CAFE_TABLE_ID] = IMAGE_SANDWICH_BOARD_ID;
	t[MESH_SIDEWALK_BARRIER_ID - MESH_CAFE_TABLE_ID] = IMAGE_SIDEWALK_BARRIER_ID;
	t[MESH_SIGN01_ID - MESH_CAFE_TABLE_ID] = IMAGE_SIGN01_ID;
	t[MESH_SIGN02_ID - MESH_CAFE_TABLE_ID] = IMAGE_SIGN02_ID;
	t[MESH_SIGN03_ID - MESH_CAFE_TABLE_ID] = IMAGE_SIGN03_ID;
	t[MESH_SIGN04_ID - MESH_CAFE_TABLE_ID] = IMAGE_SIGN04_ID;
	t[MESH_SIGN05_ID - MESH_CAFE_TABLE_ID] = IMAGE_SIGN05_ID;
	t[MESH_SIGN06_ID - MESH_CAFE_TABLE_ID] = IMAGE_SIGN06_ID;
	t[MESH_SPRINKLER_ID - MESH_CAFE_TABLE_ID] = IMAGE_SPRINKLER_ID;
	t[MESH_BENCH_ID - MESH_CAFE_TABLE_ID] = IMAGE_BENCH_ID;
	t[MESH_STREET_LIGHT_01_ID - MESH_CAFE_TABLE_ID] = 	IMAGE_STREET_LIGHT_01_ID;
	t[MESH_STREET_LIGHT_02_ID - MESH_CAFE_TABLE_ID] = 	IMAGE_STREET_LIGHT_02_ID;
	t[MESH_SWITCHBOX_ID - MESH_CAFE_TABLE_ID] = IMAGE_SWITCHBOX_ID;
	t[MESH_TRAFFIC_CONE_ID - MESH_CAFE_TABLE_ID] = IMAGE_TRAFFIC_CONE_ID;
	t[MESH_HOUSE_ID - MESH_CAFE_TABLE_ID] = IMAGE_HOUSE_ID;
	t[MESH_HOUSE_2_ID - MESH_CAFE_TABLE_ID] = IMAGE_HOUSE_2_ID;
	t[MESH_HOUSE_3_ID - MESH_CAFE_TABLE_ID] = IMAGE_HOUSE_3_ID;
	t[MESH_HOUSE_4_ID - MESH_CAFE_TABLE_ID] = IMAGE_HOUSE_4_ID;
	t[MESH_HOUSE_5_ID - MESH_CAFE_TABLE_ID] = IMAGE_HOUSE_5_ID;

	return t[meshID - MESH_CAFE_TABLE_ID];
	
	
}

float GetRelativeScale(float a_mapScale)
{
	float mapSize = 512.0f;
	float planeSize = 500.0f;

	return a_mapScale * (planeSize/mapSize);
}

float GetCorrespondingScale(int meshID)
{
	
	float t_scales[27];
	t_scales[MESH_CAFE_TABLE_ID - MESH_CAFE_TABLE_ID]				= 2.2f;
	t_scales[MESH_GARDEN_BORDER_ID - MESH_CAFE_TABLE_ID]			= 4.49f;
	t_scales[MESH_MAILBOX01_ID - MESH_CAFE_TABLE_ID]				= 2.29f;
	t_scales[MESH_MAILBOX02_ID - MESH_CAFE_TABLE_ID]				= 2.24f;
	t_scales[MESH_MAILBOX03_ID - MESH_CAFE_TABLE_ID]				= 1.99f;
	t_scales[MESH_PARKING_BARRIER_ID - MESH_CAFE_TABLE_ID]			= 2.9f;
	t_scales[MESH_PALETTE_ID - MESH_CAFE_TABLE_ID]					= 2.5f;
	t_scales[MESH_PIPE_CAGE_ID - MESH_CAFE_TABLE_ID]				= 3.47f;
	t_scales[MESH_SANDWICH_BOARD_ID - MESH_CAFE_TABLE_ID]			= 3.19f;
	t_scales[MESH_SIDEWALK_BARRIER_ID - MESH_CAFE_TABLE_ID]			= 1.57f;
	t_scales[MESH_SIGN01_ID - MESH_CAFE_TABLE_ID]					= 2.68f;
	t_scales[MESH_SIGN02_ID - MESH_CAFE_TABLE_ID]					= 2.23f;
	t_scales[MESH_SIGN03_ID - MESH_CAFE_TABLE_ID]					= 2.68f;
	t_scales[MESH_SIGN04_ID - MESH_CAFE_TABLE_ID]					= 2.42f;
	t_scales[MESH_SIGN05_ID - MESH_CAFE_TABLE_ID]					= 3.25f;
	t_scales[MESH_SIGN06_ID - MESH_CAFE_TABLE_ID]					= 3.31f;
	t_scales[MESH_SPRINKLER_ID - MESH_CAFE_TABLE_ID]				= 6.83f;
	t_scales[MESH_BENCH_ID - MESH_CAFE_TABLE_ID]					= 1.94f;
	t_scales[MESH_STREET_LIGHT_01_ID - MESH_CAFE_TABLE_ID]			= 0.51f;
	t_scales[MESH_STREET_LIGHT_02_ID - MESH_CAFE_TABLE_ID]			= 2.97f;
	t_scales[MESH_SWITCHBOX_ID - MESH_CAFE_TABLE_ID]				= 1.66f;
	t_scales[MESH_TRAFFIC_CONE_ID - MESH_CAFE_TABLE_ID]				= 2.04f;
	t_scales[MESH_HOUSE_ID - MESH_CAFE_TABLE_ID]					= 4.39f;
	t_scales[MESH_HOUSE_2_ID - MESH_CAFE_TABLE_ID]					= 6.99f;
	t_scales[MESH_HOUSE_3_ID - MESH_CAFE_TABLE_ID]					= 4.39f;
	t_scales[MESH_HOUSE_4_ID - MESH_CAFE_TABLE_ID]					= 4.39f;
	t_scales[MESH_HOUSE_5_ID - MESH_CAFE_TABLE_ID]					= 4.39f;

	if(meshID == MESH_TREE_0_ID || meshID == MESH_TREE_1_ID || meshID == MESH_TREE_2_ID || meshID == MESH_TREE_3_ID)
	{
		return 0.2f;
	}


	return t_scales[meshID - MESH_CAFE_TABLE_ID];
}

D3DXVECTOR2 GetPlanePositions(float x, float y)
{
	float tx = x;
	float ty = y;
	float t_normalizedX = tx / 512.0f;
	float t_normalizedZ = ty / 512.0f;
	float t_groundSize = 500.0f;

	D3DXVECTOR2 t_returned = D3DXVECTOR2(t_normalizedX * t_groundSize - (t_groundSize/2.0f),250.0f - t_normalizedZ * t_groundSize);
	return t_returned;
}



void Game::OnKeyUp(int key)
{
	
}
