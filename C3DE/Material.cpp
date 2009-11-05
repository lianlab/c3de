#include "Material.h"
#include "DebugMemory.h"

//Material * Material::WHITE = new Material(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 16.0f);

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

