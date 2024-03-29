#include "D3DRenderer.h"
#include "Debug.h"
#include "D3DSprite.h"
#include "ResourceManager.h"
#include "D3DMesh.h"
#include "D3DMirror.h"
#include "FXManager.h"
#include "ShadowFX.h"
#include "D3DShadowSurface.h"
#include "SkinnedMeshBookFX.h"
#include "VertexDeclarations.h"
#include "Dwarf.h"
#include "FireRingFX.h"
#include "PerVertexLighting.h"
#include "C3DESkinnedMeshFX.h"
#include "C3DESkinnedMesh.h"
#include "C3DESkinnedMeshContainer.h"
#include "PerVertexLightingWallNoFog.h"
#include "TextureOnlyFX.h"
#include "DiffuseStaticLight.h"
#include "AmbientLightFX.h"
#include "SpecularLightFX.h"
#include "DebugMemory.h"

#define REAL_HACK 0
#define DRAW_BOUNDING_BOXES 0

#define MAX_NUM_PARTICLES 50



#if REAL_HACK
IDirect3DVertexDeclaration9* VertexPosHACK::Decl = 0;
#endif

IDirect3DDevice9 * D3DRenderer::m_device = NULL;
D3DRenderer * D3DRenderer::m_instance = NULL;

D3DRenderer * D3DRenderer::GetInstance()
{
	
	if(!m_instance)
	{
		m_instance = new D3DRenderer();
	}

	return m_instance;
}

D3DRenderer::D3DRenderer()
{	
	m_font = NULL;	
	hidden = 0;
	shown = 0;
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
	D3DXMatrixPerspectiveFovLH(&m_proj, D3DX_PI * 0.25f, w/h, 1.0f, FAR_Z);
	
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

#if REAL_HACK

void D3DRenderer::DrawScene(Scene *scene)
{
	
	Mesh *mesh = scene->GetMeshesVector()->at(0);	
	D3DMesh *d3dmesh = (D3DMesh *)mesh;	
	

	

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

	HR(m_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID));
	//HR(m_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12));
	int numTriangles = d3dmesh->GetIndices()->size() / 3;
	int numVertices = d3dmesh->GetVertices()->size();		
	
	HR(m_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, numVertices, 0, numTriangles));
	
	
}


#else

void D3DRenderer::CalculateFrustumPlanes()
{
	D3DCamera *cam = (D3DCamera *) m_camera;
	D3DXMATRIX t_view = cam->GetMatrix();	
	
	D3DXMATRIX VP = t_view*m_proj;	

	D3DXVECTOR4 col0(VP(0,0), VP(1,0), VP(2,0), VP(3,0));
	D3DXVECTOR4 col1(VP(0,1), VP(1,1), VP(2,1), VP(3,1));
	D3DXVECTOR4 col2(VP(0,2), VP(1,2), VP(2,2), VP(3,2));
	D3DXVECTOR4 col3(VP(0,3), VP(1,3), VP(2,3), VP(3,3));

	m_frustumPlane[0] = (D3DXPLANE)(col2);
	m_frustumPlane[1] = (D3DXPLANE)(col3 - col2);
	m_frustumPlane[2] = (D3DXPLANE)(col3 + col0);
	m_frustumPlane[3] = (D3DXPLANE)(col3 - col0);
	m_frustumPlane[4] = (D3DXPLANE)(col3 - col1);
	m_frustumPlane[5] = (D3DXPLANE)(col3 + col1);

	for(int i = 0; i < 6; i++)
	{
		D3DXPlaneNormalize(&m_frustumPlane[i], &m_frustumPlane[i]);
	}
}

bool D3DRenderer::IsAABBWithinView(D3DXMATRIX a_transform,AABB *a_box)
{
	
	D3DXVECTOR3 P;
	D3DXVECTOR3 Q;

	D3DXPLANE t_planes[6];
	D3DXPLANE t_plane1;
	D3DXPLANE t_plane2;
	D3DXPLANE t_plane3;
	D3DXPLANE t_plane4;
	D3DXPLANE t_plane5;
	D3DXPLANE t_plane6;


	D3DXMATRIX t_matrix = a_transform;	

	D3DXMatrixTranspose(&t_matrix, &t_matrix);

	D3DXPlaneTransform(&t_plane1, &m_frustumPlane[0], &t_matrix);
	D3DXPlaneTransform(&t_plane2, &m_frustumPlane[1], &t_matrix);
	D3DXPlaneTransform(&t_plane3, &m_frustumPlane[2], &t_matrix);
	D3DXPlaneTransform(&t_plane4, &m_frustumPlane[3], &t_matrix);
	D3DXPlaneTransform(&t_plane5, &m_frustumPlane[4], &t_matrix);
	D3DXPlaneTransform(&t_plane6, &m_frustumPlane[5], &t_matrix);

	D3DXPlaneNormalize(&t_plane1, &t_plane1);
	D3DXPlaneNormalize(&t_plane2, &t_plane2);
	D3DXPlaneNormalize(&t_plane3, &t_plane3);
	D3DXPlaneNormalize(&t_plane4, &t_plane4);
	D3DXPlaneNormalize(&t_plane5, &t_plane5);
	D3DXPlaneNormalize(&t_plane6, &t_plane6);

	t_planes[0] = t_plane1;
	t_planes[1] = t_plane2;
	t_planes[2] = t_plane3;
	t_planes[3] = t_plane4;
	t_planes[4] = t_plane5;
	t_planes[5] = t_plane6;
	

	for(int i = 0; i < 6; ++i)
	{

		for(int j = 0; j < 3; ++j)
		{
			if(t_planes[i][j] >= 0.0f)
			{
				P[j] = a_box->minPoint[j];
				Q[j] = a_box->maxPoint[j];
			}
			else
			{
				P[j] = a_box->maxPoint[j];
				Q[j] = a_box->minPoint[j];
			}
		}
		if(D3DXPlaneDotCoord(&t_planes[i], &Q) < 0.0f)

		return false;
	}

	return true;

	
}

bool D3DRenderer::IsMeshWithinView(D3DMesh *a_mesh, D3DXMATRIX a_matrix)
{
	
	D3DXVECTOR3 P;
	D3DXVECTOR3 Q;

	D3DXPLANE t_planes[6];
	D3DXPLANE t_plane1;
	D3DXPLANE t_plane2;
	D3DXPLANE t_plane3;
	D3DXPLANE t_plane4;
	D3DXPLANE t_plane5;
	D3DXPLANE t_plane6;

	AABB *t_box = a_mesh->GetBoundingBox();


	D3DXVECTOR3 t_min = t_box->minPoint;
	D3DXVECTOR3 t_max = t_box->maxPoint;	

	D3DXMATRIX t_matrix = a_matrix;

	D3DXMatrixTranspose(&t_matrix, &t_matrix);

	D3DXPlaneTransform(&t_plane1, &m_frustumPlane[0], &t_matrix);
	D3DXPlaneTransform(&t_plane2, &m_frustumPlane[1], &t_matrix);
	D3DXPlaneTransform(&t_plane3, &m_frustumPlane[2], &t_matrix);
	D3DXPlaneTransform(&t_plane4, &m_frustumPlane[3], &t_matrix);
	D3DXPlaneTransform(&t_plane5, &m_frustumPlane[4], &t_matrix);
	D3DXPlaneTransform(&t_plane6, &m_frustumPlane[5], &t_matrix);

	D3DXPlaneNormalize(&t_plane1, &t_plane1);
	D3DXPlaneNormalize(&t_plane2, &t_plane2);
	D3DXPlaneNormalize(&t_plane3, &t_plane3);
	D3DXPlaneNormalize(&t_plane4, &t_plane4);
	D3DXPlaneNormalize(&t_plane5, &t_plane5);
	D3DXPlaneNormalize(&t_plane6, &t_plane6);

	t_planes[0] = t_plane1;
	t_planes[1] = t_plane2;
	t_planes[2] = t_plane3;
	t_planes[3] = t_plane4;
	t_planes[4] = t_plane5;
	t_planes[5] = t_plane6;
	

	for(int i = 0; i < 6; ++i)
	{
		for(int j = 0; j < 3; ++j)
		{
			if(t_planes[i][j] >= 0.0f)
			{
				P[j] = t_min[j];
				Q[j] = t_max[j];
			}
			else
			{
				P[j] = t_max[j];
				Q[j] = t_min[j];
			}
		}
		if(D3DXPlaneDotCoord(&t_planes[i], &Q) < 0.0f)

		return false;
	}

	return true;

	
}

