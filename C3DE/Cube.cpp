#if 0
#include "Renderer.h"
#include "Cube.h"
#include "ResourceManager.h"
#include "ShadowFX.h"

#include "DebugMemory.h"

Cube::Cube()
{
	
	m_vertices = new vector<VertexPos>;
	m_indices = new vector<int>;

	//vertices

	m_vertices->push_back(VertexPos(-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f));
	m_vertices->push_back(VertexPos(-1.0f,  1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f));
	m_vertices->push_back(VertexPos( 1.0f,  1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f));
	m_vertices->push_back(VertexPos( 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f));

	// Fill in the back face vertex data.
	m_vertices->push_back(VertexPos(-1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f));
	m_vertices->push_back(VertexPos( 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f));
	m_vertices->push_back(VertexPos( 1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f));
	m_vertices->push_back(VertexPos(-1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f));

	// Fill in the top face vertex data.
	m_vertices->push_back(VertexPos(-1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f));
	m_vertices->push_back(VertexPos(-1.0f, 1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f));
	m_vertices->push_back(VertexPos( 1.0f, 1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f));
	m_vertices->push_back(VertexPos( 1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f));

	// Fill in the bottom face vertex data.
	m_vertices->push_back(VertexPos(-1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f));
	m_vertices->push_back(VertexPos( 1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f));
	m_vertices->push_back(VertexPos( 1.0f, -1.0f,  1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f));
	m_vertices->push_back(VertexPos(-1.0f, -1.0f,  1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f));

	// Fill in the left face vertex data.
	m_vertices->push_back(VertexPos(-1.0f, -1.0f,  1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f));
	m_vertices->push_back(VertexPos(-1.0f,  1.0f,  1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f));
	m_vertices->push_back(VertexPos(-1.0f,  1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f));
	m_vertices->push_back(VertexPos(-1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f));

	// Fill in the right face vertex data.
	m_vertices->push_back(VertexPos( 1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f));
	m_vertices->push_back(VertexPos( 1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f));
	m_vertices->push_back(VertexPos( 1.0f,  1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f));
	m_vertices->push_back(VertexPos( 1.0f, -1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f));

	//indices
	//front face
	



	m_indices->push_back(0);
	m_indices->push_back(1);
	m_indices->push_back(2);
	m_indices->push_back(0);
	m_indices->push_back(2);
	m_indices->push_back(3);
	m_indices->push_back(4);
	m_indices->push_back(5);
	m_indices->push_back(6);
	m_indices->push_back(4);
	m_indices->push_back(6);
	m_indices->push_back(7);
	m_indices->push_back(8);
	m_indices->push_back(9);
	m_indices->push_back(10);
	m_indices->push_back(8);
	m_indices->push_back(10);
	m_indices->push_back(11);
	m_indices->push_back(12);
	m_indices->push_back(13);
	m_indices->push_back(14);
	m_indices->push_back(12);
	m_indices->push_back(14);
	m_indices->push_back(15);
	m_indices->push_back(16);
	m_indices->push_back(17);
	m_indices->push_back(18);
	m_indices->push_back(16);
	m_indices->push_back(18);
	m_indices->push_back(19);
	m_indices->push_back(20);
	m_indices->push_back(21);
	m_indices->push_back(22);
	m_indices->push_back(20);
	m_indices->push_back(22);
	m_indices->push_back(23);


	D3DImage * d3dImage = new D3DImage(ResourceManager::GetInstance()->GetImageByID(IMAGE_CRATE_ID));
	m_texture = (Image *) d3dImage;

	m_alpha = 0.5f;

	m_effect = ShaderManager::GetInstance()->GetFXByID(SHADER_SHADOW_FX_ID);

	
		
}

void Cube::SetShaderHandlers()
{
	
	
	ShadowFX *t_effect = (ShadowFX *) m_effect;
	t_effect->SetObjectMaterials(	m_material->GetAmbient(), m_material->GetDiffuse(),
									m_material->GetSpecular(), m_material->GetSpecularPower());

	D3DImage *t_d3dText = (D3DImage *) m_texture;
	t_effect->SetObjectTexture(t_d3dText->GetTexture());

	t_effect->SetTransformMatrix(GetTransformMatrix());
	
}

Cube::~Cube()
{
	ReleaseCOM(m_vertexDeclaration);
}


#endif

#if 0

#include "Renderer.h"
#include "Cube.h"
#include "ResourceManager.h"
#include "PerVertexLighting.h"

