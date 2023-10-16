/*
 *  Functions related to the tetris window that shows the next
 *  block to be picked.
 * */
#include "nextwin.h"

#include <string.h>

#include "tblocks.h"

t_block *next = NULL;

/*
 *  Initializes the window in correct position and dimensions.
 *  Returns the pointer to the window.
 * */
WINDOW *init_nextwin(point startpos, int width, int height) {
  WINDOW *nextwin = newwin(height, width, startpos.y, startpos.x);
  ifnullexit(nextwin, "init_nextwin");
  return nextwin;
}

/*
 *  Draws the window initialized in init_nextwin.
 * */
void draw_nextwin(WINDOW *nextwin) {
  int y __attribute__((unused)), x;
  getmaxyx(nextwin, y, x);

  werase(nextwin);
  wattron(nextwin, A_REVERSE);
  wborder(nextwin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
  wattroff(nextwin, A_REVERSE);
  mvwaddstr(nextwin, 2, (x - 4) / 2, "NEXT");

  // one of the i-block rotations doesn't fit well
  if (next->type == T_IBLOCK && next->map[0][0]) {
    next->pos.y--;
    draw_tblock(nextwin, next);
    next->pos.y++;
  } else
    draw_tblock(nextwin, next);
}

/*
 *  Updates the window with a new block t_block.
 *  Calls draw_nextwin and refreshes.
 * */
void update_nextwin(WINDOW *nextwin, t_block *block) {
  if (next != NULL) free(next);
  next = (t_block *)malloc(sizeof(t_block));
  ifnullexit(next, "update_nextwin");

  copy_matrix(block->map, next->map);
  int pivoti = 0, pivotj = 0;
  for (int i = 3; i >= 0; i--) {
    for (int j = 3; j >= 0; j--) {
      if (block->map[i][j] && !pivotj) {
        pivoti = i;
        pivotj = j;
      }
    }
  }

  next->pos.x = 10 - pivotj;
  next->pos.y = 6 - pivoti;
  next->type = block->type;

  draw_nextwin(nextwin);
  wrefresh(nextwin);
}

/*
 *  Cleanup function. Erases nextwin and frees all associated pointers.
 * */
void clean_nextwin(WINDOW *nextwin) {
  wclear(nextwin);
  delwin(nextwin);
  free(next);
}
