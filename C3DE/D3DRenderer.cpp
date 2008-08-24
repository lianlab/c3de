#include "D3DRenderer.h"
#include "Debug.h"
#include "D3DSprite.h"
//#include "DebugMemory.h"
#include "ResourceManager.h"

// For Demo
IDirect3DVertexDeclaration9* VertexPos::Decl = 0;

D3DRenderer::D3DRenderer()
{
	m_windowed = true;
	m_font = NULL;
}

D3DRenderer::~D3DRenderer()
{
	if(m_font)
	{
		ReleaseCOM(m_font);
	}

	ReleaseCOM(m_vb);
	ReleaseCOM(m_ib);

	DestroyAllVertexDeclarations();


}

void D3DRenderer::BuildProjMtx()
{

	float w = (float)m_d3dpp.BackBufferWidth;
	float h = (float)m_d3dpp.BackBufferHeight;
	D3DXMatrixPerspectiveFovLH(&m_proj, D3DX_PI * 0.25f, w/h, 1.0f, 5000.0f);

}

void D3DRenderer::SetScreenMode(int newScreenMode)
{

	if(newScreenMode == m_currentScreenMode)
	{
		return;
	}

	m_currentScreenMode = newScreenMode;

	if(m_currentScreenMode == SCREEN_MODE_FULL)
	{
		int width = GetSystemMetrics(SM_CXSCREEN);
		int height = GetSystemMetrics(SM_CYSCREEN);

		m_d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
		m_d3dpp.BackBufferWidth = width;
		m_d3dpp.BackBufferHeight = height;
		m_d3dpp.Windowed = false;

		SetWindowLongPtr(m_mainWindow, GWL_STYLE, WS_POPUP);

		SetWindowPos(m_mainWindow, HWND_TOP, 0, 0, width, height, SWP_NOZORDER | SWP_SHOWWINDOW);
	}
	else
	{
		RECT rt = {0,0,800,600};
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
		m_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
		m_d3dpp.BackBufferWidth = 800;
		m_d3dpp.BackBufferHeight = 600;
		m_d3dpp.Windowed = true;

		SetWindowLongPtr(m_mainWindow, GWL_STYLE, WS_OVERLAPPEDWINDOW);

		SetWindowPos(m_mainWindow, HWND_TOP, 100, 100, rt.right, rt.bottom, SWP_NOZORDER | SWP_SHOWWINDOW);
	}

	RendererListener *listener;

	UINT i;
	for(i = 0; i < m_listeners->size(); i++)
	{
		listener = m_listeners->at(i);
		listener->OnLostDevice();		
	}

	HR(m_device->Reset(&m_d3dpp));

	for(i = 0; i < m_listeners->size(); i++)
	{
		listener = m_listeners->at(i);
		listener->OnResetDevice();
	}


}

void D3DRenderer::DrawMesh(Mesh *mes)
{
	HR(m_device->SetStreamSource(0, m_vb, 0, sizeof(VertexPos)));
	HR(m_device->SetIndices(m_ib));
	HR(m_device->SetVertexDeclaration(VertexPos::Decl));

	D3DXMATRIX W;
	D3DXMatrixIdentity(&W);
	HR(m_device->SetTransform(D3DTS_WORLD, &W));
	D3DCamera *cam = (D3DCamera *) m_camera;
	HR(m_device->SetTransform(D3DTS_VIEW, &cam->GetMatrix()));
	HR(m_device->SetTransform(D3DTS_PROJECTION, &m_proj));
	HR(m_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME));
	HR(m_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12));	

}

#if 0
void D3DRenderer::BuildViewMtx()
{

	float x = m_cameraRadius * cosf(m_cameraRotationY);
	float z = m_cameraRadius * sinf(m_cameraRotationY);
	D3DXVECTOR3 pos(x, m_cameraHeight, z);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&m_view, &pos, &target, &up);

}
#endif



