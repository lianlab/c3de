#ifndef INTPOINT_H
#define INTPOINT_H

#include <d3dx9.h>
#include <math.h>
#include "Debug.h"

class IntPoint{
	public:
		IntPoint(){x = y = 0;}
		IntPoint(int _x, int _y){Set(_x,_y);}

		void operator=(const POINT rhs){x = rhs.x;y = rhs.y;}
		bool operator==(const IntPoint rhs){return rhs.x == x && rhs.y == y;}
		bool operator!=(const IntPoint rhs){return rhs.x != x || rhs.y != y;}
		void operator+=(const IntPoint rhs){x += rhs.x; y += rhs.y;}
		void operator/=(const int rhs){x /= rhs; y /= rhs;}
		IntPoint operator/(const IntPoint rhs){return IntPoint(x / rhs.x, y / rhs.y);}
		IntPoint operator/(const int d){return IntPoint(x / d, y / d);}
		IntPoint operator-(const IntPoint &rhs){return IntPoint(x - rhs.x, y - rhs.y);}
		IntPoint operator+(const IntPoint &rhs){return IntPoint(x + rhs.x, y + rhs.y);}
		IntPoint operator-(const int &rhs){return IntPoint(x - rhs, y - rhs);}
		IntPoint operator+(const int &rhs){return IntPoint(x + rhs, y + rhs);}

		float Distance(IntPoint p){return sqrtf((p.x-x)*(p.x-x)+(p.y-y)*(p.y-y));}
		bool inRect(RECT r){if(x < r.left || x > r.right || y < r.top || y > r.bottom)return false;else return true;}

		void Set(int _x, int _y){x = _x; y = _y;}
		int x,y;
};

#endif