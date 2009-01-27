#include "Game.h"
#include "ShaderManager.h"
#include "D3DCamera.h"
#include "D3DRenderer.h"


//THIS CLASS CAN'T OVERRIDE THE NEW OPERATOR OR IT WILL SCREW UP ALL DIRECTX DRAWING
//#include "DebugMemory.h"


using namespace std;

Game::Game(Application * app)
{
	m_application = app;

	IDirect3DTexture9 * t = ResourceManager::GetInstance()->GetImageByID(IMAGE_EXPLOSION_ID);
	D3DImage *image = new D3DImage(t);				

	t = ResourceManager::GetInstance()->GetImageByID(IMAGE_BUTTON_ID);
	D3DImage *image2 = new D3DImage(t);			
	m_sprite = new D3DSprite(image, 64, 64, 30, 6, 5, 50);

	m_sprite->SetX(50);
	m_sprite->SetY(50);

	m_speed = 1;
	m_yspeed = 1;

	m_cameraRadius = 10.0f;
	m_cameraRotation = 1.2 * D3DX_PI;
	m_cameraHeight = 5.0f;

	m_cameraHeightIncrease = 0.0f;

	m_renderer = app->GetRenderer();

	//CreateTestMesh();
	InitializeMeshes();

	vector<RECT> *frames = new vector<RECT>;
	RECT r;
	r.left = 0;
	r.right = 255;
	r.top = 0;
	r.bottom = 85;
	frames->push_back(r);
	r.left = 0;
	r.right = 256;
	r.top = 85;
	r.bottom = 170;
	frames->push_back(r);
	r.left = 0;
	r.right = 255;
	r.top = 170;
	r.bottom = 255;
	frames->push_back(r);

	
	r.left = 0;
	r.right = 256;
	r.top = 0;
	r.bottom = 85;

	
	m_button = new Button(image2, frames, r);
	m_button->SetX(50);
	m_button->SetY(340);

	m_button->AddListener(this);

	
	hx = 0;
	hy = 0;
	
}

void Game::OnButtonDown(Button *down)
{
	int khgfd = 987;
}

void Game::OnButtonUp(Button *button)
{
	int otrte= 987;
}

void Game::OnButtonOver(Button *button)
{
	int hjsfs = 9874324;
}

void Game::SetInputer(DirectInput *inputer)
{
	m_inputer = inputer;
	m_inputer->AddMouseListener((MouseListener*)m_button);
}

Game::~Game()
{
	//delete m_testScene;
	delete m_sprite;
	delete m_button;


#if 1
	//delete m_testMesh;
	
	//delete m_grid;

	
	//delete m_plane ;

	//delete m_pivot;
	
	

	//delete m_wall;

	//delete m_mirror;
	
	
	
	//delete m_shadowSurface;
#endif
}

void Game::Update(int deltaTime)
{
	
	//m_sprite->SetX(m_sprite->GetX() + m_speed);
	//m_sprite->SetY(m_sprite->GetY() + m_yspeed);

	if(m_sprite->GetX() > 640 || m_sprite->GetX() < 0)
	{
		m_speed = m_speed * -1;
	}

	if(m_sprite->GetY() > 480 || m_sprite->GetY() < 0)
	{
		m_yspeed = m_yspeed * -1;
	}
	m_sprite->Update(deltaTime);

	m_deltaTime = deltaTime;

	m_testScene->Update(deltaTime);

	//m_testMesh->Update(1);

	//m_grid->Update(10);
	
}




void Game::Render(Renderer *renderer)
{
	//

	D3DCamera * cam = (D3DCamera *)renderer->GetCamera();
	float x = m_cameraRadius * cosf(m_cameraRotation);
	float z =  m_cameraRadius * sinf(m_cameraRotation);
	cam->SetPosition(x, m_cameraHeight, z);

	
	renderer->DrawScene(m_testScene);
	renderer->DrawSprite(m_button);
	renderer->DrawSprite((Sprite *)m_sprite);
	static_cast<D3DRenderer *>(renderer)->DrawAxis();

	
}

void Game::OnMouseDown(int button, int x , int y)
{
	int fdfd = 878;
}

void Game::OnMouseUp(int button, int x, int y)
{
	int moueskfd = button;
}

void Game::OnMouseMove(int x, int y, int dx, int dy)
{

	m_cameraRotation += dx / 50.0f;
	m_cameraRadius += dy / 50.0f;
	if(fabsf(m_cameraRotation) >= 2.0f * D3DX_PI)
		m_cameraRotation = 0.0f;

	if(m_cameraRadius < 5.0f)
		m_cameraRadius = 5.0f;

	m_sprite->SetX(x);
	m_sprite->SetY(y);

	hx = x;
	hy = y;

}


