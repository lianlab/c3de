#ifndef LIGHT_H
#define LIGHT_H

#include "Material.h"
#include <d3dx9.h>

class Light
{
public:
	Light();
	~Light();
	void SetColor(Material a_color);
	Material GetColor(){return m_color;}
	D3DXCOLOR GetD3DColor(){return m_d3dColor;}
protected:
	Material m_color;
	D3DXCOLOR m_d3dColor;
};
#endif