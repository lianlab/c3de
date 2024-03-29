#ifndef FX_MANAGER_H
#define FX_MANAGER_H

#include "CommonDefs.h"
#include "d3dx9.h"
#include "Scene.h"
#include "FX.h"

#include <vector>



using namespace std;


class FXManager
{
public:
	static FXManager * GetInstance();
	~FXManager();

	//updates a list of all used effects in the scene
	void SetSceneEffects(Scene *scene);
	void AddMeshesEffects(Scene *a_scene, vector<Mesh *> *meshes);

	//updates the parameters that needs to be updated on every render, like the camera position
	void SetUpdateHandlers(D3DXVECTOR3 cameraPosition, D3DXMATRIX worldViewProjection);

	//updates the handlers that are suppose to be updated only once per scene, like lights
	//specs
	void setSceneHandlers(	D3DXCOLOR ambientLightColor, D3DXCOLOR diffuseLightColor,
							D3DXCOLOR specularLightColor, D3DXVECTOR3 lightPosition,
							D3DXVECTOR3 lightDirection, D3DXVECTOR3 lightAttenuation,
							float spotLightPower, D3DXMATRIX world, D3DXMATRIX worldInverseTranspose);
							

	
	void PreRender();
	void PosRender();
	
	void Begin(FX *effect);
	void End();

			
	void AddEffect(FX *effect);
	void AddEffect2(Scene *a_scene, FX *effect);
private:
	vector<FX *> *m_effects;

	FX *m_currentEffect;

	
	
	static FXManager * m_instance;
	FXManager();

	
};
#endif