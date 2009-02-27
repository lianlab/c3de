#include "D3DMesh.h"
#include "ResourceManager.H"
//#include "DebugMemory.h"

IDirect3DVertexDeclaration9* VertexPos::Decl = 0;

D3DMesh::D3DMesh():Mesh()
{


	m_vertices = NULL;
	m_indices = NULL;

	m_transformedBox = NULL;
	
	

	m_numShaderPasses = 1;

	
	//m_fxHandlesInitialized = false;

	
	SetPosition(0.0f, 0.0f, 0.0f);

	m_xMesh = NULL;

	m_ID = -1;

	//m_materials = NULL;
	//m_textures = NULL;


	m_effect = NULL;

	m_xMesh = NULL;

	//m_currentTex = NULL;
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
		delete m_xMesh;
		m_xMesh = NULL;
	}


	//m_materials->push_back(m_material);
#if 0
	D3DImage *t_image = (D3DImage *)m_texture;
	if(t_image)
	{

		m_textures->push_back((Image*)t_image);
	}
#endif
	

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

	if(err == D3DERR_INVALIDCALL)
	{
		int picles = 39872;
	}
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

AABB* D3DMesh::GetBoundingBox()
{
//IMPORTANT, THIS METHOD IS NOT WORKING FOR ROTATIONS
	float t_rotationX = m_rotateX;
	float t_rotationY = m_rotateY;
	float t_rotationZ = m_rotateZ;

	m_rotateX = 0.0f;
	m_rotateY = 0.0f;
	m_rotateZ = 0.0f;
	D3DXMATRIX t_matrix = GetTransformMatrix();

	m_rotateX = t_rotationX;
	m_rotateY = t_rotationY;
	m_rotateZ = t_rotationZ;

	D3DXVECTOR4 t_min = D3DXVECTOR4(m_boundingBox->minPoint, 1.0f);
	D3DXVECTOR4 t_max = D3DXVECTOR4(m_boundingBox->maxPoint, 1.0f);
	D3DXVec3Transform(&t_min, &m_boundingBox->minPoint, &t_matrix);
	D3DXVec3Transform(&t_max, &m_boundingBox->maxPoint, &t_matrix);

	if(m_transformedBox)
	{
		delete m_transformedBox;
		m_transformedBox = NULL;
	}
	//D3DXVECTOR3 t_diff2 = D3DXVECTOR3(t_max.x - t_min.x, t_max.y - t_min.y, t_max.z - t_min.z);
	//D3DXVECTOR3 t_max3 = D3DXVECTOR3(t_min.x + t_diff.x,t_min.y + t_diff.y, t_min.z + t_diff.z);
	m_transformedBox = new AABB(D3DXVECTOR3(t_min.x, t_min.y, t_min.z), D3DXVECTOR3(t_max.x, t_max.y, t_max.z));		

	return m_transformedBox;

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


	ReleaseCOM(materialBuffer);
}

#if 0
void D3DMesh::SetD3DTexture(IDirect3DTexture9 *a_tex)
{

}
#endif


/*
void D3DMesh::SetCurrentD3DTexture(IDirect3DTexture9 *a_tex)
{
	m_currentTex = a_tex;

	
}
*/


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
	
		
		
#if 0
	D3DXMATRIX T;
	D3DXMATRIX S;
	D3DXMATRIX Rx;
	D3DXMATRIX Ry;
	D3DXMATRIX Rz;
	D3DXMATRIX R;
	D3DXMATRIX O;
	
	D3DXMatrixScaling(&S, m_scaleX, m_scaleY, m_scaleZ);
	
	D3DXMatrixTranslation(&T, m_x, m_y, m_z);

	D3DXMatrixIdentity(&R);
	D3DXMatrixIdentity(&Rx);
	D3DXMatrixIdentity(&Ry);
	D3DXMatrixIdentity(&Rz);

	D3DXMatrixMultiply(&O, &S, &T);


	if((m_rotateX > 0.0f || m_rotateY > 0.0f || m_rotateZ > 0.0f) && !auei)
	{
		D3DXMatrixRotationX(&Rx, m_rotateX);
		D3DXMatrixRotationY(&Ry, m_rotateY);
		D3DXMatrixRotationZ(&Rz, m_rotateZ);


		D3DXMatrixMultiply(&R, &Rx, &Ry);
		D3DXMatrixMultiply(&R, &R, &Rz);

		D3DXMatrixMultiply(&O, &O, &R);

		auei = true;
	}
	

	

	

	return O;
	

	return m_transformMatrix;
	
#endif
#if 1

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

#endif
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
