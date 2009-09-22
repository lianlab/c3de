#ifndef C3DE_SKINNED_MESH_H
#define C3DE_SKINNED_MESH_H

#include "D3DMesh.h"



class C3DESkinnedMesh : public D3DMesh
{
public:
	C3DESkinnedMesh(char * a_meshBuffer, char *a_bonesBuffer, Image *a_texture, int frameDuration);
	C3DESkinnedMesh(char *a_meshBuffer, vector<char *> *a_bonesBuffer, Image *a_texture, int frameDuration);
	~C3DESkinnedMesh();	
	
	void SetShaderHandlers();	

	D3DXMATRIX * GetMatrices();
	int GetTotalBones();
	int GetTotalFrames();

	vector<int> * GetAnimationFramesDuration();
	vector<int> * GetAnimationTotalFrames();	


	vector<D3DXMATRIX *> *GetPoseMatrices();

protected:	

	D3DXMATRIX *m_roots;	

	int m_totalBones;

	int m_totalFrames;		

	vector<int> *m_animationFramesDuration;
	vector<int> *m_animationsTotalFrames;

	D3DXMATRIX *m_currentFrameToRoots; //disposable

	D3DXVECTOR3 *m_bonesBegin; //disposable
	D3DXVECTOR3 *m_bonesEnd; //disposable

	vector<D3DXMATRIX *> * m_poseMatrices;
	
	
	
	
};
#endif

