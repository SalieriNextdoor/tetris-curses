/*
 *  Functions related to the map of the game.
 * */
#ifndef TMAP_H
#define TMAP_H
#include "tblocks.h"
#include "tcommons.h"

void init_map(char map[NLINES + 1][NCOLS + 1], int max_y, int max_x);
void update_map(char map[NLINES + 1][NCOLS + 1], t_block* block);
void draw_map(WINDOW* win, char map[NLINES + 1][NCOLS + 1]);
int check_game_state(char map[NLINES + 1][NCOLS + 1]);
void empty_line(char map[NLINES + 1][NCOLS + 1], int line);
void move_lines_down(char map[NLINES + 1][NCOLS + 1], int line);
#endif
