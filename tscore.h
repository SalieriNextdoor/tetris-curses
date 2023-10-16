/*
 *  Functions and structures related to keeping track of score.
 * */
#ifndef TSCORE_H
#define TSCORE_H
#include "tcommons.h"

typedef struct _tscore {
  uint score;
  char *scorestr;
} tscore;

WINDOW *init_scorewin(point startpos, tscore *score, int width, int height);
void update_score(WINDOW *scorewin, tscore *score, int lines_cleared);
void clean_scorewin(WINDOW *scorewin, tscore *score);

#endif
