#ifndef __APPLICATION_HPP__
#define __APPLICATION_HPP__

#include <vector>
#include <memory>
#include <gtk/gtk.h>
#include "car.hpp"



#define NUM_CARS 20



class MyApp
{
private:
    GtkWidget *window;
    GtkWidget *draw_area;
    GdkPixbuf *frame;
    GdkPixbuf *road;
    GdkPixbuf *cars_images[5];

    float zoom;

public:
    std::vector<std::shared_ptr<Car>> cars;

public:
    static int zoom_callback(GtkWidget *widget, GdkEventScroll *event, void *app);
    static int draw_callback(GtkWidget *widget, cairo_t *cr, void *app);
    static int tick(GtkWidget *widget, GdkFrameClock *frame_clock, void *app);

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
};



#endif