void D3DRenderer::InitAllVertexDeclarations()
{
	

	D3DVERTEXELEMENT9 VertexPosElements[] =
	{
		{0,0,D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		D3DDECL_END()
	};
	HR(m_device->CreateVertexDeclaration(VertexPosElements, &VertexPos::Decl));
	

}

void D3DRenderer::DrawSprite(Sprite *sprite)
{	
	m_sprite->Begin(0);

	D3DSprite * d3dSprite = static_cast<D3DSprite *> (sprite);
	Image * image = sprite->GetImage();
	D3DImage *tex = static_cast<D3DImage *>(image);	

	m_sprite->SetTransform(&d3dSprite->GetTransformationMatrix());

	IDirect3DTexture9 * t = tex->GetTexture();
	int colIndex = d3dSprite->GetCurrentFrame() % d3dSprite->GetNumColumns();
	int rowIndex = d3dSprite->GetCurrentFrame() / d3dSprite->GetNumColumns();
	int frameWidth = d3dSprite->GetFrameWidth();
	int frameHeight = d3dSprite->GetFrameHeight();

	
	RECT src;
	src.left = colIndex * frameWidth;
	src.right = (colIndex * frameWidth) + frameWidth;
	src.top = rowIndex * frameHeight;
	src.bottom = (rowIndex * frameHeight) + frameHeight;
	m_sprite->Draw(t, &src, 0, 0, D3DCOLOR_XRGB(255,255,255));

	m_sprite->Flush();	

	m_sprite->End();

}

bool D3DRenderer::IsDeviceLost()
{
	HRESULT hr = m_device->TestCooperativeLevel();

	if(hr == D3DERR_DEVICELOST)
	{
		Sleep(20);
		return true;
	}
	else if(hr == D3DERR_DRIVERINTERNALERROR)
	{
		PostQuitMessage(0);
		return true;
	}
	else if(hr == D3DERR_DEVICENOTRESET)
	{
		RendererListener *listener;

		UINT i;
		for(i = 0; i < m_listeners->size(); i++)
		{
			listener = m_listeners->at(i);
			listener->OnLostDevice();		
		}

		m_device->Reset(&m_d3dpp);
		for(i = 0; i < m_listeners->size(); i++)
		{
			listener = m_listeners->at(i);
			listener->OnResetDevice();
		}

		return false;
	}
	else
	{
		return false;
	}

}

void D3DRenderer::RenderText(char *text)
{

	if(!m_font)
	{
		//Load Application Specific resources here...
		D3DXCreateFont(m_device, 18, 0, 0, 1, false,  
				   DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY,
				   DEFAULT_PITCH | FF_DONTCARE, "Arial", &m_font);

	}

	RECT r[] = {{10, 10, 0,0}, {10, 30, 0,0}, {10, 50, 0,0}, {10, 70, 0,0}, {10, 90, 0,0}};
	m_font->DrawText(NULL, text, -1, &r[0], DT_LEFT | DT_TOP | DT_NOCLIP, 0xff000000);

}

bool D3DRenderer::Init(WindowsApplicationWindow *window)
{

	WindowsApplicationWindow *wnd = window;
	m_hInstance = wnd->getHInstance();
	m_mainWindow = wnd->getHandle();

	//Create IDirect3D9 Interface
	IDirect3D9* d3d9 = Direct3DCreate9(D3D_SDK_VERSION);

    if(d3d9 == NULL)
	{
		Debug::GetInstance()->Print("Direct3DCreate9() - FAILED");
		return false;
	}

	//Check that the Device supports what we need from it
	D3DCAPS9 caps;
	d3d9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);

	//Hardware Vertex Processing or not?
	int vp = 0;
	if(caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	//Check vertex & pixelshader versions
	if(caps.VertexShaderVersion < D3DVS_VERSION(2, 0) || caps.PixelShaderVersion < D3DPS_VERSION(2, 0))
	{
		Debug::GetInstance()->Print("Warning - Your graphic card does not support vertex and pixelshaders version 2.0");
	}

	//Set D3DPRESENT_PARAMETERS
	
	m_d3dpp.BackBufferWidth            = 0;
	m_d3dpp.BackBufferHeight           = 0;
	m_d3dpp.BackBufferFormat           = D3DFMT_UNKNOWN;
	m_d3dpp.BackBufferCount            = 1;
	m_d3dpp.MultiSampleType            = D3DMULTISAMPLE_NONE;
	m_d3dpp.MultiSampleQuality         = 0;
	m_d3dpp.SwapEffect                 = D3DSWAPEFFECT_DISCARD; 
	m_d3dpp.hDeviceWindow              = m_mainWindow;
	m_d3dpp.Windowed                   = m_windowed;
	m_d3dpp.EnableAutoDepthStencil     = true; 
	m_d3dpp.AutoDepthStencilFormat     = D3DFMT_D24S8;
	m_d3dpp.Flags                      = 0;
	m_d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	m_d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;

	//Create the IDirect3DDevice9
	if(FAILED(d3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_mainWindow,
								 vp, &m_d3dpp, &m_device)))
	{
		Debug::GetInstance()->Print("Failed to create IDirect3DDevice9");
		return false;
	}

	//Release IDirect3D9 interface
	d3d9->Release();

	HR(D3DXCreateSprite(m_device, &m_sprite));

	delete window;

	//2D stuff
	
	D3DXMATRIX V;
	D3DXVECTOR3 pos(0.0f, 0.0f, -1000.0f);
	D3DXVECTOR3 up (0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXMatrixLookAtLH(&V, &pos, &target, &up);
	HR(m_device->SetTransform(D3DTS_VIEW, &V));

	D3DXMATRIX P;
	RECT R;
	GetClientRect(m_mainWindow, &R);
	float width = (float)R.right;
	float height = (float)R.bottom;
	D3DXMatrixPerspectiveFovLH(&P, D3DX_PI * 0.25f, width/height, 1.0f, 5000.0f);
	HR(m_device->SetTransform(D3DTS_PROJECTION, &P));

	HR(m_device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR));
	HR(m_device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR));
	HR(m_device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR));

	HR(m_device->SetRenderState(D3DRS_LIGHTING, false));
	HR(m_device->SetRenderState(D3DRS_ALPHATESTENABLE, true));
	HR(m_device->SetRenderState(D3DRS_ALPHAREF, 10));
	HR(m_device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER));

	HR(m_device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE));
	HR(m_device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1));
	HR(m_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA));
	HR(m_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA));
	HR(m_device->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2));					














	D3DCamera *cam = new D3DCamera();
	m_camera = (Camera *)cam;	
	m_camera->SetPosition(0.0f, 0.0f, 0.0f);
	m_camera->SetTarget(0.0f, 0.0f, 0.0f);

