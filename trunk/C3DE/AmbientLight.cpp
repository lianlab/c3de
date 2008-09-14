#include "AmbientLight.h"

AmbientLight::AmbientLight():Light()
{
	m_color = Material(1.0f, 1.0f, 1.0f, 1.0f);
}

AmbientLight::~AmbientLight()
{

}