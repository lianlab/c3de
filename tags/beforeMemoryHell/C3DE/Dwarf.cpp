
#include "D3DRenderer.h"

#include "Dwarf.h"
#include "ResourceManager.h"
#include "PerVertexLighting.h"

#include "DebugMemory.h"

Dwarf::Dwarf()
{
	
	m_vertices = new vector<VertexPos>;
	m_indices = new vector<int>;

	

	

	//D3DImage * d3dImage = new D3DImage(ResourceManager::GetInstance()->GetTextureByID(IMAGE_CRATE_ID));
	//m_texture = (Image *) d3dImage;


	//m_effect = ShaderManager::GetInstance()->GetFXByID(SHADER_LIGHTS_PER_VERTEX_TEXTURES_ID);
	m_effect = ShaderManager::GetInstance()->GetFXByID(SHADER_LIGHTS_PER_VERTEX_TEXTURES_ID);
	
	m_vertexDeclaration = NULL;

	LoadFromXFile(ResourceManager::GetInstance()->GetMeshFilenameByID(MESH_DWARF_ID), D3DRenderer::GetDevice());

	//m_material = NULL;
	
}






void Dwarf::SetShaderHandlers()
{		
	PerVertexLighting *t_effect = (PerVertexLighting *) m_effect;

	
	
	t_effect->SetObjectMaterials(	m_currentMaterial->GetAmbient(), m_currentMaterial->GetDiffuse(),
									m_currentMaterial->GetSpecular(), m_currentMaterial->GetSpecularPower());
									
	
	//t_effect->SetObjectTexture(m_d3dTex);

	D3DImage *t_image = (D3DImage*) m_currentTexture;

	t_effect->SetObjectTexture(t_image->GetTexture());

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

