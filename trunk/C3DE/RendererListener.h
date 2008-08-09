#ifndef RENDERER_LISTENER_H
#define RENDERER_LISTENER_H

class RendererListener
{
public:
	RendererListener();
	virtual ~RendererListener();

	virtual void OnLostDevice() = 0;
	virtual void OnResetDevice() = 0;
};
#endif