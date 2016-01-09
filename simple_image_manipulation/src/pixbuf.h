#ifndef __PIXBUF_H__
#define __PIXBUF_H__


#include "element.h"



class Pixbuf
{
private:
	GdkPixbuf *_ref;
	int _scale;
    
    
public:
	Pixbuf();
	~Pixbuf();
    
   	GdkPixbuf *get_ref() {return _ref;};

    void set_scale(int scale);    
    void point(int x, int y);
};


#endif
