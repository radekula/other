#ifndef __TOGGLE_BUTTON_H__
#define __TOGGLE_BUTTON_H__


#include "element.h"
#include <string>


class ToggleButton : public Element
{
public:
	ToggleButton();
	ToggleButton(std::string label);
	~ToggleButton();
	
public:
	void set_label(std::string label);
	void set_on_clicked(void (*fun)(GtkWidget*, void*));
	
	void set_active(bool active);
	bool get_active();
};



#endif
