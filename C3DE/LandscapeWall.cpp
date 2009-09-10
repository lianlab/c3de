
#include "D3DRenderer.h"
#include "LandscapeWall.h"
#include "ResourceManager.h"
#include "PerVertexLightingWallNoFog.h"

#include "DebugMemory.h"

LandscapeWall::LandscapeWall(int texID)
{
	
	m_vertices = new vector<VertexPos>;
	m_indices = new vector<int>;

	//vertices


	m_vertices->push_back(VertexPos(-0.5f, 0.0f, -0.25, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f)); // 0
	m_vertices->push_back(VertexPos(-0.5f,  5.8f, -0.25, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f)); // 1
	m_vertices->push_back(VertexPos( 0.5f,  5.8f, -0.25, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f));//2
	m_vertices->push_back(VertexPos( 0.5f, 0.0f, -0.25, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f));//3

	// Fill in the back face vertex data.
	m_vertices->push_back(VertexPos(-0.5f, 0.0f, 0.25f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f));//4
	m_vertices->push_back(VertexPos( 0.5f, 0.0f, 0.25f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f));//5
	m_vertices->push_back(VertexPos( 0.5f,  5.8f, 0.25f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f));//6
	m_vertices->push_back(VertexPos(-0.5f,  5.8f, 0.25f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f));//7

	

	// Fill in the left face vertex data.
	m_vertices->push_back(VertexPos(-0.5f, 0.0f,  0.25f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f));//8
	m_vertices->push_back(VertexPos(-0.5f,  5.8f,  0.25f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f));//9
	m_vertices->push_back(VertexPos(-0.5f,  5.8f, -0.25f, -1.0f, 0.0f, 0.0f, 0.12f, 0.0f));//10
	m_vertices->push_back(VertexPos(-0.5f, 0.0f, -0.25f, -1.0f, 0.0f, 0.0f, 0.12f, 1.0f));//11

	// Fill in the right face vertex data.
	m_vertices->push_back(VertexPos( 0.5f, 0.0f, -0.25f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f));//12
	m_vertices->push_back(VertexPos( 0.5f,  5.8f, -0.25f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f));//13
	m_vertices->push_back(VertexPos( 0.5f,  5.8f,  0.25f, 1.0f, 0.0f, 0.0f, 0.12f, 0.0f));//14
	m_vertices->push_back(VertexPos( 0.5f, 0.0f,  0.25f, 1.0f, 0.0f, 0.0f, 0.12f, 1.0f));//15

	
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




	

	D3DImage * d3dImage = new D3DImage(ResourceManager::GetInstance()->GetTextureByID(texID));	
	AddTexture((Image *) d3dImage);

	Material *t_material = new Material(	D3DXCOLOR(0.0f, 0.0f, 0.0f,0.0f),D3DXCOLOR(0.0f, 0.0f, 0.0f,1.0f),
										D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f), 16.0f);	

	AddMaterial(t_material);

	CreateXMesh(D3DRenderer::GetDevice());

	m_effect = ShaderManager::GetInstance()->GetFXByID(SHADER_LIGHTS_PER_VERTEX_TEXTURES_WALL_NO_FOG_ID);

	
	
}

void LandscapeWall::Scale(float x, float y, float z)
{

	
	m_vertices->clear();

	float t_halfX = x/2.0f;

	float t_ratio = x/5.8f;
	x = t_ratio;

	m_vertices->push_back(VertexPos(-t_halfX, 0.0f, -0.25, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f));
	m_vertices->push_back(VertexPos(-t_halfX,  5.8f, -0.25, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f));
	m_vertices->push_back(VertexPos( t_halfX,  5.8f, -0.25, 0.0f, 0.0f, -1.0f, x, 0.0f));
	m_vertices->push_back(VertexPos( t_halfX, 0.0f, -0.25, 0.0f, 0.0f, -1.0f, x, 1.0f));

	// Fill in the back face vertex data.
	m_vertices->push_back(VertexPos(-t_halfX, 0.0f, 0.25f, 0.0f, 0.0f, 1.0f, x, 1.0f));
	m_vertices->push_back(VertexPos( t_halfX, 0.0f, 0.25f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f));
	m_vertices->push_back(VertexPos( t_halfX,  5.8f, 0.25f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f));
	m_vertices->push_back(VertexPos(-t_halfX,  5.8f, 0.25f, 0.0f, 0.0f, 1.0f, x, 0.0f));



	// Fill in the left face vertex data.
	m_vertices->push_back(VertexPos(-t_halfX, 0.0f,  0.25f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f));
	m_vertices->push_back(VertexPos(-t_halfX,  5.8f,  0.25f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f));
	m_vertices->push_back(VertexPos(-t_halfX,  5.8f, -0.25f, -1.0f, 0.0f, 0.0f, 0.12f, 0.0f));
	m_vertices->push_back(VertexPos(-t_halfX, 0.0f, -0.25f, -1.0f, 0.0f, 0.0f, 0.12f, 1.0f));

	// Fill in the right face vertex data.
	m_vertices->push_back(VertexPos( t_halfX, 0.0f, -0.25f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f));
	m_vertices->push_back(VertexPos( t_halfX,  5.8f, -0.25f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f));
	m_vertices->push_back(VertexPos( t_halfX,  5.8f,  0.25f, 1.0f, 0.0f, 0.0f, 0.12f, 0.0f));
	m_vertices->push_back(VertexPos( t_halfX, 0.0f,  0.25f, 1.0f, 0.0f, 0.0f, 0.12f, 1.0f));

	CreateXMesh(D3DRenderer::GetDevice());


}

void LandscapeWall::SetShaderHandlers()
{
	
	
	PerVertexLightingWallNoFog *t_effect = (PerVertexLightingWallNoFog *) m_effect;
	
	t_effect->SetObjectMaterials(	m_currentMaterial->GetAmbient(), m_currentMaterial->GetDiffuse(),
									m_currentMaterial->GetSpecular(), m_currentMaterial->GetSpecularPower());

									
	
	D3DImage *t_d3dText = (D3DImage *) m_currentTexture;
	t_effect->SetObjectTexture(t_d3dText->GetTexture());

	t_effect->SetTransformMatrix(GetTransformMatrix());
	//t_effect->SetAlpha(m_alpha);
	
}

LandscapeWall::~LandscapeWall()
{
	ReleaseCOM(m_vertexDeclaration);

	FreeTextures();
	//CRASH
	FreeMaterials();
	
}



