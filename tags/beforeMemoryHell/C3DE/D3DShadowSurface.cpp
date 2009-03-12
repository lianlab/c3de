#include "D3DShadowSurface.h"
#include "DebugMemory.h"

D3DShadowSurface::D3DShadowSurface(D3DMesh * mesh):ShadowSurface((Mesh *)mesh)
{
	m_plane = NULL;
	
}

D3DShadowSurface::~D3DShadowSurface()
{
	if(m_plane)
	{
		delete m_plane;
		m_plane = NULL;
	}
}
