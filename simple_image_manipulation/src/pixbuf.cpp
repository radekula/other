#include "pixbuf.h"
#include <iostream>


Pixbuf::Pixbuf()
{
	_width = 500;
	_height = 500;
	
    _ref = gdk_pixbuf_new(GDK_COLORSPACE_RGB, false, 8, _width, _height);
    gdk_pixbuf_fill(_ref, 0xffffffff );
    _scale = 1;
    
    n_channels = gdk_pixbuf_get_n_channels(_ref);
	rowstride = gdk_pixbuf_get_rowstride(_ref);
	pixels = gdk_pixbuf_get_pixels(_ref);
};



Pixbuf::~Pixbuf()
{
};



void Pixbuf::set_scale(int scale)
{
    _scale = scale;
};



void Pixbuf::point(int x, int y, int r, int g, int b)
{
	for(int i = 0; i < _scale; i++)
	{
		for(int l = 0; l < _scale; l++)
		{
			auto p = pixels + (y * _scale + l) * rowstride + (x * _scale + i) * n_channels;
			p[0] = r;
			p[1] = g;
			p[2] = b;
		};
	};
};


guchar* Pixbuf::get_point(int x, int y)
{
	return (pixels + (y * _scale) * rowstride + (x * _scale) * n_channels);
};

