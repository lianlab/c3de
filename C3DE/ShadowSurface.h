#ifndef SHADOW_SURFACE_H
#define SHADOW_SURFACE_H


#include "Mesh.h"


class ShadowSurface 
{
public:
	ShadowSurface(Mesh *);
	virtual ~ShadowSurface();
	Mesh * GetMesh(){return m_mesh;}
protected:
	Mesh *m_mesh;
};

#endif

