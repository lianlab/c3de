#include "BillboardMesh.h"
#include "D3DImage.h"
#include "ShaderManager.h"
#include "BillboardFX.h"


BillboardMesh::BillboardMesh(D3DImage * a_texture) : D3DMesh()
{
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

	
	AddTexture((Image *) a_texture);


	m_effect = ShaderManager::GetInstance()->GetFXByID(SHADER_BILLBOARD_FX_ID);

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

BillboardMesh::~BillboardMesh()
{

}
