#include "Renderer.h"
#include "PlanarMirror.h"
#include "ResourceManager.h"
#include "DebugMemory.h"

PlanarMirror::PlanarMirror(D3DMesh *mesh):D3DMirror(mesh)
{
	m_plane = new D3DXPLANE(0.0f, 0.0f, 1.0f, 0.0f); // xy plane
	
}


PlanarMirror::~PlanarMirror()
{
	//ReleaseCOM(m_vertexDeclaration);
}

