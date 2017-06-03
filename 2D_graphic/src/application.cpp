#include "application.hpp"




MyApp::MyApp()
{
    window = 0;
};




MyApp::~MyApp()
{
};




int MyApp::init(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    
    return 0;
};




int MyApp::run()
{
    gtk_widget_show_all (window);
    
    gtk_main();
    return 0;
};

