#ifndef __ELEMENT_H__
#define __ELEMENT_H__

#include <gtk/gtk.h>



class Element
{
public:
	GtkWidget *_ref;

public:
	Element() {_ref = 0;};
	virtual ~Element() {};

public:
	GtkWidget *get_ref() {return _ref;};
	void show() {if(_ref) gtk_widget_show_all(_ref);};
};


#endif
