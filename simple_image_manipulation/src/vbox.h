#ifndef __VBOX_H__
#define __VBOX_H__



#include "element.h"



class VBox : public Element
{
public:
	VBox();
	~VBox();

public:
	void add(Element *elem, int expand, int fill, int padding);
};


#endif
