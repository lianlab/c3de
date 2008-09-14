#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "AmbientLight.h"
#include "DirectionalLight.h"
#include "Mesh.h"

using namespace std;

class Scene
{
public:
	Scene();
	virtual ~Scene();
	void SetUpFromXMLFile(char *xmlPath){};
	vector<AmbientLight *> *GetAmbientLightsVector(){return m_ambientLights;}
	vector<DirectionalLight *> *GetDirectionalLightsVector(){return m_directionalLights;}
	vector<Mesh *> *GetMeshesVector(){return m_meshes;}

	void AddMesh(Mesh*mesh){m_meshes->push_back(mesh);}
	void AddAmbientLight(AmbientLight*light){m_ambientLights->push_back(light);}
	void AddDirectionalLight(DirectionalLight*light){m_directionalLights->push_back(light);}
	void RemoveMesh(Mesh*mesh);
	void RemoveAmbientLight(AmbientLight*light);
	void RemoveDirectionalLight(DirectionalLight*light);
private:
	vector<AmbientLight *> * m_ambientLights;
	vector<DirectionalLight *> * m_directionalLights;
	vector<Mesh *> *m_meshes;
};
#endif