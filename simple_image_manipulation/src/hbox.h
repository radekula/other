#ifndef __HBOX_H__
#define __HBOX_H__



#include "element.h"



class HBox : public Element
{
public:
	HBox();
	~HBox();

public:
	void add(Element *elem, int expand, int fill, int padding);
};


#endif
