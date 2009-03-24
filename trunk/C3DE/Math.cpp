#include "Math.h"
#include <stdlib.h>

float GetRandomFloat(float a, float b)
{
	if( a >= b ) // bad input
		return a;

	// Get random float in [0, 1] interval.
	float f = (rand()%10001) * 0.0001f;

	return (f*(b-a))+a;
}

void GetRandomVec(D3DXVECTOR3& out)
{
	out.x = GetRandomFloat(-1.0f, 1.0f);
	out.y = GetRandomFloat(-1.0f, 1.0f);
	out.z = GetRandomFloat(-1.0f, 1.0f);

	// Project onto unit sphere.
	D3DXVec3Normalize(&out, &out);
}