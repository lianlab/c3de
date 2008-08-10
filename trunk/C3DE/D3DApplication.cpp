#include "D3DApplication.h"
#include "Debug.h"
#include "WindowsPerformanceCounter.h"
#include "DirectInput.h"
#include "DebugMemory.h"

D3DApplication::D3DApplication()
{
	SetupRenderer();
	SetupWindow();
}

D3DApplication::~D3DApplication()
{
	delete m_renderer;
	delete m_input;
}

void D3DApplication::SetupRenderer()
{
	m_renderer = new D3DRenderer();
}

void D3DApplication::SetupWindow()
{

}

void D3DApplication::OnMouseDown(int button)
{
	int fdfd = 878;
}

void D3DApplication::OnMouseUp(int button)
{
	int moueskfd = button;
}

void D3DApplication::OnMouseMove(int x, int y)
{

}

void D3DApplication::OnKeyDown(int key)
{
	
}

void D3DApplication::OnKeyUp(int key)
{
	if(key == DIK_ESCAPE)
	{
		PostQuitMessage(0);
	}
}

bool D3DApplication::Init(HINSTANCE hInstance, int width, int height, bool windowed)
{	
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF |
		_CRTDBG_LEAK_CHECK_DF);
#endif
	m_hInstance = hInstance;
	m_width = width;
	m_height = height;
	m_windowed = windowed;

	Debug::GetInstance()->Print("Application initiated");

	//Create Window Class
	WNDCLASS wc;
	memset(&wc, 0, sizeof(WNDCLASS));
	wc.style         = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc   = (WNDPROC)::DefWindowProc; 
	wc.hInstance     = m_hInstance;
	wc.lpszClassName = "D3DWND";

	//Register Class and Create new Window
	RegisterClass(&wc);
	
	m_mainWindow = CreateWindow("D3DWND", "C3DE", WS_EX_TOPMOST, 0, 0, width, height, 0, 0, hInstance, 0); 
	SetCursor(NULL);
	ShowWindow(m_mainWindow, SW_SHOW);
	UpdateWindow(m_mainWindow);

	//*D3DRenderer(m_renderer)->Init(m_hInstance, m_mainWindow, width, height, windowed);
	//D3DRenderer d3dRenderer = D3DRenderer(*m_renderer);
	WindowsApplicationWindow *window = new WindowsApplicationWindow(m_hInstance, m_mainWindow, width, height);
	m_renderer->Init(window);

	//m_renderer->SetScreenMode(SCREEN_MODE_WINDOWED);
	
	m_input = new DirectInput();

	m_input->Init(m_hInstance, m_mainWindow);
	m_input->AddKeyboardListener(this);
	m_input->AddMouseListener(this);

	//int id = SPRITE_SHIP_ID;
	//C3DESprite * sprite = ResourceManager::GetInstance()->GetSpriteByID(id);
	//m_sprite = new D3DSprite(sprite->ge

	m_performanceCounter = WindowsPerformanceCounter::GetInstance();

	ResourceManager::GetInstance()->SetDevice(m_renderer->GetDevice());

	//int *leak = new int();


	/////////////
	//HACK
	IDirect3DTexture9 * t = ResourceManager::GetInstance()->GetImageByID(IMAGE_EXPLOSION_ID);
	D3DImage *image = new D3DImage(t);				
	m_sprite = new D3DSprite(image, 64, 64, 30, 6, 5, 100);

	//

	m_sprite->SetX(50);
	m_sprite->SetY(50);
	
	


	return true;
}

void D3DApplication::OnLostDevice()
{
	int n = 43;
}

void D3DApplication::OnResetDevice()
{
	int n = 43;
}

bool D3DApplication::Render()
{
	
	m_renderer->Clear();
	m_renderer->BeginRender();

	static char msg[256];
	float fps = m_performanceCounter->GetFPS();
	sprintf_s(msg, "FPS: %.4f", fps);

	

	m_renderer->RenderText(msg);		
	m_renderer->DrawSprite((Sprite *) m_sprite, 0, 0);
	m_renderer->EndRender();

	
	return true;
}

bool D3DApplication::Update(float deltaTime)
{
	m_performanceCounter->Update(deltaTime);
	m_sprite->Update(1);
	m_input->Update();
	return true;
}

bool D3DApplication::Quit()
{
	return true;
}

bool D3DApplication::Cleanup()
{
	return true;
}


