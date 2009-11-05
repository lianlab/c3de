#include "VideoMesh.h"
#include "PerVertexLighting.h"
#include "D3DRenderer.h"
#include "DebugMemory.h"

VideoMesh::VideoMesh(VideoStructure *a_video):D3DMesh()
{
	m_video = a_video;
	
	m_currentFrameTexture = NULL;
	m_currentFrame = 0;
	m_effect = ShaderManager::GetInstance()->GetFXByID(SHADER_LIGHTS_PER_VERTEX_TEXTURES_NO_FOG_ID);


	Material *t_material = new Material(	D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),
										D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f), 16.0f);
	AddMaterial(t_material);
	D3DImage * d3dImage = new D3DImage(ResourceManager::GetInstance()->GetTextureByID(IMAGE_CRATE_ID));	
	AddTexture((Image *) d3dImage);
}

VideoMesh::~VideoMesh()
{
	FreeMaterials();
	FreeTextures();
	
}

void VideoMesh::Update(int deltaTime)
{
	m_currentFrame += deltaTime;
	m_currentFrame = m_currentFrame%m_video->m_totalTime;

	float t_msecs = (float)m_currentFrame;

	IDirect3DTexture9 * t_texture;
	
	AVIFileInit();	

	
	PAVISTREAM *t_stream = m_video->m_stream;
	PGETFRAME * t_frame = m_video->m_frames;

	long frame = AVIStreamTimeToSample(*t_stream, t_msecs);

	BITMAPINFOHEADER *bip = NULL;
	bip = (BITMAPINFOHEADER*)AVIStreamGetFrame(*t_frame, frame);
	
	

	IDirect3DTexture9 * newFrame = NULL;
	int size = bip->biSize + bip->biWidth * bip->biHeight * bip->biBitCount / 8;

	if(m_currentFrameTexture != NULL)
	{
		m_currentFrameTexture->Release();		
	}

	IDirect3DDevice9 * t_device = D3DRenderer::GetDevice();
	D3DXCreateTextureFromFileInMemoryEx(t_device, bip, size, bip->biWidth, bip->biHeight, 1, D3DUSAGE_DYNAMIC, D3DFMT_R8G8B8, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &newFrame);
	
	m_currentFrameTexture = newFrame;

	AVIFileExit();

	

	
}

void VideoMesh::SetShaderHandlers()
{
	

	PerVertexLighting *t_effect = (PerVertexLighting *) m_effect;
	
	t_effect->SetObjectMaterials(	m_currentMaterial->GetAmbient(), m_currentMaterial->GetDiffuse(),
									m_currentMaterial->GetSpecular(), m_currentMaterial->GetSpecularPower());

									
	
	D3DImage *t_d3dText = (D3DImage *) m_currentTexture;
	
	if(m_currentFrameTexture)
	{
		t_effect->SetObjectTexture(m_currentFrameTexture);
	}
	else
	{
		t_effect->SetObjectTexture(t_d3dText->GetTexture());
	}

	t_effect->SetTransformMatrix(GetTransformMatrix());
	t_effect->SetAlpha(m_alpha);
	
}