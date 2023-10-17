/*
 *  Functions related to the creation and manipulation
 *  of tetris blocks.
 * */
#include "tblocks.h"

#include <curses.h>

#include "tmap.h"

// model blocks
t_block iblock = {
    {0, 0}, {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 1}}, T_IBLOCK};
t_block jblock = {
    {0, 0}, {{0, 0, 0, 0}, {0, 0, 0, 0}, {1, 0, 0, 0}, {1, 1, 1, 0}}, T_JBLOCK};
t_block lblock = {
    {0, 0}, {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 1, 0}, {1, 1, 1, 0}}, T_LBLOCK};
t_block oblock = {
    {0, 0}, {{0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 0, 0}, {1, 1, 0, 0}}, T_OBLOCK};
t_block sblock = {
    {0, 0}, {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 1, 1, 0}, {1, 1, 0, 0}}, T_SBLOCK};
t_block tblock = {
    {0, 0}, {{0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 0}, {0, 1, 0, 0}}, T_TBLOCK};
t_block zblock = {
    {0, 0}, {{0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 1, 0}}, T_ZBLOCK};

bool game_over = false;

bool check_game_over(void) { return game_over; }

/*
 *  Checks if there is collision between the position and map of a
 *  block and the game map.
 *  If so returns true, otherwise returns false.
 * */
bool check_for_col(char map[NLINES + 1][NCOLS + 1], t_block *block) {
  for (int i = 3; i >= 0; i--)
    for (int j = 3; j >= 0; j--)
      if (block->map[i][j] && map[block->pos.y + i][block->pos.x + j])
        return true;
  return false;
}

/*
 *  Creates a block based on its type and starting pos.
 *  If the block starting point collides with blocks on the map,
 *  updates the game_over variable to true.
 *  Returns a pointer to the newly-created block.
 * */
t_block *new_block(char map[NLINES + 1][NCOLS + 1], point pos,
                   enum tblock_type type) {
  t_block *newblock = (t_block *)malloc(sizeof(t_block));
  ifnullexit(newblock, "new_block");
  newblock->pos.x = pos.x;
  newblock->pos.y = pos.y;
  switch (type) {
    case T_IBLOCK:
      copy_matrix(iblock.map, newblock->map);
      newblock->type = T_IBLOCK;
      break;
    case T_JBLOCK:
      copy_matrix(jblock.map, newblock->map);
      newblock->type = T_JBLOCK;
      break;
    case T_LBLOCK:
      copy_matrix(lblock.map, newblock->map);
      newblock->type = T_LBLOCK;
      break;
    case T_OBLOCK:
      copy_matrix(oblock.map, newblock->map);
      newblock->type = T_OBLOCK;
      break;
    case T_SBLOCK:
      copy_matrix(sblock.map, newblock->map);
      newblock->type = T_SBLOCK;
      break;
    case T_TBLOCK:
      copy_matrix(tblock.map, newblock->map);
      newblock->type = T_TBLOCK;
      break;
    case T_ZBLOCK:
      copy_matrix(zblock.map, newblock->map);
      newblock->type = T_ZBLOCK;
      break;
  }
  game_over = check_for_col(map, newblock);
  return newblock;
}

/*
 *  Picks a block of random type and of starting position pos.
 *  Returns a pointer to the picked block.
 * */
t_block *pick_random_block(char map[NLINES + 1][NCOLS + 1], point pos) {
  t_block *picked = NULL;
  int pick = ((rand() + 1) % 7) + 1;
  picked = new_block(map, pos, pick);

  int rotations = (rand() + 1) % 4;
  for (int i = 0; i < rotations; i++) rotate_block(map, picked);

  return picked;
}

/*
 *  Gets the most leftward active point of the block in its map.
 *  Returns its column.
 * */
int get_min_width(t_block *block) {
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      if (block->map[j][i]) return i;
  return -1;  // will never happen
}

/*
 *  Gets the most rightward active point of the block in its map.
 *  Returns its column.
 * */
int get_max_width(t_block *block) {
  for (int i = 3; i >= 0; i--)
    for (int j = 3; j >= 0; j--)
      if (block->map[j][i]) return i;
  return -1;  // will never happen
}

/*
 *  Gets the lowest active point of the block in its map.
 *  Returns its line.
 * */
int get_max_height(t_block *block) {
  for (int i = 3; i >= 0; i--) {
    for (int j = 0; j < 4; j++)
      if (block->map[i][j]) return i;
  }
  return -1;  // will never happen
}

/*
 *  Given a block, rotates its map 90 degrees clockwise.
 *  Also does some correction on its position.
 * */
void rotate_block(char map[NLINES + 1][NCOLS + 1], t_block *block) {
  if (block->type == T_OBLOCK) return;
  t_block temp;
  copy_matrix(block->map, temp.map);
  temp.pos.x = block->pos.x;
  temp.pos.y = block->pos.y;
  int pivoti = 0, pivotj = 0;

  for (int i = 0; i < 4; i++)
    for (int j = 0; j < i; j++) swap(&temp.map[i][j], &temp.map[j][i]);

  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 2; j++) swap(&temp.map[i][j], &temp.map[i][3 - j]);

  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      if (temp.map[j][i] && !pivoti) {
        pivoti = j;
        pivotj = i;
      }

  temp.pos.x -= pivotj - 1;
  temp.pos.y -= pivoti - 1;
  if (!check_for_col(map, &temp)) {
    copy_matrix(temp.map, block->map);
    block->pos.y = temp.pos.y;
    block->pos.x = temp.pos.x;
  }
}

/*
 *  Updates the horizontal position of a block.
 *  If dir is true, decreases x position, otherwise increases.
 *  If this results in the block going beyond the border or
 *  colliding with another block, cancels the update.
 * */
void update_pos_hor(char map[NLINES + 1][NCOLS + 1], t_block *block, bool dir,
                    int max_x) {
  int min_width = get_min_width(block);
  int max_width = get_max_width(block);
  if (dir) {
    block->pos.x--;
    if (block->pos.x + min_width < 0 || check_for_col(map, block))
      block->pos.x++;
  } else {
    block->pos.x++;
    if (block->pos.x + max_width >= NCOLS || check_for_col(map, block))
      block->pos.x--;
  }
}

/*
 *  Increases the y position of the block.
 *  If this results in a collision with the map, it returns true and
 *  undoes the update. Also adds the block to the game map.
 *  Otherwise returns false.
 * */
bool update_pos_ver(char map[NLINES + 1][NCOLS + 1], t_block *block) {
  ++block->pos.y;
  if (check_for_col(map, block)) {
    --block->pos.y;
    update_map(map, block);
    return true;
  }
  return false;
}

/*
 *  Draws a block on the screen in its position and according to its map.
 *  It is also colored according to its type attribute.
 * */
void draw_tblock(WINDOW *win, t_block *block) {
  wattron(win, A_REVERSE | COLOR_PAIR(block->type));
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (block->map[i][j])
        mvwaddch(win, block->pos.y + i, block->pos.x + j, ' ');
    }
  }
  wattroff(win, A_REVERSE | COLOR_PAIR(block->type));
}

