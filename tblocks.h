/*
 *  Functions and structs related to tetris blocks.
 * */
#ifndef DRAWBLOCKS_H
#define DRAWBLOCKS_H
#include <curses.h>

#include "tcommons.h"

enum tblock_type {
  T_IBLOCK = 1,
  T_OBLOCK = 2,
  T_SBLOCK = 3,
  T_TBLOCK = 4,
  T_LBLOCK = 5,
  T_JBLOCK = 6,
  T_ZBLOCK = 7,
};

typedef struct _t_block {
  point pos;       // current block position
  char map[4][4];  // matrix representing the active points of the block
  enum tblock_type type;
} t_block;

void rotate_block(char map[NLINES + 1][NCOLS + 1], t_block *block);
void update_pos_hor(char map[NLINES + 1][NCOLS + 1], t_block *block, bool dir);
bool update_pos_ver(char map[NLINES + 1][NCOLS + 1], t_block *block);
void draw_tblock(WINDOW *win, t_block *block);
t_block *pick_random_block(char map[NLINES + 1][NCOLS + 1], point pos);
bool check_game_over(void);

#endif
