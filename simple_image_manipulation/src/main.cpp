#include <iostream>
#include <gtk/gtk.h>
#include <list>
#include <memory>
#include "memory.h"
#include "vbox.h"
#include "hbox.h"
#include "button.h"
#include "window.h"
#include "image.h"
#include "label.h"
#include "pixbuf.h"
#include "toggle_button.h"
#include "table.h"


class cords
{
public:
	cords() {x = y = 0;};
	int x;
	int y;

};




Pixbuf *pixbuf;
Image *image;
ToggleButton *sasiedztwo[3][3];
bool sprawdzony[101][101];
std::list<std::shared_ptr<cords>> points;
bool do_the_job = false;





int refresh_screen(void *)
{
	if(image && pixbuf)
		image->refresh();   
		
	return 1;
};



int fill_to_line(void *data)
{
	if(points.empty() || do_the_job == false)
		return 0;
		
	auto it = points.begin();
	
	auto x = (*it)->x;
	auto y = (*it)->y;
	pixbuf->point(x, y, 255,0,0);	
	
	for(int s_y = 0; s_y < 3; s_y++)
	{
		for(int s_x = 0; s_x < 3; s_x++)
		{	
			if(s_x == 1 && s_y == 1)
				continue;
				
			if(sasiedztwo[s_x][s_y]->get_active())
			{
				int n_x = (x + s_x) - 1;
				int n_y = (y + s_y) - 1;
				
				if(n_x < 0 || n_x >= 100)
					continue;

				if(n_y < 0 || n_y >= 100)
					continue;
					
				if(sprawdzony[n_x][n_y])
					continue;
					
				auto pixel = pixbuf->get_point(n_x, n_y);
				if(pixel[0] == 255 && pixel[1] == 255)
				{
					std::shared_ptr<cords> point(new cords);
					point->x = n_x;
					point->y = n_y;
					points.push_back(point);
				};
					
				sprawdzony[n_x][n_y] = true;
			};
		};
	};

	points.pop_front();

	return 1;
};



void clear_image(GtkWidget *button, void *user_data)
{
	for(int i = 0; i < pixbuf->_width / pixbuf->_scale; i++)
	{
		for(int l = 0; l < pixbuf->_height / pixbuf->_scale; l++)
		{
			pixbuf->point(i, l, 255, 255, 255);
		};
	};
};



void line_fill(GtkWidget *button, void *user_data)
{
	do_the_job = true;
	
	clear_image(button, user_data);
	
	for(int i = 0; i < pixbuf->_width / pixbuf->_scale; i++)
	{
		pixbuf->point(i, i, 0, 0, 0);
	};
	
	points.erase(points.begin(), points.end());

	std::shared_ptr<cords> point(new cords);
	point->x = (pixbuf->_width / pixbuf->_scale) / 3;
	point->y = (pixbuf->_height / pixbuf->_scale) * 3 / 5;
	
	points.push_back(point);

	for(int i = 0; i < 101; i++)
		for(int l = 0; l < 101; l++)
			sprawdzony[i][l] = false;

	sprawdzony[point->x][point->y] = true;

	g_timeout_add(1, fill_to_line, 0);
};




void stop(GtkWidget *button, void *user_data)
{
	do_the_job = false;
};



int main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);

	Window *main_window = new Window();
	main_window->resize(-1,-1);

	VBox *main_vbox = new VBox();
	HBox *menu_hbox = new HBox();
	
	Label *label = new Label("Sąsiedztwo: ");
	menu_hbox->add(label, 0, 0, 0);
	
	Table *table = new Table();
	menu_hbox->add(table, 0, 0, 0);
	
	for(int y = 0; y < 3; y++)
	{
		for(int x = 0; x < 3; x++)
		{
			sasiedztwo[x][y] = new ToggleButton();
			sasiedztwo[x][y]->set_label(std::to_string(x + (y * 3) + 1));
			
			if(x == 1 && y == 1)
			{
				table->add(new Label("x"), x, y, x + 1, y + 1);
				continue;
			};
			
			table->add(sasiedztwo[x][y], x, y, x + 1, y + 1);
		};
	};
		
	main_vbox->add(menu_hbox, 0, 0, 0);
	
    pixbuf = new Pixbuf();
    pixbuf->set_scale(5);

	image = new Image();
	image->set_from_pixbuf(pixbuf);  
	main_vbox->add(image, 1, 1, 0);
 
	Button *start_button = new Button("Start");
	start_button->set_on_clicked(line_fill);
	main_vbox->add(start_button, 0, 0, 0);

	Button *stop_button = new Button("Stop");
	stop_button->set_on_clicked(stop);
	main_vbox->add(stop_button, 0, 0, 0);
	
	main_window->add(main_vbox);

    clear_image(main_window->get_ref(), 0);   
	main_window->show();
	
	g_timeout_add(50, refresh_screen, 0);
	
	gtk_main();
		
	return 0;
};
