#ifndef BOOK_LIGHTS_H
#define BOOK_LIGHTS_H

#include "FX.h"

class BookLights : public FX
{
public:
	BookLights(ID3DXEffect * effect);
	~BookLights();
};
#endif