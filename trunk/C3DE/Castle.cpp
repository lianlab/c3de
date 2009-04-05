
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

	LoadFromXFile(	ResourceManager::GetInstance()->GetMeshFilenameByID(MESH_CAFE_TABLE_ID), 
		D3DRenderer::GetDevice());

	AddMaterial(new Material(	D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),
										D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f), 16.0f));
	IDirect3DTexture9 *tex = 0;
	tex = ResourceManager::GetInstance()->GetTextureByID(IMAGE_CAFE_TABLE_ID);

	D3DImage *t_image = new D3DImage(tex);
	AddTexture((Image*) t_image);
	
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
	/*
	HR(D3DRenderer::GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, true));
	HR(D3DRenderer::GetDevice()->SetRenderState(D3DRS_ALPHAREF, 200));
	HR(D3DRenderer::GetDevice()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER));
	
*/
}
	
void Castle::PosRender(Renderer *a_renderer)
{
	/*
HR(D3DRenderer::GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, false));
	*/
}

