#include "Ground.h"
#include "PerVertexLightingNoFog.h"
#include "D3DRenderer.h"
#include "ResourceManager.h"
#include "DebugMemory.h"


Ground::Ground():Plane(500, 500)
{
	FreeTextures();
	FreeMaterials();

	m_materials = new vector<Material *>;
	m_textures = new vector<Image *>;

	D3DImage * d3dImage = new D3DImage(ResourceManager::GetInstance()->GetTextureByID(IMAGE_STREET_GROUND_ID));	
	AddTexture((Image *) d3dImage);

	Material *t_material = new Material(	D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),
										D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f), 16.0f);	

	AddMaterial(t_material);


	m_effect = ShaderManager::GetInstance()->GetFXByID(SHADER_LIGHTS_PER_VERTEX_TEXTURES_NO_FOG_ID);
	PerVertexLightingNoFog *t_effect = (PerVertexLightingNoFog *) m_effect;
	t_effect->SetAlpha(1.0f);

}

Ground::~Ground()
{
	ReleaseCOM(m_vertexDeclaration);
}

void Ground::SetShaderHandlers()
{		
	PerVertexLightingNoFog *t_effect = (PerVertexLightingNoFog *) m_effect;
	
	t_effect->SetObjectMaterials(	m_currentMaterial->GetAmbient(), m_currentMaterial->GetDiffuse(),
									m_currentMaterial->GetSpecular(), m_currentMaterial->GetSpecularPower());

									
	
	D3DImage *t_d3dText = (D3DImage *) m_currentTexture;
	t_effect->SetObjectTexture(t_d3dText->GetTexture());

	t_effect->SetTransformMatrix(GetTransformMatrix());
}

