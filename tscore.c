/*
 *  Functions related to keeping track of score.
 * */
#include "tscore.h"

#include <string.h>

/*
 *  Draws the score window with the current score.
 * */
void draw_scorewin(WINDOW *scorewin, tscore *score) {
  int y __attribute__((unused)), x;
  getmaxyx(scorewin, y, x);

  werase(scorewin);
  wattron(scorewin, A_REVERSE);
  wborder(scorewin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
  wattroff(scorewin, A_REVERSE);
  mvwaddstr(scorewin, 1, (x - 5) / 2, "SCORE");

  int len = strlen(score->scorestr);
  wmove(scorewin, 2, (x - TSDIGITS) / 2);
  for (int i = 0; i < TSDIGITS; i++) {
    if (i < TSDIGITS - len)
      waddch(scorewin, '0');
    else
      waddch(scorewin, *(score->scorestr + i - (TSDIGITS - len)));
  }
}

/*
 *  Initializes the window for the score-keping and
 *  its associated string of TSDIGITS digits.
 * */
WINDOW *init_scorewin(point startpos, tscore *score, int width, int height) {
  WINDOW *scorewin = newwin(height, width, startpos.y, startpos.x);
  ifnullexit(scorewin, "init_scorewin");
  score->scorestr = malloc((TSDIGITS + 1) * sizeof(char));
  ifnullexit(score->scorestr, "init_scorewin2");
  *score->scorestr = '0';
  *(score->scorestr + 1) = '\0';
  draw_scorewin(scorewin, score);
  wrefresh(scorewin);
  return scorewin;
}

/*
 *  Given the amount of lines cleared at once, adds the corresponding
 *  value to the score.
 * */
void update_score_val(tscore *score, int lines_cleared) {
  switch (lines_cleared) {
    case 0:
      return;
      break;
    case 1:
      score->score += 40;
      break;
    case 2:
      score->score += 100;
      break;
    case 3:
      score->score += 300;
      break;
    default:
      score->score += 1200;
      break;
  }
  score->scorestr = itoa(score->score, score->scorestr);
}

/*
 *  Updates the struct with a call to update_score_val.
 *  It then calls draw_scorewin and refreshes the window.
 * */
void update_score(WINDOW *scorewin, tscore *score, int lines_cleared) {
  update_score_val(score, lines_cleared);
  draw_scorewin(scorewin, score);
  wrefresh(scorewin);
}

/*
 *  Cleanup function. Clears the score window and
 *  frees associated pointers.
 * */
void clean_scorewin(WINDOW *scorewin, tscore *score) {
  wclear(scorewin);
  wrefresh(scorewin);
  delwin(scorewin);
  free(score->scorestr);
}
