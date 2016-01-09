#include "window.h"



Window::Window()
{
	_ref = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(GTK_WINDOW(_ref), "destroy", G_CALLBACK(gtk_main_quit), NULL);
};



Window::~Window()
{
//	if(_ref)
//		gtk_widget_destroy(_ref);
};



void Window::resize(int width, int height)
{
	if(_ref)
		gtk_window_set_default_size(GTK_WINDOW(_ref), width, height);
};



void Window::add(Element *elem)
{
	if(_ref)
		gtk_container_add(GTK_CONTAINER(_ref), GTK_WIDGET(elem->get_ref()));
};







