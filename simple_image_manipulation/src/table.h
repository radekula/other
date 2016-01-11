#ifndef __TABLE_H__
#define __TABLE_H__


#include "element.h"


class Table : public Element
{
public:
	Table();
	~Table();
	
	void add(Element *elem, int x, int y, int w, int h);
};




#endif
