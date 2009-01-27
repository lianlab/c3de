#include "Grid.h"
#include "PerVertexLighting.h"
#include "DebugMemory.h"

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

	m_effect = ShaderManager::GetInstance()->GetFXByID(SHADER_LIGHTS_PER_VERTEX_TEXTURES_ID);
	PerVertexLighting *t_effect = (PerVertexLighting *) m_effect;
	t_effect->SetAlpha(1.0f);


}

Grid::~Grid()
{
	ReleaseCOM(m_vertexDeclaration);
}

void Grid::SetShaderHandlers()
{		
	PerVertexLighting *t_effect = (PerVertexLighting *) m_effect;
	//t_effect->SetObjectMaterials(	m_material->GetAmbient(), m_material->GetDiffuse(),
	//								m_material->GetSpecular(), m_material->GetSpecularPower());

	t_effect->SetTransformMatrix(GetTransformMatrix());
	
	
}

#if 0
void Grid::SetLightParameters(D3DXCOLOR ambientLightColor, D3DXCOLOR diffuseLightColor,
							D3DXCOLOR specularLightColor, D3DXVECTOR3 lightPosition, 
							D3DXVECTOR3 lightDirection, D3DXVECTOR3 lightAttenuation,
							float spotLightPower)
{	
	
	HR(m_effect->SetValue(m_shaderLightPosition, &lightPosition, sizeof(D3DXVECTOR3)));	
	HR(m_effect->SetValue(m_shaderLightDirection, &lightDirection, sizeof(D3DXVECTOR3)));	
	HR(m_effect->SetValue(m_shaderAmbientLightMaterial, &ambientLightColor, sizeof(D3DXCOLOR)));
	HR(m_effect->SetValue(m_shaderDiffuseLightMaterial, &diffuseLightColor, sizeof(D3DXCOLOR)));		
	HR(m_effect->SetValue(m_shaderSpecularLightMaterial, &specularLightColor, sizeof(D3DXCOLOR)));		
	HR(m_effect->SetValue(m_shaderLightAttenuation, lightAttenuation, sizeof(D3DXVECTOR3)));
	HR(m_effect->SetFloat(m_shaderSpotLightPower, spotLightPower));	

}
	
void Grid::SetWorldParameters(D3DXMATRIX worldMatrix, D3DXMATRIX worldViewProjection,
									D3DXMATRIX worldInverseTranspose, D3DXVECTOR3 eyePosition)
{
	
	HR(m_effect->SetMatrix(m_shaderWorldMatrix, &worldMatrix));	
	HR(m_effect->SetMatrix(m_shaderViewMatrix, &worldViewProjection));	
	HR(m_effect->SetMatrix(m_shaderWorldInverseTransposeMatrix, &worldInverseTranspose));												
	HR(m_effect->SetValue(m_shaderEyePosition, eyePosition, sizeof(D3DXVECTOR3)));	
	
}





void Grid::SetPreRenderEffectHandles(/*ID3DXEffect* fx*/)
{
	if(!m_fxHandlesInitialized)
	{
		InitializeEffectHandles(/*fx*/);
	}

	HR(m_effect->SetTechnique(m_shaderTechnique));
	//D3DImage *t_d3dText = (D3DImage *) m_texture;
	//HR(m_effect->SetTexture(m_hTex, t_d3dText->GetTexture()));

	HR(m_effect->SetValue(m_shaderObjectAmbientMaterial, &GetMaterial()->GetAmbient(),sizeof(D3DXCOLOR)));
	HR(m_effect->SetValue(m_shaderObjectDiffuseMaterial, &GetMaterial()->GetDiffuse(), sizeof(D3DXCOLOR)));
	HR(m_effect->SetValue(m_shaderObjectSpecularMaterial, &GetMaterial()->GetSpecular(), sizeof(D3DXCOLOR)));
	HR(m_effect->SetFloat(m_shaderSpecularLightPower, GetMaterial()->GetSpecularPower()));
}

void Grid::InitializeEffectHandles(/*ID3DXEffect* fx*/)
{
	m_effect = ShaderManager::GetInstance()->GetEffectById(SHADER_ONLY_LIGHTS_ID);
	m_hTex = m_effect->GetParameterByName(0, "gTex");

	m_shaderTechnique = m_effect->GetTechniqueByName("LightsTech");	
	m_shaderViewMatrix  = m_effect->GetParameterByName(0, "gWVP");	
	m_shaderEyePosition= m_effect->GetParameterByName(0, "gEyePosW");
	m_shaderAmbientLightMaterial = m_effect->GetParameterByName(0, "gAmbientLight");
	m_shaderDiffuseLightMaterial = m_effect->GetParameterByName(0, "gDiffuseLight");
	m_shaderSpecularLightMaterial = m_effect->GetParameterByName(0, "gSpecLight");
	m_shaderLightPosition = m_effect->GetParameterByName(0, "gLightPosW");
	m_shaderLightDirection = m_effect->GetParameterByName(0, "gLightDirW");
	m_shaderLightAttenuation = m_effect->GetParameterByName(0, "gAttenuation012");
	m_shaderSpotLightPower = m_effect->GetParameterByName(0, "gSpotPower");

	m_shaderObjectAmbientMaterial = m_effect->GetParameterByName(0, "gAmbientMtrl");
	m_shaderObjectDiffuseMaterial = m_effect->GetParameterByName(0, "gDiffuseMtrl");
	m_shaderObjectSpecularMaterial = m_effect->GetParameterByName(0, "gSpecMtrl");
	m_shaderSpecularLightPower = m_effect->GetParameterByName(0, "gSpecPower");

	m_shaderWorldMatrix = m_effect->GetParameterByName(0, "gWorld");
	m_shaderWorldInverseTransposeMatrix = m_effect->GetParameterByName(0, "gWorldInvTrans");
	m_fxHandlesInitialized = true;
}

#endif