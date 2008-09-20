#ifndef LIGHT_H
#define LIGHT_H

#include "Material.h"
#include <d3dx9.h>

class Light
{
public:
	Light();
	~Light();
	void SetColor(D3DXCOLOR a_color){m_color = a_color;}
	D3DXCOLOR GetColor(){return m_color;}
	
protected:
	D3DXCOLOR m_color;
	
};
#endif