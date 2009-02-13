#include "D3DRenderer.h"
#include "Debug.h"
#include "D3DSprite.h"
#include "ResourceManager.h"
#include "D3DMesh.h"
#include "D3DMirror.h"
#include "FXManager.h"


#include "ShadowFX.h"
#include "D3DShadowSurface.h"
//#include "DebugMemory.h"
#include "SkinnedMeshBookFX.h"

#include "Dwarf.h"

#if HACK_FROM_SCRATCH
IDirect3DVertexDeclaration9* VertexPosHACK::Decl = 0;
#endif

IDirect3DDevice9 * D3DRenderer::m_device = NULL;

D3DRenderer::D3DRenderer()
{	
	m_font = NULL;	
	//mSkinnedMesh = NULL;
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

void D3DRenderer::CreateMeshBuffers(D3DMesh *mesh)
{			
	
	//indices
	IDirect3DIndexBuffer9 *ib;

	int indicesSize = mesh->GetIndices()->size();
	
	HR(GetDevice()->CreateIndexBuffer(indicesSize * sizeof(WORD), D3DUSAGE_WRITEONLY,
	D3DFMT_INDEX16, D3DPOOL_MANAGED, &ib, 0));
	WORD *k = 0;

	HR(ib->Lock(0,0,(void**)&k, 0));

	for(int i = 0; i < indicesSize; i++)
	{
		k[i] = mesh->GetIndices()->at(i);
	}

	HR(ib->Unlock());

	//vertices
	IDirect3DVertexBuffer9 * vb;
	int vertexSize = mesh->GetVertices()->size();
	HR(GetDevice()->CreateVertexBuffer(vertexSize * mesh->GetVertexSize(), D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED, &vb, 0));
	VertexPos *v = 0;
	HR(vb->Lock(0,0,(void**)&v,0));

	for(int i = 0; i < vertexSize; i++)
	{
		v[i] = mesh->GetVertices()->at(i);
	}
	
	HR(vb->Unlock());

	//vertexDeclaration
#if 0
	D3DVERTEXELEMENT9 VertexPosElements[] =
	{
		{0,0,D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
		D3DDECL_END()
	};
#endif

	D3DVERTEXELEMENT9 VertexPosElements[] = 
	{
		{0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
		{0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
		D3DDECL_END()
	};	

	

	IDirect3DVertexDeclaration9 *Decl;
	HR(GetDevice()->CreateVertexDeclaration(VertexPosElements, &Decl));

	mesh->SetBuffers(vb, ib);
	mesh->SetVertexDeclaration(Decl);

	//mesh->Translate(0.0f, 0.0f, 0.0f);
}

#if HACK_FROM_SCRATCH

void D3DRenderer::DrawScene(Scene *scene)
{
	
	Mesh *mesh = scene->GetMeshesVector()->at(0);	
	D3DMesh *d3dmesh = (D3DMesh *)mesh;	
	

	// Clear the backbuffer and depth buffer.
	HR(m_device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0));

	HR(m_device->BeginScene());

	// Let Direct3D know the vertex buffer, index buffer and vertex 
	// declaration we are using.
	//HR(m_device->SetStreamSource(0, mVB, 0, sizeof(VertexPosHACK)));
	HR(m_device->SetStreamSource(0, d3dmesh->GetVertexBuffer(), 0, d3dmesh->GetVertexSize()));
	//HR(m_device->SetIndices(mIB));
	HR(m_device->SetIndices(d3dmesh->GetIndexBuffer()));
	
	//HR(m_device->SetVertexDeclaration(VertexPosHACK::Decl));
	HR(m_device->SetVertexDeclaration(d3dmesh->GetVertexDeclaration()));

	// World matrix is identity.
	D3DXMATRIX W;
	D3DXMatrixIdentity(&W);
	HR(m_device->SetTransform(D3DTS_WORLD, &W));
	//HR(m_device->SetTransform(D3DTS_VIEW, &mView));
	HR(m_device->SetTransform(D3DTS_PROJECTION, &mProj));

	D3DCamera *cam = (D3DCamera *) m_camera;
	
	
	
	HR(m_device->SetTransform(D3DTS_VIEW, &cam->GetMatrix()));

	HR(m_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME));
	//HR(m_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12));
	int numTriangles = d3dmesh->GetIndices()->size() / 3;
	int numVertices = d3dmesh->GetVertices()->size();		
	
	HR(m_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, numVertices, 0, numTriangles));
	
	//mGfxStats->display();

	HR(m_device->EndScene());

	// Present the backbuffer.
	HR(m_device->Present(0, 0, 0, 0));
}


#else

void D3DRenderer::DrawScene(Scene *scene)
{		

	int totalMeshes = scene->GetMeshesVector()->size();		
	int totalMirrors = scene->GetMirrorsVector()->size();	
	int totalShadowSurfaces = scene->GetShadowSurfacesVector()->size();
	
	D3DScene *t_scene = static_cast<D3DScene *> (scene);						
	D3DCamera *cam = (D3DCamera *) m_camera;
	D3DXMATRIX t_view = cam->GetMatrix();	
	
	D3DXMATRIX t_projView = t_view*m_proj;	
	

	FXManager::GetInstance()->SetUpdateHandlers(cam->GetPosition(), t_projView);


	UINT num = 0;			
	
	
	for(int i = 0; i < totalMirrors; i++)
	{
		DrawMirror(scene->GetMirrorsVector()->at(i), scene);		
	}		

	for(int i = 0; i < totalMeshes; i++)
	{		
		Mesh *mesh = scene->GetMeshesVector()->at(i);	
		D3DMesh *d3dmesh = (D3DMesh *)mesh;	
		
		if(d3dmesh->GetXMesh())
		{
			DrawXMesh(d3dmesh);
		}
		else
		{
			DrawMesh(mesh);
		}
		
	}	

	for(int i = 0; i < totalShadowSurfaces; i++)
	{				
		DrawShadowSurface(scene->GetShadowSurfacesVector()->at(i), scene);
	}


}


#endif



void D3DRenderer::DrawXMesh(D3DMesh * a_mesh)
{	

	//PerVertexLighting * t_auei = static_cast<PerVertexLighting *>(a_mesh->GetEffect());			
	FXManager::GetInstance()->Begin(a_mesh->GetEffect());				

	//int t_totalMaterials = a_mesh->GetMaterials()->size();
	int t_totalMaterials = a_mesh->GetMaterials()->size();
	ID3DXMesh *t_xMesh = a_mesh->GetXMesh();		
	

	for(int j = 0; j < t_totalMaterials; j++)
	{				
		
		a_mesh->SetCurrentMaterial(a_mesh->GetMaterials()->at(j));

		
		int t_totalTextures = a_mesh->GetTextures()->size();
		
		if(j < t_totalTextures)
		{			
			Image *t_image = a_mesh->GetTextures()->at(j);			
			a_mesh->SetCurrentTexture(t_image);
		}
		
		a_mesh->SetShaderHandlers();
		FXManager::GetInstance()->PreRender();	
		HR(t_xMesh->DrawSubset(j));
		FXManager::GetInstance()->PosRender();
	}						

	
	FXManager::GetInstance()->End();

}

void D3DRenderer::DrawShadowSurface(ShadowSurface *shadowSurface, Scene *scene)
{
	Mesh *mesh = shadowSurface->GetMesh();	
	D3DMesh *d3dmesh = (D3DMesh *)mesh;	
	DrawMesh(mesh);	

	int totalMeshes = scene->GetMeshesVector()->size();	

	HR(m_device->SetRenderState(D3DRS_STENCILENABLE,    true));
    HR(m_device->SetRenderState(D3DRS_STENCILFUNC,      D3DCMP_EQUAL));
    HR(m_device->SetRenderState(D3DRS_STENCILREF,       0x0));
    HR(m_device->SetRenderState(D3DRS_STENCILMASK,      0xffffffff));
    HR(m_device->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff));
    HR(m_device->SetRenderState(D3DRS_STENCILZFAIL,     D3DSTENCILOP_KEEP));
    HR(m_device->SetRenderState(D3DRS_STENCILFAIL,      D3DSTENCILOP_KEEP));
    HR(m_device->SetRenderState(D3DRS_STENCILPASS,      D3DSTENCILOP_INCR)); 

	// Position shadow.
	D3DXVECTOR4 lightDirection(0.577f, -0.577f, 0.577f, 0.0f);
	D3DXPLANE *groundPlane = static_cast<D3DShadowSurface *>(shadowSurface)->GetPlane();
	

	D3DXMATRIX S;
	D3DXMatrixShadow(&S, &lightDirection, groundPlane);

	// Offset the shadow up slightly so that there is no
	// z-fighting with the shadow and ground.
	D3DXMATRIX eps;
	D3DXMatrixTranslation(&eps, 0.0f, 0.002f, 0.0f);
	

	// Alpha blend the shadow.
	HR(m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, true));
	HR(m_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA));
	HR(m_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA));

	
	for(int i = 0; i < totalMeshes; i++)
	{		
		Mesh *mesh = scene->GetMeshesVector()->at(i);	
		D3DMesh *d3dmesh = (D3DMesh *)mesh;					
		D3DXMATRIX previous = d3dmesh->GetTransformMatrix();
		d3dmesh->SetTransformMatrix(previous*S*eps);				
		DrawMesh(mesh, ShaderManager::GetInstance()->GetDefaultShadowFX());
		d3dmesh->SetTransformMatrix(previous);	
	}

	// Restore settings.
	
	HR(m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, false));
	HR(m_device->SetRenderState(D3DRS_STENCILENABLE,    false));
}


