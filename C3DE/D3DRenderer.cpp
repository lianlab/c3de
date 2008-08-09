#include "D3DRenderer.h"
#include "Debug.h"
#include "D3DSprite.h"
#include "DebugMemory.h"
#include "ResourceManager.h"

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

void D3DRenderer::DrawSprite(C3DESprite *sprite, int x, int y)
{
	D3DSprite * d3dSprite = static_cast<D3DSprite *> (sprite);
	Image * image = sprite->GetImage();
	D3DImage *tex = static_cast<D3DImage *>(image);

	D3DXMATRIX texScaling;
	D3DXMatrixScaling(&texScaling, 10.0f, 10.0f, 0.0f);
	m_device->SetTransform(D3DTS_TEXTURE0, &texScaling);

	D3DXMATRIX T, S;
	D3DXMatrixTranslation(&T, 0, 0, 0);
	D3DXMatrixScaling(&S, 20.0f, 20.0f, 0.0f);

	m_sprite->SetTransform(&(S*T));

	IDirect3DTexture9 * t = tex->GetTexture();
	//m_sprite->Draw(t, 0, 0, 0, D3DCOLOR_XRGB(255,255,255));

	m_sprite->Flush();
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
	
	m_d3dpp.BackBufferWidth            = wnd->getWidth();
	m_d3dpp.BackBufferHeight           = wnd->getHeight();
	m_d3dpp.BackBufferFormat           = D3DFMT_A8R8G8B8;
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
	HR(m_device->SetRenderState(D3DRS_ALPHAREF, 10));
	HR(m_device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER));

	HR(m_device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE));
	HR(m_device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1));
	HR(m_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA));
	HR(m_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA));
	HR(m_device->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2));

	HR(D3DXCreateTextureFromFile(m_device, "Images/bkgd1.bmp", &dummy));

	ResourceManager::GetInstance()->SetDevice(m_device);
	return true;
}

void D3DRenderer::Reset()
{

}

void D3DRenderer::Clear()
{	
	m_device->Clear( 0L, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0L );
}

bool D3DRenderer::BeginRender()
{
	m_device->BeginScene();
	m_sprite->Begin(D3DXSPRITE_OBJECTSPACE | D3DXSPRITE_DONOTMODIFY_RENDERSTATE);

	D3DXMATRIX texScaling;
	D3DXMatrixScaling(&texScaling, 10.0f, 10.0f, 0.0f);
	HR(m_device->SetTransform(D3DTS_TEXTURE0, &texScaling));

	D3DXMATRIX T, S;
	D3DXMatrixTranslation(&T, 0, 0, 0);
	D3DXMatrixScaling(&S, 20.0f, 20.0f, 0.0f);
	HR(m_sprite->SetTransform(&(S*T)));

	IDirect3DTexture9 * dum = ResourceManager::GetInstance()->GetImageByID(2);
	
	HR(m_sprite->Draw(dum, 0,0,0, D3DCOLOR_XRGB(255,255,255)));
	return true;
}

void D3DRenderer::EndRender()
{
	m_sprite->End();
	m_device->EndScene();
	m_device->Present(0, 0, 0, 0);
}