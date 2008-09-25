#ifndef CUBE_H
#define CUBE_H

#include "D3DMesh.h"

class Cube : public D3DMesh
{
public:
	Cube();
	~Cube();

	
	void SetEffectHandles(ID3DXEffect* fx);
	void InitializeEffectHandles(ID3DXEffect* fx);

private:

	D3DXHANDLE   m_hTex;
	
};
#endif

