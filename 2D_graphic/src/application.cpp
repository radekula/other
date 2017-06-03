#include <string>
#include <iostream>
#include "application.hpp"




MyApp::MyApp()
{
    window = 0;
    draw_area = 0;
    zoom = 1.0;
};




MyApp::~MyApp()
{
};




int MyApp::zoom_callback(GtkWidget *widget, GdkEventScroll *event, void *app)
{
    ((MyApp*)app)->change_zoom(event->delta_y);
    return 1;
};




int MyApp::draw_callback(GtkWidget *widget, cairo_t *cr, void *app)
{
    ((MyApp*)app)->draw(cr);
    return 1;
};




int MyApp::tick(GtkWidget *widget, GdkFrameClock *frame_clock, void *app)
{
    ((MyApp*)app)->draw_frame();
    return 1;
};




int MyApp::init(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_add_events(GTK_WIDGET(window), GDK_SCROLL_MASK);
    g_signal_connect(GTK_WINDOW(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(GTK_WINDOW(window), "scroll-event", G_CALLBACK(zoom_callback), this);
    gtk_window_set_resizable(GTK_WINDOW(window), false);

    draw_area = gtk_drawing_area_new();
    g_signal_connect(draw_area, "draw", G_CALLBACK(draw_callback), this);
    gtk_container_add (GTK_CONTAINER(window), draw_area);

    gtk_widget_add_tick_callback(draw_area, tick, this, NULL);

    gtk_widget_set_size_request(window, 1000, 600);
    frame = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, 1000, 600);

    road = gdk_pixbuf_new_from_file("images/road.png", 0);

    for(int i = 0; i < 5; i++)
    {
        std::string file = std::string("images/car") + std::to_string(i) + ".png";
        cars[i] = gdk_pixbuf_new_from_file(file.c_str(), 0);
    };

    return 0;
};




int MyApp::run()
{
    gtk_widget_show_all (window);
    
    gtk_main();
    return 0;
};




void MyApp::draw(cairo_t *cr)
{
    gdk_cairo_set_source_pixbuf(cr, frame, 0, 0);
    cairo_paint(cr);
};




void MyApp::draw_frame()
{
    gdk_pixbuf_fill(frame, 0);
    GdkRectangle r1, r2, dest;

    r1.x = 500 - (gdk_pixbuf_get_width(road) / 2) * zoom;
    r1.y = 300 - (gdk_pixbuf_get_height(road) / 2) * zoom;
    r1.width = gdk_pixbuf_get_width(road) * zoom;
    r1.height = gdk_pixbuf_get_height(road) * zoom;

    r2.x = 0;
    r2.y = 0;
    r2.width = 1000;
    r2.height = 600;

    double offset_x = r1.x;
    double offset_y = r1.y;
    double scale_x = zoom;
    double scale_y = zoom;
    
    if(gdk_rectangle_intersect (&r1, &r2, &dest)) 
        gdk_pixbuf_composite(road, frame, dest.x, dest.y, dest.width, dest.height, offset_x, offset_y, scale_x, scale_y, GDK_INTERP_NEAREST, 255);
        
    gtk_widget_queue_draw(draw_area);
};




void MyApp::change_zoom(double delta)
{
    zoom += delta / 10;
    if(zoom > 1.5)
        zoom = 1.5;

    if(zoom < 0.5)
        zoom = 0.5;
};
