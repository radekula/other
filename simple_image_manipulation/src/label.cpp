#include "label.h"




Label::Label()
{
	_ref = gtk_label_new("");
};



Label::Label(std::string label)
{
	_ref = gtk_label_new(label.c_str());
};


Label::~Label()
{
};



void Label::set_label(std::string label)
{
	if(_ref)
		gtk_label_set_text(GTK_LABEL(_ref), label.c_str());
};
