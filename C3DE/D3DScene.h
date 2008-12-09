#ifndef D3DSCENE_H
#define D3DSCENE_H

#include "Scene.h"
#include "D3DCommonDefs.h"

class D3DScene : public Scene
{
public:
	D3DScene();
	virtual ~D3DScene();
	D3DXVECTOR3 * GetLightAttenuation(){return m_lightAttenuation;}
	void SetLightAttenuation(D3DXVECTOR3 *attenuation);

	virtual void Initialize();

	

	D3DXVECTOR3 *m_lightAttenuation;
};
#endif