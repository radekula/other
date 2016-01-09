#include "vbox.h"



VBox::VBox()
{
	_ref = gtk_vbox_new(false, 0);
};



VBox::~VBox()
{
};



void VBox::add(Element *elem, int expand, int fill, int padding)
{
	if(_ref)
		gtk_box_pack_start(GTK_BOX(_ref), GTK_WIDGET(elem->get_ref()), expand, fill, padding);
};

