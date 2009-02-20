#include "Game.h"
#include "ShaderManager.h"
#include "D3DCamera.h"
#include "D3DRenderer.h"
#include "TerrainFactory.h"
#include "TerrainForest.h"
#include "DirectInput.h"


//THIS CLASS CAN'T OVERRIDE THE NEW OPERATOR OR IT WILL SCREW UP ALL DIRECTX DRAWING
//#include "DebugMemory.h"


using namespace std;

Game::Game(Application * app)
{
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
	m_cubeY = 50.0f;
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
	//delete m_testScene;
	delete m_sprite;
	delete m_button;


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

void Game::Update(int deltaTime)
{
	
	//m_sprite->SetX(m_sprite->GetX() + m_speed);
	//m_sprite->SetY(m_sprite->GetY() + m_yspeed);

	UpdateInput();

	if(m_sprite->GetX() > 640 || m_sprite->GetX() < 0)
	{
		m_speed = m_speed * -1;
	}

	if(m_sprite->GetY() > 480 || m_sprite->GetY() < 0)
	{
		m_yspeed = m_yspeed * -1;
	}
	m_sprite->Update(deltaTime);

	m_deltaTime = deltaTime;

	m_testScene->Update(deltaTime);

	//m_videoMesh->Update(deltaTime);

	//m_testMesh->Update(1);

	//m_grid->Update(10);
	
}

void Game::UpdateInput()
{

	float step = 0.1f;
	float t_fleps = 0.0f;

	float t_angle = 0.0f;

	if(DirectInput::GetInstance()->IsKeyDown(1))
	{
		m_application->Quit();
		return;
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
	
	m_cube->Rotate(m_cube->GetRotationX(), m_cube->GetRotationY() + t_dAngle, m_cube->GetRotationZ());

	m_cubeX += newPos.x;
	m_cubeY += newPos.y;
	m_cubeZ += newPos.z;

	m_cube->SetPosition(m_cubeX, m_cubeY, m_cubeZ);

#define LOCK_CAMERA 0
#define FIXED_CAMERA 1
#if LOCK_CAMERA
	D3DXVECTOR3 t_camLook = m_carDirection * -15.0f;
	t_camLook.x = m_cubeX + t_camLook.x;
	t_camLook.y = m_cubeY + t_camLook.y;
	t_camLook.z = m_cubeZ + t_camLook.z;

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




void Game::Render(Renderer *renderer)
{
	//

	D3DCamera * cam = (D3DCamera *)renderer->GetCamera();
	float x = m_cameraRadius * cosf(m_cameraRotation);
	float z =  m_cameraRadius * sinf(m_cameraRotation);

	cam->SetPosition(m_camX, m_camY, m_camZ);
	cam->SetUp(m_camUpX, m_camUpY, m_camUpZ);	
	cam->SetTarget(m_camTargetX, m_camTargetY, m_camTargetZ);
	
	renderer->DrawScene(m_testScene);
	renderer->DrawSprite(m_button);
	renderer->DrawSprite((Sprite *)m_sprite);
	static_cast<D3DRenderer *>(renderer)->DrawAxis();

	
}

void Game::OnMouseDown(int button, int x , int y)
{
	int fdfd = 878;
}

void Game::OnMouseUp(int button, int x, int y)
{
	int moueskfd = button;
}

#if 1
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
	float t_angle = yAngle * 57.29577951308232286465f;

	m_cube->Rotate(m_cube->GetRotationX(), m_cube->GetRotationY() + t_angle, m_cube->GetRotationZ());
	
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
	Mesh * target = (Mesh*)m_auei;
	//Mesh * target = (Mesh*)m_skinMesh;
	float step = 0.1f;

	if(key == 1)
	{
		m_application->Quit();
	}

	
	

#if 0
	else if(key == 200)
	{		
		target->Scale(target->GetXScale(), target->GetYScale(), target->GetZScale() - step);		
		
		
	}
	else if(key == 208)
	{		
		target->Scale(target->GetXScale(), target->GetYScale(), target->GetZScale() + step);		
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
#if 1
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

void Game::InitializeMeshes()
{	
	m_testScene = new DefaultScene1();	
	Material *t_material = new Material(	D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),
										D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f), 16.0f);		
	
	m_auei = (Terrain*)TerrainFactory::GetInstance()->GetTerrainMesh(TERRAIN_NORMAL_ID);	

	Terrain *porra = (Terrain*)TerrainFactory::GetInstance()->GetTerrainMesh(TERRAIN_FOREST_ID);	

	Terrain *carai = (Terrain*)TerrainFactory::GetInstance()->GetTerrainMesh(TERRAIN_NORMAL_ID);

	//Terrain *tt = (Terrain*)TerrainFactory::GetInstance()->GetTerrainMesh(TERRAIN_FOREST_ID);	
	//m_testScene->AddTerrain(tt);

	//tt->SetPosition(0.0f, 500.0f, 0.0f);
#if HACK_FROM_SCRATCH
	CreateMeshBuffers(m_auei);
#endif

	m_testScene->AddTerrain(m_auei);

	porra->SetPosition(0.0f, -100.0f, 0.0f);

	carai->SetPosition(0.0f, -200.0f, 0.0f);
	m_testScene->AddTerrain(porra);
	m_testScene->AddTerrain(carai);
	//m_testScene->AddMesh(m_auei);

	//Terrain *porra = (Terrain*)TerrainFactory::GetInstance()->GetTerrainMesh(TERRAIN_NORMAL_ID);		
	//m_testScene->AddMesh(porra);
	//m_testScene->AddTerrain(porra);

	//Terrain *carai = (Terrain*)TerrainFactory::GetInstance()->GetTerrainMesh(TERRAIN_FOREST_ID);		
	//m_testScene->AddMesh(carai);

	//m_testScene->AddTerrain(carai);

	//porra->SetPosition(0.0f, 15.0f, 0.0f);

	//carai->SetPosition(0.0f, 30.0f, 0.0f);

#if 1
	m_cube = new Cube();
	m_cube->AddMaterial(t_material);
	CreateMeshBuffers(m_cube);
	m_cube->SetPosition(m_cubeX, m_cubeY, m_cubeZ);
	m_testScene->AddMesh(m_cube);
#endif

	m_videoMesh = new Billboard();
	//m_videoMesh->AddMaterial(t_material);
	m_videoMesh->SetPosition(0.0f, 0.0f, 15.0f);
	//CreateMeshBuffers((D3DMesh*)m_videoMesh);
	//m_testScene->AddMesh(m_videoMesh);

	m_cubeMovie = new CubeMovie();
	m_cubeMovie->SetPosition(0.0f, 0.0f, 2.0f);
	//CreateMeshBuffers((D3DMesh*)m_cubeMovie);
	//m_testScene->AddMesh(m_cubeMovie);

	m_testScene->Initialize();
	
}


void Game::OnKeyUp(int key)
{
	
}
