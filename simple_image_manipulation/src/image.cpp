#include "image.h"



Image::Image()
{
    _ref = gtk_image_new();
};


void Image::set_from_pixbuf(Pixbuf *pixbuf)
{
    if(_ref)
        gtk_image_set_from_pixbuf(GTK_IMAGE(_ref), GDK_PIXBUF(pixbuf->get_ref()));
};


void Image::refresh()
{
	if(_ref)
		gtk_widget_queue_draw(GTK_WIDGET(_ref));
};
