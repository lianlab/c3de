#ifndef C3DE_TRANSFORM_H
#define C3DE_TRANSFORM_H

#include <d3dx9.h>

class C3DETransform
{
public:
	C3DETransform();
	~C3DETransform();

	

	void Translate(float x, float y, float z);
	void Scale(float x, float y, float z);
	void Rotate(float angle, D3DXVECTOR3 * t_axis);
	D3DXMATRIX * GetMatrix();
	void Set(D3DXMATRIX *a_transform);
private:
	D3DXMATRIX * m_matrix;
};
#endif