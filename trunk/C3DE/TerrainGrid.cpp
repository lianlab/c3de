#include "TerrainGrid.h"
#include "PerVertexLighting.h"
#include "SkinnedMeshFX.h"
#include "DebugMemory.h"

TerrainGrid::TerrainGrid(int a_ID, int a_rows, int a_cols, IDirect3DTexture9 *a_texture, float maxHeight, float cellSize)
{
	m_id = a_ID;

	a_rows--;
	a_cols--;

	//m_ambientMaterial = Material(0.0f, 0.0f, 1.0f, 1.0f);
	int numVertices = (a_rows +1)*(a_cols + 1);
	
	int numTris = a_rows*a_cols*2;

	float width = (float)a_cols*1.0f;
	float depth = (float)a_rows*1.0f;

	float xOffset = -width * 0.5f;
	float zOffset = depth * 0.5f;

	//int k = 0;

	m_vertices = new vector<VertexPos>;
	m_indices = new vector<int>;

	D3DLOCKED_RECT sRect;
	a_texture->LockRect(0, &sRect, NULL, NULL);
	BYTE *bytes = (BYTE*)sRect.pBits;

	D3DSURFACE_DESC desc;
	a_texture->GetLevelDesc(0, &desc);	

	float t_ratio = (float)desc.Width / a_rows;
		
	//int t_ratioInt = ROUND_FLOAT(t_ratio);	
	int t_ratioInt = (int)t_ratio;	

	//buildVertex
	for(int i = 0; i < (a_rows + 1); i++)
	{
		for(int j = 0; j < (a_cols + 1); j++)
		{
					
			int t_index = (int)(i * sRect.Pitch + j)*t_ratioInt;
			float tx = j*cellSize + xOffset;
			float tz = -i*cellSize + zOffset;		
			BYTE *b = bytes  + t_index;
			float ty = (*b/255.0f)*maxHeight;
			
			float u = (float(i) / a_rows);
			float v = (float(j) / a_cols);
			m_vertices->push_back(VertexPos(tx, ty, tz, 0.0f, 1.0f, 0.0f, u , v));		
			
		}
	}

	//build indices
	for(int i = 0; i < (a_rows); i++)
	{
		for(int j = 0; j < (a_cols); j++)
		{
			int index1 = i*(a_rows + 1) + j;
			int index2 = i*(a_rows + 1) + j + 1;
			int index3 = (i+1)*(a_rows + 1) + j;
			
			int index4 = (i+1)*(a_rows + 1) + j;
			int index5 = i*(a_rows + 1) + j + 1;
			int index6 = (i+1)*(a_rows + 1) + j + 1;
			
			m_indices->push_back(index1);
			m_indices->push_back(index2);
			m_indices->push_back(index3);
			m_indices->push_back(index4);
			m_indices->push_back(index5);
			m_indices->push_back(index6);
			
		}

	}

	m_effect = ShaderManager::GetInstance()->GetFXByID(SHADER_LIGHTS_PER_VERTEX_TEXTURES_ID);
	PerVertexLighting *t_effect = (PerVertexLighting *) m_effect;
	t_effect->SetAlpha(1.0f);


}

TerrainGrid::~TerrainGrid()
{
	ReleaseCOM(m_vertexDeclaration);
}

void TerrainGrid::SetShaderHandlers()
{		

	PerVertexLighting *t_effect = (PerVertexLighting *) m_effect;
	
	t_effect->SetObjectMaterials(	m_currentMaterial->GetAmbient(), m_currentMaterial->GetDiffuse(),
									m_currentMaterial->GetSpecular(), m_currentMaterial->GetSpecularPower());

									
	
	D3DImage *t_d3dText = (D3DImage *) m_currentTexture;
	t_effect->SetObjectTexture(t_d3dText->GetTexture());

	t_effect->SetTransformMatrix(GetTransformMatrix());
	t_effect->SetAlpha(m_alpha);
	
}
