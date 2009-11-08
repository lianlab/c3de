#include "SceneNode.h"
#include "DebugMemory.h"

SceneNode::SceneNode(Mesh * a_mesh, C3DETransform *a_transform, int effect, Material * a_material)
{
	m_mesh = a_mesh;
	m_transform = a_transform;
	m_effect = effect;
	m_material = a_material;
}

Material * SceneNode::GetMaterial()
{
	return m_material;
}

int SceneNode::GetEffect()
{
	return m_effect;
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