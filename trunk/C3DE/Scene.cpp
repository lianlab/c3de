#include "Scene.h"

Scene::Scene()
{
	m_pointLights = new vector<PointLight *>;
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

void Scene::RemovePointLight(PointLight *light)
{
	int totalLights = m_pointLights->size();

	for(int i = 0; i < totalLights; i++)
	{
		PointLight *totalLights = m_pointLights->at(i);
		if(light == totalLights)
		{
			m_pointLights->erase(m_pointLights->begin() + i);
			return;
		}
	}
}