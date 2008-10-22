#include "FXManager.h"
#include "D3DMesh.h"

FXManager * FXManager::m_instance = NULL;

FXManager::FXManager()
{
	m_effects = new vector<FX *>;

	//m_effect = ShaderManager::GetInstance()->GetFXByID(SHADER_LIGHTS_PER_VERTEX_TEXTURES_ID)->GetEffect();
}

FXManager * FXManager::GetInstance()
{
	if(!m_instance)
	{
		m_instance = new FXManager();
	}

	return m_instance;
}

void FXManager::PreRender()
{
	
	ShaderManager::GetInstance()->GetFXByID(SHADER_LIGHTS_PER_VERTEX_TEXTURES_ID)->GetEffect()->CommitChanges();		
	ShaderManager::GetInstance()->GetFXByID(SHADER_LIGHTS_PER_VERTEX_TEXTURES_ID)->GetEffect()->BeginPass(0);
}

void FXManager::Begin()
{
	UINT num = 0;
	ShaderManager::GetInstance()->GetFXByID(SHADER_LIGHTS_PER_VERTEX_TEXTURES_ID)->GetEffect()->Begin(&num,0);
	
}

void FXManager::End()
{
	
	ShaderManager::GetInstance()->GetFXByID(SHADER_LIGHTS_PER_VERTEX_TEXTURES_ID)->GetEffect()->End();
	
}

void FXManager::PosRender()
{
	ShaderManager::GetInstance()->GetFXByID(SHADER_LIGHTS_PER_VERTEX_TEXTURES_ID)->GetEffect()->EndPass();
	
}

void FXManager::SetUpdateHandlers(D3DXVECTOR3 cameraPosition, D3DXMATRIX worldViewProjection)
{
	ShaderManager::GetInstance()->GetFXByID(SHADER_LIGHTS_PER_VERTEX_TEXTURES_ID)->SetWorldHandlers(cameraPosition, worldViewProjection);

}

void FXManager::AddEffect(FX * effect)
{
	int totalEffecs = m_effects->size();

	for(int i = 0; i < totalEffecs; i++)
	{
		FX *t_effect = m_effects->at(i);
		if(t_effect == effect)
		{			
			return;
		}
	}

	m_effects->push_back(effect);
}

void FXManager::SetSceneEffects(Scene *scene)
{
	int totalMeshes = scene->GetMeshesVector()->size();

	vector<Mesh *> *t_meshes = scene->GetMeshesVector();

	for(int i = 0; i < totalMeshes; i++)
	{
		D3DMesh *t_mesh = static_cast<D3DMesh *>(t_meshes->at(i));
		//AddEffect(t_mesh->GetEffect());
	}

	D3DXCOLOR ambient = scene->GetAmbientLight()->GetColor();
	D3DXCOLOR diffuse = scene->GetDiffuseLight()->GetColor();
	D3DXCOLOR specular = scene->GetSpecularLight()->GetColor();
	D3DXVECTOR3 lightPosition = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	ShaderManager::GetInstance()->GetFXByID(SHADER_LIGHTS_PER_VERTEX_TEXTURES_ID)->SetLightHandlers(ambient, diffuse, specular, lightPosition);

}



FXManager::~FXManager()
{

}