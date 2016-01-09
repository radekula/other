#include "drawing_area.h"



DrawingArea::DrawingArea()
{
	_ref = gtk_drawing_area_new();
	gtk_signal_connect(GTK_OBJECT(_ref), "expose_event", (GtkSignalFunc) DrawingArea::expose_event, this);	
	gtk_signal_connect(GTK_OBJECT(_ref), "configure_event", (GtkSignalFunc) DrawingArea::configure_event, this);
	
    _pixmap = 0;
};



DrawingArea::~DrawingArea()
{
};



void DrawingArea::resize(int width, int height)
{
	if(!_ref)
        return;
        
    gtk_widget_set_size_request(GTK_WIDGET(_ref), width, height);
};




gint DrawingArea::expose_event(GtkWidget *widget, GdkEventExpose *event, DrawingArea *elem)
{
	gdk_draw_pixmap(widget->window, widget->style->fg_gc[GTK_WIDGET_STATE(widget)], 
		elem->_pixmap->get_ref(), 
		event->area.x, 
		event->area.y, 
		event->area.x, 
		event->area.y, 
		event->area.width,
		event->area.height);

    return FALSE;
};



gint DrawingArea::configure_event(GtkWidget *widget, GdkEventConfigure *event, DrawingArea *elem)
{
    if(elem->_pixmap)
        delete elem->_pixmap;
        
    elem->_pixmap = new Pixmap(elem);

	gdk_draw_rectangle(elem->_pixmap->get_ref(),
                      widget->style->white_gc,
                      TRUE,
                      0, 0,
                      widget->allocation.width,
                      widget->allocation.height);
                      
	return TRUE;
}
