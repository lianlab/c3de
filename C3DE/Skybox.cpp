#include "Skybox.h"
#include "D3DRenderer.h"
#include "PerVertexLightingNoFog.h"
#include "ResourceManager.h"
#include "DebugMemory.h"

Skybox::Skybox(float size)
{
	m_vertices = new vector<VertexPos>;
	m_indices = new vector<int>;

	float halfSize = size/2.0f;

	float quarter = (1.0f/4.0f);
	float third = (1.0f/3.0f);

	m_vertices->push_back(VertexPos(-halfSize, -halfSize, -halfSize, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f));
	m_vertices->push_back(VertexPos(-halfSize,  halfSize, -halfSize, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f));
	m_vertices->push_back(VertexPos( halfSize,  halfSize, -halfSize, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f));
	m_vertices->push_back(VertexPos( halfSize, -halfSize, -halfSize, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f));

	// Fill in the back face vertex data.
	m_vertices->push_back(VertexPos(-halfSize, -halfSize, halfSize, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f));
	m_vertices->push_back(VertexPos( halfSize, -halfSize, halfSize, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f));
	m_vertices->push_back(VertexPos( halfSize,  halfSize, halfSize, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f));
	m_vertices->push_back(VertexPos(-halfSize,  halfSize, halfSize, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f));


	// Fill in the top face vertex data.
	m_vertices->push_back(VertexPos(-halfSize, halfSize, -halfSize, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f));
	m_vertices->push_back(VertexPos(-halfSize, halfSize,  halfSize, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f));
	m_vertices->push_back(VertexPos( halfSize, halfSize,  halfSize, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f));
	m_vertices->push_back(VertexPos( halfSize, halfSize, -halfSize, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f));

	// Fill in the left face vertex data.
	m_vertices->push_back(VertexPos(-halfSize, -halfSize,  halfSize, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f));
	m_vertices->push_back(VertexPos(-halfSize,  halfSize,  halfSize, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f));
	m_vertices->push_back(VertexPos(-halfSize,  halfSize, -halfSize, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f));
	m_vertices->push_back(VertexPos(-halfSize, -halfSize, -halfSize, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f));

	// Fill in the right face vertex data.
	m_vertices->push_back(VertexPos( halfSize, -halfSize, -halfSize, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f));
	m_vertices->push_back(VertexPos( halfSize,  halfSize, -halfSize, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f));
	m_vertices->push_back(VertexPos( halfSize,  halfSize,  halfSize, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f));
	m_vertices->push_back(VertexPos( halfSize, -halfSize,  halfSize, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f));

	//indices
	//front face

	m_indices->push_back(2);
	m_indices->push_back(1);
	m_indices->push_back(0);
	m_indices->push_back(2);
	m_indices->push_back(0);
	m_indices->push_back(3);

	m_indices->push_back(6);
	m_indices->push_back(5);
	m_indices->push_back(4);
	m_indices->push_back(6);
	m_indices->push_back(4);
	m_indices->push_back(7);


	m_indices->push_back(10);
	m_indices->push_back(9);
	m_indices->push_back(8);
	m_indices->push_back(10);
	m_indices->push_back(8);
	m_indices->push_back(11);

	m_indices->push_back(14);
	m_indices->push_back(13);
	m_indices->push_back(12);
	m_indices->push_back(14);
	m_indices->push_back(12);
	m_indices->push_back(15);

	m_indices->push_back(18);
	m_indices->push_back(17);
	m_indices->push_back(16);
	m_indices->push_back(18);
	m_indices->push_back(16);
	m_indices->push_back(19);

	D3DImage * d3dImage = new D3DImage(ResourceManager::GetInstance()->GetTextureByID(IMAGE_SKYBOX_ID));	
	AddTexture((Image *) d3dImage);

	Material *t_material = new Material(	D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),
										D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f), 16.0f);	

	AddMaterial(t_material);


	CreateXMesh(D3DRenderer::GetDevice());


	//Set Attributes
	DWORD *att = 0;
	m_xMesh->LockAttributeBuffer(0,&att);

	//Set each quad to its own sub mesh
	//for(int i=0;i<12;i++)
	for(int i=0;i<10;i++)
		att[i] = i / 2;

	m_xMesh->UnlockAttributeBuffer();


	FreeTextures();
	FreeMaterials();

	m_materials = new vector<Material *>;
	m_textures = new vector<Image *>;

	AddMaterial(new Material(	D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),
										D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f), 16.0f));	
	AddMaterial(new Material(	D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),
										D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f), 16.0f));	
	AddMaterial(new Material(	D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),
										D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f), 16.0f));	
	AddMaterial(new Material(	D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),
										D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f), 16.0f));	
	AddMaterial(new Material(	D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),
										D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f), 16.0f));	
	
	AddTexture((Image *) new D3DImage(ResourceManager::GetInstance()->GetTextureByID(IMAGE_SKYBOX_FRONT_ID)));
	AddTexture((Image *) new D3DImage(ResourceManager::GetInstance()->GetTextureByID(IMAGE_SKYBOX_BACK_ID)));
	AddTexture((Image *) new D3DImage(ResourceManager::GetInstance()->GetTextureByID(IMAGE_SKYBOX_UP_ID)));
	AddTexture((Image *) new D3DImage(ResourceManager::GetInstance()->GetTextureByID(IMAGE_SKYBOX_LEFT_ID)));
	AddTexture((Image *) new D3DImage(ResourceManager::GetInstance()->GetTextureByID(IMAGE_SKYBOX_RIGHT_ID)));


	m_effect = ShaderManager::GetInstance()->GetFXByID(SHADER_LIGHTS_PER_VERTEX_TEXTURES_NO_FOG_ID);

	
	
}

Skybox::~Skybox()
{
	ReleaseCOM(m_vertexDeclaration);

	FreeTextures();
	
	FreeMaterials();
}


void Skybox::SetShaderHandlers()
{
	D3DCamera *t_camera = (D3DCamera*)D3DRenderer::GetInstance()->GetCamera();
	SetPosition(t_camera->GetPosition().x, t_camera->GetPosition().y, t_camera->GetPosition().z);
	PerVertexLightingNoFog *t_effect = (PerVertexLightingNoFog *) m_effect;
	
	t_effect->SetObjectMaterials(	m_currentMaterial->GetAmbient(), m_currentMaterial->GetDiffuse(),
									m_currentMaterial->GetSpecular(), m_currentMaterial->GetSpecularPower());

									
	
	D3DImage *t_d3dText = (D3DImage *) m_currentTexture;
	t_effect->SetObjectTexture(t_d3dText->GetTexture());

	t_effect->SetTransformMatrix(GetTransformMatrix());
	//t_effect->SetAlpha(m_alpha);
	
}