bool D3DRenderer::IsMeshWithinView(D3DMesh *a_mesh)
{
	
	D3DXVECTOR3 P;
	D3DXVECTOR3 Q;

	D3DXPLANE t_planes[6];
	D3DXPLANE t_plane1;
	D3DXPLANE t_plane2;
	D3DXPLANE t_plane3;
	D3DXPLANE t_plane4;
	D3DXPLANE t_plane5;
	D3DXPLANE t_plane6;

	AABB *t_box = a_mesh->GetBoundingBox();

	D3DXMATRIX t_scaleMatrix;
	D3DXMatrixScaling(&t_scaleMatrix, a_mesh->GetXScale(), a_mesh->GetYScale(), a_mesh->GetZScale());

	D3DXVECTOR3 t_min = t_box->minPoint;
	D3DXVECTOR3 t_max = t_box->maxPoint;

	
	D3DXVECTOR4 t_min4 = D3DXVECTOR4(t_min, 1.0f);
	D3DXVECTOR4 t_max4 = D3DXVECTOR4(t_min, 1.0f);
	D3DXVec3Transform(&t_min4, &t_min, &t_scaleMatrix);
	D3DXVec3Transform(&t_max4, &t_max, &t_scaleMatrix);

	t_min.x = t_min4.x;
	t_min.y = t_min4.y;
	t_min.z = t_min4.z;

	t_max.x = t_max4.x;
	t_max.y = t_max4.y;
	t_max.z = t_max4.z;	

	float t_x = a_mesh->GetX();
	float t_y = a_mesh->GetY();
	float t_z = a_mesh->GetZ();

	float t_rotateX = a_mesh->GetRotationX();
	float t_rotateY = a_mesh->GetRotationY();
	float t_rotateZ = a_mesh->GetRotationZ();

	#define RADIAN_TO_DEGREES 57.29577951308232286465f
	D3DXMATRIX matRotation,matTranslation;
	int mat;
	D3DXVECTOR3 vAxis1, vAxis2, vAxis3;
	D3DXQUATERNION qR;

	// Set default translation
	D3DXMatrixIdentity( &matTranslation );

	//D3DXMatrixScaling( &matScale, m_scaleX, m_scaleY, m_scaleZ );

	vAxis2.x = 0.0f;
	vAxis2.y = 1.0f;
	vAxis2.z = 0.0f;
	D3DXQuaternionNormalize(&qR, &qR);
	D3DXQuaternionRotationAxis( &qR, &vAxis2, t_rotateY/RADIAN_TO_DEGREES );
	D3DXMatrixRotationQuaternion( &matRotation, &qR );
	D3DXMatrixMultiply( &matTranslation, &matRotation , &matTranslation );
	vAxis1.x = 1.0f;
	vAxis1.y = 0.0f;
	vAxis1.z = 0.0f;
	D3DXQuaternionNormalize(&qR, &qR);
	D3DXQuaternionRotationAxis( &qR, &vAxis1, t_rotateX/RADIAN_TO_DEGREES );
	D3DXMatrixRotationQuaternion( &matRotation, &qR );
	D3DXMatrixMultiply( &matTranslation, &matRotation , &matTranslation );
	vAxis3.x = 0.0f;
	vAxis3.y = 0.0f;
	vAxis3.z = 1.0f;
	D3DXQuaternionNormalize(&qR, &qR);
	D3DXQuaternionRotationAxis( &qR, &vAxis3, t_rotateZ/RADIAN_TO_DEGREES );
	D3DXMatrixRotationQuaternion( &matRotation, &qR );


	
	D3DXMatrixMultiply( &matTranslation, &matRotation , &matTranslation );

	//D3DXMatrixMultiply(&matTranslation, &matScale, &matTranslation);

	// Move to X,Y,Z coordinates
	matTranslation._41 = t_x;
	matTranslation._42 = t_y;
	matTranslation._43 = t_z;
	// Set the matrix

	D3DXMATRIX t_matrix = matTranslation;
	


	D3DXMatrixTranspose(&t_matrix, &t_matrix);

	D3DXPlaneTransform(&t_plane1, &m_frustumPlane[0], &t_matrix);
	D3DXPlaneTransform(&t_plane2, &m_frustumPlane[1], &t_matrix);
	D3DXPlaneTransform(&t_plane3, &m_frustumPlane[2], &t_matrix);
	D3DXPlaneTransform(&t_plane4, &m_frustumPlane[3], &t_matrix);
	D3DXPlaneTransform(&t_plane5, &m_frustumPlane[4], &t_matrix);
	D3DXPlaneTransform(&t_plane6, &m_frustumPlane[5], &t_matrix);

	D3DXPlaneNormalize(&t_plane1, &t_plane1);
	D3DXPlaneNormalize(&t_plane2, &t_plane2);
	D3DXPlaneNormalize(&t_plane3, &t_plane3);
	D3DXPlaneNormalize(&t_plane4, &t_plane4);
	D3DXPlaneNormalize(&t_plane5, &t_plane5);
	D3DXPlaneNormalize(&t_plane6, &t_plane6);

	t_planes[0] = t_plane1;
	t_planes[1] = t_plane2;
	t_planes[2] = t_plane3;
	t_planes[3] = t_plane4;
	t_planes[4] = t_plane5;
	t_planes[5] = t_plane6;
	

	for(int i = 0; i < 6; ++i)
	{
		for(int j = 0; j < 3; ++j)
		{
			if(t_planes[i][j] >= 0.0f)
			{
				P[j] = t_min[j];
				Q[j] = t_max[j];
			}
			else
			{
				P[j] = t_max[j];
				Q[j] = t_min[j];
			}
		}
		if(D3DXPlaneDotCoord(&t_planes[i], &Q) < 0.0f)

		return false;
	}

	return true;

	
}


bool D3DRenderer::IsPointWithinView(D3DXVECTOR3 aPoint)
{
	//0 == left
	//1 == right
	//2 == front
	//3 == back
	//4 == top
	//5 == bottom

	D3DXPLANE t_left = m_frustumPlane[2];
	D3DXPLANE t_right = m_frustumPlane[3];
	D3DXPLANE t_front= m_frustumPlane[1];
	D3DXPLANE t_back = m_frustumPlane[0];
	D3DXPLANE t_top = m_frustumPlane[4];
	D3DXPLANE t_bottom = m_frustumPlane[5];


	for(int i = 0; i < 6; i++)
	{
		float d = D3DXPlaneDotCoord(&m_frustumPlane[i], &aPoint);
		if(d < 0.0f)
		{
			return false;
		}
	}
	
	return true;

	
}



void D3DRenderer::DrawParticleSystem(ParticleSystem *a_particleSystem)
{	
	FX *t_effect;
	
	t_effect =  (FireRingFX*) a_particleSystem->GetEffect();



	a_particleSystem->SetShaderHandlers();

	UINT numPasses = 0;
	ID3DXEffect *t_fx = t_effect->GetEffect();

	FXManager::GetInstance()->Begin(t_effect);		
	//mesh->SetShaderHandlers();
	FXManager::GetInstance()->PreRender();	

	IDirect3DVertexBuffer9* t_vb = a_particleSystem->GetVertexBuffer();
	std::vector<VertexParticle*> *mAliveParticles = a_particleSystem->GetAliveParticles();

	HR(m_device->SetStreamSource(0, t_vb, 0, sizeof(VertexParticle)));
	HR(m_device->SetVertexDeclaration(VertexParticle::Decl));

	

	//AABB boxWorld;
	//mBox.xform(mWorld, boxWorld);
	//if( gCamera->isVisible( boxWorld ) )
	if(true)
	{
		// Initial lock of VB for writing.
		VertexParticle* p = 0;		
		HR(t_vb->Lock(0, 0, (void**)&p, D3DLOCK_DISCARD));
		int vbIndex = 0;

		// For each living particle.
		int t_size = mAliveParticles->size();
		for(UINT i = 0; i < t_size; ++i)		
		{
			// Copy particle to VB
			//p[vbIndex] = *mAliveParticles->at(i);			
			p[vbIndex] = *(*mAliveParticles)[i];			
			++vbIndex;
		}
		
		HR(t_vb->Unlock());

		// Render however many particles we copied over.
		if(vbIndex > 0)
		{
			HR(m_device->DrawPrimitive(D3DPT_POINTLIST, 0, vbIndex));
		}
	}



	FXManager::GetInstance()->PosRender();		
	//mesh->SetShaderHandlers();
	FXManager::GetInstance()->End();

	
}

