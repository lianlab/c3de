#ifndef VIDEO_MESH_H
#define VIDEO_MESH_H

#include "D3DMesh.h"
#include "ResourceManager.h"
#include <vfw.h>

class VideoMesh : public D3DMesh
{
public:	
	VideoMesh(VideoStructure *a_video);
	~VideoMesh();
	void Update(int deltaTime);

	void SetShaderHandlers();



protected:
	VideoStructure *m_video;
	
	long m_currentFrame;

	IDirect3DTexture9 *m_currentFrameTexture;

	D3DXHANDLE  m_hTex;
	D3DXHANDLE	m_shaderAlpha;//galpha

	//PGETFRAME * m_video;
};
#endif