/*
 *  Functions related to the tetris window that shows the next
 *  block to be picked.
 * */
#ifndef NEXTWIN_H
#define NEXTWIN_H
#include <curses.h>

#include "tblocks.h"
#include "tcommons.h"

WINDOW *init_nextwin(point startpos, int width, int height);
void update_nextwin(WINDOW *nextwin, t_block *next);
void clean_nextwin(WINDOW *nextwin);

#endif