void D3DRenderer::DrawScene(Scene *scene)
{	
	this->hidden = 0;
	this->shown = 0;
	int totalMeshes = scene->GetMeshesVector()->size();		
	int totalMirrors = scene->GetMirrorsVector()->size();	
	int totalShadowSurfaces = scene->GetShadowSurfacesVector()->size();
	
	D3DScene *t_scene = static_cast<D3DScene *> (scene);						
	D3DCamera *cam = (D3DCamera *) m_camera;
	D3DXMATRIX t_view = cam->GetMatrix();	
	
	D3DXMATRIX t_projView = t_view*m_proj;	

	CalculateFrustumPlanes();
	

	FXManager::GetInstance()->SetUpdateHandlers(cam->GetPosition(), t_projView);


	UINT num = 0;			
	
	
	for(int i = 0; i < totalMirrors; i++)
	{
		//DrawMirror(scene->GetMirrorsVector()->at(i), scene);		
		DrawMirror((*scene->GetMirrorsVector())[i], scene);		
	}	

	int t_totalTerrains = scene->GetTerrains()->size();

	
	for(int i = 0; i < t_totalTerrains; i++)
	{		
		Terrain *t_terrain = (*scene->GetTerrains())[i];	

		int t_totalSubMeshes = t_terrain->GetSubMeshes()->size();

		for(int j = 0; j < t_totalSubMeshes; j++)
		//for(int j = 0; j < 1; j++)
		{
			
			//if(!IsAABBWithinView(t_terrain->GetSubMeshes()->at(j)->GetBoundingBox()))
			D3DXMATRIX t_terrainTransform;
			D3DXMatrixIdentity(&t_terrainTransform);
			if(!IsAABBWithinView(t_terrainTransform,(*t_terrain->GetSubMeshes())[j]->GetBoundingBox()))
			//if(false)
			
			{
				this->hidden++;
				continue;
			}
			else
			{
				this->shown++;
			}
			//if(j%3)continue;
			FXManager::GetInstance()->Begin(t_terrain->GetEffect());			
			//ID3DXMesh *t_mesh = t_terrain->GetSubMeshes()->at(j)->GetXMesh();																
			ID3DXMesh *t_mesh = (*t_terrain->GetSubMeshes())[j]->GetXMesh();																
			//ID3DXMesh *t_mesh = t_terrain->GetXMesh();		
			//t_terrain->SetCurrentMaterial(t_terrain->GetMaterials()->at(0));			
			t_terrain->SetCurrentMaterial((*t_terrain->GetMaterials())[0]);			
			
			//Image *t_image = t_terrain->GetTextures()->at(0);			
			Image *t_image = (*t_terrain->GetTextures())[0];			
			t_terrain->SetCurrentTexture(t_image);			
			
			t_terrain->SetShaderHandlers();
			FXManager::GetInstance()->PreRender();	

			HR(t_mesh->DrawSubset(0));
			FXManager::GetInstance()->PosRender();									
			
			FXManager::GetInstance()->End();
		}			
		
	}	

	for(int i = 0; i < totalMeshes; i++)
	{				
		//Mesh *mesh = scene->GetMeshesVector()->at(i);	
		Mesh *mesh = (*scene->GetMeshesVector())[i];	
		D3DMesh *d3dmesh = (D3DMesh *)mesh;	
		
		
		//if(d3dmesh->GetXMesh() && d3dmesh->GetBoundingBox())
		if(d3dmesh->GetXMesh())
		{

			AABB *t_boundingBox = d3dmesh->GetBoundingBox();
			if(!t_boundingBox)
			{
				this->shown++;
				
				DrawXMesh(d3dmesh);
				continue;
			}
			//if(IsAABBWithinView(d3dmesh->GetTransformMatrix(),t_boundingBox))
			//if(IsMeshWithinView(d3dmesh))
			if(true)
			{
				this->shown++;
				#if DRAW_BOUNDING_BOXES
				//DrawOBB(d3dmesh);
				#endif
				DrawXMesh(d3dmesh);
			}
			else
			{
				this->hidden++;
			}
		}
			

	}	


	int t_totalParticleSystems = scene->GetParticleSystems()->size();
	for(int i = 0; i < t_totalParticleSystems; i++)
	{
		DrawParticleSystem((*scene->GetParticleSystems())[i]);
	}

	for(int i = 0; i < totalShadowSurfaces; i++)
	{				
		//DrawShadowSurface(scene->GetShadowSurfacesVector()->at(i), scene);
		DrawShadowSurface((*scene->GetShadowSurfacesVector())[i], scene);
	}


}

#endif

void D3DRenderer::DrawScene2(Scene *scene)
{	
	this->hidden = 0;
	this->shown = 0;
	int totalNodes = scene->GetSceneNodes()->size();
	
	D3DScene *t_scene = static_cast<D3DScene *> (scene);						
	D3DCamera *cam = (D3DCamera *) m_camera;
	D3DXMATRIX t_view = cam->GetMatrix();	
	
	D3DXMATRIX t_projView = t_view*m_proj;	

	CalculateFrustumPlanes();
	

	FXManager::GetInstance()->SetUpdateHandlers(cam->GetPosition(), t_projView);


	UINT num = 0;						
	

	for(int i = 0; i < totalNodes; i++)
	{				
		
		Mesh *mesh = (*scene->GetSceneNodes())[i]->GetMesh();
		D3DXMATRIX *t_matrix = (*scene->GetSceneNodes())[i]->GetTransform();
		D3DMesh *d3dmesh = (D3DMesh *)mesh;	
		
		if(d3dmesh->GetXMesh())
		{
			AABB *t_boundingBox = d3dmesh->GetBoundingBox();
			if(t_boundingBox != NULL)
			{
				if(IsMeshWithinView(d3dmesh, *t_matrix))
				//if(true)
				{
					this->shown++;
					#if DRAW_BOUNDING_BOXES
					DrawOBB(d3dmesh, *t_matrix);
					#endif
					DrawXMesh2(d3dmesh, t_matrix);
				}
				else
				{
					this->hidden++;
				}
			}
			else
			{
				DrawXMesh2(d3dmesh, t_matrix);
			}


		}
			

	}	

}

void D3DRenderer::DrawScene3(Scene *scene)
{	
	this->hidden = 0;
	this->shown = 0;
	int totalNodes = scene->GetSceneNodes()->size();
	
	D3DScene *t_scene = static_cast<D3DScene *> (scene);						
	D3DCamera *cam = (D3DCamera *) m_camera;
	D3DXMATRIX t_view = cam->GetMatrix();	
	
	D3DXMATRIX t_projView = t_view*m_proj;	

	CalculateFrustumPlanes();
	

	FXManager::GetInstance()->SetUpdateHandlers(cam->GetPosition(), t_projView);


	UINT num = 0;						
	

	for(int i = 0; i < totalNodes; i++)
	{				
		
		Mesh *mesh = (*scene->GetSceneNodes())[i]->GetMesh();
		int nodeEffect = (*scene->GetSceneNodes())[i]->GetEffect();
		D3DXMATRIX *t_matrix = (*scene->GetSceneNodes())[i]->GetTransform();
		D3DMesh *d3dmesh = (D3DMesh *)mesh;	
		
		if(d3dmesh->GetXMesh())
		{
			AABB *t_boundingBox = d3dmesh->GetBoundingBox();
			if(t_boundingBox != NULL)
			{
				if(IsMeshWithinView(d3dmesh, *t_matrix))
				//if(true)
				{
					this->shown++;
					#if DRAW_BOUNDING_BOXES
					DrawOBB(d3dmesh, *t_matrix);
					#endif
					DrawXMesh3(d3dmesh, t_matrix, nodeEffect, (*scene->GetSceneNodes())[i]->GetMaterial());
				}
				else
				{
					this->hidden++;
				}
			}
			else
			{
				DrawXMesh3(d3dmesh, t_matrix, nodeEffect, (*scene->GetSceneNodes())[i]->GetMaterial());
			}


		}
			

	}	

}

void D3DRenderer::DrawXMesh2(D3DMesh * a_mesh, D3DXMATRIX *a_transform)
{	

	//PerVertexLighting * t_auei = static_cast<PerVertexLighting *>(a_mesh->GetEffect());			
	FXManager::GetInstance()->Begin(a_mesh->GetEffect());				

	//int t_totalMaterials = a_mesh->GetMaterials()->size();
	int t_totalMaterials = a_mesh->GetMaterials()->size();
	ID3DXMesh *t_xMesh = a_mesh->GetXMesh();		
	

	for(int j = 0; j < t_totalMaterials; j++)
	{				
		
		//a_mesh->SetCurrentMaterial(a_mesh->GetMaterials()->at(j));
		a_mesh->SetCurrentMaterial((*a_mesh->GetMaterials())[j]);

		
		int t_totalTextures = a_mesh->GetTextures()->size();
		
		if(j < t_totalTextures)
		{			
			//Image *t_image = a_mesh->GetTextures()->at(j);			
			Image *t_image = (*a_mesh->GetTextures())[j];			
			a_mesh->SetCurrentTexture(t_image);
		}
		
		a_mesh->SetShaderHandlers();
		FX * t_effect = a_mesh->GetEffect();
		t_effect->SetTransformMatrix(*a_transform);
		FXManager::GetInstance()->PreRender();	
		a_mesh->PreRender((Renderer*)this);
		HR(t_xMesh->DrawSubset(j));
		a_mesh->PosRender((Renderer*)this);
		FXManager::GetInstance()->PosRender();
	}		
	
	FXManager::GetInstance()->End();

}

