#include "button.h"




Button::Button()
{
	_ref = gtk_button_new_with_label("");
};



Button::Button(std::string label)
{
	_ref = gtk_button_new_with_label(label.c_str());
};


Button::~Button()
{
};



void Button::set_label(std::string label)
{
	if(_ref)
		gtk_button_set_label(GTK_BUTTON(_ref), label.c_str());
};



void Button::set_on_clicked(void (*fun)(GtkWidget*, void*))
{
	if(_ref)
		g_signal_connect(_ref, "clicked", G_CALLBACK(fun), this);
};
