#include "toggle_button.h"




ToggleButton::ToggleButton()
{
	_ref = gtk_toggle_button_new_with_label("");
};



ToggleButton::ToggleButton(std::string label)
{
	_ref = gtk_toggle_button_new_with_label(label.c_str());
};


ToggleButton::~ToggleButton()
{
};



void ToggleButton::set_label(std::string label)
{
	if(_ref)
		gtk_button_set_label(GTK_BUTTON(_ref), label.c_str());
};



void ToggleButton::set_on_clicked(void (*fun)(GtkWidget*, void*))
{
	if(_ref)
		g_signal_connect(_ref, "clicked", G_CALLBACK(fun), this);
};



void ToggleButton::set_active(bool active)
{
	if(_ref)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(_ref), active);
};


bool ToggleButton::get_active()
{
	bool active = false;
	
	if(_ref)
		active = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(_ref));
		
	return active;
};