void D3DRenderer::DrawXMesh3(D3DMesh * a_mesh, D3DXMATRIX *a_transform, int effect, Material * a_material)
{	

	//PerVertexLighting * t_auei = static_cast<PerVertexLighting *>(a_mesh->GetEffect());			
	//FXManager::GetInstance()->Begin(a_mesh->GetEffect());				

	//int t_totalMaterials = a_mesh->GetMaterials()->size();
	int t_totalMaterials = a_mesh->GetMaterials()->size();
	ID3DXMesh *t_xMesh = a_mesh->GetXMesh();

	
	FX * t_targetFX;	

	switch(effect)
	{
		case EFFECT_PER_VERTEX_LIGHTING:
			t_targetFX = ShaderManager::GetInstance()->GetFXByID(SHADER_LIGHTS_PER_VERTEX_TEXTURES_NO_FOG_ID);
			break;

		case EFFECT_SKINNED_MESH:
			t_targetFX = ShaderManager::GetInstance()->GetFXByID(SHADER_C3DE_SKINNED_MESH_FX_ID);
			break;

		case EFFECT_TEXTURE_ONLY:
			t_targetFX = ShaderManager::GetInstance()->GetFXByID(SHADER_TEXTURE_ONLY_ID);
			break;

		case EFFECT_TREE:
			//t_targetFX = ShaderManager::GetInstance()->GetFXByID(SHADER_LIGHTS_PER_VERTEX_TEXTURES_NO_FOG_ID);
			t_targetFX = ShaderManager::GetInstance()->GetFXByID(SHADER_TEXTURE_ONLY_ID);
			break;

		case EFFECT_WALL:
			t_targetFX = ShaderManager::GetInstance()->GetFXByID(SHADER_LIGHTS_PER_VERTEX_TEXTURES_WALL_NO_FOG_ID);
			break;

		case EFFECT_MOVING_LIGHT:
			t_targetFX = ShaderManager::GetInstance()->GetFXByID(SHADER_LIGHTS_PER_VERTEX_TEXTURES_NO_FOG_ID);
			break;
		case EFFECT_DIFFUSE_STATIC_LIGHT:
			t_targetFX = ShaderManager::GetInstance()->GetFXByID(SHADER_DIFFUSE_STATIC_LIGHT_ID);
			break;
		case EFFECT_AMBIENT_LIGHT:
			t_targetFX = ShaderManager::GetInstance()->GetFXByID(SHADER_AMBIENT_LIGHT_ID);
			break;
		case EFFECT_SPECULAR_LIGHT:
			t_targetFX = ShaderManager::GetInstance()->GetFXByID(SHADER_SPECULAR_LIGHT_ID);
			break;

	}

	FXManager::GetInstance()->Begin(t_targetFX);		
	

	for(int j = 0; j < t_totalMaterials; j++)
	{				
		
		//a_mesh->SetCurrentMaterial(a_mesh->GetMaterials()->at(j));
		a_mesh->SetCurrentMaterial((*a_mesh->GetMaterials())[j]);

		
		int t_totalTextures = a_mesh->GetTextures()->size();
		
		if(j < t_totalTextures)
		{			
			//Image *t_image = a_mesh->GetTextures()->at(j);			
			Image *t_image = (*a_mesh->GetTextures())[j];			
			a_mesh->SetCurrentTexture(t_image);
		}

#if 1

		ApplyEffect(effect, a_mesh, a_transform, j, a_material);
		
#else
		a_mesh->SetShaderHandlers();
		FX * t_effect = a_mesh->GetEffect();
		t_effect->SetTransformMatrix(*a_transform);
		FXManager::GetInstance()->PreRender();	
		a_mesh->PreRender((Renderer*)this);
		HR(t_xMesh->DrawSubset(j));
		a_mesh->PosRender((Renderer*)this);
		FXManager::GetInstance()->PosRender();
#endif
	}		
	
	FXManager::GetInstance()->End();

}

void D3DRenderer::ApplyEffect(int effect, D3DMesh * a_mesh, D3DXMATRIX *a_transform, int subset, Material * a_material)
{
	ID3DXMesh *t_xMesh = a_mesh->GetXMesh();	
	PerVertexLighting *t_effect;
	D3DImage *t_image;
	C3DESkinnedMesh * t_mesh;
	D3DImage *t_d3dText;
	C3DESkinnedMeshFX *t_skinnedMeshEffect;
	C3DESkinnedMeshContainer *t_skinnedMesh;
	PerVertexLightingWallNoFog *t_wallEffect;
	TextureOnlyFX *t_textureOnlyEffect;
	DiffuseStaticLight * t_diffuseStaticLightEffect;
	AmbientLightFX * t_ambientLightEffect;
	SpecularLightFX * t_specularLightEffect;

	switch(effect)
	{
		case EFFECT_PER_VERTEX_LIGHTING:
			t_effect = (PerVertexLighting *)ShaderManager::GetInstance()->GetFXByID(SHADER_LIGHTS_PER_VERTEX_TEXTURES_NO_FOG_ID);
			
			if(a_material == NULL)
			{
				t_effect->SetObjectMaterials(	a_mesh->GetCurrentMaterial()->GetAmbient(), a_mesh->GetCurrentMaterial()->GetDiffuse(),
											a_mesh->GetCurrentMaterial()->GetSpecular(), a_mesh->GetCurrentMaterial()->GetSpecularPower());											
			}
			else
			{
				t_effect->SetObjectMaterials(	a_material->GetAmbient(), a_material->GetDiffuse(),
												a_material->GetSpecular(), a_material->GetSpecularPower());											
			}
			
			t_image = (D3DImage*) a_mesh->GetCurrentTexture();
			t_effect->SetObjectTexture(t_image->GetTexture());
			t_effect->SetTransformMatrix(*a_transform);
			t_effect->SetAlpha(1.0f);

			FXManager::GetInstance()->PreRender();	
			HR(t_xMesh->DrawSubset(subset));
			FXManager::GetInstance()->PosRender();

			break;
		case EFFECT_SKINNED_MESH:


			t_skinnedMeshEffect = (C3DESkinnedMeshFX *) ShaderManager::GetInstance()->GetFXByID(SHADER_C3DE_SKINNED_MESH_FX_ID);
			
			if(a_material == NULL)
			{
				t_skinnedMeshEffect->SetObjectMaterials(	a_mesh->GetCurrentMaterial()->GetAmbient(), a_mesh->GetCurrentMaterial()->GetDiffuse(),
											a_mesh->GetCurrentMaterial()->GetSpecular(), a_mesh->GetCurrentMaterial()->GetSpecularPower());											
			}
			else
			{
				t_skinnedMeshEffect->SetObjectMaterials(	a_material->GetAmbient(), a_material->GetDiffuse(),
												a_material->GetSpecular(), a_material->GetSpecularPower());											
			}
			
			
			t_d3dText = (D3DImage *) a_mesh->GetCurrentTexture();
			t_skinnedMeshEffect->SetObjectTexture(t_d3dText->GetTexture());
			t_skinnedMeshEffect->SetTransformMatrix(*a_transform);
			t_skinnedMesh = (C3DESkinnedMeshContainer*) a_mesh;
			
			t_mesh = t_skinnedMesh->GetMesh();
			
			t_skinnedMeshEffect->SetFrameRootMatrices(t_skinnedMesh->GetPoseMatrix(), t_mesh->GetTotalBones());


			//a_mesh->SetShaderHandlers();
			//FX * t_effect = a_mesh->GetEffect();
			//t_effect->SetTransformMatrix(*a_transform);
			FXManager::GetInstance()->PreRender();	
			//a_mesh->PreRender((Renderer*)this);
			HR(t_xMesh->DrawSubset(subset));
			//a_mesh->PosRender((Renderer*)this);
			FXManager::GetInstance()->PosRender();

			break;
		case EFFECT_WALL:


			t_wallEffect = (PerVertexLightingWallNoFog *)ShaderManager::GetInstance()->GetFXByID(SHADER_LIGHTS_PER_VERTEX_TEXTURES_WALL_NO_FOG_ID);
			

			if(a_material == NULL)
			{
				t_wallEffect->SetObjectMaterials(	a_mesh->GetCurrentMaterial()->GetAmbient(), a_mesh->GetCurrentMaterial()->GetDiffuse(),
											a_mesh->GetCurrentMaterial()->GetSpecular(), a_mesh->GetCurrentMaterial()->GetSpecularPower());											
			}
			else
			{
				t_wallEffect->SetObjectMaterials(	a_material->GetAmbient(), a_material->GetDiffuse(),
												a_material->GetSpecular(), a_material->GetSpecularPower());											
			}

			
			t_image = (D3DImage*) a_mesh->GetCurrentTexture();
			t_wallEffect->SetObjectTexture(t_image->GetTexture());
			t_wallEffect->SetTransformMatrix(*a_transform);
			t_wallEffect->SetAlpha(1.0f);

			FXManager::GetInstance()->PreRender();	
			HR(t_xMesh->DrawSubset(subset));
			FXManager::GetInstance()->PosRender();
			break;
		case EFFECT_TREE:

			HR(D3DRenderer::GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, true));
			HR(D3DRenderer::GetDevice()->SetRenderState(D3DRS_ALPHAREF, 200));
			HR(D3DRenderer::GetDevice()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER));

	
			t_textureOnlyEffect = (TextureOnlyFX *)ShaderManager::GetInstance()->GetFXByID(SHADER_TEXTURE_ONLY_ID);
									
			t_image = (D3DImage*) a_mesh->GetCurrentTexture();
			t_textureOnlyEffect->SetObjectTexture(t_image->GetTexture());
			t_textureOnlyEffect->SetTransformMatrix(*a_transform);
			t_textureOnlyEffect->SetAlpha(1.0f);

			FXManager::GetInstance()->PreRender();	
			HR(t_xMesh->DrawSubset(subset));
			FXManager::GetInstance()->PosRender();

			HR(D3DRenderer::GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, false));
			

			break;
		case EFFECT_TEXTURE_ONLY:

			t_textureOnlyEffect = (TextureOnlyFX *)ShaderManager::GetInstance()->GetFXByID(SHADER_TEXTURE_ONLY_ID);
			
			


			
			t_image = (D3DImage*) a_mesh->GetCurrentTexture();
			t_textureOnlyEffect->SetObjectTexture(t_image->GetTexture());
			t_textureOnlyEffect->SetTransformMatrix(*a_transform);
			t_textureOnlyEffect->SetAlpha(1.0f);

			FXManager::GetInstance()->PreRender();	
			HR(t_xMesh->DrawSubset(subset));
			FXManager::GetInstance()->PosRender();



			break;

		case EFFECT_MOVING_LIGHT:
			t_effect = (PerVertexLighting *)ShaderManager::GetInstance()->GetFXByID(SHADER_LIGHTS_PER_VERTEX_TEXTURES_NO_FOG_ID);
			
			if(a_material == NULL)
			{
				t_effect->SetObjectMaterials(	a_mesh->GetCurrentMaterial()->GetAmbient(), a_mesh->GetCurrentMaterial()->GetDiffuse(),
											a_mesh->GetCurrentMaterial()->GetSpecular(), a_mesh->GetCurrentMaterial()->GetSpecularPower());											
			}
			else
			{
				t_effect->SetObjectMaterials(	a_material->GetAmbient(), a_material->GetDiffuse(),
												a_material->GetSpecular(), a_material->GetSpecularPower());											
			}
			
			t_image = (D3DImage*) a_mesh->GetCurrentTexture();
			t_effect->SetObjectTexture(t_image->GetTexture());
			t_effect->SetTransformMatrix(*a_transform);
			t_effect->SetAlpha(1.0f);

			FXManager::GetInstance()->PreRender();	
			HR(t_xMesh->DrawSubset(subset));
			FXManager::GetInstance()->PosRender();

			break;
		case EFFECT_DIFFUSE_STATIC_LIGHT:
			t_diffuseStaticLightEffect = (DiffuseStaticLight *)ShaderManager::GetInstance()->GetFXByID(SHADER_DIFFUSE_STATIC_LIGHT_ID);
			
			if(a_material == NULL)
			{
				t_diffuseStaticLightEffect->SetObjectMaterials(	a_mesh->GetCurrentMaterial()->GetAmbient(), a_mesh->GetCurrentMaterial()->GetDiffuse(),
											a_mesh->GetCurrentMaterial()->GetSpecular(), a_mesh->GetCurrentMaterial()->GetSpecularPower());											
			}
			else
			{
				t_diffuseStaticLightEffect->SetObjectMaterials(	a_material->GetAmbient(), a_material->GetDiffuse(),
												a_material->GetSpecular(), a_material->GetSpecularPower());											
			}
			
			t_image = (D3DImage*) a_mesh->GetCurrentTexture();
			t_diffuseStaticLightEffect->SetObjectTexture(t_image->GetTexture());
			t_diffuseStaticLightEffect->SetTransformMatrix(*a_transform);
			t_diffuseStaticLightEffect->SetAlpha(1.0f);

			FXManager::GetInstance()->PreRender();	
			HR(t_xMesh->DrawSubset(subset));
			FXManager::GetInstance()->PosRender();

			break;

		case EFFECT_AMBIENT_LIGHT:
			t_ambientLightEffect = (AmbientLightFX *)ShaderManager::GetInstance()->GetFXByID(SHADER_AMBIENT_LIGHT_ID);
			
			if(a_material == NULL)
			{
				t_ambientLightEffect->SetObjectMaterials(	a_mesh->GetCurrentMaterial()->GetAmbient(), a_mesh->GetCurrentMaterial()->GetDiffuse(),
											a_mesh->GetCurrentMaterial()->GetSpecular(), a_mesh->GetCurrentMaterial()->GetSpecularPower());											
			}
			else
			{
				t_ambientLightEffect->SetObjectMaterials(	a_material->GetAmbient(), a_material->GetDiffuse(),
												a_material->GetSpecular(), a_material->GetSpecularPower());											
			}
			
			t_image = (D3DImage*) a_mesh->GetCurrentTexture();
			t_ambientLightEffect->SetObjectTexture(t_image->GetTexture());
			t_ambientLightEffect->SetTransformMatrix(*a_transform);
			t_ambientLightEffect->SetAlpha(1.0f);

			FXManager::GetInstance()->PreRender();	
			HR(t_xMesh->DrawSubset(subset));
			FXManager::GetInstance()->PosRender();

			break;

		case EFFECT_SPECULAR_LIGHT:
			t_specularLightEffect = (SpecularLightFX *)ShaderManager::GetInstance()->GetFXByID(SHADER_SPECULAR_LIGHT_ID);
			
			if(a_material == NULL)
			{
				t_specularLightEffect->SetObjectMaterials(	a_mesh->GetCurrentMaterial()->GetAmbient(), a_mesh->GetCurrentMaterial()->GetDiffuse(),
											a_mesh->GetCurrentMaterial()->GetSpecular(), a_mesh->GetCurrentMaterial()->GetSpecularPower());											
			}
			else
			{
				t_specularLightEffect->SetObjectMaterials(	a_material->GetAmbient(), a_material->GetDiffuse(),
												a_material->GetSpecular(), a_material->GetSpecularPower());											
			}
			
			t_image = (D3DImage*) a_mesh->GetCurrentTexture();
			t_specularLightEffect->SetObjectTexture(t_image->GetTexture());
			t_specularLightEffect->SetTransformMatrix(*a_transform);
			t_specularLightEffect->SetAlpha(1.0f);

			FXManager::GetInstance()->PreRender();	
			HR(t_xMesh->DrawSubset(subset));
			FXManager::GetInstance()->PosRender();

			break;
	}
}



