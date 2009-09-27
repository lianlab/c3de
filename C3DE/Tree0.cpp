
#include "Tree0.h"
#include "ResourceManager.h"
#include "PerVertexLighting.h"
#include "ResourceManager.h"
#include "D3DRenderer.h"
#include "DebugMemory.h"

Tree0::Tree0()
{
	
	m_effect = ShaderManager::GetInstance()->GetFXByID(SHADER_LIGHTS_PER_VERTEX_TEXTURES_NO_FOG_ID);
	

	LoadFromXFile(	ResourceManager::GetInstance()->GetMeshFilenameByID(MESH_TREE_0_ID), 
		D3DRenderer::GetDevice());
	
}






void Tree0::SetShaderHandlers()
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

Tree0::~Tree0()
{

	if(m_vertexDeclaration)
	{
		ReleaseCOM(m_vertexDeclaration);
	}
	

	
}


void Tree0::PreRender(Renderer * a_renderer)
{
	
	HR(D3DRenderer::GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, true));
	HR(D3DRenderer::GetDevice()->SetRenderState(D3DRS_ALPHAREF, 200));
	HR(D3DRenderer::GetDevice()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER));
}
	
void Tree0::PosRender(Renderer *a_renderer)
{
	HR(D3DRenderer::GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, false));
	
}