void D3DRenderer::DrawMirror(Mirror *mirror, Scene *scene)
{
	Mesh *mesh = mirror->GetMesh();	
	D3DMesh *d3dmesh = (D3DMesh *)mesh;	
	if(d3dmesh->GetXMesh())
	{
		DrawXMesh(d3dmesh);
	}
	else
	{
		DrawMesh(mesh);	
	}		

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
    //HR(m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, true));
    HR(m_device->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_ZERO));
    HR(m_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE));

	if(d3dmesh->GetXMesh())
	{
		DrawXMesh(d3dmesh);
	}
	else
	{
		DrawMesh(mesh);	
	}

	// Re-enable depth writes
	
	HR(m_device->SetRenderState( D3DRS_ZWRITEENABLE, true ));

	// Only draw reflected teapot to the pixels where the mirror
	// was drawn to.
	HR(m_device->SetRenderState(D3DRS_STENCILFUNC,  D3DCMP_EQUAL));
    HR(m_device->SetRenderState(D3DRS_STENCILPASS,  D3DSTENCILOP_KEEP));

	// Disable depth buffer and render the reflected objects.
	HR(m_device->SetRenderState(D3DRS_ZENABLE, false));
	//HR(m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, false));
	HR(m_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA));
	HR(m_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA));

	int totalMeshes = scene->GetMeshesVector()->size();	
	
	
	// Build Reflection transformation.
	D3DXMATRIX R;
	D3DXPLANE *plane = static_cast<D3DMirror *>(mirror)->GetPlane();
	D3DXMatrixReflect(&R, plane);

	
	D3DScene *t_scene = static_cast<D3DScene *> (scene);				
	
	
	HR(m_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW));

	UINT num = 0;

	for(int i = 0; i < totalMeshes; i++)
	{		
		Mesh *mesh = scene->GetMeshesVector()->at(i);	
		D3DMesh *d3dmesh = (D3DMesh *)mesh;			
		D3DXMatrixReflect(&R,plane);
		D3DXMATRIX previous = d3dmesh->GetTransformMatrix();
		d3dmesh->SetTransformMatrix(previous*R);		
		if(d3dmesh->GetXMesh())
		{
			DrawXMesh(d3dmesh);
		}
		else
		{
			DrawMesh(mesh);	
		}
		d3dmesh->SetTransformMatrix(previous);	
	}
	
	// Restore render states.		
	HR(m_device->SetRenderState(D3DRS_ZENABLE, true));
	HR(m_device->SetRenderState( D3DRS_STENCILENABLE, false));
	HR(m_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW));

}

