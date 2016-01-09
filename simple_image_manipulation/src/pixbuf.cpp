#include "pixbuf.h"


Pixbuf::Pixbuf()
{
    _ref = gdk_pixbuf_new(GDK_COLORSPACE_RGB, false, 8, 500, 500);
    _scale = 1;
    
    cairo_t *cr;

    auto surface = cairo_image_surface_create(gdk_pixbuf_get_has_alpha(_ref) ? CAIRO_FORMAT_ARGB32 : CAIRO_FORMAT_RGB24, gdk_pixbuf_get_width(_ref), gdk_pixbuf_get_height(_ref));
    
    cr = cairo_create(surface);
    
    gdk_cairo_set_source_pixbuf(cr, _ref, 0, 0);
    cairo_paint(cr);

    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_rectangle (cr, 0, 0, 500, 500);
    cairo_fill(cr);
    cairo_surface_destroy (surface);
    cairo_destroy (cr);
};



Pixbuf::~Pixbuf()
{
};



void Pixbuf::set_scale(int scale)
{
    _scale = scale;
};



void Pixbuf::point(int x, int y)
{
    cairo_t *cr;

    auto surface = cairo_image_surface_create(gdk_pixbuf_get_has_alpha(_ref) ? CAIRO_FORMAT_ARGB32 : CAIRO_FORMAT_RGB24, gdk_pixbuf_get_width(_ref), gdk_pixbuf_get_height(_ref));
    
    cr = cairo_create(surface);
    
    gdk_cairo_set_source_pixbuf(cr, _ref, 0, 0);
    cairo_paint(cr);

    cairo_fill(cr);
    cairo_set_source_rgb(cr, 1, 0, 0);
    cairo_rectangle (cr, x, y, x + _scale, y + _scale);
    cairo_surface_destroy (surface);
    cairo_destroy (cr);
};

