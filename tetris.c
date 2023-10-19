/*
 *  A simple Tetris game in the terminal.
 *  Use the arrow keys to move the block, z to rotate, space
 *  to drop the block and F3 to exit.
 *  Works best on a 80x24 terminal screen with color capabilities.
 * */
#include <curses.h>
#include <time.h>
#include <unistd.h>

#include "menus.h"
#include "nextwin.h"
#include "tblocks.h"
#include "tmap.h"
#include "tscore.h"

#define DELAYU 300000UL

tscore score = {0, "0000000"};
char map[NLINES + 1][NCOLS + 1];

void init_curses(void) {
  initscr();
  cbreak();
  noecho();
  curs_set(0);
  start_color();
}

void init_colors(void) {
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_BLUE, COLOR_BLACK);
  init_pair(3, COLOR_GREEN, COLOR_BLACK);
  init_pair(4, COLOR_YELLOW, COLOR_BLACK);
  init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(6, COLOR_WHITE, COLOR_BLACK);
  init_pair(7, COLOR_CYAN, COLOR_BLACK);
}

/*
 *  Initializes the game window and creates a border around it
 *  as part of its own window.
 *  Assigns both windows to pointer to pointer gamewin and borderwin.
 * */
void init_gamewin(WINDOW **gamewin, WINDOW **borderwin) {
  *gamewin = newwin(NLINES, NCOLS, (LINES - NLINES) / 2, (COLS - NCOLS) / 2);
  *borderwin = newwin(NLINES + 2, NCOLS + 2, (LINES - NLINES) / 2 - 1,
                      (COLS - NCOLS) / 2 - 1);
  ifnullexit(*gamewin, "gamewin");
  ifnullexit(*borderwin, "borderwin");
  wattron(*borderwin, A_REVERSE);
  wborder(*borderwin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
  wattroff(*borderwin, A_REVERSE);
  wrefresh(*borderwin);
  wtimeout(*gamewin, 0);
  keypad(*gamewin, TRUE);
}

/*
 * Cleanup function.
 * Clears and deletes used windows.
 * */
void cleanup(WINDOW **gamewin, WINDOW **borderwin, WINDOW **nextwin,
             WINDOW **scorewin) {
  wclear(*borderwin);
  wrefresh(*borderwin);
  delwin(*borderwin);
  wclear(*gamewin);
  wrefresh(*gamewin);
  delwin(*gamewin);
  clean_nextwin(*nextwin);
  clean_scorewin(*scorewin, &score);
}

int main() {
  WINDOW *gamewin;
  WINDOW *borderwin;
  WINDOW *nextwin;
  WINDOW *scorewin;
  int c, line;

  init_curses();
  init_colors();
  srand(time(NULL));

  bool force_exit = start_menu();

  init_gamewin(&gamewin, &borderwin);

  point next_startpos = {5, COLS - 25};
  nextwin = init_nextwin(next_startpos, 20, 10);

  point score_startpos = {1, COLS - 25};
  scorewin = init_scorewin(score_startpos, &score, 20, 5);

  point startpos = {1, NCOLS / 2};
  t_block *cur = pick_random_block(map, startpos);
  t_block *next = pick_random_block(map, startpos);
  t_block *prev = NULL;
  init_map(map);
  update_nextwin(nextwin, next);

  uint accum = 1;
  int scorecnt = 0;
  bool skip = false;
  while ((c = wgetch(gamewin)) != KEY_F(3) && !force_exit) {
    flushinp();
    draw_tblock(gamewin, cur);
    draw_map(gamewin, map);
    wrefresh(gamewin);

    usleep(DELAYU);
    switch (c) {
      case KEY_RIGHT:
        update_pos_hor(map, cur, false);
        break;
      case KEY_LEFT:
        update_pos_hor(map, cur, true);
        break;
      case 'z':
      case 'Z':
        rotate_block(map, cur);
        break;
      case ' ':
        while (!update_pos_ver(map, cur))
          ;
        skip = true;
        break;
    }

    // accum makes it so that the block goes down once
    // every two UDELAYs
    if ((accum % 2 == 0 && update_pos_ver(map, cur)) || skip) {
      skip = false;
      prev = cur;
      cur = next;
      next = pick_random_block(map, startpos);
      update_nextwin(nextwin, next);
    }

    if (check_game_over()) {
      wtimeout(gamewin, -1);
      wattron(gamewin, A_BOLD);
      mvwaddstr(gamewin, 0, (NCOLS - 9) / 2, "GAME OVER");
      wattroff(gamewin, A_BOLD);
      wrefresh(gamewin);
      wgetch(gamewin);
      break;
    }
    if (prev != NULL) {
      while ((line = check_game_state(map, prev)) != -1) {
        empty_line(map, line);
        move_lines_down(map, line);
        scorecnt++;
      }
      free(prev);
      prev = NULL;
    }

    update_score(scorewin, &score, scorecnt);
    scorecnt = 0;

    werase(gamewin);
    accum++;
  }

  cleanup(&gamewin, &borderwin, &nextwin, &scorewin);
  if (cur != NULL) free(cur);
  if (prev != NULL) free(prev);

  endwin();
  return 0;
}

