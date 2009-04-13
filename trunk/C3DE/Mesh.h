#ifndef MESH_H
#define MESH_H

#include "Material.h"
#include "Image.h"
#include <vector>


class Renderer;

using namespace std;

const float EPSILON  = 0.001f;

class Mesh
{
public:
	Mesh();
	virtual void SetPosition(float x, float y, float z){m_x = x;m_y=y;m_z=z;}
	float GetX(){return m_x;}
	float GetY(){return m_y;}
	float GetZ(){return m_z;}

	virtual void Rotate(float x, float y, float z){m_rotateX = x;m_rotateY=y;m_rotateZ=z;}
	float GetRotationX(){return m_rotateX;}
	float GetRotationY(){return m_rotateY;}
	float GetRotationZ(){return m_rotateZ;}

	virtual void Scale(float x, float y, float z){m_scaleX=x;m_scaleY=y;m_scaleZ=z;}
	virtual void UniformScale(float value){m_scaleX=value;m_scaleY=value;m_scaleZ=value;}
	float GetXScale(){return m_scaleX;}
	float GetYScale(){return m_scaleY;}
	float GetZScale(){return m_scaleZ;}
	virtual ~Mesh() = 0;
	virtual void Update(int deltaTime) = 0;

	//virtual void SetTexture(Image *tex) = 0;

	//virtual Image * GetTexture() = 0;

	std::vector<Material*> *GetMaterials(){return m_materials;};
	std::vector<Image*> *GetTextures(){return m_textures;}

	void AddTexture(Image *a_image){m_textures->push_back(a_image);}
	//void SetMaterial(Material *material);
	void AddMaterial(Material *a_material){m_materials->push_back(a_material);}
	void SetCurrentMaterial(Material *a_material){m_currentMaterial = a_material;}
	void SetCurrentTexture(Image *a_texture){m_currentTexture = a_texture;}
	//Material * GetMaterial(){return m_material;}

	virtual void PreRender(Renderer *a_renderer){}
	virtual void PosRender(Renderer *a_renderer){}

	void SetAlpha(float a_alpha){m_alpha = a_alpha;}
	float GetAlpha(){return m_alpha;}

	virtual void SetShaderHandlers(){}

protected:
	Material *m_currentMaterial;
	float m_x;
	float m_y;
	float m_z;

	float m_alpha;

	float m_scaleX;
	float m_scaleY;
	float m_scaleZ;

	float m_rotateX;
	float m_rotateY;
	float m_rotateZ;

	//Image *m_texture;
	Image *m_currentTexture;


	//Material *m_material;

	vector<Image*> *m_textures;
	vector<Material*> *m_materials;

};
#endif