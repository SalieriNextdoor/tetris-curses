/*
 *  General functions for utility purposes.
 * */
#include "tcommons.h"

#include <string.h>

/*
 *  Simply swaps the contents of two char pointers.
 * */
void swap(char *x, char *y) {
  char temp = *x;
  *x = *y;
  *y = temp;
}

/*
 *  Given two 4x4 matrixes, copies the contents of src to matrix to.
 * */
void copy_matrix(char src[4][4], char to[4][4]) {
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) to[i][j] = src[i][j];
}

/*
 *  Given a string and its length, reverses it.
 *  Returns a pointer to the first character.
 * */
char *reverse(char *str, uint length) {
  char *temp = strdup(str);
  ifnullexit(temp, "reverse");
  temp += length;

  while (*str != '\0') *str++ = *--temp;
  free(temp);
  return str - length;
}

/*
 *  Given an int value and a char buffer, adds digits in character
 *  form to buffer.
 *  Returns a pointer to the first char of the buffer.
 * */
char *itoa(uint val, char *buf) {
  char *bufbegin = buf;
  do {
    *buf++ = (val % 10) + '0';
    val /= 10;
  } while (val != 0);
  *buf = '\0';
  return reverse(bufbegin, buf - bufbegin);
}
