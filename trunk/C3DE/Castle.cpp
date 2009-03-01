
#include "Castle.h"
#include "ResourceManager.h"
#include "PerVertexLighting.h"
#include "ResourceManager.h"
#include "D3DRenderer.h"
#include "DebugMemory.h"

Castle::Castle()
{
	
	

	//m_effect = ShaderManager::GetInstance()->GetFXByID(SHADER_LIGHTS_PER_VERTEX_TEXTURES_ID);
	m_effect = ShaderManager::GetInstance()->GetFXByID(SHADER_LIGHTS_PER_VERTEX_TEXTURES_ID);
	
	//m_vertexDeclaration = NULL;

	//m_material = NULL;

	LoadFromXFile(	ResourceManager::GetInstance()->GetMeshFilenameByID(MESH_CASTLE_ID), 
		D3DRenderer::GetDevice());
	
}






void Castle::SetShaderHandlers()
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

Castle::~Castle()
{

	if(m_vertexDeclaration)
	{
		ReleaseCOM(m_vertexDeclaration);
	}
	

	
}


void Castle::PreRender(Renderer * a_renderer)
{
	
	

}
	
void Castle::PosRender(Renderer *a_renderer)
{
	

	
}

