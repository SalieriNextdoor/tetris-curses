/*
 *  Functions related to the map of the game.
 *  The map is represented as a double array (matrix) of
 *  [NLINES+1][NCOLS+1], where NLINES and NCOLS are the
 *  dimensions of the game window.
 * */
#include "tmap.h"

#include <stdlib.h>

/*
 *  Given a map, initializes all its lines till NLINES-1 to 0.
 *  Line NLINES is initialized to 8 to represent the bottom border.
 * */
void init_map(char map[NLINES + 1][NCOLS + 1]) {
  for (int i = 0; i < NLINES; i++)
    for (int j = 0; j < COLS; j++) map[i][j] = 0;

  // 8 so it won't conflict with 0 (nothing) nor with any of the block types
  for (int j = 0; j < NCOLS + 1; j++) map[NLINES][j] = 8;
}

/*
 *  Given a block, registers it on the map.
 *  Each block is represented on the map by its block type value.
 * */
void update_map(char map[NLINES + 1][NCOLS + 1], t_block* block) {
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      if (block->map[i][j])
        map[block->pos.y + i][block->pos.x + j] = block->type;
}

/*
 *  Draws all map positions within [0,NLINES-1][0,NCOLS-1]
 *  with the respective block colors.
 * */
void draw_map(WINDOW* win, char map[NLINES + 1][NCOLS + 1]) {
  for (int i = 0; i < NLINES; i++)
    for (int j = 0; j < NCOLS; j++) {
      if (map[i][j]) {
        wattron(win, A_REVERSE | COLOR_PAIR(map[i][j]));
        mvwaddch(win, i, j, ' ');
        wattroff(win, A_REVERSE | COLOR_PAIR(map[i][j]));
      }
    }
}

/*
 * Returns the index of a complete line on the map within
 * [block->pos.y,NLINES-1], if it exists. Otherwise returns -1
 */
int check_game_state(char map[NLINES + 1][NCOLS + 1], t_block* last_block) {
  int line = 0;
  for (int i = last_block->pos.y; i < NLINES; i++) {
    line = i;
    for (int j = 0; j < NCOLS; j++) {
      if (!map[i][j]) {
        line = 0;
        break;
      }
    }
    if (line) return line;
  }
  return -1;
}

/*
 * Empties the given line on the map from [0,NCOLS-1].
 * */
void empty_line(char map[NLINES + 1][NCOLS + 1], int line) {
  for (int j = 0; j < NCOLS; j++) map[line][j] = 0;
}

/*
 *  Returns true if a line is fully 0s within [0,COLS-1].
 *  Otherwise returns false.
 * */
bool check_line_empty(char map[NLINES + 1][NCOLS + 1], int line) {
  bool empty = true;
  for (int j = 0; j < NCOLS; j++)
    if (map[line][j]) {
      empty = false;
      break;
    }
  return empty;
}

/*
 *  Given a line, checks if it is empty.
 *  If so, moves the line above to its position.
 *  The previous position of the moved line is turned empty.
 * */
void move_lines_down(char map[NLINES + 1][NCOLS + 1], int line) {
  while (check_line_empty(map, line) && line > 0) {
    line--;
    for (int j = 0; j < NCOLS; j++) {
      map[line + 1][j] = map[line][j];
      map[line][j] = 0;
    }
  }
}
