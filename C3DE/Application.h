#ifndef APPLICATION_H
#define APPLICATION_H

#include "Renderer.h"
#include "RendererListener.h"
#include "PerformanceCounter.h"
#include "Input.h"
#include "ResourceManager.h"



class Application : public RendererListener
{
public:
	Application();
	virtual ~Application();
	bool Init();
	bool Update(int deltaTime);
	bool Render();
	bool Cleanup();
	virtual bool Quit() = 0;

	virtual void OnLostDevice() = 0;
	virtual void OnResetDevice() = 0;

	virtual Renderer *GetRenderer() = 0;
	
	
protected:
	Renderer *m_renderer;
	bool m_windowed;
	int m_width;
	int m_height;
	PerformanceCounter *m_performanceCounter;
	Input *m_input;
	
	
private:
	virtual void SetupRenderer() = 0;
	virtual void SetupWindow() = 0;
	
	
};

#endif
