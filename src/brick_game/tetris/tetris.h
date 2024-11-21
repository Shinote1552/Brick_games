#ifndef TETRIS_BACKEND_H
#define TETRIS_BACKEND_H

#define SHAPE_SIZE 4
#define HIGH_SCORE_FILE_PATH "./brick_game/tetris/hightscores/high_score.txt"

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "../common/common.h"

#define PLAY_BRICK_GAME                     \
  game = updateCurrentState(&game);         \
  draw_game_main(game);                     \
  action = (UserAction_t)keys_controller(); \
  userInput(action);

typedef struct {
  int x, y;
  int shape[SHAPE_SIZE][SHAPE_SIZE];
  FinitState_machine_t FSM_state;
} MainGameObject_t;

typedef enum {
  FIELD,
  WALLS,
  J_SHAPE,
  I_SHAPE,
  L_SHAPE,
  O_SHAPE,
  S_SHAPE,
  T_SHAPE,
  Z_SHAPE
} TetrominoShape;

void init_matrix_with_shapes_colored(int **matrix, int x, int y, int id);
void init_high_score_from_file();
void write_high_score_to_file();
void shape_matrix_update();
void init_game_field();
void init_next_shape();
void update_score(int full_lines);
bool is_full_line(int y);
void clear_line(int y);
void drop_lines_above(int y);
void check_for_full_rows();
void update_shape_in_field();
int check_collision(int dx, int dy, int shape[4][4]);
void remove_shape_drom_field();
void copy_shape(int temp[4][4]);
bool try_move_shape(int temp[4][4], int offset);
bool try_update_shape(int temp[4][4]);
void rotate_90_degrees(int temp[4][4]);
void rotate_shape();
void update_game_time(UserAction_t action);
void move_down();
void move_left();
void move_right();
void level_update();
void shape_action();
void input_controller(UserAction_t action);
void init_game_obeject();
void check_top_rows();
void input_pause();

#ifdef __cplusplus
}
#endif

#endif  // TETRIS_BACKEND_H
