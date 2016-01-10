#ifndef __IMAGE_H__
#define __IMAGE_H__


#include "element.h"
#include "pixbuf.h"


class Image : public Element
{
public:
    Image();
    
    void set_from_pixbuf(Pixbuf *pixbuf);
    
    void refresh();
};


#endif
