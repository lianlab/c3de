#include "D3DMesh.h"
#include "ResourceManager.H"
//#include "DebugMemory.h"

IDirect3DVertexDeclaration9* VertexPos::Decl = 0;

D3DMesh::D3DMesh():Mesh()
{


	m_hack = NULL;
	m_vertices = NULL;
	m_indices = NULL;

	m_transformedBox = NULL;
	
	m_fleps = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_auei = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	

	m_numShaderPasses = 1;

	
	//m_fxHandlesInitialized = false;

	
	SetPosition(0.0f, 0.0f, 0.0f);

	m_xMesh = NULL;

	m_ID = -1;

	//m_materials = NULL;
	//m_textures = NULL;

	m_vertexDeclaration = NULL;


	m_effect = NULL;

	m_xMesh = NULL;

	//m_currentTex = NULL;
	m_boundingBox = NULL;
}

void D3DMesh::SetXMesh(ID3DXMesh *a_mesh)
{
	if(m_xMesh)
	{
		delete m_xMesh;
		m_xMesh = NULL;
	}

	m_xMesh = a_mesh;
}


void D3DMesh::CreateXMesh(IDirect3DDevice9 *a_device)
{

	if(m_xMesh)
	{
		ReleaseCOM(m_xMesh);
		delete m_xMesh;
		m_xMesh = NULL;
	}


	

	D3DVERTEXELEMENT9 VertexPosElements[] = 
	{
		{0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
		{0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
		D3DDECL_END()
	};	

	D3DVERTEXELEMENT9 elems[MAX_FVF_DECL_SIZE];

	int totalVertices = m_vertices->size();
	int totalIndices = m_indices->size();
	DWORD indices = totalIndices/3;
	DWORD vertices = totalVertices;
	//HRESULT err = D3DXCreateMesh(totalIndices/3, totalVertices, D3DXMESH_SYSTEMMEM|D3DXMESH_32BIT, VertexPosElements, a_device, &m_xMesh);
	//HRESULT err = D3DXCreateMesh(indices, vertices, D3DXMESH_SYSTEMMEM|D3DXMESH_32BIT, VertexPosElements, a_device, &m_xMesh);
	HRESULT err = D3DXCreateMesh(indices, vertices, D3DXMESH_MANAGED, VertexPosElements, a_device, &m_xMesh);
	//HRESULT err = D3DXCreateMesh(totalIndices/3, totalVertices, D3DXMESH_32BIT, VertexPosElements, a_device, &m_xMesh);

	
	VertexPos *v = NULL;
	m_xMesh->LockVertexBuffer(0, (void**)&v);

	for(int i = 0; i < totalVertices; i++)
	{
		v[i] = GetVertices()->at(i);
	}

	D3DXVECTOR3 t_min;
	D3DXVECTOR3 t_max;

	HR(D3DXComputeBoundingBox((D3DXVECTOR3*)v, m_xMesh->GetNumVertices(), 
		sizeof(VertexPos), &t_min, &t_max));

	

	m_boundingBox = new AABB(t_min, t_max);
	
	
	m_xMesh->UnlockVertexBuffer();

	WORD *k = NULL;

	m_xMesh->LockIndexBuffer(0, (void**)&k);

	for(int i = 0; i < totalIndices; i++)
	{
		k[i] = GetIndices()->at(i);
	}

	m_xMesh->UnlockIndexBuffer();
	



}

void D3DMesh::SetBoundingBox(D3DXVECTOR3 a_min, D3DXVECTOR3 a_max)
{
	if(m_boundingBox)
	{
		delete m_boundingBox;
		m_boundingBox = NULL;
	}

	m_boundingBox = new AABB(a_min, a_max);
}

AABB* D3DMesh::GetBoundingBox()
{

	return m_boundingBox;

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
	m_textures = new std::vector<Image*>;

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
			//m_materials->push_back(t);
			m_materials->push_back(t);

			if(d3dxmaterial[i].pTextureFilename != 0)
			{
				IDirect3DTexture9 *tex = 0;
				char *texFN = d3dxmaterial[i].pTextureFilename;
				//HR(D3DXCreateTextureFromFile(a_device, texFN, &tex));
				tex = ResourceManager::GetInstance()->GetTextureByFilename(texFN);

				D3DImage *t_image = new D3DImage(tex);
				m_textures->push_back((Image*)t_image);
			}
			
		}
	}

	D3DXVECTOR3 t_min;
	D3DXVECTOR3 t_max;

	VertexPos *v = NULL;
	m_xMesh->LockVertexBuffer(0, (void**)&v);

	HR(D3DXComputeBoundingBox((D3DXVECTOR3*)v, m_xMesh->GetNumVertices(), 
		sizeof(VertexPos), &t_min, &t_max));

	m_xMesh->UnlockVertexBuffer();

	m_boundingBox = new AABB(t_min, t_max);

	//m_obb = new OBB(t_min, t_max);
	//m_boundingBox = new AABB();


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

	if(m_boundingBox != NULL)
	{
		delete m_boundingBox;
		m_boundingBox = NULL;
	}

	FreeTextures();
	FreeMaterials();

	if(m_xMesh)
	{
		ReleaseCOM(m_xMesh);
		//HR(m_xMesh->Release());
		int gffd = 9876;
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

void D3DMesh::SetVertices(vector<VertexPos> * a_vertices)
{
	if(m_vertices)
	{
		delete m_vertices;
		m_vertices = NULL;
	}

	m_vertices = a_vertices;

}
	

void D3DMesh::SetIndices(vector<int> * a_indices)
{
	if(m_indices)
	{
		delete m_indices;
		m_indices = NULL;
	}

	m_indices = a_indices;
}


bool auei = false;

D3DXMATRIX D3DMesh::GetTransformMatrix()
{
	


	auei = true;
#define RADIAN_TO_DEGREES 57.29577951308232286465f
	D3DXMATRIX matRotation,matTranslation,matScale;
	int mat;
	D3DXVECTOR3 vAxis1, vAxis2, vAxis3;
	D3DXQUATERNION qR;

	// Set default translation
	D3DXMatrixIdentity( &matTranslation );

	D3DXMatrixScaling( &matScale, m_scaleX, m_scaleY, m_scaleZ );

	vAxis2.x = 0.0f;
	vAxis2.y = 1.0f;
	vAxis2.z = 0.0f;
	D3DXQuaternionNormalize(&qR, &qR);
	D3DXQuaternionRotationAxis( &qR, &vAxis2, m_rotateY/RADIAN_TO_DEGREES );
	D3DXMatrixRotationQuaternion( &matRotation, &qR );
	D3DXMatrixMultiply( &matTranslation, &matRotation , &matTranslation );
	vAxis1.x = 1.0f;
	vAxis1.y = 0.0f;
	vAxis1.z = 0.0f;
	D3DXQuaternionNormalize(&qR, &qR);
	D3DXQuaternionRotationAxis( &qR, &vAxis1, m_rotateX/RADIAN_TO_DEGREES );
	D3DXMatrixRotationQuaternion( &matRotation, &qR );
	D3DXMatrixMultiply( &matTranslation, &matRotation , &matTranslation );
	vAxis3.x = 0.0f;
	vAxis3.y = 0.0f;
	vAxis3.z = 1.0f;
	D3DXQuaternionNormalize(&qR, &qR);
	D3DXQuaternionRotationAxis( &qR, &vAxis3, m_rotateZ/RADIAN_TO_DEGREES );
	D3DXMatrixRotationQuaternion( &matRotation, &qR );


	
	D3DXMatrixMultiply( &matTranslation, &matRotation , &matTranslation );

	D3DXMatrixMultiply(&matTranslation, &matScale, &matTranslation);

	// Move to X,Y,Z coordinates
	matTranslation._41 = m_x;
	matTranslation._42 = m_y;
	matTranslation._43 = m_z;
	// Set the matrix

	return matTranslation;


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