void D3DRenderer::DrawXMesh(D3DMesh * a_mesh)
{	

	//PerVertexLighting * t_auei = static_cast<PerVertexLighting *>(a_mesh->GetEffect());			
	FXManager::GetInstance()->Begin(a_mesh->GetEffect());				

	//int t_totalMaterials = a_mesh->GetMaterials()->size();
	int t_totalMaterials = a_mesh->GetMaterials()->size();
	ID3DXMesh *t_xMesh = a_mesh->GetXMesh();		
	

	for(int j = 0; j < t_totalMaterials; j++)
	{				
		
		//a_mesh->SetCurrentMaterial(a_mesh->GetMaterials()->at(j));
		a_mesh->SetCurrentMaterial((*a_mesh->GetMaterials())[j]);

		
		int t_totalTextures = a_mesh->GetTextures()->size();
		
		if(j < t_totalTextures)
		{			
			//Image *t_image = a_mesh->GetTextures()->at(j);			
			Image *t_image = (*a_mesh->GetTextures())[j];			
			a_mesh->SetCurrentTexture(t_image);
		}
		
		a_mesh->SetShaderHandlers();
		FXManager::GetInstance()->PreRender();	
		a_mesh->PreRender((Renderer*)this);
		HR(t_xMesh->DrawSubset(j));
		a_mesh->PosRender((Renderer*)this);
		FXManager::GetInstance()->PosRender();
	}		
	
	FXManager::GetInstance()->End();

}


void D3DRenderer::DrawTerrainSubMesh(D3DMesh * a_mesh, D3DMesh *a_subMesh)
{	

	//PerVertexLighting * t_auei = static_cast<PerVertexLighting *>(a_mesh->GetEffect());			
	FXManager::GetInstance()->Begin(a_mesh->GetEffect());				

	//int t_totalMaterials = a_mesh->GetMaterials()->size();
	int t_totalMaterials = a_mesh->GetMaterials()->size();

	ID3DXMesh *t_mesh = a_subMesh->GetXMesh();			

	for(int j = 0; j < t_totalMaterials; j++)
	{				
		
		a_mesh->SetCurrentMaterial((*a_mesh->GetMaterials())[j]);

		
		int t_totalTextures = a_mesh->GetTextures()->size();
		
		if(j < t_totalTextures)
		{			
			Image *t_image = (*a_mesh->GetTextures())[j];			
			a_mesh->SetCurrentTexture(t_image);
		}
		
		a_mesh->SetShaderHandlers();
		FXManager::GetInstance()->PreRender();	
		HR(t_mesh->DrawSubset(j));
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
		Mesh *mesh = (*scene->GetMeshesVector())[i];	
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
		Mesh *mesh = (*scene->GetMeshesVector())[i];	
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
	
	IDirect3DIndexBuffer9 * t_indexBuffer = mesh->GetIndexBuffer();
	if(t_indexBuffer)
	{
		HR(m_device->SetIndices(t_indexBuffer));	
	}
	
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
	HR(m_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID));
	

	int numTriangles = mesh->GetIndices()->size() / 3;
	int numVertices = mesh->GetVertices()->size();		
	
	HR(m_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, numVertices, 0, numTriangles));

	FXManager::GetInstance()->PosRender();
	FXManager::GetInstance()->End();
	
}

void D3DRenderer::DrawLine(int aX, int aY, int bX, int bY, int color)
{		
	t_lineVertices[0] = D3DXVECTOR2(aX, aY);
	t_lineVertices[1] = D3DXVECTOR2(bX, bY);
	lpLine->Draw(t_lineVertices, 2, color);
}

void D3DRenderer::DrawRect(int x, int y, int w, int h, int color)
{
	DrawLine(x, y, x + w, y, color);
	DrawLine(x, y, x, y + h, color);
	DrawLine(x, y +h, x + w, y + h, color);
	DrawLine(x + w, y, x + w, y + h, color);
}

void D3DRenderer::DrawFillRect(int x, int y, int w, int h, int color)
{
	for(int i = 0; i < h; i++)
	{
		DrawLine(x, y + i, x + w, y + i, color);
	}
	
	
}

void D3DRenderer::DrawSprite(Sprite *sprite)
{	
	
	
	HR(m_device->SetRenderState(D3DRS_ALPHATESTENABLE, true));
	HR(m_device->SetRenderState(D3DRS_ALPHAREF, 200));
	HR(m_device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER));

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

	HR(m_device->SetRenderState(D3DRS_ALPHATESTENABLE, false));

}

