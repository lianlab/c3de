#include "Game.h"
//#include "DebugMemory.h"
#include "D3DCamera.h"
#include "D3DRenderer.h"

using namespace std;

Game::Game(Application * app)
{
	m_application = app;

	IDirect3DTexture9 * t = ResourceManager::GetInstance()->GetImageByID(IMAGE_EXPLOSION_ID);
	D3DImage *image = new D3DImage(t);				
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

	CreateTestMesh();

	vector<RECT> *frames = new vector<RECT>;
	RECT r;
	r.left = 0;
	r.right = 50;
	r.top = 0;
	r.bottom = 50;
	frames->push_back(r);
	r.left = 0;
	r.right = 50;
	r.top = 50;
	r.bottom = 100;
	frames->push_back(r);
	r.left = 0;
	r.right = 150;
	r.top = 0;
	r.bottom = 200;
	frames->push_back(r);

	
	r.left = 0;
	r.right = 50;
	r.top = 0;
	r.bottom = 50;

	m_button = new Button(image, frames, r);
	m_button->SetX(50);
	m_button->SetY(50);
	
}

void Game::SetInputer(DirectInput *inputer)
{
	m_inputer = inputer;
	m_inputer->AddMouseListener((MouseListener*)m_button);
}

Game::~Game()
{
	delete m_sprite;
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
	
}

void Game::Render(Renderer *renderer)
{
	//

	D3DCamera * cam = (D3DCamera *)renderer->GetCamera();
	float x = m_cameraRadius * cosf(m_cameraRotation);
	float z =  m_cameraRadius * sinf(m_cameraRotation);
	cam->SetPosition(x, m_cameraHeight, z);

	renderer->DrawSprite((Sprite *)m_sprite);
	renderer->DrawMesh(m_testMesh);
	renderer->DrawSprite(m_button);
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
}

void Game::CreateTestMesh()
{
#if 1
	m_testMesh = new Cube();
	
	D3DRenderer *renderer = (D3DRenderer *) m_renderer;
	
	//indices
	IDirect3DIndexBuffer9 *ib;

	int indicesSize = m_testMesh->GetIndices()->size();
	
	HR(renderer->GetDevice()->CreateIndexBuffer(indicesSize * sizeof(WORD), D3DUSAGE_WRITEONLY,
	D3DFMT_INDEX16, D3DPOOL_MANAGED, &ib, 0));
	WORD *k = 0;

	HR(ib->Lock(0,0,(void**)&k, 0));

	for(int i = 0; i < indicesSize; i++)
	{
		k[i] = m_testMesh->GetIndices()->at(i);
	}

	HR(ib->Unlock());

	//vertices
	IDirect3DVertexBuffer9 * vb;
	int vertexSize = m_testMesh->GetVertices()->size();
	HR(renderer->GetDevice()->CreateVertexBuffer(vertexSize * m_testMesh->GetVertexSize(), D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED, &vb, 0));
	VertexPos *v = 0;
	HR(vb->Lock(0,0,(void**)&v,0));

	for(int i = 0; i < vertexSize; i++)
	{
		v[i] = m_testMesh->GetVertices()->at(i);
	}
	
	HR(vb->Unlock());

	//vertexDeclaration
	D3DVERTEXELEMENT9 VertexPosElements[] =
	{
		{0,0,D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		D3DDECL_END()
	};

	IDirect3DVertexDeclaration9 *Decl;
	HR(renderer->GetDevice()->CreateVertexDeclaration(VertexPosElements, &Decl));

	m_testMesh->SetBuffers(vb, ib);
	m_testMesh->SetVertexDeclaration(Decl);

#endif
	
}

void Game::OnKeyUp(int key)
{
	
}
