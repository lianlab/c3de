
#include "Tree3.h"
#include "ResourceManager.h"
#include "PerVertexLighting.h"
#include "ResourceManager.h"
#include "D3DRenderer.h"
#include "DebugMemory.h"

Tree3::Tree3()
{
	
	//m_vertices = new vector<VertexPos>;
	//m_indices = new vector<int>;

	

	

	//D3DImage * d3dImage = new D3DImage(ResourceManager::GetInstance()->GetTextureByID(IMAGE_CRATE_ID));
	//m_texture = (Image *) d3dImage;


	//m_effect = ShaderManager::GetInstance()->GetFXByID(SHADER_LIGHTS_PER_VERTEX_TEXTURES_ID);
	m_effect = ShaderManager::GetInstance()->GetFXByID(SHADER_LIGHTS_PER_VERTEX_TEXTURES_ID);
	
	//m_vertexDeclaration = NULL;

	//m_material = NULL;

	LoadFromXFile(	ResourceManager::GetInstance()->GetMeshFilenameByID(MESH_TREE_3_ID), 
		D3DRenderer::GetDevice());
	
}






void Tree3::SetShaderHandlers()
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

Tree3::~Tree3()
{

	if(m_vertexDeclaration)
	{
		ReleaseCOM(m_vertexDeclaration);
	}
	

	
}


void Tree3::PreRender(Renderer * a_renderer)
{
	
	HR(D3DRenderer::GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, true));
	HR(D3DRenderer::GetDevice()->SetRenderState(D3DRS_ALPHAREF, 200));
	HR(D3DRenderer::GetDevice()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER));
}
	
void Tree3::PosRender(Renderer *a_renderer)
{
	HR(D3DRenderer::GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, false));
	
}