#include "DebugMemory.h"

Cube::Cube()
{
	
	m_vertices = new vector<VertexPos>;
	m_indices = new vector<int>;

	//vertices

#if 1
	m_vertices->push_back(VertexPos(-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f));
	m_vertices->push_back(VertexPos(-1.0f,  1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f));
	m_vertices->push_back(VertexPos( 1.0f,  1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f));
	m_vertices->push_back(VertexPos( 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f));

	// Fill in the back face vertex data.
	m_vertices->push_back(VertexPos(-1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f));
	m_vertices->push_back(VertexPos( 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f));
	m_vertices->push_back(VertexPos( 1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f));
	m_vertices->push_back(VertexPos(-1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f));

	// Fill in the top face vertex data.
	m_vertices->push_back(VertexPos(-1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f));
	m_vertices->push_back(VertexPos(-1.0f, 1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f));
	m_vertices->push_back(VertexPos( 1.0f, 1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f));
	m_vertices->push_back(VertexPos( 1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f));

	// Fill in the bottom face vertex data.
	m_vertices->push_back(VertexPos(-1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f));
	m_vertices->push_back(VertexPos( 1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f));
	m_vertices->push_back(VertexPos( 1.0f, -1.0f,  1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f));
	m_vertices->push_back(VertexPos(-1.0f, -1.0f,  1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f));

	// Fill in the left face vertex data.
	m_vertices->push_back(VertexPos(-1.0f, -1.0f,  1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f));
	m_vertices->push_back(VertexPos(-1.0f,  1.0f,  1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f));
	m_vertices->push_back(VertexPos(-1.0f,  1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f));
	m_vertices->push_back(VertexPos(-1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f));

	// Fill in the right face vertex data.
	m_vertices->push_back(VertexPos( 1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f));
	m_vertices->push_back(VertexPos( 1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f));
	m_vertices->push_back(VertexPos( 1.0f,  1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f));
	m_vertices->push_back(VertexPos( 1.0f, -1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f));
#endif
	
	//indices
	//front face
	


#if 1
	m_indices->push_back(0);
	m_indices->push_back(1);
	m_indices->push_back(2);
	m_indices->push_back(0);
	m_indices->push_back(2);
	m_indices->push_back(3);
	m_indices->push_back(4);
	m_indices->push_back(5);
	m_indices->push_back(6);
	m_indices->push_back(4);
	m_indices->push_back(6);
	m_indices->push_back(7);
	m_indices->push_back(8);
	m_indices->push_back(9);
	m_indices->push_back(10);
	m_indices->push_back(8);
	m_indices->push_back(10);
	m_indices->push_back(11);
	m_indices->push_back(12);
	m_indices->push_back(13);
	m_indices->push_back(14);
	m_indices->push_back(12);
	m_indices->push_back(14);
	m_indices->push_back(15);
	m_indices->push_back(16);
	m_indices->push_back(17);
	m_indices->push_back(18);
	m_indices->push_back(16);
	m_indices->push_back(18);
	m_indices->push_back(19);
	m_indices->push_back(20);
	m_indices->push_back(21);
	m_indices->push_back(22);
	m_indices->push_back(20);
	m_indices->push_back(22);
	m_indices->push_back(23);
#endif

	

	D3DImage * d3dImage = new D3DImage(ResourceManager::GetInstance()->GetImageByID(IMAGE_CRATE_ID));
	m_texture = (Image *) d3dImage;


	m_effect = ShaderManager::GetInstance()->GetFXByID(SHADER_LIGHTS_PER_VERTEX_TEXTURES_ID);

	
	
}

void Cube::SetShaderHandlers()
{
	
	
	PerVertexLighting *t_effect = (PerVertexLighting *) m_effect;
	t_effect->SetObjectMaterials(	m_material->GetAmbient(), m_material->GetDiffuse(),
									m_material->GetSpecular(), m_material->GetSpecularPower());

	D3DImage *t_d3dText = (D3DImage *) m_texture;
	t_effect->SetObjectTexture(t_d3dText->GetTexture());

	t_effect->SetTransformMatrix(GetTransformMatrix());
	t_effect->SetAlpha(m_alpha);
	
}

Cube::~Cube()
{
	ReleaseCOM(m_vertexDeclaration);

	
}


#endif

#if 1

#include "Renderer.h"
#include "Cube.h"
#include "ResourceManager.h"
#include "SkinnedMeshFX.h"

