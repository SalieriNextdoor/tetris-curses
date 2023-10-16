/*
 * Functions related to printing letters used for the menu logos.
 * Typefont based on the Commodore 64 typefont.
 * */
#include "letters.h"

void print_t(WINDOW *win, int height, int width, point start) {
  print_highlight_horizontal(win, start.y, start.x, width);
  print_highlight_horizontal(win, start.y, start.x, width);
  print_highlight_vertical(win, start.y + 1, start.x + width / 2, height - 1);
  print_highlight_vertical(win, start.y + 1, start.x + width / 2 - 1,
                           height - 1);
}

void print_e(WINDOW *win, int height, int width, point start) {
  print_highlight_horizontal(win, start.y, start.x, width);
  print_highlight_horizontal(win, start.y + height - 1, start.x, width);
  print_highlight_horizontal(win, start.y + height / 2 - 1, start.x,
                             2 * width / 3 + 1);
  print_highlight_vertical(win, start.y, start.x, height);
  print_highlight_vertical(win, start.y, start.x + 1, height);
}

void print_r(WINDOW *win, int height, int width, point start) {
  print_highlight_vertical(win, start.y, start.x, height);
  print_highlight_vertical(win, start.y, start.x + 1, height);
  print_highlight_horizontal(win, start.y, start.x, width - 1);
  print_highlight_vertical(win, start.y, start.x + width - 2, 4);
  print_highlight_vertical(win, start.y + 1, start.x + width - 1, 2);
  print_highlight_horizontal(win, start.y + 3, start.x + 2, 4);
  print_highlight_horizontal(win, start.y + 4, start.x + 2, 3);
  print_highlight_horizontal(win, start.y + 5, start.x + 4, 2);
  print_highlight_horizontal(win, start.y + 6, start.x + 5, 2);
  print_highlight_horizontal(win, start.y + 7, start.x + 6, 2);
}

void print_i(WINDOW *win, int height, int width, point start) {
  print_t(win, height, width, start);
  print_highlight_horizontal(win, start.y + height - 1, start.x, width);
}

void print_s(WINDOW *win, int height, int width, point start) {
  print_highlight_horizontal(win, start.y, start.x + 1, width - 2);
  print_highlight_horizontal(win, start.y + 1, start.x, 2);
  print_highlight_horizontal(win, start.y + 2, start.x, 2);
  print_highlight_horizontal(win, start.y + 1, start.x + width - 2, 2);
  print_highlight_horizontal(win, start.y + 3, start.x + 1, width - 2);
  print_highlight_vertical(win, start.y + 4, start.x + width - 2, 3);
  print_highlight_vertical(win, start.y + 4, start.x + width - 1, 3);
  print_highlight_horizontal(win, start.y + height - 1, start.x + 1, width - 2);
  print_highlight_horizontal(win, start.y + height - 2, start.x, 2);
}
