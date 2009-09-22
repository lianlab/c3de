#if 1
#include "C3DESkinnedMeshContainer.h"
#include "C3DESkinnedMeshFX.h"

C3DESkinnedMeshContainer::C3DESkinnedMeshContainer(C3DESkinnedMesh *a_mesh)
{
	m_mesh = a_mesh;
	SetCurrentAnimation(0);

	m_xMesh = a_mesh->GetXMesh();

	m_effect = a_mesh->GetEffect();

	m_materials = a_mesh->GetMaterials();

	m_textures = a_mesh->GetTextures();

	m_boundingBox = a_mesh->GetBoundingBox();

	m_poseMatrix = NULL;

	m_elapsedTime = 0;
}

C3DESkinnedMeshContainer::~C3DESkinnedMeshContainer()
{
	
}

void C3DESkinnedMeshContainer::SetShaderHandlers()
{
	C3DESkinnedMeshFX *t_effect = (C3DESkinnedMeshFX *) m_effect;
	
	t_effect->SetObjectMaterials(	m_currentMaterial->GetAmbient(), m_currentMaterial->GetDiffuse(),
									m_currentMaterial->GetSpecular(), m_currentMaterial->GetSpecularPower());

	D3DImage *t_d3dText = (D3DImage *) m_currentTexture;
	t_effect->SetObjectTexture(t_d3dText->GetTexture());

	t_effect->SetTransformMatrix(GetTransformMatrix());


	t_effect->SetFrameRootMatrices(m_poseMatrix, m_mesh->GetTotalBones());
}

int C3DESkinnedMeshContainer::GetCurrentAnimation()
{
	return m_currentAnimation;
}

void C3DESkinnedMeshContainer::SetCurrentAnimation(int animationIdx)
{	
	
	m_currentAnimation = animationIdx;
	m_currentAnimationStartFrame = 0;
	
	
	int totalAnimations = m_mesh->GetAnimationTotalFrames()->size();

	for(int i = 0; i < totalAnimations; i++)
	{
		if(animationIdx - 1 < i)
		{
			break;
		}
		else
		{
			
			m_currentAnimationStartFrame += (*m_mesh->GetAnimationTotalFrames())[i];
		}
		
	}


	m_currentAnimationTotalTime = 0;
	int animationLastFrame = m_currentAnimationStartFrame + (*m_mesh->GetAnimationTotalFrames())[animationIdx];

	for(int i = m_currentAnimationStartFrame; i < animationLastFrame; i++)
	{
		
		m_currentAnimationTotalTime += (*m_mesh->GetAnimationFramesDuration())[i];
	}
}


int C3DESkinnedMeshContainer::GetTotalAnimationTime()
{
	return m_currentAnimationTotalTime;
}

void C3DESkinnedMeshContainer::SetAnimationTime(int time)
{
	m_elapsedTime = 0;
	Update(time);
}

