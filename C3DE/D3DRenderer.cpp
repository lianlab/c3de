#include "D3DRenderer.h"
#include "Debug.h"
#include "D3DSprite.h"
#include "ResourceManager.h"
#include "D3DMesh.h"
#include "D3DMirror.h"
#include "FXManager.h"
#include "DebugMemory.h"

D3DRenderer::D3DRenderer()
{	
	m_font = NULL;
}

D3DRenderer::~D3DRenderer()
{
	if(m_font)
	{
		ReleaseCOM(m_font);
	}

	if(m_camera)
	{
		delete m_camera;
		m_camera = NULL;
	}
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

/*
void D3DRenderer::SetMeshLights(Scene * scene, Mesh *mesh)
{
	D3DScene *t_scene = static_cast<D3DScene *> (scene);
	D3DMesh *d3dmesh = static_cast<D3DMesh *> (mesh);
	D3DCamera *cam = (D3DCamera *) m_camera;
	D3DXVECTOR3 lightDir = cam->GetTarget() - cam->GetPosition();
	D3DXVec3Normalize(&lightDir, &lightDir);

	d3dmesh->SetLightParameters(t_scene->GetAmbientLight()->GetColor(), t_scene->GetDiffuseLight()->GetColor(),
								t_scene->GetSpecularLight()->GetColor(), cam->GetPosition(), lightDir, 
								*t_scene->GetLightAttenuation(), t_scene->GetPointLight()->GetPower());
}
void D3DRenderer::SetMeshWorldHandlers(Scene *scene, Mesh *mesh)
{
	D3DScene *t_scene = static_cast<D3DScene *> (scene);
	D3DMesh *d3dmesh = static_cast<D3DMesh *> (mesh);
	D3DXMATRIX W;		
	D3DXMatrixIdentity(&W);			

	D3DCamera *cam = (D3DCamera *) m_camera;
	D3DXMATRIX t_view = cam->GetMatrix();
	D3DXMATRIX t_projView = t_view*m_proj;	

	D3DXMATRIX WIT;
	D3DXMatrixInverse(&WIT, 0, &W);
	D3DXMatrixTranspose(&WIT, &WIT);														
	
	d3dmesh->SetWorldParameters(W, t_projView,WIT,cam->GetPosition());
}

*/

void D3DRenderer::DrawScene(Scene *scene)
{
	
#if 1
	int totalMeshes = scene->GetMeshesVector()->size();	
	int totalMirrors = scene->GetMirrorsVector()->size();	

	D3DScene *t_scene = static_cast<D3DScene *> (scene);						

	D3DCamera *cam = (D3DCamera *) m_camera;
	D3DXMATRIX t_view = cam->GetMatrix();

	
	D3DXMATRIX t_projView = t_view*m_proj;	


	
	
	//hackTheKasbah();
	//group1();
	FXManager::GetInstance()->SetUpdateHandlers(cam->GetPosition(), t_projView);

	UINT num = 0;
	//m_effect->Begin(&num,0);
	

	for(int i = 0; i < totalMeshes; i++)
	{
		
		Mesh *mesh = scene->GetMeshesVector()->at(i);	
		D3DMesh *d3dmesh = (D3DMesh *)mesh;	

		FXManager::GetInstance()->Begin(d3dmesh->GetEffect());

		
		d3dmesh->SetShaderHandlers();
		//group3();

		FXManager::GetInstance()->PreRender();
		//m_effect->CommitChanges();

		
		//m_effect->BeginPass(0);
		DrawMesh(mesh);
		//m_effect->EndPass();
		FXManager::GetInstance()->PosRender();
		FXManager::GetInstance()->End();
	}

	//m_effect->End();
	

	
#endif
#if 0
	int totalMeshes = scene->GetMeshesVector()->size();	
	int totalMirrors = scene->GetMirrorsVector()->size();	

	D3DScene *t_scene = static_cast<D3DScene *> (scene);						

	

	for(int i = 0; i < totalMeshes; i++)
	{
		Mesh *mesh = scene->GetMeshesVector()->at(i);	
		D3DMesh *d3dmesh = (D3DMesh *)mesh;	

		
		
		
		
		d3dmesh->PreRender(this);

		d3dmesh->SetPreRenderEffectHandles();

		SetMeshLights(scene,mesh);
		SetMeshWorldHandlers(scene, mesh);
		d3dmesh->CommitEffectHandles();

		// Begin passes.

		UINT numPasses = d3dmesh->GetNumShaderPasses();
		d3dmesh->BeginShader();
		for(UINT i = 0; i < numPasses; ++i)
		{
			d3dmesh->BeginShaderPass(i);
			DrawMesh(mesh);
			d3dmesh->EndShaderPass(i);
		}
		d3dmesh->EndShader();
		d3dmesh->PosRender(this);
		

		
		
		
	}

	

	for(int i = 0; i < totalMirrors; i++)
	{
		Mirror *mirror = scene->GetMirrorsVector()->at(i);	
		D3DMirror *d3dmirror = (D3DMirror *)mirror;	

		
		d3dmirror->PreRender(this);

		d3dmirror->SetPreRenderEffectHandles();

		SetMeshLights(scene,(Mesh *)mirror);
		SetMeshWorldHandlers(scene, (Mesh*)mirror);
		d3dmirror->CommitEffectHandles();

		// Begin passes.

		UINT numPasses = d3dmirror->GetNumShaderPasses();
		d3dmirror->BeginShader();
		for(UINT i = 0; i < numPasses; ++i)
		{
			d3dmirror->BeginShaderPass(i);
			DrawMesh((Mesh*)d3dmirror);
			d3dmirror->EndShaderPass(i);
		}
		d3dmirror->EndShader();
		d3dmirror->PosRender(this);
		
		
	}
#endif
}

void D3DRenderer::EnableAlphaBlending()
{
	// Enable alpha blending.
	HR(m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, true));
	HR(m_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA));
	HR(m_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA));
}

