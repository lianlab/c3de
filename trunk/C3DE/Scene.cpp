#include "Scene.h"

Scene::Scene()
{
	m_directionalLights = new vector<DirectionalLight *>;
	m_ambientLights = new vector<AmbientLight *>;
	m_meshes = new vector<Mesh *>;

}

Scene::~Scene()
{

}

void Scene::RemoveMesh(Mesh *mesh)
{
	int totalMeshes = m_meshes->size();

	for(int i = 0; i < totalMeshes; i++)
	{
		Mesh *t_mesh = m_meshes->at(i);
		if(mesh == t_mesh)
		{
			m_meshes->erase(m_meshes->begin() + i);
			return;
		}
	}
}

void Scene::RemoveAmbientLight(AmbientLight *light)
{
	int totalLights = m_ambientLights->size();

	for(int i = 0; i < totalLights; i++)
	{
		AmbientLight *totalLights = m_ambientLights->at(i);
		if(light == totalLights)
		{
			m_ambientLights->erase(m_ambientLights->begin() + i);
			return;
		}
	}
}

void Scene::RemoveDirectionalLight(DirectionalLight *light)
{
	int totalLights = m_directionalLights->size();

	for(int i = 0; i < totalLights; i++)
	{
		DirectionalLight *totalLights = m_directionalLights->at(i);
		if(light == totalLights)
		{
			m_directionalLights->erase(m_directionalLights->begin() + i);
			return;
		}
	}
}