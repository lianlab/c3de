#if 0
#include "Plane.h"
#include "PerPixelLighting.h"
#include "PerVertexLighting.h"
#include "DebugMemory.h"


Plane::Plane(float width, float height)
{
	m_vertices = new vector<VertexPos>;
	m_indices = new vector<int>;

	m_vertices->push_back(VertexPos(- (width /2), 0.0f, -(width/2)));	
	m_vertices->push_back(VertexPos((width /2), 0.0f, -(width/2)));	
	m_vertices->push_back(VertexPos(-(width /2), 0.0f, (width/2)));	
	m_vertices->push_back(VertexPos( (width /2), 0.0f,(width/2)));	
	
	
	
	m_indices->push_back(0);
	m_indices->push_back(2);
	m_indices->push_back(1);
	m_indices->push_back(2);
	m_indices->push_back(3);
	m_indices->push_back(1);

	m_effect = ShaderManager::GetInstance()->GetFXByID(SHADER_LIGHTS_PER_VERTEX_TEXTURES_ID);

}

Plane::~Plane()
{
	ReleaseCOM(m_vertexDeclaration);
}

void Plane::SetShaderHandlers()
{
	
	
	PerVertexLighting *t_effect = (PerVertexLighting *) m_effect;
	t_effect->SetObjectMaterials(	m_material->GetAmbient(), m_material->GetDiffuse(),
									m_material->GetSpecular(), m_material->GetSpecularPower());

	
	
}



#endif

#if 1
#include "Plane.h"
#include "PerPixelLighting.h"
#include "PerVertexLighting.h"
#include "DebugMemory.h"


Plane::Plane(float width, float height)
{
	m_vertices = new vector<VertexPos>;
	m_indices = new vector<int>;

	m_vertices->push_back(VertexPos(- (width /2), 0.0f, -(width/2)));	
	m_vertices->push_back(VertexPos((width /2), 0.0f, -(width/2)));	
	m_vertices->push_back(VertexPos(-(width /2), 0.0f, (width/2)));	
	m_vertices->push_back(VertexPos( (width /2), 0.0f,(width/2)));	
	
	
	
	m_indices->push_back(0);
	m_indices->push_back(2);
	m_indices->push_back(1);
	m_indices->push_back(2);
	m_indices->push_back(3);
	m_indices->push_back(1);

	m_effect = ShaderManager::GetInstance()->GetFXByID(SHADER_LIGHTS_PER_PIXEL_TEXTURES_ID);

}

Plane::~Plane()
{
	ReleaseCOM(m_vertexDeclaration);
}

void Plane::SetShaderHandlers()
{
	
	
	PerPixelLighting *t_effect = (PerPixelLighting *) m_effect;
	t_effect->SetObjectMaterials(	m_material->GetAmbient(), m_material->GetDiffuse(),
									m_material->GetSpecular(), m_material->GetSpecularPower());

	
	
}
#endif