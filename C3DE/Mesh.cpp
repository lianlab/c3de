#include "Mesh.h"

Mesh::Mesh()
{
	/*
	m_ambientMaterial = Material(0.0f, 0.0f, 0.0f, 0.0f);
	m_diffuseMaterial = Material(0.0f, 0.0f, 0.0f, 0.0f);
	m_specularMaterial = Material(0.0f, 0.0f, 0.0f, 0.0f);
	*/
	m_material = new Material(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), 16.0f);
}

Mesh::~Mesh()
{

}