#ifndef C3DE_SKINNED_MESH_H
#define C3DE_SKINNED_MESH_H

#include "D3DMesh.h"



class C3DESkinnedMesh : public D3DMesh
{
public:
	C3DESkinnedMesh();
	~C3DESkinnedMesh();	
	void SetShaderHandlers();

	void SetSelectedBoneIndex(int index);
	int GetSelectedBoneIndex();

	void SetOffset(float offset);
	float GetOffset();

	int GetTotalBones();

	D3DXVECTOR3 * GetBonesBegins();
	D3DXVECTOR3 * GetBonesEnd();

	void Update(int deltaTime);

	IDirect3DVertexBuffer9 * GetBonesVertexBuffer();

	void SetCurrentAnimation(int animationIdx);

protected:

	float m_offset;
	IDirect3DVertexBuffer9 * m_bonesVertexBuffer;
	int m_selectedBoneIndex;
	
	//D//3DXHANDLE  m_hTex;
	//D3DXHANDLE	m_shaderAlpha;//galpha

	//D3DXMATRIX m_matrices[2];

	D3DXMATRIX *m_roots;
	D3DXMATRIX *m_currentFrameToRoots;

	

	vector<D3DXMATRIX *> * m_poseMatrices;

	D3DXVECTOR3 *m_bonesBegin;
	D3DXVECTOR3 *m_bonesEnd;

	int m_totalBones;

	int m_totalFrames;

	int m_elapsedTime;
	

	vector<int> *m_animationFramesDuration;
	vector<int> *m_animationsTotalFrames;
	int m_currentAnimation;
	int m_currentAnimationStartFrame;
	int m_currentAnimationTotalTime;
	D3DXMATRIX *m_poseMatrix;
	
	
};
#endif

