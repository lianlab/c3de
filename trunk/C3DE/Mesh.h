#ifndef MESH_H
#define MESH_H

#include "Material.h"
#include "Image.h"

class Mesh
{
public:
	Mesh();
	void SetPosition(float x, float y, float z){m_x = x;m_y=y;m_z=z;}
	float GetX(){return m_x;}
	float GetY(){return m_y;}
	float GetZ(){return m_z;}

	void Scale(float x, float y, float z){m_scaleX=x;m_scaleY=y;m_scaleZ=z;}
	float GetXScale(){return m_scaleX;}
	float GetYScale(){return m_scaleY;}
	float GetZScale(){return m_scaleZ;}
	virtual ~Mesh() = 0;
	virtual void Update(int deltaTime) = 0;

	virtual void SetTexture(Image *tex) = 0;

	virtual Image * GetTexture() = 0;

	void SetMaterial(Material *material);
	Material * GetMaterial(){return m_material;}

protected:
	float m_x;
	float m_y;
	float m_z;

	float m_scaleX;
	float m_scaleY;
	float m_scaleZ;

	Image *m_texture;


	Material *m_material;
};
#endif