#ifndef WINDOWS_PERFORMANCE_COUNTER_H
#define WINDOWS_PERFORMANCE_COUNTER_H

#include "PerformanceCounter.h"
#include "windows.h"

class WindowsPerformanceCounter : public PerformanceCounter
{
private:
	WindowsPerformanceCounter();
	static WindowsPerformanceCounter * m_instance;

public:
	static WindowsPerformanceCounter *GetInstance();
	virtual ~WindowsPerformanceCounter();
	void Update(float dt);
	
	int GetFPS();
	
};
#endif