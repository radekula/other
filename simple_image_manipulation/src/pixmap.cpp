#include "pixmap.h"




Pixmap::Pixmap()
{
};



Pixmap::Pixmap(Element *elem)
{
	create(elem);
};



Pixmap::Pixmap(Element *elem, int width, int height)
{
    create(elem, width, height);
};




Pixmap::~Pixmap()
{
    gdk_pixmap_unref(_ref);
};



void Pixmap::create(Element *elem)
{
	_ref = gdk_pixmap_new(elem->get_ref()->window, elem->get_ref()->allocation.width, elem->get_ref()->allocation.height, -1);
};



void Pixmap::create(Element *elem, int width, int height)
{
	_ref = gdk_pixmap_new(elem->get_ref()->window, width, height, -1);
};
