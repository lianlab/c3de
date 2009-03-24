#ifndef AABB_H
#define AABB_H

#include <d3dx9.h>
#include "D3DCommonDefs.h"
//#include "DebugMemory.h"

class AABB
{
public:
	AABB(D3DXVECTOR3 a_min, D3DXVECTOR3 a_max){minPoint = a_min; maxPoint =  a_max;}
	//AABB(){minPoint = D3DXVECTOR3(0.0f, 0.0f, 0.0f); maxPoint =  D3DXVECTOR3(0.0f, 0.0f, 0.0f);}
	~AABB(){};
	D3DXVECTOR3 minPoint;
	D3DXVECTOR3 maxPoint;
};

#endif