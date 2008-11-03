#include "Wall.h"
#include "PerPixelLighting.h"

Wall::Wall()
{
	float width = 10.0f;
	
	m_vertices = new vector<VertexPos>;
	m_indices = new vector<int>;
	
	/*
	m_vertices->push_back(VertexPos(0.0f, - (width /2), -(width/2)));	
	m_vertices->push_back(VertexPos(0.0f, (width /2), -(width/2)));	
	m_vertices->push_back(VertexPos(0.0f, -(width /2), (width/2)));	
	m_vertices->push_back(VertexPos(0.0f , (width /2),(width/2)));	

	*/

	m_vertices->push_back(VertexPos(-2.5f, 0.0f, 0.0f));	
	m_vertices->push_back(VertexPos(-2.5f, 5.0f, 0.0f));	
	m_vertices->push_back(VertexPos(2.5f, 5.0f, 0.0f));	
	m_vertices->push_back(VertexPos(-2.5f, 0.0f, 0.0f));	
	m_vertices->push_back(VertexPos(2.5f, 5.0f, 0.0f));	
	m_vertices->push_back(VertexPos(2.5f, 0.0f, 0.0f));	

	/*
	v[18] = VertexPNT(-2.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	v[19] = VertexPNT(-2.5f, 5.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	v[20] = VertexPNT( 2.5f, 5.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	
	v[21] = VertexPNT(-2.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	v[22] = VertexPNT( 2.5f, 5.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	v[23] = VertexPNT( 2.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);
	*/
	
	/*
	m_indices->push_back(0);
	m_indices->push_back(2);
	m_indices->push_back(1);
	m_indices->push_back(2);
	m_indices->push_back(3);
	m_indices->push_back(1);
	*/
	m_indices->push_back(0);
	m_indices->push_back(1);
	m_indices->push_back(2);
	m_indices->push_back(3);
	m_indices->push_back(4);
	m_indices->push_back(5);

	m_effect = ShaderManager::GetInstance()->GetFXByID(SHADER_LIGHTS_PER_PIXEL_TEXTURES_ID);
	PerPixelLighting *t_effect = (PerPixelLighting *) m_effect;
	//t_effect->SetAlpha(1.0f);
}

Wall::~Wall()
{
	ReleaseCOM(m_vertexDeclaration);
}

void Wall::SetShaderHandlers()
{		
	PerPixelLighting *t_effect = (PerPixelLighting *) m_effect;
	t_effect->SetObjectMaterials(	m_material->GetAmbient(), m_material->GetDiffuse(),
									m_material->GetSpecular(), m_material->GetSpecularPower());	
	t_effect->SetTransformMatrix(GetTransformMatrix());
}
