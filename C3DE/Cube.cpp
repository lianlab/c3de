#include "Cube.h"

Cube::Cube()
{
	
	m_vertices = new vector<VertexPos>;
	m_indices = new vector<int>;

	//vertices
	m_vertices->push_back(VertexPos(-1.0f, -1.0f, -1.0f));
	m_vertices->push_back(VertexPos(-1.0f,  1.0f, -1.0f));
	m_vertices->push_back(VertexPos(1.0f,  1.0f, -1.0f));
	m_vertices->push_back(VertexPos(1.0f, -1.0f, -1.0f));
	m_vertices->push_back(VertexPos(-1.0f, -1.0f,  1.0f));
	m_vertices->push_back(VertexPos(-1.0f,  1.0f,  1.0f));
	m_vertices->push_back(VertexPos(1.0f,  1.0f,  1.0f));
	m_vertices->push_back(VertexPos(1.0f, -1.0f,  1.0f));

	//indices
	//front face
	
	m_indices->push_back(0);
	m_indices->push_back(1);
	m_indices->push_back(2);
	m_indices->push_back(0);
	m_indices->push_back(2);
	m_indices->push_back(3);
	m_indices->push_back(4);
	m_indices->push_back(6);
	m_indices->push_back(5);
	m_indices->push_back(4);
	m_indices->push_back(7);
	m_indices->push_back(6);
	m_indices->push_back(4);
	m_indices->push_back(5);
	m_indices->push_back(1);
	m_indices->push_back(4);
	m_indices->push_back(1);
	m_indices->push_back(0);
	m_indices->push_back(3);
	m_indices->push_back(2);
	m_indices->push_back(6);
	m_indices->push_back(3);
	m_indices->push_back(6);
	m_indices->push_back(7);
	m_indices->push_back(1);
	m_indices->push_back(5);
	m_indices->push_back(6);
	m_indices->push_back(1);
	m_indices->push_back(6);
	m_indices->push_back(2);
	m_indices->push_back(4);
	m_indices->push_back(0);
	m_indices->push_back(3);
	m_indices->push_back(4);
	m_indices->push_back(3);
	m_indices->push_back(7);
	
	

}

void Cube::SetEffectHandles()
{
	if(m_effect)
	{
		m_shaderTechnique = m_effect->GetTechniqueByName("ColorTech");
		m_shaderViewMatrix  = m_effect->GetParameterByName(0, "gWVP");
	}
	
}

Cube::~Cube()
{
	ReleaseCOM(m_vertexDeclaration);
}

