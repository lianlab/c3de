#include "WomanMesh.h"
#include "ResourceManager.h"
#include "ShaderManager.h"
#include "SkinnedMeshBookFX.h"

WomanMesh::WomanMesh() : D3DSkinnedMesh()
{

	D3DImage * d3dImage = new D3DImage(ResourceManager::GetInstance()->GetImageByID(IMAGE_TINY_ANIM_SKIN_ID));
	m_texture = (Image *) d3dImage;

	m_effect = ShaderManager::GetInstance()->GetFXByID(SHADER_SKINNED_MESH_BOOK_FX_ID);

}

void WomanMesh::SetShaderHandlers()
{
	
	
	SkinnedMeshBookFX *t_effect = (SkinnedMeshBookFX *) m_effect;
	//t_effect->SetObjectMaterials(	m_material->GetAmbient(), m_material->GetDiffuse(),
	//								m_material->GetSpecular(), m_material->GetSpecularPower());

	D3DImage *t_d3dText = (D3DImage *) m_texture;
	t_effect->SetObjectTexture(t_d3dText->GetTexture());

	t_effect->SetTransformMatrix(GetTransformMatrix());
	t_effect->SetAlpha(m_alpha);

	t_effect->SetBoneMatrix(getFinalXFormArray(), numBones());
	
}



WomanMesh::~WomanMesh()
{

}