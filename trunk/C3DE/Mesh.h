#ifndef MESH_H
#define MESH_H

#include "Material.h"

class Mesh
{
public:
	Mesh();
	virtual void Translate(float x, float y, float z) = 0;
	virtual float GetX() = 0;
	virtual float GetY() = 0;
	virtual float GetZ() = 0;
	virtual ~Mesh() = 0;
	virtual void Update(int deltaTime) = 0;

	void SetAmbientMaterial(Material a_material){m_ambientMaterial = a_material;}
	void SetDiffuseMaterial(Material d_material){m_diffuseMaterial = d_material;}
	void SetSpecularMaterial(Material s_material){m_specularMaterial = s_material;}

	Material GetAmbientMaterial(){return m_ambientMaterial;}
	Material GetDiffuseMaterial(){return m_diffuseMaterial;}
	Material GetSpecularMaterial(){return m_specularMaterial;}
protected:
	float m_x;
	float m_y;
	float m_z;

	Material m_ambientMaterial;
	Material m_diffuseMaterial;
	Material m_specularMaterial;
};
#endif