#include "hbox.h"



HBox::HBox()
{
	_ref = gtk_hbox_new(false, 0);
};



HBox::~HBox()
{
};



void HBox::add(Element *elem, int expand, int fill, int padding)
{
	if(_ref)
		gtk_box_pack_start(GTK_BOX(_ref), GTK_WIDGET(elem->get_ref()), expand, fill, padding);
};

