#ifndef __LABEL_H__
#define __LABEL_H__


#include "element.h"
#include <string>


class Label : public Element
{
public:
	Label();
	Label(std::string label);
	~Label();
	
public:
	void set_label(std::string label);
};


#endif
