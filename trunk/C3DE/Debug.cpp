#include "Debug.h"
#include "DebugMemory.h"

std::ofstream out("debug.txt");

Debug * Debug::m_instance = NULL;

Debug::Debug()
{
	
}

Debug * Debug::GetInstance()
{
	if(!m_instance)
	{
		m_instance = new Debug();
	}

	return m_instance;
}

Debug::~Debug()
{
	if(out.good())
		out.close();
}

void Debug::Print(char c[])
{
	out << c << std::endl;
}
std::ofstream& Debug::operator<<(char c[]){out << c; return out;}
std::ofstream& Debug::operator<<(int i){out << i; return out;}
std::ofstream& Debug::operator<<(float f){out << f; return out;}
std::ofstream& Debug::operator<<(bool b){if(b)out << "True"; else out << "False"; return out;}
std::ofstream& Debug::operator<<(D3DXVECTOR3 v){out << "x: " << v.x << ", y: " << v.y << ", z: " << v.z;return out;}
void Debug::Endl(int nr){for(int i=0;i<nr;i++)out << std::endl;}