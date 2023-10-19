#include <assert.h>
#include <string.h>
#include <time.h>

#include "tblocks.h"
#include "tcommons.h"
#include "tmap.h"
#include "tscore.h"
t_block *new_block(char map[NLINES + 1][NCOLS + 1], point pos,
                   enum tblock_type type);
bool check_line_empty(char map[NLINES + 1][NCOLS + 1], int line);
bool check_for_col(char map[NLINES + 1][NCOLS + 1], t_block *block);
int get_max_width(t_block *block);
int get_min_width(t_block *block);
int get_max_height(t_block *block);
void update_score_val(tscore *score, int lines_cleared);

char map[NLINES + 1][NCOLS + 1];
extern bool game_over;

extern t_block iblock;
extern t_block jblock;
extern t_block lblock;
extern t_block oblock;
extern t_block sblock;
extern t_block tblock;
extern t_block zblock;

void tcommons_swap(void) {
  char x = 0, y = 4;
  swap(&x, &y);
  assert(x == 4 && y == 0);
}

void tcommons_copy_matrix(void) {
  char mat1[4][4] = {
      {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
  char mat2[4][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
  copy_matrix(mat1, mat2);
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) assert(mat2[i][j] == mat1[i][j]);
}

void tcommons_reverse(void) {
  char *test = strdup("Hello");
  assert(strcmp("olleH", reverse(test, 5)) == 0);
  char *test2 = strdup("");
  assert(strcmp("", reverse(test2, 0)) == 0);
  free(test);
  free(test2);
}

void tcommons_itoa(void) {
  char *test = (char *)malloc(10 * sizeof(char));
  assert(strcmp(itoa(0, test), "0") == 0);
  assert(strcmp(itoa(10, test), "10") == 0);
  assert(strcmp(itoa(100000000, test), "100000000") == 0);
  free(test);
}

void test_tcommons(void) {
  tcommons_swap();
  tcommons_copy_matrix();
  tcommons_reverse();
  tcommons_itoa();
}

bool comp_matrix(char map1[4][4], char map2[4][4]) {
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      if (map1[i][j] != map2[i][j]) return false;
  return true;
}

void tblocks_new_block(void) {
  init_map(map);
  game_over = false;
  point pos = {0, NCOLS / 2};
  t_block *block;
  for (int i = T_IBLOCK; i <= T_ZBLOCK; i++) {
    block = new_block(map, pos, i);
    assert(block->type == i);
    assert(block->pos.x == pos.x && block->pos.y == pos.y);
    switch (i) {
      case T_IBLOCK:
        assert(comp_matrix(iblock.map, block->map));
        break;
      case T_JBLOCK:
        assert(comp_matrix(jblock.map, block->map));
        break;
      case T_LBLOCK:
        assert(comp_matrix(lblock.map, block->map));
        break;
      case T_OBLOCK:
        assert(comp_matrix(oblock.map, block->map));
        break;
      case T_SBLOCK:
        assert(comp_matrix(sblock.map, block->map));
        break;
      case T_TBLOCK:
        assert(comp_matrix(tblock.map, block->map));
        break;
      case T_ZBLOCK:
        assert(comp_matrix(zblock.map, block->map));
        break;
    }
    free(block);
  }
  pos.y = NLINES - 3;
  block = new_block(map, pos, T_SBLOCK);
  assert(block->pos.x == pos.x && block->pos.y == pos.y);
  assert(game_over);
  free(block);
}

void tblocks_check_for_col(void) {
  init_map(map);
  point pos = {0, NCOLS / 2};
  t_block *block = new_block(map, pos, T_IBLOCK);
  assert(!check_for_col(map, block));
  block->pos.y++;
  map[4][NCOLS / 2] = 3;
  assert(check_for_col(map, block));
  point pos2 = {NLINES - 3, 0};
  t_block *block2 = new_block(map, pos2, T_IBLOCK);
  assert(check_for_col(map, block2));
  free(block);
  free(block2);
}

void tblocks_pick_random_block(void) {
  init_map(map);
  srand(time(NULL));
  int possibles[7] = {0};
  point pos = {0, NCOLS / 2};
  t_block *block;
  for (int i = 0; i < 10000; i++) {
    block = pick_random_block(map, pos);
    possibles[block->type - 1]++;
    free(block);
  }
  for (int i = 0; i < 7; i++) assert(possibles[i] > 1200);
}

void tblocks_get_min_width(void) {
  point pos = {0, NCOLS / 2};
  t_block *block = new_block(map, pos, T_IBLOCK);
  assert(get_min_width(block) == 0);
  block->map[3][0] = 0;
  assert(get_min_width(block) == 1);
  free(block);
}

void tblocks_get_max_width(void) {
  point pos = {0, NCOLS / 2};
  t_block *block = new_block(map, pos, T_IBLOCK);
  assert(get_max_width(block) == 3);
  free(block);
  block = new_block(map, pos, T_LBLOCK);
  assert(get_max_width(block) == 2);
  free(block);
}

void tblocks_get_max_height(void) {
  point pos = {0, NCOLS / 2};
  t_block *block = new_block(map, pos, T_IBLOCK);
  assert(get_max_height(block) == 3);
  free(block);
  block = new_block(map, pos, T_TBLOCK);
  block->map[3][1] = 0;
  assert(get_max_height(block) == 2);
  free(block);
}

void tblocks_rotate_block(void) {
  init_map(map);
  point pos = {4, NCOLS / 2};
  t_block *block = new_block(map, pos, T_IBLOCK);
  char comp[4][4] = {{1, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}};
  point newpos = {4, 13};
  rotate_block(map, block);
  assert(comp_matrix(comp, block->map));
  assert(block->pos.y == newpos.y && block->pos.x == newpos.x);
  free(block);
  map[4][13] = 1;
  block = new_block(map, pos, T_IBLOCK);
  copy_matrix(block->map, comp);
  rotate_block(map, block);
  assert(comp_matrix(comp, block->map));
  assert(block->pos.y == pos.y && block->pos.x == pos.x);
  free(block);
}

void tblocks_update_pos_hor(void) {
  init_map(map);
  point pos = {0, NCOLS / 2};
  t_block *block = new_block(map, pos, T_IBLOCK);
  update_pos_hor(map, block, true);
  assert(block->pos.x == pos.x - 1);
  update_pos_hor(map, block, false);
  assert(block->pos.x == pos.x);
  map[3][NCOLS / 2 - 1] = 1;
  update_pos_hor(map, block, true);
  assert(block->pos.x == pos.x);
  map[3][NCOLS / 2 + 4] = 1;
  update_pos_hor(map, block, false);
  assert(block->pos.x == pos.x);
  block->pos.x = 0;
  update_pos_hor(map, block, true);
  assert(block->pos.x == 0);
  block->pos.x = NCOLS - 4;
  update_pos_hor(map, block, false);
  assert(block->pos.x == NCOLS - 4);
  free(block);
}

void tblocks_update_pos_ver(void) {
  init_map(map);
  point pos = {0, COLS / 2};
  t_block *block = new_block(map, pos, T_IBLOCK);
  assert(!update_pos_ver(map, block));
  assert(block->pos.y == 1);
  map[5][COLS / 2] = 1;
  assert(update_pos_ver(map, block));
  assert(block->pos.y == 1);
  free(block);
}

void test_tblocks(void) {
  tblocks_check_for_col();
  tblocks_new_block();
  tblocks_pick_random_block();
  tblocks_get_min_width();
  tblocks_get_max_width();
  tblocks_get_max_height();
  tblocks_rotate_block();
  tblocks_update_pos_hor();
  tblocks_update_pos_ver();
}

void tmap_update_map(void) {
  init_map(map);
  point pos = {NLINES / 2, NCOLS / 2};
  t_block *block = new_block(map, pos, T_JBLOCK);
  update_map(map, block);
  for (int i = pos.y; i < pos.y + 4; i++)
    for (int j = pos.x; j < pos.x + 4; j++)
      if (block->map[i - pos.y][j - pos.x]) assert(map[i][j] == T_JBLOCK);
  free(block);
}

void tmap_check_game_state(void) {
  init_map(map);
  point pos = {NLINES - 4, 0};
  t_block *dummy = new_block(map, pos, T_JBLOCK);
  for (int j = 0; j < NCOLS; j++) map[NLINES - 3][j] = 1;
  assert(check_game_state(map, dummy) == NLINES - 3);
  dummy->pos.y = NLINES - 1;
  assert(check_game_state(map, dummy) == -1);
  dummy->pos.y = NLINES - 4;
  map[NLINES - 3][0] = 0;
  assert(check_game_state(map, dummy) == -1);
  free(dummy);
}

void tmap_check_line_empty(void) {
  assert(check_line_empty(map, 0));
  assert(!check_line_empty(map, NLINES - 3));
}

void tmap_empty_line(void) {
  empty_line(map, 0);
  assert(check_line_empty(map, 0));
  empty_line(map, NLINES - 3);
  assert(check_line_empty(map, NLINES - 3));
}

void tmap_move_lines_down(void) {
  init_map(map);
  for (int j = 0; j < NCOLS; j++) {
    map[NLINES - 3][j] = 4;
    map[NLINES - 4][j] = 7;
    map[NLINES - 6][j] = 1;
  }
  move_lines_down(map, NLINES - 2);
  for (int j = 0; j < NCOLS; j++) {
    assert(map[NLINES - 2][j] == 4);
    assert(map[NLINES - 3][j] == 7);
    assert(map[NLINES - 5][j] == 1);
  }
  move_lines_down(map, NLINES - 2);
  for (int j = 0; j < NCOLS; j++) assert(map[NLINES - 5][j] == 1);
  move_lines_down(map, NLINES - 6);
  for (int j = 0; j < NCOLS; j++) assert(map[NLINES - 5][j] == 1);
}

void test_tmap(void) {
  tmap_update_map();
  tmap_check_game_state();
  tmap_check_line_empty();
  tmap_empty_line();
  tmap_move_lines_down();
}

void tscore_update_score_val(void) {
  tscore score = {0, NULL};
  score.scorestr = malloc((TSDIGITS + 1) * sizeof(char));
  ifnullexit(score.scorestr, "tscore_update_score_val");
  *score.scorestr = '0';
  *(score.scorestr + 1) = '\0';
  update_score_val(&score, 1);
  assert(score.score == 40);
  assert(strcmp(score.scorestr, "40") == 0);
  update_score_val(&score, 2);
  assert(score.score == 140);
  assert(strcmp(score.scorestr, "140") == 0);
  update_score_val(&score, 3);
  assert(score.score == 440);
  assert(strcmp(score.scorestr, "440") == 0);
  update_score_val(&score, 4);
  assert(score.score == 1640);
  assert(strcmp(score.scorestr, "1640") == 0);
  update_score_val(&score, 99);
  assert(score.score == 2840);
  assert(strcmp(score.scorestr, "2840") == 0);
  free(score.scorestr);
}

void test_tscore(void) { tscore_update_score_val(); }

int main() {
  test_tcommons();
  test_tblocks();
  test_tmap();
  test_tscore();

  return 0;
}
