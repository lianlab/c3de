#include "Scene.h"
#include "DebugMemory.h"

Scene::Scene()
{

	m_meshes = new vector<Mesh *>;
	m_mirrors = new vector<Mirror *>;

	m_ambientLight = new AmbientLight();
	m_diffuseLight = new DiffuseLight();;
	m_specularLight = new SpecularLight();;
	m_pointLight = new PointLight();

}

Scene::~Scene()
{
	FreeMeshes();

	if(m_ambientLight)
	{
		delete m_ambientLight;
		m_ambientLight = NULL;
	}

	if(m_diffuseLight)
	{
		delete m_diffuseLight;
		m_diffuseLight = NULL;
	}

	if(m_specularLight)
	{
		delete m_specularLight;
		m_specularLight = NULL;
	}

	if(m_pointLight)
	{
		delete m_pointLight;
		m_pointLight = NULL;
	}
}

void Scene::SetAmbientLight(AmbientLight *light)
{
	if(m_ambientLight)
	{
		delete m_ambientLight;
		m_ambientLight = NULL;
	}
	m_ambientLight = light;
}
	
void Scene::SetDiffuseLight(DiffuseLight *light)
{
	if(m_diffuseLight)
	{
		delete m_diffuseLight;
		m_diffuseLight = NULL;
	}
	m_diffuseLight = light;
}

void Scene::SetSpecularLight(SpecularLight *light)
{
	if(m_specularLight)
	{
		delete m_specularLight;
		m_specularLight = NULL;
	}
	m_specularLight = light;
}

void Scene::SetPointLight(PointLight *light)
{
	if(m_pointLight)
	{
		delete m_pointLight;
		m_pointLight = NULL;
	}
	m_pointLight = light;
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

void Scene::FreeMeshes()
{
	int totalMeshes = m_meshes->size();

	for(int i = 0; i < totalMeshes; i++)
	{
		Mesh *t_mesh = m_meshes->at(i);
		if(t_mesh)
		{
			delete t_mesh;
		}
	}

	if(m_meshes)
	{
		delete m_meshes;
		m_meshes = NULL;
	}
}

void Scene::AddMesh(Mesh*mesh)
{

	if(mesh->GetAlpha() < 1.0f)
	{
		m_meshes->push_back(mesh);
	}
	else
	{
		m_meshes->insert(m_meshes->begin(), mesh);
	}

}	

void Scene::AddMirror(Mirror*mirror)
{
	m_mirrors->push_back(mirror);	
}

void Scene::RemoveMirror(Mirror *mirror)
{
	int totalMirrors = m_mirrors->size();

	for(int i = 0; i < totalMirrors; i++)
	{
		Mirror *t_mirror = m_mirrors->at(i);
		if(mirror == t_mirror)
		{
			m_mirrors->erase(m_mirrors->begin() + i);
			return;
		}
	}
}



