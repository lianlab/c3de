#include "D3DApplication.h"
#include "Debug.h"
#include "WindowsPerformanceCounter.h"
#include "DirectInput.h"
#include "DebugMemory.h"



D3DApplication::D3DApplication()
{
	SetupWindow();	
	SetupRenderer();
}

D3DApplication::~D3DApplication()
{
	delete m_renderer;
	delete m_input;
	delete m_game;
}


void D3DApplication::SetupRenderer()
{
	m_renderer = new D3DRenderer();
}

void D3DApplication::SetupWindow()
{

}


bool D3DApplication::Init(HINSTANCE hInstance, int width, int height, bool windowed)
{	


#if defined(DEBUG) | defined(_DEBUG)
	
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF |_CRTDBG_LEAK_CHECK_DF);
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF);
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
	
	m_mainWindow = CreateWindow("D3DWND", "C3DE", WS_EX_TOPMOST| WS_POPUPWINDOW, 0, 0, width, height, 0, 0, hInstance, 0); 
	SetCursor(NULL);
	ShowWindow(m_mainWindow, SW_SHOW);
	UpdateWindow(m_mainWindow);
	
	WindowsApplicationWindow *window = new WindowsApplicationWindow(m_hInstance, m_mainWindow, width, height);
	m_renderer->Init(window, windowed);	
	
	m_input = DirectInput::GetInstance();
	m_input->Init(m_hInstance, m_mainWindow);		

	m_performanceCounter = WindowsPerformanceCounter::GetInstance();

	ResourceManager::GetInstance()->SetDevice(m_renderer->GetDevice());

	ShaderManager::GetInstance()->SetDevice(m_renderer->GetDevice());
	

	m_game = new Game(this);

	//m_input->AddKeyboardListener((KeyboardListener *)m_game);
	m_input->AddMouseListener((MouseListener *)m_game);	

	//m_game->SetInputer(m_input);

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
	sprintf_s(msg, "FPS: %.4f\n%d\n%d", fps, m_game->hx, m_game->hy);

	m_game->Render(m_renderer);
	m_renderer->RenderText(msg);	
	

	m_renderer->EndRender();
	
	return true;
}

bool D3DApplication::Update(int deltaTime)
{
	m_performanceCounter->Update(deltaTime);		
	m_input->Update();
	m_game->Update(deltaTime);
	return true;
}

bool D3DApplication::Quit()
{	
	m_input->RemoveKeyboardListener((KeyboardListener *)m_game);
	m_input->RemoveMouseListener((MouseListener*)m_game);
	PostQuitMessage(0);
	return true;
}

bool D3DApplication::Cleanup()
{
	return true;
}




