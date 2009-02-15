#include "Billboard.h"
#include "ResourceManager.h"
#include "Grid.h"
#include "Terrain.h"
#include "TerrainFactory.h"

Billboard::Billboard():VideoMesh(ResourceManager::GetInstance()->GetVideoByID(VIDEO_FIRST_ID))
{
	m_vertices = new vector<VertexPos>;
	m_indices = new vector<int>;
	Terrain *t_mesh = (Terrain*)TerrainFactory::GetInstance()->GetTerrainMesh(2);
	
	m_xMesh = t_mesh->GetXMesh();
#if 0
	m_vertices = t_mesh->GetVertices();
	m_indices = t_mesh->GetIndices();



	m_vertices->push_back(VertexPos(-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f));
	m_vertices->push_back(VertexPos(-1.0f,  1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f));
	m_vertices->push_back(VertexPos( 1.0f,  1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f));
	m_vertices->push_back(VertexPos( 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f));


	// Fill in the back face vertex data.
	m_vertices->push_back(VertexPos(-1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f));
	m_vertices->push_back(VertexPos( 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f));
	m_vertices->push_back(VertexPos( 1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f));
	m_vertices->push_back(VertexPos(-1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f));

	// Fill in the top face vertex data.
	m_vertices->push_back(VertexPos(-1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f));
	m_vertices->push_back(VertexPos(-1.0f, 1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f));
	m_vertices->push_back(VertexPos( 1.0f, 1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f));
	m_vertices->push_back(VertexPos( 1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f));

	// Fill in the bottom face vertex data.
	m_vertices->push_back(VertexPos(-1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f));
	m_vertices->push_back(VertexPos( 1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f));
	m_vertices->push_back(VertexPos( 1.0f, -1.0f,  1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f));
	m_vertices->push_back(VertexPos(-1.0f, -1.0f,  1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f));

	// Fill in the left face vertex data.
	m_vertices->push_back(VertexPos(-1.0f, -1.0f,  1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f));
	m_vertices->push_back(VertexPos(-1.0f,  1.0f,  1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f));
	m_vertices->push_back(VertexPos(-1.0f,  1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f));
	m_vertices->push_back(VertexPos(-1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f));

	// Fill in the right face vertex data.
	m_vertices->push_back(VertexPos( 1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f));
	m_vertices->push_back(VertexPos( 1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f));
	m_vertices->push_back(VertexPos( 1.0f,  1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f));
	m_vertices->push_back(VertexPos( 1.0f, -1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f));

#endif

#if 0
	m_indices->push_back(0);
	m_indices->push_back(1);
	m_indices->push_back(2);
	m_indices->push_back(0);
	m_indices->push_back(2);
	m_indices->push_back(3);

	m_indices->push_back(4);
	m_indices->push_back(5);
	m_indices->push_back(6);
	m_indices->push_back(4);
	m_indices->push_back(6);
	m_indices->push_back(7);
	m_indices->push_back(8);
	m_indices->push_back(9);
	m_indices->push_back(10);
	m_indices->push_back(8);
	m_indices->push_back(10);
	m_indices->push_back(11);
	m_indices->push_back(12);
	m_indices->push_back(13);
	m_indices->push_back(14);
	m_indices->push_back(12);
	m_indices->push_back(14);
	m_indices->push_back(15);
	m_indices->push_back(16);
	m_indices->push_back(17);
	m_indices->push_back(18);
	m_indices->push_back(16);
	m_indices->push_back(18);
	m_indices->push_back(19);
	m_indices->push_back(20);
	m_indices->push_back(21);
	m_indices->push_back(22);
	m_indices->push_back(20);
	m_indices->push_back(22);
	m_indices->push_back(23);
#endif
}

Billboard::~Billboard()
{

}