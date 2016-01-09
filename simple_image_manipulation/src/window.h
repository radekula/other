#ifndef __WINDOW_H__
#define __WINDOW_H__


#include "element.h"



class Window : public Element
{
public:
	Window();
	~Window();
	
public:
	void resize(int width, int height);
	
	void add(Element *elem);
};


#endif
