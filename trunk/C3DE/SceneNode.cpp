#include "SceneNode.h"
#include "DebugMemory.h"

SceneNode::SceneNode(Mesh * a_mesh, C3DETransform *a_transform)
{
	m_mesh = a_mesh;
	m_transform = a_transform;
}

Mesh* SceneNode::GetMesh()
{
	return m_mesh;
}

SceneNode::~SceneNode()
{
	delete m_transform;
	m_transform = NULL;
}

D3DXMATRIX * SceneNode::GetTransform()
{
	return m_transform->GetMatrix();
}