void Game::OnKeyDown(int key)
{

	
	float step = 0.1f;
	Mesh * target = (Mesh*)m_dwarf;
	//Mesh * target = (Mesh*)m_skinMesh;
	if(key == 1)
	{
		m_application->Quit();
	}

	

#if 0
	else if(key == 200)
	{		
		target->Scale(target->GetXScale(), target->GetYScale(), target->GetZScale() - step);		
		
		
	}
	else if(key == 208)
	{		
		target->Scale(target->GetXScale(), target->GetYScale(), target->GetZScale() + step);		
	}	
	else if(key == 205)
	{
		target->Scale(target->GetXScale(), target->GetYScale() - step, target->GetZScale());
	}
	else if(key == 203)
	{
		target->Scale(target->GetXScale(), target->GetYScale() + step, target->GetZScale());
	}
	else if(key == 17)
	{
		target->Scale(target->GetXScale() + step, target->GetYScale(), target->GetZScale());
	}
	else if(key == 31)
	{
		target->Scale(target->GetXScale() - step, target->GetYScale(), target->GetZScale());
	}
#endif
#if 0
	else if(key == 200)
	{		
		target->SetPosition(target->GetX(), target->GetY(), target->GetZ() - step);		
		
		
	}
	else if(key == 208)
	{		
		target->SetPosition(target->GetX(), target->GetY(), target->GetZ() + step);		
	}	
	else if(key == 205)
	{
		target->SetPosition(target->GetX(), target->GetY() - step, target->GetZ());
	}
	else if(key == 203)
	{
		target->SetPosition(target->GetX(), target->GetY() + step, target->GetZ());
	}
	else if(key == 17)
	{
		target->SetPosition(target->GetX() + step, target->GetY(), target->GetZ());
	}
	else if(key == 31)
	{
		target->SetPosition(target->GetX() - step, target->GetY(), target->GetZ());
	}
#endif
#if 1
	else if(key == 200)
	{		
		target->Rotate(target->GetRotationX(), target->GetRotationY(), target->GetRotationZ() - step);				
		
	}
	else if(key == 208)
	{		
		target->Rotate(target->GetRotationX(), target->GetRotationY(), target->GetRotationZ() + step);		
	}	
	else if(key == 205)
	{
		target->Rotate(target->GetRotationX(), target->GetRotationY() - step, target->GetRotationZ());
	}
	else if(key == 203)
	{
		target->Rotate(target->GetRotationX(), target->GetRotationY() + step, target->GetRotationZ());
	}
	else if(key == 17)
	{
		target->Rotate(target->GetRotationX() + step, target->GetRotationY(), target->GetRotationZ());
	}
	else if(key == 31)
	{
		target->Rotate(target->GetRotationX() - step, target->GetRotationY(), target->GetRotationZ());
	}
#endif
}

