#include "Font.h"
#include "DebugMemory.h"

//Font::Font(D3DImage *a_image, vector<int> *a_chars, vector<FontRect> *a_rects, vector<D3DXVECTOR2> *a_offsets):D3DSprite(a_image, 0, 0, 0, 0, 0, 100)
Font::Font(D3DImage *a_image, int *a_descriptor)//:D3DSprite(a_image, 0, 0, 0, 0, 0, 1000)
//Font::Font(D3DImage *a_image, vector<int> *tt):D3DSprite(a_image, 0, 0, 0, 0, 0, 100)
{
	m_image = a_image;
	m_chars = new vector<int>;
	m_widths = new vector<int>;
	m_rects = new vector<FontRect>;
	m_offsets = new vector<D3DXVECTOR2>;

	m_lineSpacing = 10;
	m_spacing = 10;
	m_height = 0;

	m_descriptor = a_descriptor;
	int pointerPos = 0;
	int totalChars = m_descriptor[0];
	pointerPos++;
	
	for(int i = 0; i < totalChars; i++)
	{
		m_chars->push_back(m_descriptor[pointerPos]);
		pointerPos++;
	}

	for(int i = 0; i < totalChars; i++)
	{
		m_widths->push_back(m_descriptor[pointerPos]);
		pointerPos++;
	}

	for(int i = 0; i < totalChars; i++)
	{
		if(m_descriptor[pointerPos+3] > m_height)
		{
			m_height = m_descriptor[pointerPos+3];
		}
		m_rects->push_back(FontRect(m_descriptor[pointerPos], m_descriptor[pointerPos+1], m_descriptor[pointerPos+2], m_descriptor[pointerPos+3])) ;
		pointerPos+= 4;

	}

	for(int i = 0; i < totalChars; i++)
	{
		m_offsets->push_back(D3DXVECTOR2(m_descriptor[pointerPos], m_descriptor[pointerPos+1])) ;
		pointerPos+= 2;
	}

	

}

D3DImage * Font::GetImage()
{
	return m_image;
}

vector<int> * Font::GetCharsIndices()
{
	return m_chars;
}
vector<int> * Font::GetWidths()
{
	return m_widths;
}
vector<FontRect> * Font::GetRects()
{
	return m_rects;
}
vector<D3DXVECTOR2> * Font::GetOffsets()
{
	return m_offsets;
}

int * Font::GetDescriptor()
{
	return m_descriptor;
}

int Font::GetSpacing()
{
	return m_spacing;
}

int Font::GetLineSpacing()
{
	return m_lineSpacing;
}

int Font::GetHeight()
{
	return m_height;
}

Font::~Font()
{
	
}



