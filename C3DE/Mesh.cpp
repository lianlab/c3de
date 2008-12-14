#include "Renderer.h"
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

	m_rotateX = 0.0f;
	m_rotateY = 0.0f;
	m_rotateZ = 0.0f;

	m_texture = NULL;

	m_alpha = 1.0f;
}

Mesh::~Mesh()
{

	if(m_material)
	{
		delete m_material;
		m_material = NULL;
	}

	if(m_texture)
	{
		delete m_texture;
		m_texture = NULL;
	}
}

void Mesh::SetMaterial(Material *material)
{
	
	//if(m_material)
	//{
	//	delete m_material;
	//	m_material = NULL;
	//}
	
	m_material = material;
	int ygfd = 876;
}

/*
void Mesh::auei(Renderer *a_renderer)
{
	a_renderer->nada();
}
*/