void D3DRenderer::DisableAlphaBlending()
{
	// Disable alpha blending.
	HR(m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, false));
}


void D3DRenderer::DrawMesh(Mesh *a_mesh)
{

	D3DMesh *mesh = (D3DMesh *)a_mesh;	
	
	HR(m_device->SetStreamSource(0, mesh->GetVertexBuffer(), 0, mesh->GetVertexSize()));
	
	HR(m_device->SetIndices(mesh->GetIndexBuffer()));	
	HR(m_device->SetVertexDeclaration(mesh->GetVertexDeclaration()));

	D3DCamera *cam = (D3DCamera *) m_camera;
	
	D3DXMATRIX W;
	D3DXMatrixIdentity(&W);
	HR(m_device->SetTransform(D3DTS_WORLD, &W));
	
	HR(m_device->SetTransform(D3DTS_VIEW, &cam->GetMatrix()));
	HR(m_device->SetTransform(D3DTS_PROJECTION, &m_proj));
	HR(m_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID));

	int numTriangles = mesh->GetIndices()->size() / 3;
	int numVertices = mesh->GetVertices()->size();		
	
	HR(m_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, numVertices, 0, numTriangles));
	
	
}

void D3DRenderer::DrawSprite(Sprite *sprite)
{	
	m_sprite->Begin(0);

	D3DSprite * d3dSprite = static_cast<D3DSprite *> (sprite);
	Image * image = sprite->GetImage();
	D3DImage *tex = static_cast<D3DImage *>(image);	

	m_sprite->SetTransform(&d3dSprite->GetTransformationMatrix());

	
	IDirect3DTexture9 * t = tex->GetTexture();
	
	RECT src = d3dSprite->GetFrameRects()->at(d3dSprite->GetCurrentFrame());
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

bool D3DRenderer::Init(WindowsApplicationWindow *window, bool windowed)
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
	m_d3dpp.Windowed                   = windowed;
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

	//end of 2d stuff
	D3DCamera *cam = new D3DCamera();
	m_camera = (Camera *)cam;	
	m_camera->SetPosition(0.0f, 0.0f, 0.0f);
	m_camera->SetTarget(0.0f, 0.0f, 0.0f);
	
	BuildProjMtx();

	return true;
}

void D3DRenderer::Reset()
{

}


void D3DRenderer::Clear()
{	
	m_device->Clear( 0L, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x0000ffff, 1.0f, 0L );
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


