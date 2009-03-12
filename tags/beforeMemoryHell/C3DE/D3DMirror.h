#ifndef D3DMIRROR_H
#define D3DMIRROR_H

#include "Mirror.h"
#include "D3DMesh.h"

class D3DMirror : public Mirror
{
public:
	D3DMirror(D3DMesh *mesh);
	~D3DMirror();
	D3DXPLANE *GetPlane(){return m_plane;}
protected:
	D3DXPLANE *m_plane;

};
#endif