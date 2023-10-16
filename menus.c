/*
 * Prints the menus logos and messages.
 * */
#include "menus.h"

#include <curses.h>

#include "letters.h"

/*
 * Draws a t-shaped border around the logo in win according to point start.
 * */
void draw_border(WINDOW *win, point start) {
  int y, x;
  getmaxyx(win, y, x);
  int height1 = TYPEHEIGHT + start.y * 2 + 1;
  int width1 = x - start.x * 2;

  print_highlight_horizontal(win, start.y, start.x, width1);
  print_highlight_vertical(win, start.y, start.x, height1);
  print_highlight_vertical(win, start.y, start.x + width1, height1);
  print_highlight_horizontal(win, start.y + height1, start.x, width1 * 2 / 5);
  print_highlight_vertical(win, start.y + height1, start.x + width1 * 2 / 5,
                           height1 / 2);
  getyx(win, y, x);
  print_highlight_horizontal(win, y, x, width1 / 5);
  print_highlight_vertical(win, y - height1 / 2 + 1, x + width1 / 5,
                           height1 / 2);
  print_highlight_horizontal(win, y - height1 / 2 + 1, x + width1 / 5 + 1,
                             width1 * 2 / 5);
}

void print_menu_msg(WINDOW *win, point start, char *msg) {
  wattron(win, A_BLINK | A_BOLD);
  mvwaddstr(win, start.y, start.x, msg);
  wattroff(win, A_BLINK | A_BOLD);
}

/*
 *  Prints a colorful logo in the window starting at point start.
 *  Must have color pairs 1-7, though 6 isn't used.
 * */
void print_start_logo(WINDOW *win, point start) {
  int gap = TYPEGAP + TYPEWIDTH;
  wattron(win, A_REVERSE);
  wattron(win, COLOR_PAIR(1));
  print_t(win, TYPEHEIGHT, TYPEWIDTH, start);
  wattroff(win, COLOR_PAIR(1));
  start.x += gap;
  wattron(win, COLOR_PAIR(7));
  print_e(win, TYPEHEIGHT, TYPEWIDTH, start);
  wattroff(win, COLOR_PAIR(7));
  start.x += gap;
  wattron(win, COLOR_PAIR(2));
  print_t(win, TYPEHEIGHT, TYPEWIDTH, start);
  wattroff(win, COLOR_PAIR(2));
  start.x += gap;
  wattron(win, COLOR_PAIR(3));
  print_r(win, TYPEHEIGHT, TYPEWIDTH, start);
  wattroff(win, COLOR_PAIR(3));
  start.x += gap;
  wattron(win, COLOR_PAIR(4));
  print_i(win, TYPEHEIGHT, TYPEWIDTH, start);
  wattroff(win, COLOR_PAIR(4));
  start.x += gap;
  wattron(win, COLOR_PAIR(5));
  print_s(win, TYPEHEIGHT, TYPEWIDTH, start);
  wattroff(win, COLOR_PAIR(5));

  point borderpoint = {1, 7};
  draw_border(win, borderpoint);
  wattroff(win, A_REVERSE);
}

/*
 *  Creates a full window for the menu, draws it, waits for start
 *  input and erases it.
 *  In case F3 has been pressed, returns true.
 *  Otherwise returns false.
 * */
bool start_menu(void) {
  int c;
  WINDOW *menuwin = newwin(0, 0, 0, 0);
  ifnullexit(menuwin, "menuwin");

  keypad(menuwin, TRUE);
  point start = {3, (COLS - TYPEWIDTH * 6 - TYPEGAP * 5) / 2 - 1};
  print_start_logo(menuwin, start);
  point msgstart = {LINES - 3, (COLS - 22) / 2};
  print_menu_msg(menuwin, msgstart, "PRESS <ENTER> TO START");
  wrefresh(menuwin);

  while ((c = wgetch(menuwin)) != '\n' && c != KEY_F(3))
    ;

  wclear(menuwin);
  wrefresh(menuwin);
  delwin(menuwin);
  if (c == KEY_F(3)) return true;
  return false;
}

