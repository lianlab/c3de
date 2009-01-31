#include "TerrainFactory.h"
#include "Grid.h"

TerrainFactory * TerrainFactory::m_instance = NULL;

TerrainFactory * TerrainFactory::GetInstance()
{
	if(!m_instance)
	{
		m_instance = new TerrainFactory();
	}

	return m_instance;
}

TerrainFactory::TerrainFactory()
{

}

TerrainFactory::~TerrainFactory()
{

}

/*
TerrainFactory::TerrainFactory(int m, int n)
{

}

	
TerrainFactory::TerrainFactory(int m, int n, const std::string &filename, float heightScale, float heightOffset)
{

}
*/
	
Mesh * TerrainFactory::GetTerrainMesh(int rows, int cols, IDirect3DTexture9 *a_texture, float maxHeight)
{
	Grid *t_grid = new Grid(rows, cols, 1.0f, 1.0f);

	D3DLOCKED_RECT sRect;
	a_texture->LockRect(0, &sRect, NULL, NULL);
	BYTE *bytes = (BYTE*)sRect.pBits;



	vector<VertexPos> * t_vertices = t_grid->GetVertices();

	int size = t_vertices->size();	

	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			int index = i*rows + j;
			BYTE *b = bytes  + i * sRect.Pitch + j;

			vector<VertexPos>::iterator begin = t_vertices->begin();
			VertexPos vertexCopy = t_vertices->at(i+j*cols);				
			vertexCopy.pos.y = (*b/255.0f)*maxHeight;
			vector<VertexPos>::iterator it = begin + i+j*cols;
			t_vertices->erase(it);
			begin = t_vertices->begin();
			it = begin + i+j*cols;
			t_vertices->insert(it, vertexCopy);
			
		}
	}

#if 0
	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			BYTE *b = bytes + i * sRect.Pitch + j;

			vector<VertexPos>::iterator begin = t_vertices->begin();
			VertexPos vertexCopy = t_vertices->at(i+j*cols);				
			vertexCopy.pos.y = (*b/255.0f)*maxHeight;
			vector<VertexPos>::iterator it = begin + i+j*cols;
			t_vertices->erase(it);
			begin = t_vertices->begin();
			it = begin + i+j*cols;
			t_vertices->insert(it, vertexCopy);
		}
	}
#endif

	return t_grid;

	for(int i = 0; i< size; i++)
	{
		vector<VertexPos>::iterator begin = t_vertices->begin();
		VertexPos vertexCopy = t_vertices->at(i);				
		vertexCopy.pos.y = (rand() % 10)*0.1f;
		vector<VertexPos>::iterator it = begin + i;
		t_vertices->erase(it);
		begin = t_vertices->begin();
		it = begin + i;
		t_vertices->insert(it, vertexCopy);
		


	}
	
	return t_grid;
}
	
	
bool TerrainFactory::InBounds(int i, int j)
{
	return true;
}
	
float TerrainFactory::SampleHeight3x3(int i, int j)
{
	return 0.0f;
}
	
void TerrainFactory::Filter3x3()
{

}