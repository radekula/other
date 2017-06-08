#include <string>
#include <iostream>
#include <cmath>
#include "application.hpp"




MyApp::MyApp()
{
    window = 0;
    draw_area = 0;
    zoom = 1.0;

    for(int i = 0; i < NUM_CARS; i++)
        cars.push_back(std::make_shared<Car>(i));
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
//        std::string file = std::string("images/car") + std::to_string(i + 1) + ".png";
        std::string file = std::string("images/car1") + ".png";
        cars_images[i] = gdk_pixbuf_new_from_file(file.c_str(), 0);
        if(!cars_images[i])
            std::cout << i << std::endl;
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

    r2.x = 0;
    r2.y = 0;
    r2.width = 1000;
    r2.height = 600;

    auto middle_of_screen_x = r2.width / 2;
    auto middle_of_screen_y = r2.height / 2;
    auto middle_of_highway_x = 12 * gdk_pixbuf_get_width(road) * zoom;
    auto middle_of_highway_y = gdk_pixbuf_get_height(road) * zoom / 2.0;

    for(int i = 0; i < 25; i++)
    {

        r1.x = i * gdk_pixbuf_get_width(road) * zoom - gdk_pixbuf_get_width(road) * zoom / 2;
        r1.x = r1.x - middle_of_highway_x;
        r1.x += middle_of_screen_x + (12 - i);
        
        r1.y = middle_of_screen_y - middle_of_highway_y;

        r1.width = std::floor(gdk_pixbuf_get_width(road) * zoom);
        r1.height = std::floor(gdk_pixbuf_get_height(road) * zoom);

        if(gdk_rectangle_intersect(&r1, &r2, &dest)) 
            gdk_pixbuf_composite(road, frame, dest.x, dest.y, dest.width, dest.height, r1.x, r1.y, zoom, zoom, GDK_INTERP_NEAREST, 255);
    };

    for(auto car : cars)
        car->drive(cars);

    for(auto car : cars)
    {
        auto img = cars_images[car->get_type()];
    
        if(car->get_direction() == 1)
            img = gdk_pixbuf_flip(cars_images[car->get_type()], true);

        r1.x = car->get_pos_x() * gdk_pixbuf_get_width(road) * zoom - gdk_pixbuf_get_width(road) * zoom / 2;
        r1.x = r1.x - middle_of_highway_x;
        r1.x += middle_of_screen_x + (12 - car->get_pos_x());
        
        r1.y = 300 + (83 + car->get_pos_y() * 70) * zoom - std::floor(gdk_pixbuf_get_width(img) / 2.0) * zoom;

        r1.width = gdk_pixbuf_get_width(img) * zoom - 1;
        r1.height = gdk_pixbuf_get_width(img) * zoom - 1;
        
        if(gdk_rectangle_intersect(&r1, &r2, &dest)) 
            gdk_pixbuf_composite(img, frame, dest.x, dest.y, dest.width, dest.height, r1.x, r1.y, zoom / 3.0, zoom / 3.0, GDK_INTERP_NEAREST, 255);
        
        if(car->get_direction() == 1)
            g_object_unref(img);
    };

    gtk_widget_queue_draw(draw_area);
};




void MyApp::change_zoom(double delta)
{
    zoom += delta / 10;
    if(zoom > 1.5)
        zoom = 1.5;

    if(zoom < 0.25)
        zoom = 0.25;
};
