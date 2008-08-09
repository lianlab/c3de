#ifndef APPLICATION_WINDOW_H
#define APPLICATION_WINDOW_H

class ApplicationWindow
{
public:
	ApplicationWindow(int width, int height);
	virtual ~ApplicationWindow();
	int getWidth(){return m_width;}
	int getHeight(){return m_height;}
protected:
	int m_width;
	int m_height;

};
#endif
