#include "FXManager.h"
#include "D3DMesh.h"

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
}



FXManager::~FXManager()
{

}