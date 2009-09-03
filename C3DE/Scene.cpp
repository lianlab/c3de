#include "Scene.h"
#include "DebugMemory.h"

Scene::Scene()
{

	m_meshes = new vector<Mesh *>;
	m_sceneNodes = new vector<SceneNode *>;
	m_mirrors = new vector<Mirror *>;
	m_terrains = new vector<Terrain *>;
	m_shadowSurfaces = new vector<ShadowSurface *>;

	m_ambientLight = new AmbientLight();
	m_diffuseLight = new DiffuseLight();;
	m_specularLight = new SpecularLight();;
	m_pointLight = new PointLight();

	m_particleSystems = new vector<ParticleSystem*>;

}

Scene::~Scene()
{
	FreeMeshes();

	FreeMirrors();

	FreeTerrains();

	FreeShadowSurfaces();

	FreeParticleSystems();

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

void Scene::Update(int deltaTime)
{
	int totalMeshes = m_meshes->size();

	for(int i = 0; i < totalMeshes; i++)
	{
		Mesh *t_mesh = m_meshes->at(i);
		if(t_mesh)
		{
			t_mesh->Update(deltaTime);
			
		}
	}

	int totalParticleSystems = m_particleSystems->size();

	for(int i = 0; i < totalParticleSystems; i++)
	{
		ParticleSystem *t_particleSystem = (*m_particleSystems)[i];
		if(t_particleSystem)
		{
			//TODO, fix me
			t_particleSystem->Update(10);
			if(t_particleSystem->GetIsFinished())
			{
				RemoveParticleSystem(t_particleSystem);
				totalParticleSystems--;
			}
			
		}
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

vector<SceneNode*> *Scene::GetSceneNodes()
{
	return m_sceneNodes;
}

void Scene::AddNode(SceneNode *a_node)
{
	m_sceneNodes->push_back(a_node);
}
	
void Scene::RemoveNode(SceneNode *a_node)
{
	int totalNodes = m_sceneNodes->size();

	for(int i = 0; i < totalNodes; i++)
	{
		SceneNode *t_node = (*m_sceneNodes)[i];
		//p[vbIndex] = *mAliveParticles->at(i);			
			//p[vbIndex] = *(*mAliveParticles)[i];		
		if(t_node == a_node)
		{
			m_sceneNodes->erase(m_sceneNodes->begin() + i);
			return;
		}
	}
}
	

void Scene::ClearAllNodes()
{
	int totalNodes = m_sceneNodes->size();

	for(int i = 0; i < totalNodes; i++)
	{
		SceneNode *t_node = (*m_sceneNodes)[i];
		//m_sceneNodes->erase(m_sceneNodes->begin());			
		delete t_node;
		t_node = NULL;
		
	}
	m_sceneNodes->clear();
	
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
			t_mesh = NULL;
		}
	}

	if(m_meshes)
	{
		delete m_meshes;
		m_meshes = NULL;
	}
}


void Scene::FreeParticleSystems()
{
	int totalParticleSystems = m_particleSystems->size();

	for(int i = 0; i < totalParticleSystems; i++)
	{
		ParticleSystem *t_particleSystem = m_particleSystems->at(i);
		if(t_particleSystem)
		{
			delete t_particleSystem;
			t_particleSystem = NULL;
		}
	}

	if(m_particleSystems)
	{
		delete m_particleSystems;
		m_particleSystems = NULL;
	}
}

void Scene::FreeTerrains()
{
#if 0
	int totalTerrains = m_terrains->size();

	for(int i = 0; i < totalTerrains; i++)
	{
		Terrain *t_terrain = m_terrains->at(i);
		if(t_terrain)
		{
			delete t_terrain;
			t_terrain = NULL;
		}
	}
#endif
	if(m_terrains)
	{
		delete m_terrains;
		m_terrains = NULL;
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

void Scene::RemoveTerrain(Terrain *a_terrain)
{
	int totalTerrains = m_terrains->size();

	for(int i = 0; i < totalTerrains; i++)
	{
		Terrain *t_terrain = m_terrains->at(i);
		if(a_terrain == t_terrain)
		{
			m_terrains->erase(m_terrains->begin() + i);
			return;
		}
	}
}

void Scene::RemoveParticleSystem(ParticleSystem *a_particleSystem)
{
	int totalParticleSystems = m_particleSystems->size();

	for(int i = 0; i < totalParticleSystems; i++)
	{
		ParticleSystem *t_particleSystem = m_particleSystems->at(i);
		if(a_particleSystem == t_particleSystem)
		{
			m_particleSystems->erase(m_particleSystems->begin() + i);
			return;
		}
	}
}

void Scene::AddTerrain(Terrain *a_terrain)
{
	m_terrains->push_back(a_terrain);
}

void Scene::AddParticleSystem(ParticleSystem *a_particleSystem)
{
	m_particleSystems->push_back(a_particleSystem);
}

vector<ParticleSystem*> *Scene::GetParticleSystems()
{
	return m_particleSystems;
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



