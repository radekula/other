#include <gtk/gtk.h>
#include "vbox.h"
#include "hbox.h"
#include "button.h"
#include "window.h"
#include "image.h"
#include "label.h"
#include "pixbuf.h"




int main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);

	Window *main_window = new Window();
	main_window->resize(-1,-1);

	VBox *main_vbox = new VBox();

	HBox *menu_hbox = new HBox();
	Button *line_button = new Button("Linia");
	Button *polygon_button = new Button("Kszałt");

	Label *l1 = new Label("  Sąsiedztwo:  ");

	menu_hbox->add(line_button, 0, 0, 0);
	menu_hbox->add(polygon_button, 0, 0, 0);
	menu_hbox->add(l1, 0, 0, 0);
	main_vbox->add(menu_hbox, 0, 0, 0);
	
	Image *image = new Image();
	main_vbox->add(image, 1, 1, 0);
    
    Pixbuf *pixbuf = new Pixbuf();
    image->set_from_pixbuf(pixbuf);    

	HBox *button_hbox = new HBox();
	Button *redraw_button = new Button("Rysuj");
	Button *reset_button = new Button("Resetuj");

	button_hbox->add(redraw_button, 0, 0, 0);
	button_hbox->add(reset_button, 0, 0, 0);

	main_vbox->add(button_hbox, 0, 0, 0);
	
	main_window->add(main_vbox);
	main_window->show();
	
	gtk_main();
		
	return 0;
};