void D3DRenderer::EnableAlphaBlending(bool enable)
{
	if(enable)
	{
		// Enable alpha blending.
		HR(m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, true));
		HR(m_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA));
		HR(m_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA));
	}
	else
	{
		HR(m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, false));
	}
}

void D3DRenderer::DrawMesh(Mesh *a_mesh)
{			
	

	D3DMesh *mesh = (D3DMesh *)a_mesh;
	FXManager::GetInstance()->Begin(mesh->GetEffect());		
	//mesh->SetShaderHandlers();
	FXManager::GetInstance()->PreRender();	
	
	HR(m_device->SetStreamSource(0, mesh->GetVertexBuffer(), 0, mesh->GetVertexSize()));	
	
	HR(m_device->SetIndices(mesh->GetIndexBuffer()));	
	HR(m_device->SetVertexDeclaration(mesh->GetVertexDeclaration()));
	

	D3DCamera *cam = (D3DCamera *) m_camera;
	
	D3DXMATRIX W;
	D3DXMatrixIdentity(&W);
	HR(m_device->SetTransform(D3DTS_WORLD, &W));
	
	HR(m_device->SetTransform(D3DTS_VIEW, &cam->GetMatrix()));
	HR(m_device->SetTransform(D3DTS_PROJECTION, &m_proj));
	HR(m_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME));
	

	int numTriangles = mesh->GetIndices()->size() / 3;
	int numVertices = mesh->GetVertices()->size();		
	
	HR(m_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, numVertices, 0, numTriangles));
	

	FXManager::GetInstance()->PosRender();
	FXManager::GetInstance()->End();
	
}

