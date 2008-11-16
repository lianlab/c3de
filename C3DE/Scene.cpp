#include "Scene.h"
#include "DebugMemory.h"

Scene::Scene()
{

	m_meshes = new vector<Mesh *>;
	m_mirrors = new vector<Mirror *>;
	m_shadowSurfaces = new vector<ShadowSurface *>;

	m_ambientLight = new AmbientLight();
	m_diffuseLight = new DiffuseLight();;
	m_specularLight = new SpecularLight();;
	m_pointLight = new PointLight();

}

Scene::~Scene()
{
	FreeMeshes();

	FreeMirrors();

	FreeShadowSurfaces();

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

void Scene::FreeMirrors()
{
	int totalMirrors = m_mirrors->size();

	for(int i = 0; i < totalMirrors; i++)
	{
		Mirror *t_mirror = m_mirrors->at(i);
		if(t_mirror)
		{
			delete t_mirror;
		}
	}

	if(m_mirrors)
	{
		delete m_mirrors;
		m_mirrors = NULL;
	}
}

void Scene::FreeShadowSurfaces()
{
	int totalShadowSurfaces = m_shadowSurfaces->size();

	for(int i = 0; i < totalShadowSurfaces; i++)
	{
		ShadowSurface *t_shadowSurface = m_shadowSurfaces->at(i);
		if(t_shadowSurface)
		{
			delete t_shadowSurface;
		}
	}

	if(m_shadowSurfaces)
	{
		delete m_shadowSurfaces;
		m_shadowSurfaces = NULL;
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

void Scene::AddShadowSurface(ShadowSurface*shadowSurface)
{
	m_shadowSurfaces->push_back(shadowSurface);	
}

void Scene::RemoveShadowSurface(ShadowSurface *shadowSurface)
{
	int totalShadowSurfaces = m_shadowSurfaces->size();

	for(int i = 0; i < totalShadowSurfaces; i++)
	{
		ShadowSurface *t_shadowSurface = m_shadowSurfaces->at(i);
		if(shadowSurface == t_shadowSurface)
		{
			m_shadowSurfaces->erase(m_shadowSurfaces->begin() + i);
			return;
		}
	}
}



