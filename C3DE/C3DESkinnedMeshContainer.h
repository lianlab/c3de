#if 1
#ifndef C3DE_SKINNED_MESH_CONTAINER_H
#define C3DE_SKINNED_MESH_CONTAINER_H

#include "C3DESkinnedMesh.h"

class C3DESkinnedMeshContainer : public D3DMesh
{
public:
	C3DESkinnedMeshContainer(C3DESkinnedMesh * a_mesh);
	virtual ~C3DESkinnedMeshContainer();

	void SetCurrentAnimation(int animationIdx);

	int GetTotalAnimationTime();

	void SetAnimationTime(int time);

	void SetShaderHandlers();		

	void Update(int deltaTime);

	int GetCurrentAnimation();

protected:

	

	D3DXMATRIX *m_poseMatrix;

	

	int m_currentAnimation;
	int m_currentAnimationStartFrame;
	int m_currentAnimationTotalTime;

	C3DESkinnedMesh *m_mesh;

	int m_elapsedTime;
};

#endif

#endif