void D3DRenderer::DrawMesh(Mesh *a_mesh, FX *fx)
{		
	D3DMesh *mesh = (D3DMesh *)a_mesh;
	ShadowFX *shadowFX = ShaderManager::GetInstance()->GetDefaultShadowFX();
	FXManager::GetInstance()->Begin(shadowFX);		
	
	shadowFX->SetTransformMatrix(mesh->GetTransformMatrix());

	FXManager::GetInstance()->PreRender();	
	
	HR(m_device->SetStreamSource(0, mesh->GetVertexBuffer(), 0, mesh->GetVertexSize()));	
	HR(m_device->SetIndices(mesh->GetIndexBuffer()));	
	HR(m_device->SetVertexDeclaration(mesh->GetVertexDeclaration()));

	D3DCamera *cam = (D3DCamera *) m_camera;
	
	D3DXMATRIX W;
	D3DXMatrixIdentity(&W);
	HR(m_device->SetTransform(D3DTS_WORLD, &W));
	
	HR(m_device->SetTransform(D3DTS_VIEW, &cam->GetMatrix()));
	HR(m_device->SetTransform(D3DTS_PROJECTION, &m_proj));
	HR(m_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME));
	

	int numTriangles = mesh->GetIndices()->size() / 3;
	int numVertices = mesh->GetVertices()->size();		
	
	HR(m_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, numVertices, 0, numTriangles));

	FXManager::GetInstance()->PosRender();
	FXManager::GetInstance()->End();
	
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

	HR(m_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE));

#if HACK_FROM_SCRATCH

#else
	
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
	

	
#endif
	//end of 2d stuff
	D3DCamera *cam = new D3DCamera();
	m_camera = (Camera *)cam;	
	m_camera->SetPosition(0.0f, 0.0f, 0.0f);
	m_camera->SetTarget(0.0f, 0.0f, 0.0f);
	
	BuildProjMtx();

	EnableAlphaBlending(false);	

	CreateAxis();

	

#if HACK_FROM_SCRATCH
	D3DVERTEXELEMENT9 VertexPosElements[] = 
	{
		{0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		D3DDECL_END()
	};	
	HR(m_device->CreateVertexDeclaration(VertexPosElements, &VertexPosHACK::Decl));

	buildVertexBuffer();
	//buildIndexBuffer();

	mCameraRadius    = 10.0f;
	mCameraRotationY = 1.2 * D3DX_PI;
	mCameraHeight    = 5.0f;

	// The aspect ratio depends on the backbuffer dimensions, which can 
	// possibly change after a reset.  So rebuild the projection matrix.
	buildProjMatrix();
	buildViewMtx();

	//===============================================================
	// VertexPos

	
#endif

	
	return true;
}


