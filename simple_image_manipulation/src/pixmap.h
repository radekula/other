#ifndef __PIXMAP_H__
#define __PIXMAP_H__

#include "element.h"


class Pixmap
{
private:
	GdkPixmap *_ref;
	
public:
	Pixmap();
	Pixmap(Element *elem);
	Pixmap(Element *elem, int width, int height);
	~Pixmap();
	
	void create(Element *elem);
	void create(Element *elem, int width, int height);
	GdkPixmap *get_ref() {return _ref;};
	
};


#endif
