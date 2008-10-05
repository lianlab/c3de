#include "Application.h"

//include all singletons in this class, and delete them all at the destructor
#include "WindowsPerformanceCounter.h"
#include "Debug.h"
#include "ResourceManager.h"
#include "ShaderManager.h"
#include "DebugMemory.h"

Application::Application()
{	
	SetupRenderer();
	SetupWindow();
	
}

Application::~Application()
{	
	delete WindowsPerformanceCounter::GetInstance();
	delete Debug::GetInstance();
	delete ResourceManager::GetInstance();
	delete ShaderManager::GetInstance();
}

bool Application::Init()
{				
	return true;
}

bool Application::Update(int deltaTime)
{	
	return true;
}

bool Application::Render()
{    
	return true;
}

bool Application::Cleanup()
{	
	return true;
}

/*
bool Application::Quit()
{
	return true;
}
*/

void Application::SetupRenderer()
{

}

void Application::SetupWindow()
{

}
