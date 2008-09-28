#include "Grid.h"

Grid::Grid(int numCellsRows, int numCellsCols, float dx, float dz)
{


	//m_ambientMaterial = Material(0.0f, 0.0f, 1.0f, 1.0f);
	int numVertices = (numCellsRows +1)*(numCellsCols + 1);
	
	int numTris = numCellsRows*numCellsCols*2;

	float width = (float)numCellsCols*dx;
	float depth = (float)numCellsRows*dz;

	float xOffset = -width * 0.5f;
	float zOffset = depth * 0.5f;

	//int k = 0;

	m_vertices = new vector<VertexPos>;
	m_indices = new vector<int>;

	//buildVertex
	for(int i = 0; i < (numCellsRows + 1); i++)
	{
		for(int j = 0; j < (numCellsCols + 1); j++)
		{
					
			float tx = j*dx + xOffset;
			float tz = -i*dz + zOffset;
			m_vertices->push_back(VertexPos(tx, 0.0f, tz));		
			
		}
	}

	//build indices
	for(int i = 0; i < (numCellsRows); i++)
	{
		for(int j = 0; j < (numCellsCols); j++)
		{
			int index1 = i*(numCellsRows + 1) + j;
			int index2 = i*(numCellsRows + 1) + j + 1;
			int index3 = (i+1)*(numCellsRows + 1) + j;
			
			int index4 = (i+1)*(numCellsRows + 1) + j;
			int index5 = i*(numCellsRows + 1) + j + 1;
			int index6 = (i+1)*(numCellsRows + 1) + j + 1;
			
			m_indices->push_back(index1);
			m_indices->push_back(index2);
			m_indices->push_back(index3);
			m_indices->push_back(index4);
			m_indices->push_back(index5);
			m_indices->push_back(index6);
			
		}

	}



}

void Grid::SetEffectHandles(ID3DXEffect* fx)
{
	
	if(!m_fxHandlesInitialized)
	{
		InitializeEffectHandles(fx);
	}

	
}

void Grid::InitializeEffectHandles(ID3DXEffect* fx)
{

	
	m_hTex = fx->GetParameterByName(0, "gTex");
	m_fxHandlesInitialized = true;
	
}

Grid::~Grid()
{
	ReleaseCOM(m_vertexDeclaration);
}

