#include "Mesh.h"
#include "DebugMemory.h"

Mesh::Mesh()
{	
	m_material = new Material(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), 16.0f);
	m_scaleX = 1.0f;
	m_scaleY = 1.0f;
	m_scaleZ = 1.0f;

	m_x = 0.0f;
	m_y = 0.0f;
	m_z = 0.0f;

	m_texture = NULL;
}

Mesh::~Mesh()
{
	if(m_material)
	{
		delete m_material;
		m_material = NULL;
	}
}

void Mesh::SetMaterial(Material *material)
{
	if(m_material)
	{
		delete m_material;
		m_material = NULL;
	}
	m_material = material;
}