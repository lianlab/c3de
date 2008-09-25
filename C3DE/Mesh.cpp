#include "Mesh.h"

Mesh::Mesh()
{	
	m_material = new Material(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), 16.0f);
}

Mesh::~Mesh()
{

}