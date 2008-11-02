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


void D3DRenderer::DrawScene(Scene *scene)
{
	
		/*
	drawTeapot();
	drawReflectedTeapot();

	return;
	*/
	
	int totalMeshes = scene->GetMeshesVector()->size();	
	
	int totalMirrors = scene->GetMirrorsVector()->size();	

	
	D3DScene *t_scene = static_cast<D3DScene *> (scene);						

	D3DCamera *cam = (D3DCamera *) m_camera;
	D3DXMATRIX t_view = cam->GetMatrix();

	
	
	D3DXMATRIX t_projView = t_view*m_proj;	

	D3DXMATRIX fleps;

	D3DXMatrixTranslation(&fleps, 0.0f, 0.0f, 0.0f);

	t_projView = t_view*m_proj*fleps;


	FXManager::GetInstance()->SetUpdateHandlers(cam->GetPosition(), t_projView);

	UINT num = 0;

	for(int i = 0; i < totalMeshes; i++)
	{
		
		Mesh *mesh = scene->GetMeshesVector()->at(i);	
		D3DMesh *d3dmesh = (D3DMesh *)mesh;	
		FXManager::GetInstance()->Begin(d3dmesh->GetEffect());		
		d3dmesh->SetShaderHandlers();
		FXManager::GetInstance()->PreRender();	
		DrawMesh(mesh);
		FXManager::GetInstance()->PosRender();
		FXManager::GetInstance()->End();
	}

	//drawReflected(scene);

	/*
	for(int i = 0; i < totalMirrors; i++)
	{
		DrawMirror(scene->GetMirrorsVector()->at(i), scene);		
	}
	*/

	
}

void D3DRenderer::drawReflected(Scene *scene)
{
	int totalMeshes = scene->GetMeshesVector()->size();	
	
	int totalMirrors = scene->GetMirrorsVector()->size();	

	// Build Reflection transformation.
	D3DXMATRIX R;
	D3DXPLANE plane(0.0f, 0.0f, 1.0f, 3.0f); // xy plane
	D3DXMatrixReflect(&R, &plane);

	
	D3DScene *t_scene = static_cast<D3DScene *> (scene);						

	D3DCamera *cam = (D3DCamera *) m_camera;
	D3DXMATRIX t_view = cam->GetMatrix();

	D3DXMATRIX fleps;

	D3DXMatrixTranslation(&fleps, 5.0f, 0.0f, 0.0f);
	
	D3DXMATRIX t_projView = t_view*m_proj;		

	HR(m_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW));



	UINT num = 0;

	for(int i = 0; i < totalMeshes; i++)
	{
		
		Mesh *mesh = scene->GetMeshesVector()->at(i);	
		D3DMesh *d3dmesh = (D3DMesh *)mesh;	
		
		D3DXMatrixReflect(&R,&plane);

		D3DXMATRIX previous = d3dmesh->GetTransformMatrix();
		d3dmesh->SetTransformMatrix(previous*R);
		FXManager::GetInstance()->Begin(d3dmesh->GetEffect());		
		d3dmesh->SetShaderHandlers();
		FXManager::GetInstance()->PreRender();	
		DrawMesh(mesh);
		d3dmesh->SetTransformMatrix(previous);
		FXManager::GetInstance()->PosRender();
		FXManager::GetInstance()->End();
		

	}

	HR(m_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW));
	
}

