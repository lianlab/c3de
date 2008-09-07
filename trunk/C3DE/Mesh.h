#ifndef MESH_H
#define MESH_H

class Mesh
{
public:
	Mesh();
	virtual void Translate(float x, float y, float z) = 0;
	virtual float GetX() = 0;
	virtual float GetY() = 0;
	virtual float GetZ() = 0;
	virtual ~Mesh() = 0;
	virtual void Update(int deltaTime) = 0;
protected:
	float m_x;
	float m_y;
	float m_z;
};
#endif