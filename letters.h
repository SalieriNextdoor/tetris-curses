/*
 *  Letter functions and helper macros for the printing of letters.
 * */
#ifndef TLETTERS_H
#define TLETTERS_H
#include <curses.h>

#include "tcommons.h"

#define print_highlight_horizontal(_prwin, _prstarty, _prstartx, _prcnt) \
  wmove(_prwin, _prstarty, _prstartx);                                   \
  for (int i = 0; i < _prcnt; i++) waddch(_prwin, ' ')

#define print_highlight_vertical(_prwin, _prstarty, _prstartx, _prcnt) \
  for (int i = 0; i < _prcnt; i++)                                     \
  mvwaddch(_prwin, _prstarty + i, _prstartx, ' ')

void print_t(WINDOW *win, int height, int width, point start);
void print_e(WINDOW *win, int height, int width, point start);
void print_r(WINDOW *win, int height, int width, point start);
void print_i(WINDOW *win, int height, int width, point start);
void print_s(WINDOW *win, int height, int width, point start);
#endif
