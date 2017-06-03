#ifndef __APPLICATION_HPP__
#define __APPLICATION_HPP__

#include <gtk/gtk.h>


class MyApp
{
private:
    GtkWidget *window;

public:
    MyApp();
    ~MyApp();
    
public:
    int init(int argc, char *argv[]);
    int run();
};



#endif
