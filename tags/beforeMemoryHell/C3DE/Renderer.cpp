#include "Renderer.h"
#include "DebugMemory.h"

Renderer::Renderer()
{
	m_listeners = new vector<RendererListener *>;
}

Renderer::~Renderer()
{
	delete m_listeners;
}


void Renderer::Reset()
{

}

void Renderer::AddListener(RendererListener *listener)
{
	m_listeners->push_back(listener);
}

void Renderer::RemoveListener(RendererListener *a_listener)
{
	RendererListener *listener;
	for(int i = 0; i < m_listeners->size(); i++)
	{
		listener = m_listeners->at(i);
		if(listener == a_listener)
		{
			//m_listeners.erase(str_Vector.begin()+i,str_Vector.begin()+2);
			m_listeners->erase(m_listeners->begin() + i);
		}
	}
	
}




