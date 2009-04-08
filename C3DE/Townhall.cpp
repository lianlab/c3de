
#include "D3DRenderer.h"

#include "Townhall.h"
#include "ResourceManager.h"
#include "PerVertexLighting.h"

#include "DebugMemory.h"

Townhall::Townhall()
{
	
	m_vertices = new vector<VertexPos>;
	m_indices = new vector<int>;

	m_effect = ShaderManager::GetInstance()->GetFXByID(SHADER_LIGHTS_PER_VERTEX_TEXTURES_ID);
	
	m_vertexDeclaration = NULL;

	LoadFromXFile(ResourceManager::GetInstance()->GetMeshFilenameByID(MESH_TOWNHALL_ID), D3DRenderer::GetDevice());

}

void Townhall::SetShaderHandlers()
{		
	PerVertexLighting *t_effect = (PerVertexLighting *) m_effect;

	
	
	t_effect->SetObjectMaterials(	m_currentMaterial->GetAmbient(), m_currentMaterial->GetDiffuse(),
									m_currentMaterial->GetSpecular(), m_currentMaterial->GetSpecularPower());
									
	

	D3DImage *t_image = (D3DImage*) m_currentTexture;

	t_effect->SetObjectTexture(t_image->GetTexture());

	t_effect->SetTransformMatrix(GetTransformMatrix());
	t_effect->SetAlpha(m_alpha);
	
}

Townhall::~Townhall()
{

	if(m_vertexDeclaration)
	{
		ReleaseCOM(m_vertexDeclaration);
	}
	

	
}


void Townhall::PreRender(Renderer * a_renderer)
{
	HR(D3DRenderer::GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, false));

}
	
void Townhall::PosRender(Renderer *a_renderer)
{
	
}

