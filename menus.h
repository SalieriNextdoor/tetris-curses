/*
 *  Menu functions and type info constants.
 * */
#ifndef TSTARTMENU_H
#define TSTARTMENU_H
#include <curses.h>

#define TYPEWIDTH 8
#define TYPEHEIGHT 8
#define TYPEGAP 2

#include "tcommons.h"
void print_start_logo(WINDOW *win, point start);
void print_menu_msg(WINDOW *win, point start, char *msg);
bool start_menu(void);

#endif

