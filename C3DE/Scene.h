#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "AmbientLight.h"
#include "PointLight.h"
#include "Mesh.h"

using namespace std;

class Scene
{
public:
	Scene();
	virtual ~Scene();
	void SetUpFromXMLFile(char *xmlPath){};
	vector<AmbientLight *> *GetAmbientLightsVector(){return m_ambientLights;}
	vector<PointLight *> *GetPointLightsVector(){return m_pointLights;}
	vector<Mesh *> *GetMeshesVector(){return m_meshes;}

	void AddMesh(Mesh*mesh){m_meshes->push_back(mesh);}
	void AddAmbientLight(AmbientLight*light){m_ambientLights->push_back(light);}
	void AddPointLight(PointLight*light){m_pointLights->push_back(light);}
	void RemoveMesh(Mesh*mesh);
	void RemoveAmbientLight(AmbientLight*light);
	void RemovePointLight(PointLight*light);
private:
	vector<AmbientLight *> * m_ambientLights;
	vector<PointLight *> * m_pointLights;
	vector<Mesh *> *m_meshes;
};
#endif