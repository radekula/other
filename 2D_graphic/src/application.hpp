#ifndef __APPLICATION_HPP__
#define __APPLICATION_HPP__

#include <vector>
#include <memory>
#include <gtk/gtk.h>
#include "car.hpp"



#define NUM_CARS 40



class MyApp
{
private:
    GtkWidget *window;
    GtkWidget *draw_area;
    GdkPixbuf *frame;
    GdkPixbuf *road;
    GdkPixbuf *cars_images[5];

    int window_size_x;
    int window_size_y;
    float zoom;

private:
    gint64 start_time;

public:
    std::vector<std::shared_ptr<Car>> cars;

public:
    static int resize_callback(GtkWidget *widget, GdkEventConfigure *event, void *app);
    static int zoom_callback(GtkWidget *widget, GdkEventScroll *event, void *app);
    static int draw_callback(GtkWidget *widget, cairo_t *cr, void *app);
    static int tick(void *app);

public:
    MyApp();
    ~MyApp();
    
public:
    int init(int argc, char *argv[]);
    int run();

public:
    void draw(cairo_t *cr);
    void draw_frame();
    void change_zoom(double delta);
    
public:
    void resize(int x, int y);
};



#endif
