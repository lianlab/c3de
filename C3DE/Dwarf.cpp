
#if 1

#include "Renderer.h"
#include "Dwarf.h"
#include "ResourceManager.h"
#include "PerVertexLighting.h"

#include "DebugMemory.h"

Dwarf::Dwarf()
{
	
	m_vertices = new vector<VertexPos>;
	m_indices = new vector<int>;

	

	

	D3DImage * d3dImage = new D3DImage(ResourceManager::GetInstance()->GetImageByID(IMAGE_CRATE_ID));
	m_texture = (Image *) d3dImage;


	//m_effect = ShaderManager::GetInstance()->GetFXByID(SHADER_LIGHTS_PER_VERTEX_TEXTURES_ID);
	m_effect = ShaderManager::GetInstance()->GetFXByID(SHADER_LIGHTS_PER_VERTEX_TEXTURES_ID);
	
	m_vertexDeclaration = NULL;

	m_material = NULL;
	
}






void Dwarf::SetShaderHandlers()
{		
	PerVertexLighting *t_effect = (PerVertexLighting *) m_effect;

	
	
	t_effect->SetObjectMaterials(	m_material->GetAmbient(), m_material->GetDiffuse(),
									m_material->GetSpecular(), m_material->GetSpecularPower());
									
	
	t_effect->SetObjectTexture(m_d3dTex);

	t_effect->SetTransformMatrix(GetTransformMatrix());
	t_effect->SetAlpha(m_alpha);
	
}

Dwarf::~Dwarf()
{

	if(m_vertexDeclaration)
	{
		ReleaseCOM(m_vertexDeclaration);
	}
	

	
}


#endif