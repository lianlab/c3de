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
	
	void Begin();
	void End();
	
			
private:
	vector<FX *> *m_effects;

	void AddEffect(FX *effect);
	
	static FXManager * m_instance;
	FXManager();

	
};
#endif