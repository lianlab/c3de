#include "Renderer.h"
#include "PlanarShadowSurface.h"
#include "ResourceManager.h"
#include "DebugMemory.h"

PlanarShadowSurface::PlanarShadowSurface(D3DMesh *mesh):D3DShadowSurface(mesh)
{
	m_plane = new D3DXPLANE(0.0f, -1.0f, 0.0f, 0.0f); // xy plane
	
}


PlanarShadowSurface::~PlanarShadowSurface()
{
	//ReleaseCOM(m_vertexDeclaration);
}

