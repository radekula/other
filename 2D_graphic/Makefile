# Main makefile
CC:=g++
CFLAGS:=-std=c++14 -c -Wall -O2 `pkg-config --cflags gtk+-3.0`
LIBS=`pkg-config --libs gtk+-3.0` 
OBJDIR:=obj
SRCDIR:=src
APPNAME:=2D_graphic
CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix $(OBJDIR)/,$(notdir $(CPP_FILES:.cpp=.o)))

all: build

build: $(APPNAME)

$(APPNAME): $(OBJ_FILES) 
	$(CC) $(LIBS) $^ -o $(APPNAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CC) $(CFLAGS) $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

.PHONY:clean

clean:
	rm -f $(OBJDIR)/*.o
	rm -f $(APPNAME)