void D3DRenderer::CreateAxis()
{

	int vertexSize = 6;
	HR(GetDevice()->CreateVertexBuffer(vertexSize * sizeof(VertexCol), D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED, &m_axisBuffer, 0));
	VertexCol *v = 0;
	HR(m_axisBuffer->Lock(0,0,(void**)&v,0));
	
	v[0] = VertexCol(0, 0, 0, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
	v[1] = VertexCol(0, 0, 259, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
	v[2] = VertexCol(0, 0, 0, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	v[3] = VertexCol(0, 259, 0, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));	
	v[4] = VertexCol(0, 0, 0, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	v[5] = VertexCol(259, 0, 0, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));	
	
	HR(m_axisBuffer->Unlock());

	D3DVERTEXELEMENT9 VertexPosElements[] = 
	{
		{0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0, 12, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0},		
		D3DDECL_END()
	};		

	
	HR(GetDevice()->CreateVertexDeclaration(VertexPosElements, &m_axisDeclaration));

	
}

void D3DRenderer::DrawAxis()
{	
	
	HR(m_device->SetStreamSource(0, m_axisBuffer, 0, sizeof(VertexCol)));	
	HR(m_device->SetVertexDeclaration(m_axisDeclaration));

	D3DCamera *cam = (D3DCamera *) m_camera;
	
	D3DXMATRIX W;
	D3DXMatrixIdentity(&W);
	HR(m_device->SetTransform(D3DTS_WORLD, &W));
	
	HR(m_device->SetTransform(D3DTS_VIEW, &cam->GetMatrix()));
	HR(m_device->SetTransform(D3DTS_PROJECTION, &m_proj));
	HR(m_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME));
	
	m_device->DrawPrimitive( D3DPT_LINELIST, 0, 3 );
}

void D3DRenderer::Reset()
{

}


void D3DRenderer::Clear()
{	
#if HACK_FROM_SCRATCH
	return;
#endif
	
	m_device->Clear( 0L, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, 0xffffffff, 1.0f, 0L );
}

bool D3DRenderer::BeginRender()
{
#if HACK_FROM_SCRATCH
		return true;
#endif
	
	m_device->BeginScene();	
	m_sprite->Begin(0);
	return true;
}

void D3DRenderer::EndRender()
{
#if HACK_FROM_SCRATCH
	return;
#endif
	
	m_sprite->End();
	m_device->EndScene();
	m_device->Present(0, 0, 0, 0);
}


#if HACK_FROM_SCRATCH
void D3DRenderer::buildVertexBuffer()
{
	// Obtain a pointer to a new vertex buffer.
	HR(m_device->CreateVertexBuffer(8 * sizeof(VertexPosHACK), D3DUSAGE_WRITEONLY,
		0, D3DPOOL_MANAGED, &mVB, 0));

	// Now lock it to obtain a pointer to its internal data, and write the
	// cube's vertex data.

	VertexPosHACK* v = 0;
	HR(mVB->Lock(0, 0, (void**)&v, 0));

	v[0] = VertexPosHACK(-1.0f, -1.0f, -1.0f);
	v[1] = VertexPosHACK(-1.0f,  1.0f, -1.0f);
	v[2] = VertexPosHACK( 1.0f,  1.0f, -1.0f);
	v[3] = VertexPosHACK( 1.0f, -1.0f, -1.0f);
	v[4] = VertexPosHACK(-1.0f, -1.0f,  1.0f);
	v[5] = VertexPosHACK(-1.0f,  1.0f,  1.0f);
	v[6] = VertexPosHACK( 1.0f,  1.0f,  1.0f);
	v[7] = VertexPosHACK( 1.0f, -1.0f,  1.0f);

	HR(mVB->Unlock());
}



void D3DRenderer::buildIndexBuffer()
{
	// Obtain a pointer to a new index buffer.
	HR(m_device->CreateIndexBuffer(36 * sizeof(WORD), D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16, D3DPOOL_MANAGED, &mIB, 0));

	// Now lock it to obtain a pointer to its internal data, and write the
	// cube's index data.

	WORD* k = 0;

	HR(mIB->Lock(0, 0, (void**)&k, 0));

	// Front face.
	k[0] = 0; k[1] = 1; k[2] = 2;
	k[3] = 0; k[4] = 2; k[5] = 3;

	// Back face.
	k[6] = 4; k[7]  = 6; k[8]  = 5;
	k[9] = 4; k[10] = 7; k[11] = 6;

	// Left face.
	k[12] = 4; k[13] = 5; k[14] = 1;
	k[15] = 4; k[16] = 1; k[17] = 0;

	// Right face.
	k[18] = 3; k[19] = 2; k[20] = 6;
	k[21] = 3; k[22] = 6; k[23] = 7;

	// Top face.
	k[24] = 1; k[25] = 5; k[26] = 6;
	k[27] = 1; k[28] = 6; k[29] = 2;

	// Bottom face.
	k[30] = 4; k[31] = 0; k[32] = 3;
	k[33] = 4; k[34] = 3; k[35] = 7;

	HR(mIB->Unlock());
}

void D3DRenderer::buildProjMatrix()
{
	float w = (float)m_d3dpp.BackBufferWidth;
	float h = (float)m_d3dpp.BackBufferHeight;
	D3DXMatrixPerspectiveFovLH(&mProj, D3DX_PI * 0.25f, w/h, 1.0f, 5000.0f);
}

void D3DRenderer::buildViewMtx()
{
	float x = mCameraRadius * cosf(mCameraRotationY);
	float z = mCameraRadius * sinf(mCameraRotationY);
	D3DXVECTOR3 pos(x, mCameraHeight, z);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&mView, &pos, &target, &up);
}



#endif

