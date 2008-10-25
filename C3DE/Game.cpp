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
	delete m_testScene;
	delete m_sprite;
	delete m_button;
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

	
	//renderer->DrawMesh(m_testMesh);
	renderer->DrawScene(m_testScene);
	//renderer->DrawMesh(m_grid);
	renderer->DrawSprite(m_button);
	renderer->DrawSprite((Sprite *)m_sprite);
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
	if(key == 1)
	{
		m_application->Quit();
	}
	else if(key == 200)
	{
		m_cameraHeight += (0.025f * m_deltaTime);
		
	}
	else if(key == 208)
	{
		m_cameraHeight -= (0.025f * m_deltaTime);
		
	}	
	else if(key == 205)
	{
		
	}
	else if(key == 203)
	{
		
	}
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
}

void Game::InitializeMeshes()
{
	m_testMesh = new Cube();
	Material *t_material = new Material(	D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),
										D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f), 16.0f);
	m_testMesh->SetMaterial(t_material);
	CreateMeshBuffers(m_testMesh);
	m_grid = new Grid(100, 100, 0.2f, 0.2f);

	Material *t_material2 = new Material(	D3DXCOLOR(0.0f, 0.0f, 1.0f,1.0f),D3DXCOLOR(0.0f, 0.0f, 1.0f,1.0f),
										D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f), 16.0f);
	m_grid->SetMaterial(t_material);
	CreateMeshBuffers(m_grid);

	m_testScene = new DefaultScene1();

	m_mirror = new PlanarMirror();
	m_mirror->SetMaterial(t_material);
	CreateMeshBuffers((D3DMesh * )m_mirror);

	m_mirror->SetPosition(2.0f, 2.0f, 2.0f);

	
	//m_plane = new Plane(100, 100, 0.2f, 0.2f);
	m_plane = new Plane(20.0f, 20.0f);
	m_plane->SetMaterial(t_material);
	CreateMeshBuffers(m_plane);
	
	
	m_cube = new Cube2();
	Material *t_material3 = new Material(	D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),
										D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f), 16.0f);
	m_cube->SetMaterial(t_material3);
	CreateMeshBuffers(m_cube);

	
	
	//m_testScene->AddMirror((Mirror *)m_mirror);	
	//m_testScene->AddMesh((Mesh*)m_cube);
	//m_testScene->AddMesh((Mesh*)m_grid);	
	m_testScene->AddMesh((Mesh*)m_testMesh);
	m_testScene->AddMesh((Mesh*)m_plane);
	

	m_testScene->Initialize();


	
}


void Game::OnKeyUp(int key)
{
	
}
