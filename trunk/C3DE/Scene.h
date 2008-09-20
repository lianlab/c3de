#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "DiffuseLight.h"
#include "SpecularLight.h"
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
	void AddMesh(Mesh*mesh){m_meshes->push_back(mesh);}	
	void RemoveMesh(Mesh*mesh);
	vector<Mesh *> *GetMeshesVector(){return m_meshes;}
	
	AmbientLight * GetAmbientLight(){return m_ambientLight;}
	DiffuseLight* GetDiffuseLight(){return m_diffuseLight;}
	SpecularLight * GetSpecularLight(){return m_specularLight;}
	PointLight * GetPointLight(){ return m_pointLight;}

	void SetAmbientLight(AmbientLight *light){m_ambientLight = light;}
	void SetDiffuseLight(DiffuseLight *light){m_diffuseLight = light;}
	void SetSpecularLight(SpecularLight *light){m_specularLight = light;}
	void SetPointLight(PointLight *light){m_pointLight = light;}
	
#if 0
	vector<AmbientLight *> *GetAmbientLightsVector(){return m_ambientLights;}
	vector<PointLight *> *GetPointLightsVector(){return m_pointLights;}
	
	void AddAmbientLight(AmbientLight*light){m_ambientLights->push_back(light);}
	void AddPointLight(PointLight*light){m_pointLights->push_back(light);}
	void RemoveAmbientLight(AmbientLight*light);
	void RemovePointLight(PointLight*light);


private:
	vector<AmbientLight *> * m_ambientLights;
	vector<PointLight *> * m_pointLights;
#endif
protected:
	vector<Mesh *> *m_meshes;
	
	AmbientLight * m_ambientLight;
	DiffuseLight * m_diffuseLight;
	SpecularLight * m_specularLight;
	PointLight * m_pointLight;
	
};
#endif