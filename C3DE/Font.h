#ifndef FONT_H
#define FONT_H

#include "D3DSprite.h"
#include <vector>

using namespace std;

struct FontRect
{
	FontRect(int x, int y, int w, int h)
	{
		m_x = x;
		m_y = y;
		m_w = w;
		m_h = h;
	}

	int m_x;
	int m_y;
	int m_w;
	int m_h;
};

class Font : public D3DSprite
{
public:
	Font(D3DImage *a_image, vector<int> *a_chars, vector<FontRect> *a_rects, vector<D3DXVECTOR2> *a_offsets);
	//Font(D3DImage *a_image, vector<int> *tt);
	virtual ~Font();
	
	
};
#endif
