#ifndef MESH_H
#define MESH_H

#include "Material.h"
#include "Image.h"

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

	virtual void SetTexture(Image *tex) = 0;

	virtual Image * GetTexture() = 0;

	void SetMaterial(Material *material){m_material = material;}
	Material * GetMaterial(){return m_material;}

protected:
	float m_x;
	float m_y;
	float m_z;

	Image *m_texture;


	Material *m_material;
};
#endif