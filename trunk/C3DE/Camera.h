#ifndef CAMERA_H
#define CAMERA_H

class Camera
{
public:
	Camera();
	virtual ~Camera() = 0;
	void SetPosition(float x, float y, float z){m_x = x;m_y = y; m_z =z;}
	void SetTarget(float x, float y, float z){m_targetX = x;m_targetY = y; m_targetZ =z;}

protected:
	float m_x;
	float m_y;
	float m_z;
	float m_targetX;
	float m_targetY;
	float m_targetZ;
};
#endif