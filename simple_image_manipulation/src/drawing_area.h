#ifndef __DRAWING_AREA_H__
#define __DRAWING_AREA_H__


#include "element.h"
#include "pixmap.h"
#include "pixbuf.h"


class DrawingArea : public Element
{
public:
    Pixmap *_pixmap;
	
public:
	static gint expose_event(GtkWidget *widget, GdkEventExpose *event, DrawingArea *elem);
	static gint configure_event(GtkWidget *widget, GdkEventConfigure *event, DrawingArea *elem);
	
public:
	DrawingArea();
	~DrawingArea();
	
public:
	void resize(int width, int height);
};


#endif
