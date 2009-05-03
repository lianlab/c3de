#ifndef TEXT_H
#define TEXT_H

#include "D3DSprite.h"
#include "Font.h"

class Text : public D3DSprite
{
public:
	Text(char *a_text, Font *a_font);
	~Text();

	void SetText(char * a_text);
	char * GetText();

	void SetColor(int color);
	int GetColor();

	Font * GetFont();
	void SetFont(Font *a_font);
	vector<int> * GetRectsIndices();

	int GetTextLength();

	static const int TEXT_INVALID_CHAR = -1;
	static const int TEXT_SPACE = -2;
	static const int TEXT_LINE_FEED = -3;
protected:
	int GetIndex(char a_char);
	Font * m_font;
	char * m_text;
	vector<int> *m_rectsIndices;

	int m_textLength;

	int m_color;

	void BuildIndices();
};
#endif