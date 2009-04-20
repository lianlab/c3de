#include "Renderer.h"
#include "Mesh.h"
#include "DebugMemory.h"


Mesh::Mesh()
{	
	
	m_scaleX = 1.0f;
	m_scaleY = 1.0f;
	m_scaleZ = 1.0f;

	m_x = 0.0f;
	m_y = 0.0f;
	m_z = 0.0f;

	m_rotateX = 0.0f;
	m_rotateY = 0.0f;
	m_rotateZ = 0.0f;

	m_currentTexture = NULL;

	m_materials = new vector<Material *>;
	m_textures = new vector<Image *>;

	m_alpha = 1.0f;
}

Mesh::~Mesh()
{

	

	if(m_materials)
	{
		delete m_materials;
		m_materials = NULL;
	}

	if(m_textures)
	{
		delete m_textures;
		m_textures = NULL;
	}


}
