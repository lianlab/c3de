#ifndef D3D_SHADOW_SURFACE_H
#define D3D_SHADOW_SURFACE_H

#include "ShadowSurface.h"
#include "D3DMesh.h"

class D3DShadowSurface : public ShadowSurface
{
public:
	D3DShadowSurface(D3DMesh *mesh);
	~D3DShadowSurface();
	D3DXPLANE *GetPlane(){
		return m_plane;
	}
protected:
	D3DXPLANE *m_plane;

};
#endif