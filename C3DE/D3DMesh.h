#ifndef D3DMESH_H
#define D3DMESH_H

#include "Mesh.h"
#include <d3dx9.h>
#include <vector>
#include "D3DCommonDefs.h"

using namespace std;

//BOOK
struct VertexPos
{
	VertexPos():pos(0.0f, 0.0f, 0.0f){}
	VertexPos(float x, float y, float z):pos(x,y,z){}
	VertexPos(const D3DXVECTOR3 &v):pos(v){}

	static IDirect3DVertexDeclaration9 *Decl;

	D3DXVECTOR3 pos;	
};

class D3DMesh : public Mesh
{
public:
	D3DMesh();
	~D3DMesh();
	IDirect3DVertexDeclaration9 * GetVertexDeclaration(){return m_vertexDeclaration;}
	void SetVertexDeclaration(IDirect3DVertexDeclaration9 *vertexDeclaration){m_vertexDeclaration = vertexDeclaration;}
	IDirect3DVertexBuffer9 * GetVertexBuffer();
	IDirect3DIndexBuffer9 * GetIndexBuffer();
	void SetBuffers(IDirect3DVertexBuffer9 *vertexBuffer, IDirect3DIndexBuffer9 *indexBuffer);
	

	vector<VertexPos> * GetVertices(){return m_vertices;}
	vector<int> * GetIndices(){return m_indices;}

	int GetVertexSize(){return sizeof(VertexPos);}
protected:
	IDirect3DVertexBuffer9 * m_vertexBuffer;
	IDirect3DIndexBuffer9 * m_indexBuffer;
	IDirect3DVertexDeclaration9 *m_vertexDeclaration;

	vector<VertexPos> *m_vertices;
	vector<int> *m_indices;
};
#endif

