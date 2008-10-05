#include "Material.h"
#include "DebugMemory.h"



Material::Material(D3DXCOLOR ambient, D3DXCOLOR  diffuse, D3DXCOLOR specular, float specPower)
{
	m_ambient = ambient;
	m_diffuse = diffuse;
	m_specular = specular;
	m_specularPower = specPower;
}


Material::~Material()
{

}

