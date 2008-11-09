#ifndef PLANAR_SHADOW_SURFACE_H
#define PLANAR_SHADOW_SURFACE_H

#include "D3DShadowSurface.h"

class PlanarShadowSurface : public D3DShadowSurface
{
public:
	PlanarShadowSurface(D3DMesh *mesh);
	~PlanarShadowSurface();	

	
};
#endif

