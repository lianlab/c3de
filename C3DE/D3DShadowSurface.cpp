#include "D3DShadowSurface.h"
#include "DebugMemory.h"

D3DShadowSurface::D3DShadowSurface(D3DMesh * mesh):ShadowSurface((Mesh *)mesh)
{
	m_plane = new D3DXPLANE(0.0f, -1.0f, 0.0f, 0.0f); // xy plane
	
}

D3DShadowSurface::~D3DShadowSurface()
{

}