void C3DESkinnedMeshContainer::Update(int deltaTime)
{
	//deltaTime *= 3;
	//deltaTime = 0;
	
	m_elapsedTime += deltaTime;

	m_elapsedTime = m_elapsedTime % m_currentAnimationTotalTime;
	
	int t_totalAnimationFrames = (*m_mesh->GetAnimationTotalFrames())[m_currentAnimation];

	int animationLastFrame = m_currentAnimationStartFrame + t_totalAnimationFrames;

	
	int t_time = (*m_mesh->GetAnimationFramesDuration())[m_currentAnimationStartFrame];
	int t_currentFrame = 0;

	
	
	for(int i = m_currentAnimationStartFrame; i < animationLastFrame; i++)
	{
		if(m_elapsedTime >  t_time - 1)
		{
			t_time += (*m_mesh->GetAnimationFramesDuration())[i];
		}
		else
		{
			t_currentFrame = i;
			break;
		}

	}

	

	//int nextFrame = t_currentFrame + 1;
	int nextFrame = m_currentAnimationStartFrame + ((t_currentFrame + 1) - m_currentAnimationStartFrame) % (*m_mesh->GetAnimationTotalFrames())[m_currentAnimation];

	

	

	int t_frameTimesAccumulated = 0;
	for (int i = m_currentAnimationStartFrame; i < t_currentFrame; i++)
	{
		t_frameTimesAccumulated += (*m_mesh->GetAnimationFramesDuration())[i];
	}

	int remainingTime = m_elapsedTime - t_frameTimesAccumulated;

	float frameTimeRatio = (float)remainingTime / (float)(*m_mesh->GetAnimationFramesDuration())[t_currentFrame];


	D3DXMATRIX *t_currentFrameMatrices = (*m_mesh->GetPoseMatrices())[t_currentFrame];
	D3DXMATRIX *t_nextFrameMatrices = (*m_mesh->GetPoseMatrices())[nextFrame];
	
	if(m_poseMatrix != NULL)
	{
		free(m_poseMatrix);
		m_poseMatrix = NULL;
	}

	
	int totalBones = m_mesh->GetTotalBones();
	m_poseMatrix = (D3DXMATRIX*)malloc(sizeof(D3DXMATRIX) * totalBones);

	for(int i = 0 ; i < totalBones; i++)
	{

		
		D3DXMATRIX t_matrix;		
		t_matrix._11 = t_currentFrameMatrices[i]._11 + ((t_nextFrameMatrices[i]._11 - t_currentFrameMatrices[i]._11) * frameTimeRatio);
		t_matrix._12 = t_currentFrameMatrices[i]._12 + ((t_nextFrameMatrices[i]._12 - t_currentFrameMatrices[i]._12) * frameTimeRatio);
		t_matrix._13 = t_currentFrameMatrices[i]._13 + ((t_nextFrameMatrices[i]._13 - t_currentFrameMatrices[i]._13) * frameTimeRatio);
		t_matrix._14 = t_currentFrameMatrices[i]._14 + ((t_nextFrameMatrices[i]._14 - t_currentFrameMatrices[i]._14) * frameTimeRatio);
		t_matrix._21 = t_currentFrameMatrices[i]._21 + ((t_nextFrameMatrices[i]._21 - t_currentFrameMatrices[i]._21) * frameTimeRatio);
		t_matrix._22 = t_currentFrameMatrices[i]._22 + ((t_nextFrameMatrices[i]._22 - t_currentFrameMatrices[i]._22) * frameTimeRatio);
		t_matrix._23 = t_currentFrameMatrices[i]._23 + ((t_nextFrameMatrices[i]._23 - t_currentFrameMatrices[i]._23) * frameTimeRatio);
		t_matrix._24 = t_currentFrameMatrices[i]._24 + ((t_nextFrameMatrices[i]._24 - t_currentFrameMatrices[i]._24) * frameTimeRatio);
		t_matrix._31 = t_currentFrameMatrices[i]._31 + ((t_nextFrameMatrices[i]._31 - t_currentFrameMatrices[i]._31) * frameTimeRatio);
		t_matrix._32 = t_currentFrameMatrices[i]._32 + ((t_nextFrameMatrices[i]._32 - t_currentFrameMatrices[i]._32) * frameTimeRatio);
		t_matrix._33 = t_currentFrameMatrices[i]._33 + ((t_nextFrameMatrices[i]._33 - t_currentFrameMatrices[i]._33) * frameTimeRatio);
		t_matrix._34 = t_currentFrameMatrices[i]._34 + ((t_nextFrameMatrices[i]._34 - t_currentFrameMatrices[i]._34) * frameTimeRatio);
		t_matrix._41 = t_currentFrameMatrices[i]._41 + ((t_nextFrameMatrices[i]._41 - t_currentFrameMatrices[i]._41) * frameTimeRatio);
		t_matrix._42 = t_currentFrameMatrices[i]._42 + ((t_nextFrameMatrices[i]._42 - t_currentFrameMatrices[i]._42) * frameTimeRatio);
		t_matrix._43 = t_currentFrameMatrices[i]._43 + ((t_nextFrameMatrices[i]._43 - t_currentFrameMatrices[i]._43) * frameTimeRatio);
		t_matrix._44 = t_currentFrameMatrices[i]._44 + ((t_nextFrameMatrices[i]._44 - t_currentFrameMatrices[i]._44) * frameTimeRatio);

		m_poseMatrix[i] = t_matrix;
	}
	

	
}
#endif