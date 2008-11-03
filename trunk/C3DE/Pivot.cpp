#include "Pivot.h"
#include "HardColors.h"

Pivot::Pivot()
{
	float width = 10.0f;
	
	m_vertices = new vector<VertexPos>;
	m_indices = new vector<int>;
	
#if 0
	m_vertices->push_back(VertexPos(0.0f, 0.0f, 0.0f));	
	m_vertices->push_back(VertexPos(5.0f, 0.0f, 0.0f));	
	m_vertices->push_back(VertexPos(0.0f, 5.0f, 0.0f));	
	m_vertices->push_back(VertexPos(0.0f, 0.0f, 5.0f));	


	
	m_indices->push_back(0);
	m_indices->push_back(2);
	m_indices->push_back(1);
	m_indices->push_back(0);
	m_indices->push_back(1);
	m_indices->push_back(2);

	m_indices->push_back(0);
	m_indices->push_back(2);
	m_indices->push_back(3);

	m_indices->push_back(0);
	m_indices->push_back(3);
	m_indices->push_back(2);

#endif

	m_vertices->push_back(VertexPos(0.0f, 0.0f, 0.0f));	
	m_vertices->push_back(VertexPos(5.0f, 0.0f, 0.0f));	
	m_vertices->push_back(VertexPos(0.0f, 5.0f, 0.0f));	
	m_vertices->push_back(VertexPos(0.0f, 0.0f, 5.0f));	
	m_vertices->push_back(VertexPos(0.1f, 0.1f, 0.1f));	


	
	m_indices->push_back(0);
	m_indices->push_back(1);
	m_indices->push_back(4);

	m_indices->push_back(0);
	m_indices->push_back(4);
	m_indices->push_back(1);

	m_indices->push_back(0);
	m_indices->push_back(2);
	m_indices->push_back(4);

	m_indices->push_back(0);
	m_indices->push_back(4);
	m_indices->push_back(2);

	m_indices->push_back(0);
	m_indices->push_back(3);
	m_indices->push_back(4);

	m_indices->push_back(0);
	m_indices->push_back(4);
	m_indices->push_back(3);
	
	
	
	m_effect = ShaderManager::GetInstance()->GetFXByID(SHADER_HARD_COLORS_ID);
	HardColors *t_effect = (HardColors *) m_effect;
	//t_effect->SetAlpha(1.0f);
}

Pivot::~Pivot()
{
	ReleaseCOM(m_vertexDeclaration);
}

void Pivot::SetShaderHandlers()
{		
	HardColors *t_effect = (HardColors *) m_effect;
	t_effect->SetObjectMaterials(	m_material->GetAmbient(), m_material->GetDiffuse(),
									m_material->GetSpecular(), m_material->GetSpecularPower());	
	t_effect->SetTransformMatrix(GetTransformMatrix());
}