void D3DRenderer::DrawMirror(Mirror *mirror, Scene *scene)
{
	Mesh *mesh = mirror->GetMesh();	
	D3DMesh *d3dmesh = (D3DMesh *)mesh;
	FXManager::GetInstance()->Begin(d3dmesh->GetEffect());	
	d3dmesh->SetShaderHandlers();
	FXManager::GetInstance()->PreRender();
	DrawMesh(mesh);
	FXManager::GetInstance()->PosRender();
	FXManager::GetInstance()->End();
#if 0
	HR(m_device->SetRenderState(D3DRS_STENCILENABLE,    true));
    HR(m_device->SetRenderState(D3DRS_STENCILFUNC,      D3DCMP_ALWAYS));
    HR(m_device->SetRenderState(D3DRS_STENCILREF,       0x1));
    HR(m_device->SetRenderState(D3DRS_STENCILMASK,      0xffffffff));
    HR(m_device->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff));
    HR(m_device->SetRenderState(D3DRS_STENCILZFAIL,     D3DSTENCILOP_KEEP));
    HR(m_device->SetRenderState(D3DRS_STENCILFAIL,      D3DSTENCILOP_KEEP));
    HR(m_device->SetRenderState(D3DRS_STENCILPASS,      D3DSTENCILOP_REPLACE));

	// Disable writes to the depth and back buffers
    HR(m_device->SetRenderState(D3DRS_ZWRITEENABLE, false));
    HR(m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, true));
    HR(m_device->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_ZERO));
    HR(m_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE));

	// Draw mirror to stencil only.
	//drawMirror();
	
	
	FXManager::GetInstance()->Begin(d3dmesh->GetEffect());	
	d3dmesh->SetShaderHandlers();
	FXManager::GetInstance()->PreRender();
	DrawMesh(mesh);
	FXManager::GetInstance()->PosRender();
	FXManager::GetInstance()->End();
	///////////77
	
	// Re-enable depth writes
	HR(m_device->SetRenderState( D3DRS_ZWRITEENABLE, true ));

	// Only draw reflected teapot to the pixels where the mirror
	// was drawn to.
	HR(m_device->SetRenderState(D3DRS_STENCILFUNC,  D3DCMP_EQUAL));
    HR(m_device->SetRenderState(D3DRS_STENCILPASS,  D3DSTENCILOP_KEEP));

	// Build Reflection transformation.
	D3DXMATRIX R;
	D3DXPLANE plane(0.0f, 0.0f, 1.0f, 0.0f); // xy plane
	D3DXMatrixReflect(&R, &plane);

	// Save the original teapot world matrix.
	//D3DXMATRIX oldTeapotWorld = mTeapotWorld;

	// Add reflection transform.
	//mTeapotWorld = mTeapotWorld * R;

	// Reflect light vector also.
	//D3DXVECTOR3 oldLightVecW = mLightVecW;
	//D3DXVec3TransformNormal(&mLightVecW, &mLightVecW, &R);
	//HR(mFX->SetValue(mhLightVecW, &mLightVecW, sizeof(D3DXVECTOR3)));

	// Disable depth buffer and render the reflected teapot.
	HR(m_device->SetRenderState(D3DRS_ZENABLE, false));
	HR(m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, false));

	// Finally, draw the reflected teapot
	HR(m_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW));
	//drawTeapot();

	int totalMeshes = scene->GetMeshesVector()->size();	
	for(int i = 0; i < totalMeshes; i++)
	{
		
		mesh = scene->GetMeshesVector()->at(i);	
		d3dmesh = (D3DMesh *)mesh;	
		FXManager::GetInstance()->Begin(d3dmesh->GetEffect());		
		d3dmesh->SetShaderHandlers();
		FXManager::GetInstance()->PreRender();	
		DrawMesh(mesh);
		FXManager::GetInstance()->PosRender();
		FXManager::GetInstance()->End();
	}
	///////////////////////////77
	//mTeapotWorld = oldTeapotWorld;
	//mLightVecW   = oldLightVecW;
	
	// Restore render states.
	HR(m_device->SetRenderState(D3DRS_ZENABLE, true));
	HR(m_device->SetRenderState( D3DRS_STENCILENABLE, false));
	HR(m_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW));
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

