#include "FXManager.h"
#include "D3DMesh.h"

FXManager * FXManager::m_instance = NULL;

FXManager::FXManager()
{
	m_effects = new vector<FX *>;
}

FXManager * FXManager::GetInstance()
{
	if(!m_instance)
	{
		m_instance = new FXManager();
	}

	return m_instance;
}

void FXManager::PreRender()
{
	
	m_effect->CommitChanges();		
	m_effect->BeginPass(0);
}

void FXManager::Begin()
{
	UINT num = 0;
	m_effect->Begin(&num,0);
	
}

void FXManager::End()
{
	
	m_effect->End();
	
}

void FXManager::PosRender()
{
	m_effect->EndPass();
	
}

void FXManager::SetUpdateHandlers(D3DXVECTOR3 cameraPosition, D3DXMATRIX worldViewProjection)
{
	D3DXMATRIX W;		
	D3DXMatrixIdentity(&W);			

	D3DXMATRIX WIT;
	D3DXMatrixInverse(&WIT, 0, &W);
	D3DXMatrixTranspose(&WIT, &WIT);														
	
	
	HR(m_effect->SetMatrix(m_shaderWorldMatrix, &W));	
	HR(m_effect->SetMatrix(m_shaderViewMatrix, &worldViewProjection));	
	HR(m_effect->SetMatrix(m_shaderWorldInverseTransposeMatrix, &WIT));												
	HR(m_effect->SetValue(m_shaderEyePosition, cameraPosition, sizeof(D3DXVECTOR3)));
}

void FXManager::AddEffect(FX * effect)
{
	int totalEffecs = m_effects->size();

	for(int i = 0; i < totalEffecs; i++)
	{
		FX *t_effect = m_effects->at(i);
		if(t_effect == effect)
		{			
			return;
		}
	}

	m_effects->push_back(effect);
}

void FXManager::SetSceneEffects(Scene *scene)
{
	int totalMeshes = scene->GetMeshesVector()->size();

	vector<Mesh *> *t_meshes = scene->GetMeshesVector();

	for(int i = 0; i < totalMeshes; i++)
	{
		D3DMesh *t_mesh = static_cast<D3DMesh *>(t_meshes->at(i));
		//AddEffect(t_mesh->GetEffect());
	}

#if 1
	m_effect = ShaderManager::GetInstance()->GetEffectById(SHADER_LIGHTS_PER_VERTEX_TEXTURES_ID);
	m_hTex = m_effect->GetParameterByName(0, "gTex");

	m_shaderTechnique = m_effect->GetTechniqueByName("LightsTech");	
	m_shaderViewMatrix  = m_effect->GetParameterByName(0, "gWVP");	
	m_shaderEyePosition= m_effect->GetParameterByName(0, "gEyePosW");
	m_shaderAmbientLightMaterial = m_effect->GetParameterByName(0, "gAmbientLight");
	m_shaderDiffuseLightMaterial = m_effect->GetParameterByName(0, "gDiffuseLight");
	m_shaderSpecularLightMaterial = m_effect->GetParameterByName(0, "gSpecularLight");
	
	m_shaderLightPosition = m_effect->GetParameterByName(0, "gLightVecW");
	
	
	m_shaderObjectAmbientMaterial = m_effect->GetParameterByName(0, "gAmbientMtrl");
	m_shaderObjectDiffuseMaterial = m_effect->GetParameterByName(0, "gDiffuseMtrl");
	m_shaderObjectSpecularMaterial = m_effect->GetParameterByName(0, "gSpecularMtrl");
	m_shaderSpecularLightPower = m_effect->GetParameterByName(0, "gSpecularPower");

	m_shaderWorldMatrix = m_effect->GetParameterByName(0, "gWorld");
	m_shaderWorldInverseTransposeMatrix = m_effect->GetParameterByName(0, "gWorldInvTrans");
	

	


	t_ambientLight = new AmbientLight();
	t_ambientLight->SetColor(0.4f*D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	t_diffuseLight = new DiffuseLight();
	t_diffuseLight->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	t_specularLight = new SpecularLight();
	t_specularLight->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	t_lightAttenuation = new D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	t_pointLight = new PointLight(16.0f);

	m_material = new Material(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), 16.0f);


	t_ambientLight = new AmbientLight();
	t_ambientLight->SetColor(0.4f*D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	t_diffuseLight = new DiffuseLight();
	t_diffuseLight->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	t_specularLight = new SpecularLight();
	t_specularLight->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	t_lightAttenuation = new D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	t_pointLight = new PointLight(16.0f);

	m_material = new Material(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), 16.0f);


	D3DXVECTOR3 lightDir = D3DXVECTOR3(-0.8f,-0.4f,0.3f);
	D3DXVECTOR3 lightPos = D3DXVECTOR3(0.0f,0.0f,-1.0f);

	HR(m_effect->SetValue(m_shaderLightPosition, &lightPos, sizeof(D3DXVECTOR3)));	
	
	HR(m_effect->SetValue(m_shaderAmbientLightMaterial, &t_ambientLight->GetColor(), sizeof(D3DXCOLOR)));
	HR(m_effect->SetValue(m_shaderDiffuseLightMaterial, &t_diffuseLight->GetColor(), sizeof(D3DXCOLOR)));		
	HR(m_effect->SetValue(m_shaderSpecularLightMaterial, &t_specularLight->GetColor(), sizeof(D3DXCOLOR)));
#endif
}



FXManager::~FXManager()
{

}