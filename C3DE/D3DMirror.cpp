#include "D3DMirror.h"
#include "DebugMemory.h"

D3DMirror::D3DMirror(D3DMesh * mesh):Mirror((Mesh *)mesh)
{
	m_plane = NULL;
	
}

D3DMirror::~D3DMirror()
{
	if(m_plane)
	{
		delete m_plane;
		m_plane = NULL;
	}
}
