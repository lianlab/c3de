#include "WindowsPerformanceCounter.h"
#include "DebugMemory.h"

WindowsPerformanceCounter * WindowsPerformanceCounter::m_instance = NULL;

WindowsPerformanceCounter::WindowsPerformanceCounter()
{

}

WindowsPerformanceCounter::~WindowsPerformanceCounter()
{

}

WindowsPerformanceCounter * WindowsPerformanceCounter::GetInstance()
{
	if(!m_instance)
	{
		m_instance = new WindowsPerformanceCounter();
	}

	return m_instance;

}

int WindowsPerformanceCounter::GetFPS()
{
	return 1;
}

void WindowsPerformanceCounter::Update(float dt)
{
	static float numFrames = 0.0f;
	static float timeElapsed = 0.0f;

	numFrames += 1.0f;

	timeElapsed += dt;

	if(timeElapsed >= 1.0f)
	{
		m_fps = numFrames;
		m_milliSecondsPerFrame += 1000.0f / m_fps;
		timeElapsed = 0.0f;
		numFrames = 0.0f;
	}
}

