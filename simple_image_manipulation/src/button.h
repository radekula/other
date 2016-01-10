#ifndef __BUTTON_H__
#define __BUTTON_H__


#include "element.h"
#include <string>


class Button : public Element
{
public:
	Button();
	Button(std::string label);
	~Button();
	
public:
	void set_label(std::string label);
	
	void set_on_clicked(void (*fun)(GtkWidget*, void*));
};



#endif
