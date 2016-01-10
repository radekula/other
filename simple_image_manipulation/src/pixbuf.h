#ifndef __PIXBUF_H__
#define __PIXBUF_H__


#include "element.h"



class Pixbuf
{
private:
	GdkPixbuf *_ref;
    int rowstride;
    int n_channels;
    
public:
    guchar *pixels;
    int _width;
    int _height;
	int _scale;
    
public:
	Pixbuf();
	~Pixbuf();
    
   	GdkPixbuf *get_ref() {return _ref;};

    void set_scale(int scale);    
    void point(int x, int y, int r = 0, int g = 0, int b = 0);
    guchar *get_point(int x, int y);
};


#endif
