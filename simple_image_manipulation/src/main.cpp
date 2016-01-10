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


Pixbuf *pixbuf;
Image *image;
Label *sasiedztwo_label;


class cords
{
public:
	cords() {x = y = 0;};
	int x;
	int y;

};


bool sprawdzony[200][200];

std::list<std::shared_ptr<cords>> points;



int sasiedztwo = 4;



int refresh_screen(void *)
{
	if(image && pixbuf)
		image->refresh();   
		
	return 1;
};

int fill_to_line(void *data)
{
	if(points.empty())
		return 0;
	
	auto it = points.begin();
	
	auto x = (*it)->x;
	auto y = (*it)->y;
	pixbuf->point(x, y, 255,0,0);

	switch(sasiedztwo)
	{
		case 4:
			{
				if(x < pixbuf->_width / pixbuf->_scale && !sprawdzony[x+1][y])
				{
					auto pixel1 = pixbuf->get_point(x + 1, y);
					if(pixel1[0] == 255 && pixel1[1] == 255)
					{
						std::shared_ptr<cords> point(new cords);
						point->x = x + 1;
						point->y = y;
	
						points.push_back(point);
					};
					
					sprawdzony[x+1][y] = true;
				};

				if(x > 0 && !sprawdzony[x-1][y])
				{
					auto pixel2 = pixbuf->get_point((x - 1), y);
					if(pixel2[0] == 255 && pixel2[1] == 255)
					{
						std::shared_ptr<cords> point(new cords);
						point->x = x - 1;
						point->y = y;
	
						points.push_back(point);
					};
					sprawdzony[x-1][y] = true;
				};
				
				if(y < pixbuf->_height / pixbuf->_scale && !sprawdzony[x][y + 1])
				{
					auto pixel3 = pixbuf->get_point(x, (y + 1));
					if(pixel3[0] == 255 && pixel3[1] == 255)
					{
						std::shared_ptr<cords> point(new cords);
						point->x = x;
						point->y = y + 1;
	
						points.push_back(point);
					};	
					sprawdzony[x][y + 1] = true;
				};

				if(y > 0  && !sprawdzony[x][y - 1])
				{
					auto pixel4 = pixbuf->get_point(x, (y - 1));
					if(pixel4[0] == 255 && pixel4[1] == 255)
					{

						std::shared_ptr<cords> point(new cords);
						point->x = x;
						point->y = y - 1;
	
						points.push_back(point);
					};	
					sprawdzony[x][y - 1] = true;
				};
			}
			break;
		case 6:
			{
				if(x < pixbuf->_width / pixbuf->_scale && !sprawdzony[x+1][y])
				{
					auto pixel1 = pixbuf->get_point(x + 1, y);
					if(pixel1[0] == 255 && pixel1[1] == 255)
					{
						std::shared_ptr<cords> point(new cords);
						point->x = x + 1;
						point->y = y;
	
						points.push_back(point);
					};
					
					sprawdzony[x+1][y] = true;
				};

				if(x > 0 && !sprawdzony[x-1][y])
				{
					auto pixel2 = pixbuf->get_point((x - 1), y);
					if(pixel2[0] == 255 && pixel2[1] == 255)
					{
						std::shared_ptr<cords> point(new cords);
						point->x = x - 1;
						point->y = y;
	
						points.push_back(point);
					};
					sprawdzony[x-1][y] = true;
				};
				
				if(y < pixbuf->_height / pixbuf->_scale && !sprawdzony[x][y + 1])
				{
					auto pixel3 = pixbuf->get_point(x, (y + 1));
					if(pixel3[0] == 255 && pixel3[1] == 255)
					{
						std::shared_ptr<cords> point(new cords);
						point->x = x;
						point->y = y + 1;
	
						points.push_back(point);
					};	
					sprawdzony[x][y + 1] = true;
				};

				if(y > 0  && !sprawdzony[x][y - 1])
				{
					auto pixel4 = pixbuf->get_point(x, (y - 1));
					if(pixel4[0] == 255 && pixel4[1] == 255)
					{

						std::shared_ptr<cords> point(new cords);
						point->x = x;
						point->y = y - 1;
	
						points.push_back(point);
					};	
					sprawdzony[x][y - 1] = true;
				};
				
				if(y > 0 && x > 0 && !sprawdzony[x - 1][y - 1])
				{
					auto pixel4 = pixbuf->get_point((x - 1), (y - 1));
					if(pixel4[0] == 255 && pixel4[1] == 255)
					{

						std::shared_ptr<cords> point(new cords);
						point->x = x - 1;
						point->y = y - 1;
	
						points.push_back(point);
					};	
					sprawdzony[x - 1][y - 1] = true;
				};

				if(y < pixbuf->_height / pixbuf->_scale && x < pixbuf->_width / pixbuf->_scale && !sprawdzony[x + 1][y + 1])
				{
					auto pixel4 = pixbuf->get_point((x + 1), (y + 1));
					if(pixel4[0] == 255 && pixel4[1] == 255)
					{

						std::shared_ptr<cords> point(new cords);
						point->x = x + 1;
						point->y = y + 1;
	
						points.push_back(point);
					};	
					sprawdzony[x + 1][y + 1] = true;
				};
			}
			break;
		case 8:
			{
				if(x < pixbuf->_width / pixbuf->_scale && !sprawdzony[x+1][y])
				{
					auto pixel1 = pixbuf->get_point(x + 1, y);
					if(pixel1[0] == 255 && pixel1[1] == 255)
					{
						std::shared_ptr<cords> point(new cords);
						point->x = x + 1;
						point->y = y;
	
						points.push_back(point);
					};
					
					sprawdzony[x+1][y] = true;
				};

				if(x > 0 && !sprawdzony[x-1][y])
				{
					auto pixel2 = pixbuf->get_point((x - 1), y);
					if(pixel2[0] == 255 && pixel2[1] == 255)
					{
						std::shared_ptr<cords> point(new cords);
						point->x = x - 1;
						point->y = y;
	
						points.push_back(point);
					};
					sprawdzony[x-1][y] = true;
				};
				
				if(y < pixbuf->_height / pixbuf->_scale && !sprawdzony[x][y + 1])
				{
					auto pixel3 = pixbuf->get_point(x, (y + 1));
					if(pixel3[0] == 255 && pixel3[1] == 255)
					{
						std::shared_ptr<cords> point(new cords);
						point->x = x;
						point->y = y + 1;
	
						points.push_back(point);
					};	
					sprawdzony[x][y + 1] = true;
				};

				if(y > 0  && !sprawdzony[x][y - 1])
				{
					auto pixel4 = pixbuf->get_point(x, (y - 1));
					if(pixel4[0] == 255 && pixel4[1] == 255)
					{

						std::shared_ptr<cords> point(new cords);
						point->x = x;
						point->y = y - 1;
	
						points.push_back(point);
					};	
					sprawdzony[x][y - 1] = true;
				};
				
				if(y > 0 && x > 0 && !sprawdzony[x - 1][y - 1])
				{
					auto pixel4 = pixbuf->get_point((x - 1), (y - 1));
					if(pixel4[0] == 255 && pixel4[1] == 255)
					{

						std::shared_ptr<cords> point(new cords);
						point->x = x - 1;
						point->y = y - 1;
	
						points.push_back(point);
					};	
					sprawdzony[x - 1][y - 1] = true;
				};

				if(y < pixbuf->_height / pixbuf->_scale && x < pixbuf->_width / pixbuf->_scale && !sprawdzony[x + 1][y + 1])
				{
					auto pixel4 = pixbuf->get_point((x + 1), (y + 1));
					if(pixel4[0] == 255 && pixel4[1] == 255)
					{

						std::shared_ptr<cords> point(new cords);
						point->x = x + 1;
						point->y = y + 1;
	
						points.push_back(point);
					};	
					sprawdzony[x + 1][y + 1] = true;
				};
				
				if(y > 0 && x < pixbuf->_width / pixbuf->_scale && !sprawdzony[x + 1][y - 1])
				{
					auto pixel4 = pixbuf->get_point((x + 1), (y - 1));
					if(pixel4[0] == 255 && pixel4[1] == 255)
					{

						std::shared_ptr<cords> point(new cords);
						point->x = x + 1;
						point->y = y - 1;
	
						points.push_back(point);
					};	
					sprawdzony[x + 1][y - 1] = true;
				};

				if(y < pixbuf->_height / pixbuf->_scale && x > 0 && !sprawdzony[x - 1][y + 1])
				{
					auto pixel4 = pixbuf->get_point((x - 1), (y + 1));
					if(pixel4[0] == 255 && pixel4[1] == 255)
					{

						std::shared_ptr<cords> point(new cords);
						point->x = x - 1;
						point->y = y + 1;
	
						points.push_back(point);
					};	
					sprawdzony[x - 1][y + 1] = true;
				};
			}
			break;
		default:
			break;
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


void s_4(GtkWidget *button, void *user_data)
{
	sasiedztwo = 4;
	sasiedztwo_label->set_label("  Sąsiedztwo: 4 ");
};

void s_6(GtkWidget *button, void *user_data)
{
	sasiedztwo = 6;
	sasiedztwo_label->set_label("  Sąsiedztwo: 6 ");
};

void s_8(GtkWidget *button, void *user_data)
{
	sasiedztwo = 8;
	sasiedztwo_label->set_label("  Sąsiedztwo: 8 ");
};

void line_fill(GtkWidget *button, void *user_data)
{
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

	for(int i = 0; i < 100; i++)
		for(int l = 0; l < 100; l++)
			sprawdzony[i][l] = false;

	sprawdzony[point->x][point->y] = true;

	g_timeout_add(1, fill_to_line, 0);
};






int main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);

	Window *main_window = new Window();
	main_window->resize(-1,-1);

	VBox *main_vbox = new VBox();

	HBox *menu_hbox = new HBox();
	Button *line_button = new Button("Linia");
	line_button->set_on_clicked(line_fill);
	
	Button *polygon_button = new Button("Kszałt");

	sasiedztwo_label = new Label("  Sąsiedztwo: 4 ");

	menu_hbox->add(line_button, 0, 0, 0);
	menu_hbox->add(polygon_button, 0, 0, 0);
	menu_hbox->add(sasiedztwo_label, 0, 0, 0);
	main_vbox->add(menu_hbox, 0, 0, 0);
	
    pixbuf = new Pixbuf();
    pixbuf->set_scale(5);

	image = new Image();
	image->set_from_pixbuf(pixbuf);  
	main_vbox->add(image, 1, 1, 0);
 
    clear_image(line_button->get_ref(), 0);   

	HBox *button_hbox = new HBox();
	
	Button *sasiedztwo_4 = new Button("Sąsiedztwo 4");
	sasiedztwo_4->set_on_clicked(s_4);
	
	Button *sasiedztwo_6 = new Button("Sąsiedztwo 6");
	sasiedztwo_6->set_on_clicked(s_6);
	
	Button *sasiedztwo_8 = new Button("Sąsiedztwo 8");
	sasiedztwo_8->set_on_clicked(s_8);
	
	Button *reset_button = new Button("Wyczyść");
	reset_button->set_on_clicked(clear_image);

	button_hbox->add(sasiedztwo_4, 0, 0, 0);
	button_hbox->add(sasiedztwo_6, 0, 0, 0);
	button_hbox->add(sasiedztwo_8, 0, 0, 0);
	button_hbox->add(reset_button, 0, 0, 0);

	main_vbox->add(button_hbox, 0, 0, 0);
	
	main_window->add(main_vbox);
	main_window->show();

	g_timeout_add(50, refresh_screen, 0);
	
	gtk_main();
		
	return 0;
};