#include "DebugMemory.h"

Cube::Cube()
{
	
	m_vertices = new vector<VertexPos>;
	m_indices = new vector<int>;

	//vertices

#if 1
	m_vertices->push_back(VertexPos(-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f));
	m_vertices->push_back(VertexPos(-1.0f,  1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f));
	m_vertices->push_back(VertexPos( 1.0f,  1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f));
	m_vertices->push_back(VertexPos( 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f));

	// Fill in the back face vertex data.
	m_vertices->push_back(VertexPos(-1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f));
	m_vertices->push_back(VertexPos( 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f));
	m_vertices->push_back(VertexPos( 1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f));
	m_vertices->push_back(VertexPos(-1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f));

	// Fill in the top face vertex data.
	m_vertices->push_back(VertexPos(-1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f));
	m_vertices->push_back(VertexPos(-1.0f, 1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f));
	m_vertices->push_back(VertexPos( 1.0f, 1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f));
	m_vertices->push_back(VertexPos( 1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f));

	// Fill in the bottom face vertex data.
	m_vertices->push_back(VertexPos(-1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f));
	m_vertices->push_back(VertexPos( 1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f));
	m_vertices->push_back(VertexPos( 1.0f, -1.0f,  1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f));
	m_vertices->push_back(VertexPos(-1.0f, -1.0f,  1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f));

	// Fill in the left face vertex data.
	m_vertices->push_back(VertexPos(-1.0f, -1.0f,  1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f));
	m_vertices->push_back(VertexPos(-1.0f,  1.0f,  1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f));
	m_vertices->push_back(VertexPos(-1.0f,  1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f));
	m_vertices->push_back(VertexPos(-1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f));

	// Fill in the right face vertex data.
	m_vertices->push_back(VertexPos( 1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f));
	m_vertices->push_back(VertexPos( 1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f));
	m_vertices->push_back(VertexPos( 1.0f,  1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f));
	m_vertices->push_back(VertexPos( 1.0f, -1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f));
#endif
	
	//indices
	//front face
	


#if 1
	m_indices->push_back(0);
	m_indices->push_back(1);
	m_indices->push_back(2);
	m_indices->push_back(0);
	m_indices->push_back(2);
	m_indices->push_back(3);
	m_indices->push_back(4);
	m_indices->push_back(5);
	m_indices->push_back(6);
	m_indices->push_back(4);
	m_indices->push_back(6);
	m_indices->push_back(7);
	m_indices->push_back(8);
	m_indices->push_back(9);
	m_indices->push_back(10);
	m_indices->push_back(8);
	m_indices->push_back(10);
	m_indices->push_back(11);
	m_indices->push_back(12);
	m_indices->push_back(13);
	m_indices->push_back(14);
	m_indices->push_back(12);
	m_indices->push_back(14);
	m_indices->push_back(15);
	m_indices->push_back(16);
	m_indices->push_back(17);
	m_indices->push_back(18);
	m_indices->push_back(16);
	m_indices->push_back(18);
	m_indices->push_back(19);
	m_indices->push_back(20);
	m_indices->push_back(21);
	m_indices->push_back(22);
	m_indices->push_back(20);
	m_indices->push_back(22);
	m_indices->push_back(23);
#endif

	

	D3DImage * d3dImage = new D3DImage(ResourceManager::GetInstance()->GetImageByID(IMAGE_CRATE_ID));
	//m_texture = (Image *) d3dImage;
	AddTexture((Image *) d3dImage);


	m_effect = ShaderManager::GetInstance()->GetFXByID(SHADER_SKINNED_MESH_FX_ID);

	
	
}

void Cube::SetShaderHandlers()
{
	
	
	SkinnedMeshFX *t_effect = (SkinnedMeshFX *) m_effect;
	
	t_effect->SetObjectMaterials(	m_currentMaterial->GetAmbient(), m_currentMaterial->GetDiffuse(),
									m_currentMaterial->GetSpecular(), m_currentMaterial->GetSpecularPower());

									
	//D3DImage *t_d3dText = (D3DImage *) m_texture;
	D3DImage *t_d3dText = (D3DImage *) m_currentTexture;
	t_effect->SetObjectTexture(t_d3dText->GetTexture());

	t_effect->SetTransformMatrix(GetTransformMatrix());
	t_effect->SetAlpha(m_alpha);
	
}

Cube::~Cube()
{
	ReleaseCOM(m_vertexDeclaration);

	
}


#endif