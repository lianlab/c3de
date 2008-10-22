#include "Renderer.h"
#include "PlanarMirror.h"
#include "ResourceManager.h"
#include "DebugMemory.h"

PlanarMirror::PlanarMirror():D3DMirror()
{
	
	m_vertices = new vector<VertexPos>;
	m_indices = new vector<int>;

	//vertices

	m_vertices->push_back(VertexPos(-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f));
	m_vertices->push_back(VertexPos(-1.0f,  1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f));
	m_vertices->push_back(VertexPos( 1.0f,  1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f));
	m_vertices->push_back(VertexPos( 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f));

	

	//indices
	//front face
	



	m_indices->push_back(0);
	m_indices->push_back(1);
	m_indices->push_back(2);
	m_indices->push_back(0);
	m_indices->push_back(2);
	m_indices->push_back(3);
	


	D3DImage * d3dImage = new D3DImage(ResourceManager::GetInstance()->GetImageByID(IMAGE_CRATE_ID));
	m_texture = (Image *) d3dImage;

	m_alpha = 0.5f;

	
}

#if 0
void PlanarMirror::SetLightParameters(D3DXCOLOR ambientLightColor, D3DXCOLOR diffuseLightColor,
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
	
void PlanarMirror::SetWorldParameters(D3DXMATRIX worldMatrix, D3DXMATRIX worldViewProjection,
									D3DXMATRIX worldInverseTranspose, D3DXVECTOR3 eyePosition)
{
	
	HR(m_effect->SetMatrix(m_shaderWorldMatrix, &worldMatrix));	
	HR(m_effect->SetMatrix(m_shaderViewMatrix, &worldViewProjection));	
	HR(m_effect->SetMatrix(m_shaderWorldInverseTransposeMatrix, &worldInverseTranspose));												
	HR(m_effect->SetValue(m_shaderEyePosition, eyePosition, sizeof(D3DXVECTOR3)));	
	
	HR(m_effect->SetMatrix(m_shaderTransformMatrix, &GetTransformMatrix()));	
	
}





void PlanarMirror::SetPreRenderEffectHandles(/*ID3DXEffect* fx*/)
{
	if(!m_fxHandlesInitialized)
	{
		InitializeEffectHandles(/*fx*/);
	}

	HR(m_effect->SetTechnique(m_shaderTechnique));
	D3DImage *t_d3dText = (D3DImage *) m_texture;
	HR(m_effect->SetTexture(m_hTex, t_d3dText->GetTexture()));

	HR(m_effect->SetValue(m_shaderObjectAmbientMaterial, &GetMaterial()->GetAmbient(),sizeof(D3DXCOLOR)));
	HR(m_effect->SetValue(m_shaderObjectDiffuseMaterial, &GetMaterial()->GetDiffuse(), sizeof(D3DXCOLOR)));
	HR(m_effect->SetValue(m_shaderObjectSpecularMaterial, &GetMaterial()->GetSpecular(), sizeof(D3DXCOLOR)));
	HR(m_effect->SetFloat(m_shaderSpecularLightPower, GetMaterial()->GetSpecularPower()));
	HR(m_effect->SetFloat(m_shaderAlpha, m_alpha));
}

void PlanarMirror::InitializeEffectHandles(/*ID3DXEffect* fx*/)
{
	m_effect = ShaderManager::GetInstance()->GetEffectById(SHADER_LIGHTS_TEXTURES_BLENDING_ID);
	m_hTex = m_effect->GetParameterByName(0, "gTex");

	m_shaderTechnique = m_effect->GetTechniqueByName("LightsTech");	
	m_shaderViewMatrix  = m_effect->GetParameterByName(0, "gWVP");	
	m_shaderTransformMatrix  = m_effect->GetParameterByName(0, "gTransformMatrix");	
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
	m_shaderAlpha = m_effect->GetParameterByName(0, "gAlpha");
	m_fxHandlesInitialized = true;
}


#endif

PlanarMirror::~PlanarMirror()
{
	ReleaseCOM(m_vertexDeclaration);
}

#if 0
void PlanarMirror::PreRender(Renderer *a_renderer)
{
	a_renderer->EnableAlphaBlending();
}

void PlanarMirror::PosRender(Renderer *a_renderer)
{
	a_renderer->DisableAlphaBlending();
}
#endif