#ifndef SCENE_NODE_H
#define SCENE_NODE_H

#include "Mesh.h"
#include "C3DETransform.h"
#include "Material.h"

class SceneNode
{
public:
	SceneNode(Mesh * a_mesh, C3DETransform *a_transform, int effect, Material * a_material = NULL);
	~SceneNode();

	D3DXMATRIX * GetTransform();
	Mesh* GetMesh();
	int GetEffect();
	Material * GetMaterial();
protected:
	Material * m_material;
	Mesh *m_mesh;
	C3DETransform *m_transform;
	int m_effect;
};
#endif