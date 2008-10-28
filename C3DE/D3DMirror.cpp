#include "D3DMirror.h"
#include "DebugMemory.h"

D3DMirror::D3DMirror(D3DMesh * mesh):Mirror((Mesh *)mesh)
{
	m_plane = new D3DXPLANE(0.0f, 0.0f, 1.0f, 0.0f); // xy plane
	
}

D3DMirror::~D3DMirror()
{

}
