#include "Plane.h"
#include "PerPixelLighting.h"
#include "PerVertexLighting.h"
#include "D3DRenderer.h"
#include "ResourceManager.h"
#include "DebugMemory.h"


Plane::Plane(float width, float height)
{
	m_vertices = new vector<VertexPos>;
	m_indices = new vector<int>;

	m_vertices->push_back(VertexPos(-(width /2), 0.0f, -(height/2), 0.0f, 1.0f, 0.0f, 0.0f, 1.0f));
	m_vertices->push_back(VertexPos(-(width /2), 0.0f,  (height/2), 0.0f, 1.0f, 0.0f, 0.0f, 0.0f));
	m_vertices->push_back(VertexPos( (width/2), 0.0f,  (height/2), 0.0f, 1.0f, 0.0f, 1.0f, 0.0f));
	m_vertices->push_back(VertexPos( (width/2), 0.0f, -(height/2), 0.0f, 1.0f, 0.0f, 1.0f, 1.0f));

	m_indices->push_back(0);
	m_indices->push_back(1);
	m_indices->push_back(2);
	m_indices->push_back(0);
	m_indices->push_back(2);
	m_indices->push_back(3);

	D3DImage * d3dImage = new D3DImage(ResourceManager::GetInstance()->GetTextureByID(IMAGE_CRATE_ID));	
	AddTexture((Image *) d3dImage);

	Material *t_material = new Material(	D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),
										D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f), 16.0f);	

	AddMaterial(t_material);


	CreateXMesh(D3DRenderer::GetDevice());

	m_effect = ShaderManager::GetInstance()->GetFXByID(SHADER_LIGHTS_PER_VERTEX_TEXTURES_ID);
	PerVertexLighting *t_effect = (PerVertexLighting *) m_effect;
	t_effect->SetAlpha(1.0f);

}

Plane::~Plane()
{
	ReleaseCOM(m_vertexDeclaration);
}

void Plane::SetShaderHandlers()
{		
	PerVertexLighting *t_effect = (PerVertexLighting *) m_effect;
	
	t_effect->SetObjectMaterials(	m_currentMaterial->GetAmbient(), m_currentMaterial->GetDiffuse(),
									m_currentMaterial->GetSpecular(), m_currentMaterial->GetSpecularPower());

									
	
	D3DImage *t_d3dText = (D3DImage *) m_currentTexture;
	t_effect->SetObjectTexture(t_d3dText->GetTexture());

	t_effect->SetTransformMatrix(GetTransformMatrix());
}

