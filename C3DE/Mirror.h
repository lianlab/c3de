#ifndef MIRROR_H
#define MIRROR_H

#include "Mesh.h"


class Mirror 
{
public:
	Mirror(Mesh *);
	virtual ~Mirror();
	Mesh * GetMesh(){return m_mesh;}
protected:
	Mesh *m_mesh;
};

#endif