void D3DRenderer::DrawText(Text *a_text)
{	
	
	Font *t_font = a_text->GetFont();
	HR(m_device->SetRenderState(D3DRS_ALPHATESTENABLE, true));
	HR(m_device->SetRenderState(D3DRS_ALPHAREF, 200));
	HR(m_device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER));

	m_sprite->Begin(0);

	
	Image * image = a_text->GetImage();
	D3DImage *tex = static_cast<D3DImage *>(image);	


	int totalChars = a_text->GetTextLength();

	vector<int> * t_widths = t_font->GetWidths();
	vector<int> *t_rectsIndices = a_text->GetRectsIndices();

	float t_x = a_text->GetX();
	for(int i = 0; i < totalChars; i++)
	{
		int rectIndex = (*t_rectsIndices)[i];

		if(i > 0)
		{
			//t_x += (float)(*t_font->GetWidths())[(*a_text->GetRectsIndices())[i-1]];// + (float)(*t_font->GetOffsets())[(*a_text->GetRectsIndices())[i-1]];
			int t_index = (*t_rectsIndices)[i-1];
			if(t_index == Text::TEXT_SPACE || t_index == Text::TEXT_LINE_FEED || t_index == Text::TEXT_INVALID_CHAR)
			{
				t_x += (float)t_font->GetSpacing();;
				
			}
			else
			{
				float t_width = (float)(*t_widths)[t_index];
				t_x += t_width;
			}
			
		}				

		
		m_sprite->Begin(0);
		D3DXMATRIX t_matrix = a_text->GetTransformationMatrix();

		D3DXMatrixTranslation(&t_matrix, t_x, a_text->GetY(), 0.0f);
		//D3DXMatrixRotationZ(&t_matrix, 1.0f);
		m_sprite->SetTransform(&t_matrix);
	
		IDirect3DTexture9 * t = tex->GetTexture();		

		if(rectIndex == Text::TEXT_SPACE || rectIndex == Text::TEXT_LINE_FEED || rectIndex == Text::TEXT_INVALID_CHAR)
		{
			
			m_sprite->Flush();	

			m_sprite->End();
			continue;
		}
		
		RECT src = (*a_text->GetFrameRects())[rectIndex];
		
		m_sprite->Draw(t, &src, 0, 0, a_text->GetColor());

		m_sprite->Flush();	

		m_sprite->End();

	}


	HR(m_device->SetRenderState(D3DRS_ALPHATESTENABLE, false));

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
	static char msg[256];

	//sprintf_s(msg, "FPS: %.4f\n%d\n%d", fps, m_game->hx, m_game->hy);

	sprintf_s(msg, "%shidden objs: %d\nshownobjs: %d", text,this->hidden, this->shown);

	if(!m_font)
	{
		//Load Application Specific resources here...
		D3DXCreateFont(m_device, 18, 0, 0, 1, false,  
				   DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY,
				   DEFAULT_PITCH | FF_DONTCARE, "Arial", &m_font);

	}

	RECT r[] = {{10, 10, 0,0}, {10, 30, 0,0}, {10, 50, 0,0}, {10, 70, 0,0}, {10, 90, 0,0}};
	//m_font->DrawText(NULL, text, -1, &r[0], DT_LEFT | DT_TOP | DT_NOCLIP, 0xff000000);
	m_font->DrawText(NULL, msg, -1, &r[0], DT_LEFT | DT_TOP | DT_NOCLIP, 0xff000000);

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

	
	HR(m_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW));
	HR(m_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID));

#if REAL_HACK

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
	CreateAABB();

	

#if REAL_HACK
	//D3DVERTEXELEMENT9 VertexPosElements[] = 
	//{
	//	{0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
	//	D3DDECL_END()
	//};	
	//HR(m_device->CreateVertexDeclaration(VertexPosElements, &VertexPosHACK::Decl));

	//buildVertexBuffer();
	//buildIndexBuffer();

	
	// The aspect ratio depends on the backbuffer dimensions, which can 
	// possibly change after a reset.  So rebuild the projection matrix.
	buildProjMatrix();
	buildViewMtx();

	

	
#endif

	InitAllVertexDeclarations(m_device);
	HR(m_device->SetRenderState(D3DRS_POINTSPRITEENABLE, true));

	//D3DXMATRIX psysWorld;
	//D3DXMatrixTranslation(&psysWorld, 0.0f, 0.0f, 5.0f);
	//D3DXMatrixTranslation(&mWorld, 0.0f, 0.0f, 5.0f);
	//D3DXMatrixInverse(&mWorldInv, 0, &mWorld);

	
	HRESULT hr = D3DXCreateLine(m_device, &lpLine);
	D3DXVECTOR2 t_vertices[2] = {D3DXVECTOR2(0.0f, 0.0f),D3DXVECTOR2(0.0f, 0.0f)};	

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


void D3DRenderer::CreateAABB()
{

	int vertexSize = 48;
	HR(GetDevice()->CreateVertexBuffer(vertexSize * sizeof(VertexCol), D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED, &m_aabbBuffer, 0));
	VertexCol *v = 0;
	HR(m_aabbBuffer->Lock(0,0,(void**)&v,0));
	

	for (int i = 0; i < vertexSize; i++)
	{
		v[i] = VertexCol(0, 0, 0, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	}
	
	
	HR(m_aabbBuffer->Unlock());

	D3DVERTEXELEMENT9 VertexPosElements[] = 
	{
		{0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0, 12, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0},		
		D3DDECL_END()
	};		

	
	HR(GetDevice()->CreateVertexDeclaration(VertexPosElements, &m_aabbDeclaration));

	
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
	HR(m_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID));
	
	m_device->DrawPrimitive( D3DPT_LINELIST, 0, 3 );
}

void D3DRenderer::DrawAABB(D3DMesh * a_mesh)
{	
	AABB* t_boundingBox = a_mesh->GetBoundingBox();


	D3DXVECTOR3 t_minPoint = t_boundingBox->minPoint;
	D3DXVECTOR3 t_maxPoint = t_boundingBox->maxPoint;

	D3DXMATRIX t_matrix = a_mesh->GetTransformMatrix();

	D3DXVECTOR4 t_min4 = D3DXVECTOR4(t_minPoint, 1.0f);
	D3DXVECTOR4 t_max4 = D3DXVECTOR4(t_maxPoint, 1.0f);

	D3DXVec3Transform(&t_min4, &t_minPoint, &t_matrix);
	D3DXVec3Transform(&t_max4, &t_maxPoint, &t_matrix);

	t_minPoint.x = t_min4.x;
	t_minPoint.y = t_min4.y;
	t_minPoint.z = t_min4.z;

	t_maxPoint.x = t_max4.x;
	t_maxPoint.y = t_max4.y;
	t_maxPoint.z = t_max4.z;

	float t_offset = 0.1f;

	VertexCol *v = 0;
	HR(m_aabbBuffer->Lock(0,0,(void**)&v,0));

	float t_minX = t_minPoint.x - t_offset;
	float t_minY = t_minPoint.y - t_offset;
	float t_minZ = t_minPoint.z - t_offset ;

	float t_maxX = t_maxPoint.x + t_offset;
	float t_maxY = t_maxPoint.y + t_offset;
	float t_maxZ = t_maxPoint.z + t_offset;

	float t_lengthX = t_maxX - t_minX;
	float t_lengthY = t_maxY - t_minY;
	float t_lengthZ = t_maxZ - t_minZ;

	D3DXCOLOR t_color = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	

	
	v[0] = VertexCol(t_minX, t_minY, t_minZ, t_color);
	v[1] = VertexCol(t_minX, t_minY + t_lengthY, t_minZ, t_color);
	
	v[2] = VertexCol(t_minX, t_minY + t_lengthY, t_minZ, t_color);
	v[3] = VertexCol(t_minX + t_lengthX, t_minY + t_lengthY, t_minZ, t_color);
	
	v[4] = VertexCol(t_minX + t_lengthX, t_minY + t_lengthY, t_minZ, t_color);
	v[5] = VertexCol(t_minX + t_lengthX, t_minY , t_minZ, t_color);
	
	v[6] = VertexCol(t_minX + t_lengthX, t_minY , t_minZ, t_color);
	v[7] = VertexCol(t_minX, t_minY, t_minZ, t_color);




	v[8] = VertexCol(t_minX, t_minY, t_minZ, t_color);
	v[9] = VertexCol(t_minX, t_minY , t_minZ + t_lengthZ, t_color);

	v[10] = VertexCol(t_minX, t_minY , t_minZ + t_lengthZ, t_color);
	v[11] = VertexCol(t_minX, t_minY + t_lengthY, t_minZ + t_lengthZ, t_color);

	v[12] = VertexCol(t_minX, t_minY + t_lengthY, t_minZ + t_lengthZ, t_color);
	v[13] = VertexCol(t_minX, t_minY + t_lengthY, t_minZ, t_color);




	v[14] = VertexCol(t_minX, t_minY, t_minZ + t_lengthZ, t_color);
	v[15] = VertexCol(t_minX + t_lengthX, t_minY, t_minZ + t_lengthZ, t_color);

	v[16] = VertexCol(t_minX + t_lengthX, t_minY, t_minZ + t_lengthZ, t_color);
	v[17] = VertexCol(t_minX + t_lengthX, t_minY + t_lengthY, t_minZ + t_lengthZ, t_color);

	v[18] = VertexCol(t_minX + t_lengthX, t_minY + t_lengthY, t_minZ + t_lengthZ, t_color);
	v[19] = VertexCol(t_minX , t_minY + t_lengthY, t_minZ + t_lengthZ, t_color);



	v[20] = VertexCol(t_minX + t_lengthX, t_minY + t_lengthY, t_minZ + t_lengthZ, t_color);
	v[21] = VertexCol(t_minX + t_lengthX, t_minY + t_lengthY, t_minZ , t_color);

	v[22] = VertexCol(t_minX + t_lengthX, t_minY , t_minZ + t_lengthZ, t_color);
	v[23] = VertexCol(t_minX + t_lengthX, t_minY , t_minZ , t_color);
	
	
	
	HR(m_aabbBuffer->Unlock());


	HR(m_device->SetStreamSource(0, m_aabbBuffer, 0, sizeof(VertexCol)));	
	HR(m_device->SetVertexDeclaration(m_aabbDeclaration));

	D3DCamera *cam = (D3DCamera *) m_camera;
	
	D3DXMATRIX W;
	D3DXMatrixIdentity(&W);
	HR(m_device->SetTransform(D3DTS_WORLD, &W));
	
	HR(m_device->SetTransform(D3DTS_VIEW, &cam->GetMatrix()));
	HR(m_device->SetTransform(D3DTS_PROJECTION, &m_proj));
	HR(m_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID));
	
	m_device->DrawPrimitive( D3DPT_LINELIST, 0, 12 );
}

