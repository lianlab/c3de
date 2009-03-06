#include "BillboardMesh.h"
#include "D3DRenderer.h"
#include "Math.h"
#include "BillboardFX.h"
#include "ResourceManager.h"



BillboardMesh::BillboardMesh(D3DImage *a_texture) : D3DMesh()
{
	
	m_blockOffset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_vertices = new vector<VertexPos>;
	m_indices = new vector<int>;
	

	m_vertices->push_back(VertexPos(-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f));
	m_vertices->push_back(VertexPos(-1.0f,  1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f));
	m_vertices->push_back(VertexPos( 1.0f,  1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f));
	m_vertices->push_back(VertexPos( 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f));

	m_indices->push_back(0);
	m_indices->push_back(1);
	m_indices->push_back(2);
	m_indices->push_back(0);
	m_indices->push_back(2);
	m_indices->push_back(3);

	
	CreateXMesh(D3DRenderer::GetDevice());

	//D3DImage * d3dImage = new D3DImage(ResourceManager::GetInstance()->GetTextureByID(IMAGE_GRASS_BILLBOARD_ID));	
	AddTexture((Image *) a_texture);

	Material *t_material = new Material(	D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),
										D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f), 16.0f);	

	AddMaterial(t_material);

	

	m_effect = ShaderManager::GetInstance()->GetFXByID(SHADER_BILLBOARD_FX_ID);
}

BillboardMesh::~BillboardMesh() 
{

}

void BillboardMesh::SetShaderHandlers()
{
	
	
	BillboardFX *t_effect = (BillboardFX *) m_effect;
	
	t_effect->SetObjectMaterials(	m_currentMaterial->GetAmbient(), m_currentMaterial->GetDiffuse(),
									m_currentMaterial->GetSpecular(), m_currentMaterial->GetSpecularPower());

									
	
	D3DImage *t_d3dText = (D3DImage *) m_currentTexture;
	t_effect->SetObjectTexture(t_d3dText->GetTexture());

	t_effect->SetTransformMatrix(GetTransformMatrix());
	//t_effect->SetAlpha(m_alpha);
	
}