void Game::CreateMeshBuffers(D3DMesh *mesh)
{
	
	
	D3DRenderer *renderer = (D3DRenderer *) m_renderer;
	
	//indices
	IDirect3DIndexBuffer9 *ib;

	int indicesSize = mesh->GetIndices()->size();
	
	HR(renderer->GetDevice()->CreateIndexBuffer(indicesSize * sizeof(WORD), D3DUSAGE_WRITEONLY,
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
	HR(renderer->GetDevice()->CreateVertexBuffer(vertexSize * mesh->GetVertexSize(), D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED, &vb, 0));
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
	HR(renderer->GetDevice()->CreateVertexDeclaration(VertexPosElements, &Decl));

	mesh->SetBuffers(vb, ib);
	mesh->SetVertexDeclaration(Decl);

	//mesh->Translate(0.0f, 0.0f, 0.0f);
	mesh->CreateXMesh(((D3DRenderer *)m_renderer)->GetDevice());
}

void Game::InitializeMeshes()
{
	
#if 0
	m_testMesh = new Cube();
	Material *t_material = new Material(	D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),
										D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f), 16.0f);
	//m_testMesh->SetMaterial(t_material);
	CreateMeshBuffers(m_testMesh);
	m_grid = new Grid(100, 100, 0.2f, 0.2f);

	Material *t_material2 = new Material(	D3DXCOLOR(0.0f, 0.0f, 1.0f,1.0f),D3DXCOLOR(0.0f, 0.0f, 1.0f,1.0f),
										D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f), 16.0f);
	//m_grid->SetMaterial(t_material);
	CreateMeshBuffers(m_grid);

	m_testScene = new DefaultScene1();

	

	//m_mirror->SetPosition(2.0f, 2.0f, 2.0f);

	
	//m_plane = new Plane(100, 100, 0.2f, 0.2f);
	m_plane = new Plane(20.0f, 20.0f);
	//m_plane->SetMaterial(t_material);
	CreateMeshBuffers(m_plane);

	m_pivot = new Pivot();
	//m_pivot->SetMaterial(t_material);
	CreateMeshBuffers(m_pivot);
	
	
	m_cube = new Cube();
	Material *t_material3 = new Material(	D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),
										D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f), 16.0f);
	//m_cube->SetMaterial(t_material3);
	m_cube->AddMaterial(t_material);
	CreateMeshBuffers(m_cube);

	//m_skinnedCube = new SkinnedCube();
	//m_skinnedCube->SetMaterial(t_material3);
	//CreateMeshBuffers(m_skinnedCube);

	m_wall = new Wall();
	//m_wall->SetMaterial(t_material3);
	m_wall->SetPosition(0.0f, 0.0f, 0.0f);
	CreateMeshBuffers(m_wall);

	m_mirror = new PlanarMirror(m_wall);

	//m_testMesh->SetPosition(0.0f, -5.0f, 0.0f);
	
	m_testMesh->SetPosition(0.0f, 3.0f, -6.0f);

	//m_cube->SetPosition(0.0f, 3.0f, -3.0f);

	//m_cube->CreateXMesh(((D3DRenderer *)m_renderer)->GetDevice());
	
	m_shadowSurface = new PlanarShadowSurface(m_plane); 
	//m_cube->SetPosition(0.0f, 3.0f, -3.0f);
	//m_testScene->AddMesh(m_wall);
	//m_testScene->AddMirror((Mirror *)m_mirror);	
	//m_testScene->AddMesh((Mesh*)m_cube);
	//m_testScene->AddMesh((Mesh*)m_grid);	
	//m_testScene->AddMesh((Mesh*)m_testMesh);
	//m_testScene->AddMesh((Mesh*)m_plane);
	
	//m_testScene->AddMesh(m_plane);
	//m_testScene->AddMesh(m_wall);
	//m_testScene->AddMesh(m_pivot);
	//m_testScene->AddShadowSurface(m_shadowSurface);
	
	//m_testScene->AddMesh(m_skinnedCube);

	m_dwarf = new Dwarf();
	//m_dwarf->SetMaterial(t_material3);
	//m_dwarf->LoadFromXFile(ResourceManager::GetInstance()->GetMeshFilenameByID(MESH_DWARF_ID), ((D3DRenderer*)m_renderer)->GetDevice());
	m_dwarf->LoadFromXFile(ResourceManager::GetInstance()->GetMeshFilenameByID(MESH_SWIMMER_ID), ((D3DRenderer*)m_renderer)->GetDevice());
	//m_dwarf->LoadFromXFile("Meshes/auei.x", ((D3DRenderer*)m_renderer)->GetDevice());
	//m_dwarf->LoadFromXFile("Meshes/picles.x", ((D3DRenderer*)m_renderer)->GetDevice());
	//m_dwarf->LoadFromXFile(ResourceManager::GetInstance()->GetMeshFilenameByID(MESH_TINY_ANIM_ID), ((D3DRenderer*)m_renderer)->GetDevice());

	
	//m_dwarf->SetD3DTexture(ResourceManager::GetInstance()->GetImageByID(IMAGE_SWIMMER_SKIN_ID));
	D3DImage *t_image = new D3DImage(ResourceManager::GetInstance()->GetImageByID(IMAGE_SWIMMER_SKIN_ID));
	m_dwarf->AddTexture((Image*)t_image);
	m_dwarf->Scale(2.0f, 2.0f, 2.0f);
	
	m_testScene->AddMesh(m_dwarf);
	//m_testScene->AddMesh(m_cube);

	//m_skinMesh = new D3DSkinnedMesh("Meshes/tiny.x",  ((D3DRenderer*)m_renderer)->GetDevice());
	//m_skinMesh = new WomanMesh();
	//
	
	//m_skinMesh->LoadFromXFile("Meshes/tiny.x",  ((D3DRenderer*)m_renderer)->GetDevice());
	//m_skinMesh->LoadFromXFile(ResourceManager::GetInstance()->GetMeshFilenameByID(MESH_SWIMMER_ID),  ((D3DRenderer*)m_renderer)->GetDevice());
	
	//m_skinMesh->Scale(0.02f, 0.02f, 0.02f);
	//m_testScene->AddMesh(m_skinMesh);
	m_testScene->Initialize();

#endif

	m_testScene = new DefaultScene1();	

	m_testMesh = new Cube();
	Material *t_material = new Material(	D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),
										D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f), 16.0f);
	m_testMesh->AddMaterial(t_material);
	
	CreateMeshBuffers(m_testMesh);


	m_testScene->AddMesh(m_testMesh);

	Grid* auei = new Grid(50,50,1.0f, 1.0f);
	auei->AddMaterial(t_material);
	CreateMeshBuffers(auei);
	m_testScene->AddMesh(auei);


	m_dwarf = new Dwarf();
	m_dwarf->LoadFromXFile(ResourceManager::GetInstance()->GetMeshFilenameByID(MESH_SWIMMER_ID), ((D3DRenderer*)m_renderer)->GetDevice());
	
	D3DImage *t_image = new D3DImage(ResourceManager::GetInstance()->GetImageByID(IMAGE_SWIMMER_SKIN_ID));
	m_dwarf->AddTexture((Image*)t_image);
	m_dwarf->Scale(2.0f, 2.0f, 2.0f);
	
	m_dwarf->SetPosition(15.0f, 5.0f, 0.0f);
	m_testScene->AddMesh(m_dwarf);
	
	m_testScene->Initialize();
	
}


void Game::OnKeyUp(int key)
{
	
}
