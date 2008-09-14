#include "Mesh.h"

Mesh::Mesh()
{
	m_ambientMaterial = Material(0.0f, 0.0f, 0.0f, 0.0f);
	m_diffuseMaterial = Material(0.0f, 0.0f, 0.0f, 0.0f);
	m_specularMaterial = Material(0.0f, 0.0f, 0.0f, 0.0f);
}

Mesh::~Mesh()
{

}