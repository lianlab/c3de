#include "Text.h"

Text::Text(char *a_text, Font *a_font):D3DSprite(a_font->GetImage(), 0, 0, 0, 0, 0, 1000)
{
	m_text = a_text;
	m_font = a_font;

	m_color = 0xff000000;

	vector<FontRect> *t_rects = m_font->GetRects();

	m_rectsIndices = new vector<int>;

	m_frameRects = new vector<RECT>;

	int totalChars = m_font->GetCharsIndices()->size();
	
	for(int i = 0; i < totalChars; i++)
	{					
		
		RECT src;
		src.left = (*t_rects)[i].m_x;
		src.right = (*t_rects)[i].m_x + (*t_rects)[i].m_w;
		src.top = (*t_rects)[i].m_y;
		src.bottom = (*t_rects)[i].m_y + (*t_rects)[i].m_h;

		m_frameRects->push_back(src);
	}

	m_numFrames = totalChars;

	BuildIndices();
}

Text::~Text()
{

}

void Text::BuildIndices()
{
	m_rectsIndices->clear();

	int i = 0;
	while(true)
	{
		if(m_text[i] == 0)
		{
			break;
		}

		else if(m_text[i] == '\n')
		{
			m_rectsIndices->push_back(Text::TEXT_SPACE);
		}
		else if(m_text[i] == ' ')
		{
			m_rectsIndices->push_back(Text::TEXT_LINE_FEED);
		}
		else
		{
			m_rectsIndices->push_back(GetIndex(m_text[i]));
		}
		i++;
		
	}

	m_textLength = i;
}

int Text::GetIndex(char a_char)
{
	vector<int> *t_chars = m_font->GetCharsIndices();
	int totalIndices = t_chars->size();

	for(int i = 0 ; i < totalIndices; i++)
	{
		if((*t_chars)[i] == (int) a_char)
		{
			return i;
		}
	}

	return Text::TEXT_INVALID_CHAR;
}

void Text::SetText(char * a_text)
{
	m_text = a_text;

	BuildIndices();
}
char * Text::GetText()
{
	return m_text;
}

Font * Text::GetFont()
{
	return m_font;
}

void Text::SetFont(Font *a_font)
{
	m_font = a_font;
	BuildIndices();
}

int Text::GetTextLength()
{
	return m_textLength;
}

vector<int> * Text::GetRectsIndices()
{
	return m_rectsIndices;
}

int Text::GetColor()
{
	return m_color;
}

void Text::SetColor(int a_color)
{
	m_color = a_color;
}
