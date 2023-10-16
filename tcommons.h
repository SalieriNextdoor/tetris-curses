/*
 *  Utility functions, macros and structs.
 * */
#ifndef TCOMMONS_H
#define TCOMMONS_H
#include <curses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ifnullexit(_tptr, _msg) \
  if (_tptr == NULL) {          \
    endwin();                   \
    puts(_msg);                 \
    exit(1);                    \
  }

#define NLINES (24 * 3 / 4)
#define NCOLS (NLINES * 10 / 7)

typedef struct _point {
  int y;
  int x;
} point;

void swap(char *x, char *y);
void copy_matrix(char src[4][4], char to[4][4]);
char *reverse(char *str, uint length);
char *itoa(uint val, char *buf);
#endif