#if 0
	m_cameraRadius = 10.0f;
	m_cameraRotationY = 1.2 * D3DX_PI;
	m_cameraHeight = 5.0f;

#endif
	BuildVertexBuffer();
	BuildIndexBuffer();
	
	BuildProjMtx();

	InitAllVertexDeclarations();	

	//BuildViewMtx();

	return true;
}

void D3DRenderer::Reset()
{

}

void D3DRenderer::BuildVertexBuffer()
{

	HR(m_device->CreateVertexBuffer(8 * sizeof(VertexPos), D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED, &m_vb, 0));
	VertexPos *v = 0;
	HR(m_vb->Lock(0,0,(void**)&v,0));

	v[0] = VertexPos(-1.0f, -1.0f, -1.0f);
	v[1] = VertexPos(-1.0f,  1.0f, -1.0f);
	v[2] = VertexPos( 1.0f,  1.0f, -1.0f);
	v[3] = VertexPos( 1.0f, -1.0f, -1.0f);
	v[4] = VertexPos(-1.0f, -1.0f,  1.0f);
	v[5] = VertexPos(-1.0f,  1.0f,  1.0f);
	v[6] = VertexPos( 1.0f,  1.0f,  1.0f);
	v[7] = VertexPos( 1.0f, -1.0f,  1.0f);
	HR(m_vb->Unlock());

}

void D3DRenderer::BuildIndexBuffer()
{

	HR(m_device->CreateIndexBuffer(36 * sizeof(WORD), D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_ib, 0));
	WORD *k = 0;

	HR(m_ib->Lock(0,0,(void**)&k, 0));

	//front face
	k[0] = 0; k[1] = 1; k[2] = 2;	
	k[3] = 0; k[4] = 2; k[5] = 3;
	
	//back face
	k[6] = 4; k[7] = 6; k[8] = 5;
	k[9] = 4; k[10] = 7; k[11] = 6;

	//left face
	k[12] = 4; k[13] = 5; k[14] = 1;
	k[15] = 4; k[16] = 1; k[17] = 0;

	//right face
	k[18] = 3; k[19] = 2; k[20] = 6;
	k[21] = 3; k[22] = 6; k[23] = 7;

	//top face
	k[24] = 1; k[25] = 5; k[26] = 6;
	k[27] = 1; k[28] = 6; k[29] = 2;

	//bottom face
	k[30] = 4; k[31] = 0; k[32] = 3;
	k[33] = 4; k[34] = 3; k[35] = 7;

}


void D3DRenderer::DestroyAllVertexDeclarations()
{
	ReleaseCOM(VertexPos::Decl);
}

void D3DRenderer::Clear()
{	
	m_device->Clear( 0L, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffff43ff, 1.0f, 0L );
}

bool D3DRenderer::BeginRender()
{

	m_device->BeginScene();	
	//m_sprite->Begin(0);
	return true;
}

void D3DRenderer::EndRender()
{
	//m_sprite->End();
	m_device->EndScene();
	m_device->Present(0, 0, 0, 0);
}

