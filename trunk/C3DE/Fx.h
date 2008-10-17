#ifndef FX_H
#define FX_H

#include "d3dx9.h"
class FX
{
public:
	FX(ID3DXEffect * effect);
	~FX();

	ID3DXEffect * GetEffect(){return m_effect;}
private:
	ID3DXEffect * m_effect;
};
#endif