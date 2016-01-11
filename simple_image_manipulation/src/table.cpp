#include "table.h"



Table::Table()
{
	_ref = gtk_table_new(1,1,0);
};


Table::~Table()
{
};



void Table::add(Element *elem, int x, int y, int w, int h)
{
	if(_ref)
		gtk_table_attach(GTK_TABLE(_ref), elem->get_ref(), x, w, y, h, GTK_EXPAND, GTK_EXPAND, 0, 0);
};


