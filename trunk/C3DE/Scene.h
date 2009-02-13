#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "DiffuseLight.h"
#include "SpecularLight.h"
#include "AmbientLight.h"
#include "PointLight.h"

#include "Mesh.h"
#include "Mirror.h"
#include "ShadowSurface.h"
#include "Terrain.h"

using namespace std;

class Scene
{
public:
	Scene();
	virtual ~Scene();
	void SetUpFromXMLFile(char *xmlPath){};
	void AddMesh(Mesh*mesh);
	void RemoveMesh(Mesh*mesh);
	void AddTerrain(Terrain *a_terrain);
	void RemoveTerrain(Terrain *a_terrain);
	vector<Terrain*> *GetTerrains(){return m_terrains;}

	vector<Mesh *> *GetMeshesVector()
	{
		return m_meshes;
	}

	void AddMirror(Mirror*mirror);
	void RemoveMirror(Mirror*mirror);
	vector<Mirror *> *GetMirrorsVector(){return m_mirrors;}

	void AddShadowSurface(ShadowSurface*shadowSurface);
	void RemoveShadowSurface(ShadowSurface*shadowSurface);
	vector<ShadowSurface *> *GetShadowSurfacesVector(){return m_shadowSurfaces;}

	
	
	AmbientLight * GetAmbientLight(){return m_ambientLight;}
	DiffuseLight* GetDiffuseLight(){return m_diffuseLight;}
	SpecularLight * GetSpecularLight(){return m_specularLight;}
	PointLight * GetPointLight(){ return m_pointLight;}

	void SetAmbientLight(AmbientLight *light);
	void SetDiffuseLight(DiffuseLight *light);
	void SetSpecularLight(SpecularLight *light);
	void SetPointLight(PointLight *light);

	void FreeMeshes();

	virtual void Update(int deltaTime);

protected:
	vector<Mesh *> *m_meshes;
	vector<Mirror *> *m_mirrors;
	vector<ShadowSurface *> *m_shadowSurfaces;
	vector<Terrain*> * m_terrains;
	
	
	AmbientLight * m_ambientLight;
	DiffuseLight * m_diffuseLight;
	SpecularLight * m_specularLight;
	PointLight * m_pointLight;



	void FreeShadowSurfaces();
	void FreeMirrors();
	
};
#endif