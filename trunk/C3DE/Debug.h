#ifndef DEBUG_H
#define DEBUG_H

#include <d3dx9.h>
#include <fstream>

class Debug{
	public:		
		~Debug();
		void Print(char c[]);
		std::ofstream& operator<<(char c[]);
		std::ofstream& operator<<(int i);
		std::ofstream& operator<<(float f);
		std::ofstream& operator<<(bool b);
		std::ofstream& operator<<(D3DXVECTOR3 v);
		void Endl(int nr);
		static Debug * GetInstance();
	private:
		Debug();
		static Debug *m_instance;
};



#endif