
#include "LandscapeMesh.h"
#include "ResourceManager.h"
#include "PerVertexLighting.h"
#include "ResourceManager.h"
#include "D3DRenderer.h"
#include "DebugMemory.h"

LandscapeMesh::LandscapeMesh(int a_meshId, int a_texId)
{
	
	

	//m_effect = ShaderManager::GetInstance()->GetFXByID(SHADER_LIGHTS_PER_VERTEX_TEXTURES_ID);
	m_effect = ShaderManager::GetInstance()->GetFXByID(SHADER_LIGHTS_PER_VERTEX_TEXTURES_ID);
	
	//m_vertexDeclaration = NULL;

	//m_material = NULL;

	LoadFromXFile(	ResourceManager::GetInstance()->GetMeshFilenameByID(a_meshId), 
		D3DRenderer::GetDevice());

	AddMaterial(new Material(	D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),
										D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f), 16.0f));
	IDirect3DTexture9 *tex = 0;
	tex = ResourceManager::GetInstance()->GetTextureByID(a_texId);

	D3DImage *t_image = new D3DImage(tex);
	AddTexture((Image*) t_image);
	
}

void LandscapeMesh::UniformScale(float a_value)
{
	Scale(a_value, a_value, a_value);
}






void LandscapeMesh::SetShaderHandlers()
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

LandscapeMesh::~LandscapeMesh()
{

	if(m_vertexDeclaration)
	{
		ReleaseCOM(m_vertexDeclaration);
	}
	

	
}


void LandscapeMesh::PreRender(Renderer * a_renderer)
{
	
}
	
void LandscapeMesh::PosRender(Renderer *a_renderer)
{
	
}

