#include "D3DMesh.h"
#include "ResourceManager.H"
#include "DebugMemory.h"

IDirect3DVertexDeclaration9* VertexPos::Decl = 0;

D3DMesh::D3DMesh()
{
	m_vertices = NULL;
	m_indices = NULL;
	
	

	m_numShaderPasses = 1;

	
	//m_fxHandlesInitialized = false;

	
	SetPosition(0.0f, 0.0f, 0.0f);

	m_xMesh = NULL;

	m_ID = -1;

	m_materials = NULL;
	m_textures = NULL;
}

void D3DMesh::CreateXMesh(IDirect3DDevice9 *a_device)
{

	if(m_xMesh)
	{
		delete m_xMesh;
		m_xMesh = NULL;
	}

	FreeTextures();
	FreeMaterials();

	D3DVERTEXELEMENT9 VertexPosElements[] = 
	{
		{0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
		{0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
		D3DDECL_END()
	};	

	int totalVertices = m_vertices->size();
	int totalIndices = m_indices->size();
	D3DXCreateMesh(totalIndices/3, totalVertices, D3DXMESH_MANAGED, VertexPosElements, a_device, &m_xMesh);

	VertexPos *v = NULL;
	m_xMesh->LockVertexBuffer(0, (void**)&v);

	for(int i = 0; i < totalVertices; i++)
	{
		v[i] = GetVertices()->at(i);
	}
	
	m_xMesh->UnlockVertexBuffer();

	WORD *k = NULL;

	m_xMesh->LockIndexBuffer(0, (void**)&k);

	for(int i = 0; i < totalIndices; i++)
	{
		k[i] = GetIndices()->at(i);
	}

	m_xMesh->UnlockIndexBuffer();



	
}

void D3DMesh::FreeTextures()
{
	
	if(m_textures)
	{
		int t_size = m_textures->size();
		for(int i = 0; i < t_size; i++)
		{
			delete m_textures->at(i);
		}
		delete m_textures;
		m_textures = NULL;
	}
}

void D3DMesh::FreeMaterials()
{
	if(m_materials)
	{
		int t_size = m_materials->size();
		for(int i = 0; i < t_size; i++)
		{
			delete m_materials->at(i);
		}
		delete m_materials;
		m_materials = NULL;
	}
}

void D3DMesh::LoadFromXFile(const std::string &filename, IDirect3DDevice9* a_device)
{	
	FreeMaterials();
	FreeTextures();		

	m_materials = new std::vector<Material*>;
	m_textures = new std::vector<IDirect3DTexture9*>;

	ID3DXMesh *meshSys = 0;
	ID3DXBuffer *adjBuffer = 0;
	ID3DXBuffer * materialBuffer = 0;
	DWORD numMaterials = 0;

	HR(D3DXLoadMeshFromX(filename.c_str(), D3DXMESH_SYSTEMMEM, a_device, &adjBuffer, &materialBuffer, 0, &numMaterials, &meshSys));

	m_numSubsets = (int)numMaterials;

	D3DVERTEXELEMENT9 elems[MAX_FVF_DECL_SIZE];
	HR(meshSys->GetDeclaration(elems));

	bool hasNormals = false;
	for(int i = 0; i< MAX_FVF_DECL_SIZE; ++i)
	{
		if(elems[i].Stream == 0xff)
			break;
		if(elems[i].Type == D3DDECLTYPE_FLOAT3 && elems[i].Usage == D3DDECLUSAGE_NORMAL && elems[i].UsageIndex == 0)
		{
			hasNormals = true;
			break;
		}
	}

	D3DVERTEXELEMENT9 elements[64];
	UINT numElements = 0;

	D3DVERTEXELEMENT9 VertexPosElements[] = 
	{
		{0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
		{0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
		D3DDECL_END()
	};	

	

	IDirect3DVertexDeclaration9 *Decl;
	HR(a_device->CreateVertexDeclaration(VertexPosElements, &Decl));


	Decl->GetDeclaration(elements, &numElements);

	ID3DXMesh *temp = 0;

	HR(meshSys->CloneMesh(D3DXMESH_SYSTEMMEM, elements, a_device, &temp));
	ReleaseCOM(meshSys);
	meshSys = temp;

	if(hasNormals == false)
	{
		HR(D3DXComputeNormals(meshSys, 0));
	}

	HR(meshSys->Optimize(D3DXMESH_MANAGED | D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE, (DWORD *)adjBuffer->GetBufferPointer(), 0, 0, 0, &m_xMesh));
	ReleaseCOM(meshSys);
	ReleaseCOM(adjBuffer);

	if(materialBuffer != 0 && numMaterials != 0)
	{
		D3DXMATERIAL * d3dxmaterial = (D3DXMATERIAL*)materialBuffer->GetBufferPointer();

		for(DWORD i = 0; i < numMaterials; ++i)
		{
			Material *t = new Material(d3dxmaterial[i].MatD3D.Diffuse, d3dxmaterial[i].MatD3D.Diffuse, d3dxmaterial[i].MatD3D.Specular, d3dxmaterial[i].MatD3D.Power);
			m_materials->push_back(t);

			if(d3dxmaterial[i].pTextureFilename != 0)
			{
				IDirect3DTexture9 *tex = 0;
				char *texFN = d3dxmaterial[i].pTextureFilename;
				//HR(D3DXCreateTextureFromFile(a_device, texFN, &tex));
				tex = ResourceManager::GetInstance()->GetImageByFilename(texFN);
				m_textures->push_back(tex);
			}
			else
			{
				m_textures->push_back(0);
			}
		}
	}

	ReleaseCOM(materialBuffer);
}

D3DMesh::~D3DMesh()
{
	if(m_vertices)
	{
		delete m_vertices;
		m_vertices = NULL;
	}

	if(m_indices)
	{
		delete m_indices;
		m_indices =NULL;
	}
/*
	if(m_vertices)
	{
		delete m_vertices;
		m_vertices = NULL;
	}

	if(m_indices)
	{
		delete m_indices;
		m_indices =NULL;
	}

	if(m_texture)
	{
		delete m_texture;
		m_texture = NULL;
	}

	*/
	if(m_xMesh)
	{
		ReleaseCOM(m_xMesh);
	}
}

void D3DMesh::SetShaderHandlers()
{
	m_effect->SetTransformMatrix(GetTransformMatrix());
	//m_effect->SetTransformMatrix(m_transformMatrix);
}

void D3DMesh::Update(int deltaTime)
{
	m_updateTime = deltaTime;
	
}


D3DXMATRIX D3DMesh::GetTransformMatrix()
{
	
	D3DXMATRIX T;
	D3DXMATRIX S;
	D3DXMATRIX O;
	
	D3DXMatrixScaling(&S, m_scaleX, m_scaleY, m_scaleZ);
	
	D3DXMatrixTranslation(&T, m_x, m_y, m_z);

	D3DXMatrixMultiply(&O, &S, &T);

	return O;
	

	return m_transformMatrix;
}

void D3DMesh::SetPosition(float x, float y, float z)
{
	m_x = x;m_y=y;m_z=z;
	//D3DXMatrixTranslation(&m_transformMatrix, m_x, m_y, m_z);
	
}

void D3DMesh::SetTransformMatrix(D3DXMATRIX matrix)
{
	m_transformMatrix = matrix;
	m_x = m_transformMatrix._41;
	m_y = m_transformMatrix._42;
	m_z = m_transformMatrix._43;

	m_scaleX = m_transformMatrix._11;
	m_scaleY = m_transformMatrix._22;
	m_scaleZ = m_transformMatrix._33;
	
}

void D3DMesh::Scale(float x, float y, float z)
{
	m_scaleX=x;m_scaleY=y;m_scaleZ=z;
	//D3DXMatrixScaling(&m_transformMatrix, m_x, m_y, m_z);
	//m_effect->SetTransformMatrix(GetTransformMatrix());
	//D3DXMatrixScaling(&m_transformMatrix, m_scaleX, m_scaleY, m_scaleZ);
}


IDirect3DVertexBuffer9 * D3DMesh::GetVertexBuffer()
{
	return m_vertexBuffer;
}

IDirect3DIndexBuffer9 * D3DMesh::GetIndexBuffer()
{
	return m_indexBuffer;
}

void D3DMesh::SetBuffers(IDirect3DVertexBuffer9 *vertexBuffer, IDirect3DIndexBuffer9 *indexBuffer)
{
	m_vertexBuffer = vertexBuffer;
	m_indexBuffer = indexBuffer;
}
