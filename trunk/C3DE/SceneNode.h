#ifndef SCENE_NODE_H
#define SCENE_NODE_H

#include "Mesh.h"
#include "C3DETransform.h"

class SceneNode
{
public:
	SceneNode(Mesh * a_mesh, C3DETransform *a_transform);
	~SceneNode();

	D3DXMATRIX * GetTransform();
	Mesh* GetMesh();
protected:
	Mesh *m_mesh;
	C3DETransform *m_transform;
};
#endif