#if 1
	// Create the FX from a .fx file.
	ID3DXBuffer* errors = 0;
	HR(D3DXCreateEffectFromFile(m_device, "DirLightTex.fx", 
		0, 0, D3DXSHADER_DEBUG, 0, &mFX, &errors));
	if( errors )
		MessageBox(0, (char*)errors->GetBufferPointer(), 0, 0);

	// Obtain handles.
	mhTech          = mFX->GetTechniqueByName("DirLightTexTech");
	mhWVP           = mFX->GetParameterByName(0, "gWVP");
	mhWorldInvTrans = mFX->GetParameterByName(0, "gWorldInvTrans");
	mhLightVecW     = mFX->GetParameterByName(0, "gLightVecW");
	mhDiffuseMtrl   = mFX->GetParameterByName(0, "gDiffuseMtrl");
	mhDiffuseLight  = mFX->GetParameterByName(0, "gDiffuseLight");
	mhAmbientMtrl   = mFX->GetParameterByName(0, "gAmbientMtrl");
	mhAmbientLight  = mFX->GetParameterByName(0, "gAmbientLight");
	mhSpecularMtrl  = mFX->GetParameterByName(0, "gSpecularMtrl");
	mhSpecularLight = mFX->GetParameterByName(0, "gSpecularLight");
	mhSpecularPower = mFX->GetParameterByName(0, "gSpecularPower");
	mhEyePos        = mFX->GetParameterByName(0, "gEyePosW");
	mhWorld         = mFX->GetParameterByName(0, "gWorld");
	mhTex           = mFX->GetParameterByName(0, "gTex");

	HR(D3DXCreateTextureFromFile(m_device, "brick1.dds", &mTeapotTex));
	HR(D3DXCreateTeapot(m_device, &mTeapot, 0));
	D3DXMatrixTranslation(&mTeapotWorld, 0.0f, 1.0f, -6.0f);

	mLightVecW     = D3DXVECTOR3(0.0, 0.707f, -0.707f);
	mDiffuseLight  = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	mAmbientLight  = D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f);
	mSpecularLight = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	HR(mFX->SetTechnique(mhTech));
	HR(mFX->SetValue(mhLightVecW, &mLightVecW, sizeof(D3DXVECTOR3)));
	HR(mFX->SetValue(mhDiffuseLight, &mDiffuseLight, sizeof(D3DXCOLOR)));
	HR(mFX->SetValue(mhAmbientLight, &mAmbientLight, sizeof(D3DXCOLOR)));
	HR(mFX->SetValue(mhSpecularLight, &mSpecularLight, sizeof(D3DXCOLOR)));

	// All objects use the same material.
	D3DXCOLOR t_white = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXCOLOR t_white2 = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	HR(mFX->SetValue(mhAmbientMtrl, &t_white, sizeof(D3DXCOLOR)));
	HR(mFX->SetValue(mhDiffuseMtrl, &t_white, sizeof(D3DXCOLOR)));
	HR(mFX->SetValue(mhSpecularMtrl, &t_white2 , sizeof(D3DXCOLOR)));
	HR(mFX->SetFloat(mhSpecularPower, 16.0F));
#endif

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


#if 1



void D3DRenderer::drawTeapot()
{		
	D3DCamera *cam = (D3DCamera *) m_camera;
	D3DXMATRIX t_view = cam->GetMatrix();

	
	// Cylindrically interpolate texture coordinates.
	HR(m_device->SetRenderState(D3DRS_WRAP0, D3DWRAPCOORD_0));

	
	HR(mFX->SetMatrix(mhWVP, &(mTeapotWorld*t_view*m_proj)));
	D3DXMATRIX worldInvTrans;
	D3DXMatrixInverse(&worldInvTrans, 0, &mTeapotWorld);
	D3DXMatrixTranspose(&worldInvTrans, &worldInvTrans);
	HR(mFX->SetMatrix(mhWorldInvTrans, &worldInvTrans));
	HR(mFX->SetMatrix(mhWorld, &mTeapotWorld));
	HR(mFX->SetTexture(mhTex, mTeapotTex));

	// Begin passes.
	UINT numPasses = 0;
	HR(mFX->Begin(&numPasses, 0));
	for(UINT i = 0; i < numPasses; ++i)
	{
		HR(mFX->BeginPass(i));
		HR(mTeapot->DrawSubset(0));
		HR(mFX->EndPass());
	}
	HR(mFX->End());

	// Disable wrap.
	HR(m_device->SetRenderState(D3DRS_WRAP0, 0));
}

void D3DRenderer::drawReflectedTeapot()
{

	
	// Build Reflection transformation.
	D3DXMATRIX R;
	D3DXPLANE plane(0.0f, 0.0f, 1.0f, 0.0f); // xy plane
	D3DXMatrixReflect(&R, &plane);

	// Save the original teapot world matrix.
	D3DXMATRIX oldTeapotWorld = mTeapotWorld;

	// Add reflection transform.
	mTeapotWorld = mTeapotWorld * R;

	// Reflect light vector also.
	/*
	D3DXVECTOR3 oldLightVecW = mLightVecW;
	D3DXVec3TransformNormal(&mLightVecW, &mLightVecW, &R);
	HR(mFX->SetValue(mhLightVecW, &mLightVecW, sizeof(D3DXVECTOR3)));

	*/
	// Disable depth buffer and render the reflected teapot.
	
	D3DXMatrixTranslation(&mTeapotWorld,2.0f, 2.0f, 2.0f);
	drawTeapot();
	mTeapotWorld = oldTeapotWorld;
	//mLightVecW   = oldLightVecW;
	
}
#endif