CC=g++
CFLAGS=-std=c++14 `pkg-config --cflags gtk+-2.0`
LIBS=-std=c++14 `pkg-config --libs gtk+-2.0`


all:
		rm -f obj/*
		$(CC) $(CFLAGS) -c src/main.cpp -o obj/main.o
		$(CC) $(CFLAGS) -c src/window.cpp -o obj/window.o
		$(CC) $(CFLAGS) -c src/vbox.cpp -o obj/vbox.o
		$(CC) $(CFLAGS) -c src/hbox.cpp -o obj/hbox.o
		$(CC) $(CFLAGS) -c src/pixmap.cpp -o obj/pixmap.o
		$(CC) $(CFLAGS) -c src/pixbuf.cpp -o obj/pixbuf.o
		$(CC) $(CFLAGS) -c src/drawing_area.cpp -o obj/drawing_area.o
		$(CC) $(CFLAGS) -c src/button.cpp -o obj/button.o
		$(CC) $(CFLAGS) -c src/toggle_button.cpp -o obj/toggle_button.o
		$(CC) $(CFLAGS) -c src/label.cpp -o obj/label.o
		$(CC) $(CFLAGS) -c src/image.cpp -o obj/image.o
		$(CC) $(CFLAGS) -c src/table.cpp -o obj/table.o
		
		$(CC) -o simple_image_manipulation obj/*.o $(LIBS) 
