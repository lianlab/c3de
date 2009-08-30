#include "FXManager.h"
#include "D3DMesh.h"
#include "DebugMemory.h"

FXManager * FXManager::m_instance = NULL;

FXManager::FXManager()
{
	m_effects = new vector<FX *>;

	
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
	
	m_currentEffect->GetEffect()->CommitChanges();		
	m_currentEffect->GetEffect()->BeginPass(0);
}

void FXManager::Begin(FX *effect)
{
	m_currentEffect = effect;
	UINT num = 0;
	effect->GetEffect()->Begin(&num,0);
	
}

void FXManager::End()
{
	
	m_currentEffect->GetEffect()->End();
	
}

void FXManager::PosRender()
{
	m_currentEffect->GetEffect()->EndPass();
	m_currentEffect->ResetHandlers();
}

void FXManager::SetUpdateHandlers(D3DXVECTOR3 cameraPosition, D3DXMATRIX worldViewProjection)
{
	int totalEffecs = m_effects->size();

	for(int i = 0; i < totalEffecs; i++)
	{
		FX *t_effect = m_effects->at(i);
		t_effect->SetWorldHandlers(cameraPosition, worldViewProjection);
		
	}
	
}

void FXManager::AddEffect(FX * effect)
{
	if(effect == NULL)
	{
		return;
	}
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
	vector<Mesh *> *t_meshes = new vector<Mesh *>;
	int totalMeshes = scene->GetMeshesVector()->size();

	for(int i = 0; i < totalMeshes; i++)
	{
		t_meshes->push_back(scene->GetMeshesVector()->at(i));
	}
	

	int totalMirrors = scene->GetMirrorsVector()->size();

	for(int i= 0; i < totalMirrors; i++)
	{
		t_meshes->push_back(scene->GetMirrorsVector()->at(i)->GetMesh());
	}

	int totalShadowSurfaces = scene->GetShadowSurfacesVector()->size();

	for(int i= 0; i < totalShadowSurfaces; i++)
	{
		t_meshes->push_back(scene->GetShadowSurfacesVector()->at(i)->GetMesh());
	}

	int t_totalTerrains = scene->GetTerrains()->size();

	for(int i= 0; i < t_totalTerrains; i++)
	{
		t_meshes->push_back((Mesh*)scene->GetTerrains()->at(i));
	}

	int t_totalParticleSystems = scene->GetParticleSystems()->size();

	for(int i= 0; i < t_totalParticleSystems; i++)
	{
		t_meshes->push_back((Mesh*)scene->GetParticleSystems()->at(i));
	}

	totalMeshes = t_meshes->size();

	for(int i = 0; i < totalMeshes; i++)
	{
		D3DMesh *t_mesh = static_cast<D3DMesh *>(t_meshes->at(i));
		AddEffect(t_mesh->GetEffect());		
	}	

	D3DXCOLOR ambient = scene->GetAmbientLight()->GetColor();
	D3DXCOLOR diffuse = scene->GetDiffuseLight()->GetColor();
	D3DXCOLOR specular = scene->GetSpecularLight()->GetColor();
	D3DXVECTOR3 lightPosition = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	
	int totalEffecs = m_effects->size();

	for(int i = 0; i < totalEffecs; i++)
	{
		FX *t_effect = m_effects->at(i);
		t_effect->SetLightHandlers(ambient, diffuse, specular, lightPosition);		
	}

	AddEffect(ShaderManager::GetInstance()->GetDefaultShadowFX());


	if(t_meshes)
	{
		delete t_meshes;
		t_meshes = NULL;
	}
	
}

void FXManager::AddMeshesEffects(Scene *a_scene, vector<Mesh *> *meshes)
{		
	int totalMeshes = meshes->size();

	for(int i = 0; i < totalMeshes; i++)
	{
		D3DMesh *t_mesh = static_cast<D3DMesh *>((*meshes)[i]);
		AddEffect(t_mesh->GetEffect());		
	}	

	D3DXCOLOR ambient = a_scene->GetAmbientLight()->GetColor();
	D3DXCOLOR diffuse = a_scene->GetDiffuseLight()->GetColor();
	D3DXCOLOR specular = a_scene->GetSpecularLight()->GetColor();
	D3DXVECTOR3 lightPosition = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	
	int totalEffecs = m_effects->size();

	for(int i = 0; i < totalEffecs; i++)
	{
		FX *t_effect = m_effects->at(i);
		t_effect->SetLightHandlers(ambient, diffuse, specular, lightPosition);		
	}

	//AddEffect(ShaderManager::GetInstance()->GetDefaultShadowFX());


	
	
}

FXManager::~FXManager()
{	
	if(m_effects)
	{
#if 0
		int totalEffects = m_effects->size();
		for(int i = 0; i < totalEffects; i++)
		{
			FX * t_effect = m_effects->at(i);

			if(t_effect)
			{
				delete t_effect;
				t_effect = NULL;
			}
		}
		
#endif

		delete m_effects;
		m_effects = NULL;

	}
}