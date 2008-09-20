#ifndef MATERIAL_H
#define MATERIAL_H

#include <d3dx9.h>

class Material
{	
public:
	
	Material(D3DXCOLOR ambient, D3DXCOLOR  diffuse, D3DXCOLOR specular, float specPower);
	~Material();

	D3DXCOLOR GetAmbient(){return m_ambient;}
	D3DXCOLOR GetDiffuse(){return m_diffuse;}
	D3DXCOLOR GetSpecular(){return m_specular;}
	float GetSpecularPower(){return m_specularPower;}
	
private:
	D3DXCOLOR m_ambient;
	D3DXCOLOR m_diffuse;
	D3DXCOLOR m_specular;
	float m_specularPower;

	
};



#endif