void D3DRenderer::DrawBox(float minX, float minY, float minZ, float maxX, float maxY, float maxZ, D3DXMATRIX a_matrix)
{		
	
	VertexCol *v = 0;
	HR(m_aabbBuffer->Lock(0,0,(void**)&v,0));

	D3DXVECTOR3 minPoint;
	minPoint.x = minX;
	minPoint.y = minY;
	minPoint.z = minZ;

	D3DXVECTOR3 maxPoint;

	maxPoint.x = maxX;
	maxPoint.y = maxY;
	maxPoint.z = maxZ;

	D3DXVECTOR3 t_0 = minPoint;
	D3DXVECTOR3 t_1 = D3DXVECTOR3(minPoint.x, minPoint.y, maxPoint.z);
	D3DXVECTOR3 t_2 = D3DXVECTOR3(maxPoint.x, minPoint.y, maxPoint.z);
	D3DXVECTOR3 t_3 = D3DXVECTOR3(maxPoint.x, minPoint.y, minPoint.z);

	D3DXVECTOR3 t_4 = D3DXVECTOR3(minPoint.x, maxPoint.y, minPoint.z);
	D3DXVECTOR3 t_5 = D3DXVECTOR3(minPoint.x, maxPoint.y, maxPoint.z);
	D3DXVECTOR3 t_6 = maxPoint;
	D3DXVECTOR3 t_7 = D3DXVECTOR3(maxPoint.x, maxPoint.y, minPoint.z);

	
	D3DXVECTOR4 t_quat0;
	D3DXVECTOR4 t_quat1;
	D3DXVECTOR4 t_quat2;
	D3DXVECTOR4 t_quat3;
	D3DXVECTOR4 t_quat4;
	D3DXVECTOR4 t_quat5;
	D3DXVECTOR4 t_quat6;
	D3DXVECTOR4 t_quat7;
	//D3DXMATRIX t_matrix = a_mesh->GetTransformMatrix();
	D3DXMATRIX t_matrix = a_matrix;
	D3DXVec3Transform(&t_quat0, &t_0, &t_matrix);
	D3DXVec3Transform(&t_quat1, &t_1, &t_matrix);
	D3DXVec3Transform(&t_quat2, &t_2, &t_matrix);
	D3DXVec3Transform(&t_quat3, &t_3, &t_matrix);
	D3DXVec3Transform(&t_quat4, &t_4, &t_matrix);
	D3DXVec3Transform(&t_quat5, &t_5, &t_matrix);
	D3DXVec3Transform(&t_quat6, &t_6, &t_matrix);
	D3DXVec3Transform(&t_quat7, &t_7, &t_matrix);
	
	

	t_0.x = t_quat0.x;
	t_0.y = t_quat0.y;
	t_0.z = t_quat0.z;

	t_1.x = t_quat1.x;
	t_1.y = t_quat1.y;
	t_1.z = t_quat1.z;

	t_2.x = t_quat2.x;
	t_2.y = t_quat2.y;
	t_2.z = t_quat2.z;

	t_3.x = t_quat3.x;
	t_3.y = t_quat3.y;
	t_3.z = t_quat3.z;

	t_4.x = t_quat4.x;
	t_4.y = t_quat4.y;
	t_4.z = t_quat4.z;

	t_5.x = t_quat5.x;
	t_5.y = t_quat5.y;
	t_5.z = t_quat5.z;

	t_6.x = t_quat6.x;
	t_6.y = t_quat6.y;
	t_6.z = t_quat6.z;
	
	t_7.x = t_quat7.x;
	t_7.y = t_quat7.y;
	t_7.z = t_quat7.z;


	D3DXCOLOR t_color = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	
	D3DXVECTOR3 t_vertices[8];
	t_vertices[0] = t_0;
	t_vertices[1] = t_1;
	t_vertices[2] = t_2;
	t_vertices[3] = t_3;
	t_vertices[4] = t_4;
	t_vertices[5] = t_5;
	t_vertices[6] = t_6;
	t_vertices[7] = t_7;

	v[0] = VertexCol(t_vertices[0].x, t_vertices[0].y, t_vertices[0].z, t_color);
	v[1] = VertexCol(t_vertices[1].x, t_vertices[1].y, t_vertices[1].z, t_color);

	v[2] = VertexCol(t_vertices[1].x, t_vertices[1].y, t_vertices[1].z, t_color);
	v[3] = VertexCol(t_vertices[2].x, t_vertices[2].y, t_vertices[2].z, t_color);

	v[4] = VertexCol(t_vertices[2].x, t_vertices[2].y, t_vertices[2].z, t_color);
	v[5] = VertexCol(t_vertices[3].x, t_vertices[3].y, t_vertices[3].z, t_color);

	v[6] = VertexCol(t_vertices[3].x, t_vertices[3].y, t_vertices[3].z, t_color);
	v[7] = VertexCol(t_vertices[0].x, t_vertices[0].y, t_vertices[0].z, t_color);

	v[8] = VertexCol(t_vertices[4].x, t_vertices[4].y, t_vertices[4].z, t_color);
	v[9] = VertexCol(t_vertices[5].x, t_vertices[5].y, t_vertices[5].z, t_color);

	v[10] = VertexCol(t_vertices[5].x, t_vertices[5].y, t_vertices[5].z, t_color);
	v[11] = VertexCol(t_vertices[6].x, t_vertices[6].y, t_vertices[6].z, t_color);

	v[12] = VertexCol(t_vertices[6].x, t_vertices[6].y, t_vertices[6].z, t_color);
	v[13] = VertexCol(t_vertices[7].x, t_vertices[7].y, t_vertices[7].z, t_color);

	v[14] = VertexCol(t_vertices[7].x, t_vertices[7].y, t_vertices[7].z, t_color);
	v[15] = VertexCol(t_vertices[4].x, t_vertices[4].y, t_vertices[4].z, t_color);

	v[16] = VertexCol(t_vertices[0].x, t_vertices[0].y, t_vertices[0].z, t_color);
	v[17] = VertexCol(t_vertices[4].x, t_vertices[4].y, t_vertices[4].z, t_color);

	v[18] = VertexCol(t_vertices[1].x, t_vertices[1].y, t_vertices[1].z, t_color);
	v[19] = VertexCol(t_vertices[5].x, t_vertices[5].y, t_vertices[5].z, t_color);

	v[20] = VertexCol(t_vertices[2].x, t_vertices[2].y, t_vertices[2].z, t_color);
	v[21] = VertexCol(t_vertices[6].x, t_vertices[6].y, t_vertices[6].z, t_color);

	v[22] = VertexCol(t_vertices[3].x, t_vertices[3].y, t_vertices[3].z, t_color);
	v[23] = VertexCol(t_vertices[7].x, t_vertices[7].y, t_vertices[7].z, t_color);
	
	
	
	HR(m_aabbBuffer->Unlock());
	HR(m_device->SetStreamSource(0, m_aabbBuffer, 0, sizeof(VertexCol)));	
	HR(m_device->SetVertexDeclaration(m_aabbDeclaration));

	D3DCamera *cam = (D3DCamera *) m_camera;
	
	D3DXMATRIX W;
	D3DXMatrixIdentity(&W);
	HR(m_device->SetTransform(D3DTS_WORLD, &W));
	
	HR(m_device->SetTransform(D3DTS_VIEW, &cam->GetMatrix()));
	HR(m_device->SetTransform(D3DTS_PROJECTION, &m_proj));
	HR(m_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID));
	
	m_device->DrawPrimitive( D3DPT_LINELIST, 0, 12 );
	
}


