#include "Light.h"

Light::Light()
{
	SetColor(Material(1.0f, 1.0f, 1.0f, 1.0f));
}

Light::~Light()
{

}

void Light::SetColor(Material a_color)
{
	m_color = a_color;
	m_d3dColor = D3DXCOLOR(a_color.r,a_color.g,a_color.b,a_color.a);
}