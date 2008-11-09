#include "Wall.h"
#include "PerVertexLighting.h"

Wall::Wall()
{
	float width = 10.0f;
	
	m_vertices = new vector<VertexPos>;
	m_indices = new vector<int>;
	
	

	m_vertices->push_back(VertexPos(-2.5f, 0.0f, 0.0f));	
	m_vertices->push_back(VertexPos(-2.5f, 5.0f, 0.0f));	
	m_vertices->push_back(VertexPos(2.5f, 5.0f, 0.0f));	
	m_vertices->push_back(VertexPos(-2.5f, 0.0f, 0.0f));	
	m_vertices->push_back(VertexPos(2.5f, 5.0f, 0.0f));	
	m_vertices->push_back(VertexPos(2.5f, 0.0f, 0.0f));	

	
	m_indices->push_back(0);
	m_indices->push_back(1);
	m_indices->push_back(2);
	m_indices->push_back(3);
	m_indices->push_back(4);
	m_indices->push_back(5);

	m_effect = ShaderManager::GetInstance()->GetFXByID(SHADER_LIGHTS_PER_VERTEX_TEXTURES_ID);
	PerVertexLighting *t_effect = (PerVertexLighting *) m_effect;
	//t_effect->SetAlpha(1.0f);
}

Wall::~Wall()
{
	ReleaseCOM(m_vertexDeclaration);
}

void Wall::SetShaderHandlers()
{		
	PerVertexLighting *t_effect = (PerVertexLighting *) m_effect;
	t_effect->SetObjectMaterials(	m_material->GetAmbient(), m_material->GetDiffuse(),
									m_material->GetSpecular(), m_material->GetSpecularPower());	
	t_effect->SetTransformMatrix(GetTransformMatrix());
}
