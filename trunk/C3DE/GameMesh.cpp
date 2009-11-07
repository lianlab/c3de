
#include "GameMesh.h"
#include "ResourceManager.h"
#include "PerVertexLighting.h"
#include "TextureOnlyFX.h"
#include "ResourceManager.h"
#include "D3DRenderer.h"
#include "DebugMemory.h"

GameMesh::GameMesh(int a_meshId, int a_texId, bool a_calculateAABB)
{
	
	
	//m_effect = ShaderManager::GetInstance()->GetFXByID(SHADER_LIGHTS_PER_VERTEX_TEXTURES_ID);
	m_effect = ShaderManager::GetInstance()->GetFXByID(SHADER_LIGHTS_PER_VERTEX_TEXTURES_NO_FOG_ID);
	//m_effect = ShaderManager::GetInstance()->GetFXByID(SHADER_TEXTURE_ONLY_ID);
	
	

	//LoadFromXFile(	ResourceManager::GetInstance()->GetMeshFilenameByID(a_meshId), 
	//	D3DRenderer::GetDevice());
	LoadFromC3DEFile(ResourceManager::GetInstance()->GetMeshBuffer(a_meshId), a_calculateAABB);

	CreateXMesh(D3DRenderer::GetDevice(), a_calculateAABB);

	AddMaterial(new Material(	D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),
										D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f), 16.0f));
	IDirect3DTexture9 *tex = 0;
	tex = ResourceManager::GetInstance()->GetTextureByID(a_texId);

	D3DImage *t_image = new D3DImage(tex);
	AddTexture((Image*) t_image);
	
}


void GameMesh::SetShaderHandlers()
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

GameMesh::~GameMesh()
{

	if(m_vertexDeclaration)
	{
		ReleaseCOM(m_vertexDeclaration);
	}
	

	
}


void GameMesh::PreRender(Renderer * a_renderer)
{
	
}
	
void GameMesh::PosRender(Renderer *a_renderer)
{
	
}

