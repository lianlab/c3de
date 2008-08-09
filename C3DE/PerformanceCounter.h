#ifndef PERFORMANCE_COUNTER_H
#define PERFORMANCE_COUNTER_H

class PerformanceCounter
{	
public:
	PerformanceCounter();
	virtual ~PerformanceCounter();	
	float GetFPS(){ return m_fps;}
	virtual void Update(float dt) = 0;

	void SetTriangleCount(int totalTriangles){m_triangles = totalTriangles;}
	void SetVertexCount(int totalVertices){m_vertices = totalVertices;}
	
protected:
	float m_fps;
	float m_milliSecondsPerFrame;
	int m_triangles;
	int m_vertices;
};

#endif