void D3DRenderer::DrawOBB(D3DMesh * a_mesh, D3DXMATRIX a_matrix)
{
	VertexCol *v = 0;
	HR(m_aabbBuffer->Lock(0,0,(void**)&v,0));

	D3DXVECTOR3 minPoint = a_mesh->GetBoundingBox()->minPoint;
	D3DXVECTOR3 maxPoint = a_mesh->GetBoundingBox()->maxPoint;

	D3DXVECTOR3 t_0 = minPoint;
	D3DXVECTOR3 t_1 = D3DXVECTOR3(minPoint.x, minPoint.y, maxPoint.z);
	D3DXVECTOR3 t_2 = D3DXVECTOR3(maxPoint.x, minPoint.y, maxPoint.z);
	D3DXVECTOR3 t_3 = D3DXVECTOR3(maxPoint.x, minPoint.y, minPoint.z);

	D3DXVECTOR3 t_4 = D3DXVECTOR3(minPoint.x, maxPoint.y, minPoint.z);
	D3DXVECTOR3 t_5 = D3DXVECTOR3(minPoint.x, maxPoint.y, maxPoint.z);
	D3DXVECTOR3 t_6 = maxPoint;
	D3DXVECTOR3 t_7 = D3DXVECTOR3(maxPoint.x, maxPoint.y, minPoint.z);

	
	D3DXVECTOR4 t_quat0;
	D3DXVECTOR4 t_quat1;
	D3DXVECTOR4 t_quat2;
	D3DXVECTOR4 t_quat3;
	D3DXVECTOR4 t_quat4;
	D3DXVECTOR4 t_quat5;
	D3DXVECTOR4 t_quat6;
	D3DXVECTOR4 t_quat7;
	//D3DXMATRIX t_matrix = a_mesh->GetTransformMatrix();
	D3DXMATRIX t_matrix = a_matrix;
	D3DXVec3Transform(&t_quat0, &t_0, &t_matrix);
	D3DXVec3Transform(&t_quat1, &t_1, &t_matrix);
	D3DXVec3Transform(&t_quat2, &t_2, &t_matrix);
	D3DXVec3Transform(&t_quat3, &t_3, &t_matrix);
	D3DXVec3Transform(&t_quat4, &t_4, &t_matrix);
	D3DXVec3Transform(&t_quat5, &t_5, &t_matrix);
	D3DXVec3Transform(&t_quat6, &t_6, &t_matrix);
	D3DXVec3Transform(&t_quat7, &t_7, &t_matrix);
	
	

	t_0.x = t_quat0.x;
	t_0.y = t_quat0.y;
	t_0.z = t_quat0.z;

	t_1.x = t_quat1.x;
	t_1.y = t_quat1.y;
	t_1.z = t_quat1.z;

	t_2.x = t_quat2.x;
	t_2.y = t_quat2.y;
	t_2.z = t_quat2.z;

	t_3.x = t_quat3.x;
	t_3.y = t_quat3.y;
	t_3.z = t_quat3.z;

	t_4.x = t_quat4.x;
	t_4.y = t_quat4.y;
	t_4.z = t_quat4.z;

	t_5.x = t_quat5.x;
	t_5.y = t_quat5.y;
	t_5.z = t_quat5.z;

	t_6.x = t_quat6.x;
	t_6.y = t_quat6.y;
	t_6.z = t_quat6.z;
	
	t_7.x = t_quat7.x;
	t_7.y = t_quat7.y;
	t_7.z = t_quat7.z;


	D3DXCOLOR t_color = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	
	D3DXVECTOR3 t_vertices[8];
	t_vertices[0] = t_0;
	t_vertices[1] = t_1;
	t_vertices[2] = t_2;
	t_vertices[3] = t_3;
	t_vertices[4] = t_4;
	t_vertices[5] = t_5;
	t_vertices[6] = t_6;
	t_vertices[7] = t_7;

	v[0] = VertexCol(t_vertices[0].x, t_vertices[0].y, t_vertices[0].z, t_color);
	v[1] = VertexCol(t_vertices[1].x, t_vertices[1].y, t_vertices[1].z, t_color);

	v[2] = VertexCol(t_vertices[1].x, t_vertices[1].y, t_vertices[1].z, t_color);
	v[3] = VertexCol(t_vertices[2].x, t_vertices[2].y, t_vertices[2].z, t_color);

	v[4] = VertexCol(t_vertices[2].x, t_vertices[2].y, t_vertices[2].z, t_color);
	v[5] = VertexCol(t_vertices[3].x, t_vertices[3].y, t_vertices[3].z, t_color);

	v[6] = VertexCol(t_vertices[3].x, t_vertices[3].y, t_vertices[3].z, t_color);
	v[7] = VertexCol(t_vertices[0].x, t_vertices[0].y, t_vertices[0].z, t_color);

	v[8] = VertexCol(t_vertices[4].x, t_vertices[4].y, t_vertices[4].z, t_color);
	v[9] = VertexCol(t_vertices[5].x, t_vertices[5].y, t_vertices[5].z, t_color);

	v[10] = VertexCol(t_vertices[5].x, t_vertices[5].y, t_vertices[5].z, t_color);
	v[11] = VertexCol(t_vertices[6].x, t_vertices[6].y, t_vertices[6].z, t_color);

	v[12] = VertexCol(t_vertices[6].x, t_vertices[6].y, t_vertices[6].z, t_color);
	v[13] = VertexCol(t_vertices[7].x, t_vertices[7].y, t_vertices[7].z, t_color);

	v[14] = VertexCol(t_vertices[7].x, t_vertices[7].y, t_vertices[7].z, t_color);
	v[15] = VertexCol(t_vertices[4].x, t_vertices[4].y, t_vertices[4].z, t_color);

	v[16] = VertexCol(t_vertices[0].x, t_vertices[0].y, t_vertices[0].z, t_color);
	v[17] = VertexCol(t_vertices[4].x, t_vertices[4].y, t_vertices[4].z, t_color);

	v[18] = VertexCol(t_vertices[1].x, t_vertices[1].y, t_vertices[1].z, t_color);
	v[19] = VertexCol(t_vertices[5].x, t_vertices[5].y, t_vertices[5].z, t_color);

	v[20] = VertexCol(t_vertices[2].x, t_vertices[2].y, t_vertices[2].z, t_color);
	v[21] = VertexCol(t_vertices[6].x, t_vertices[6].y, t_vertices[6].z, t_color);

	v[22] = VertexCol(t_vertices[3].x, t_vertices[3].y, t_vertices[3].z, t_color);
	v[23] = VertexCol(t_vertices[7].x, t_vertices[7].y, t_vertices[7].z, t_color);
	
	
	
	HR(m_aabbBuffer->Unlock());
	HR(m_device->SetStreamSource(0, m_aabbBuffer, 0, sizeof(VertexCol)));	
	HR(m_device->SetVertexDeclaration(m_aabbDeclaration));

	D3DCamera *cam = (D3DCamera *) m_camera;
	
	D3DXMATRIX W;
	D3DXMatrixIdentity(&W);
	HR(m_device->SetTransform(D3DTS_WORLD, &W));
	
	HR(m_device->SetTransform(D3DTS_VIEW, &cam->GetMatrix()));
	HR(m_device->SetTransform(D3DTS_PROJECTION, &m_proj));
	HR(m_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID));
	
	m_device->DrawPrimitive( D3DPT_LINELIST, 0, 12 );

}

void D3DRenderer::Reset()
{

}


void D3DRenderer::Clear()
{		
	//m_device->Clear( 0L, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, 0xff666666, 1.0f, 0L );
	m_device->Clear( 0L, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, 0xff666666, 1.0f, 0L );
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


#if REAL_HACK
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

void D3DRenderer::GetPickingRay(const D3DXMATRIX *worldMatrix, D3DXVECTOR3 *pOutOrigin, D3DXVECTOR3 *pOutDir, int mouseX, int mouseY)
{
	
	D3DXMATRIX worldViewInverse;//, worldMatrix;
		
	//projectionMatrix = m_proj;
	//viewMatrix = (D3DCamera*)m_camera->GetMatrix();
	
	float width = (float)m_d3dpp.BackBufferWidth;
	float height = (float)m_d3dpp.BackBufferHeight;
	
	float angle_x = (((2.0f * mouseX) / width) - 1.0f) / m_proj(0,0);
	float angle_y = (((-2.0f * mouseY) / height) + 1.0f) / m_proj(1,1); 
			
	*pOutOrigin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	*pOutDir = D3DXVECTOR3(angle_x, angle_y, 1.0f);


	D3DCamera *t_camera = (D3DCamera*)m_camera;
	D3DXMATRIX t_matrix = t_camera->GetMatrix();
	D3DXMATRIX m = *worldMatrix * t_matrix;
	D3DXMatrixInverse(&worldViewInverse, 0, &m);
	
	D3DXVec3TransformCoord(pOutOrigin, pOutOrigin, &worldViewInverse);
	D3DXVec3TransformNormal(pOutDir, pOutDir, &worldViewInverse);
	D3DXVec3Normalize(pOutDir, pOutDir);	
}

bool D3DRenderer::IsMousePicked(D3DMesh *a_mesh, int mouseX, int mouseY)
{
	D3DXVECTOR3 t_origin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 t_dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	D3DXMATRIX t_transformMatrix = a_mesh->GetTransformMatrix();

	GetPickingRay(&t_transformMatrix, &t_origin, &t_dir, mouseX, mouseY);

	BOOL hit = 0;
	DWORD faceIndex = -1;
	float u = 0.0f;
	float v = 0.0f;
	float dist = 0.0f;
	ID3DXBuffer* allhits = 0;
	DWORD numHits = 0;

	
	HR(D3DXIntersect(a_mesh->GetXMesh(), &t_origin, &t_dir, &hit,
		&faceIndex, &u, &v, &dist, &allhits, &numHits));
	ReleaseCOM(allhits);

	return hit;

}

