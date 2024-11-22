#ifndef FRONTEND_CLI_H
#define FRONTEND_CLI_H

#define UP 72         // код клавиши "Вверх"
#define DOWN 80       // код клавиши "Вниз"
#define LEFT 75       // код клавиши "Влево"
#define RIGHT 77      // код клавиши "Вправо"
#define ESCAPE 27     // код клавиши "Esc"
#define ENTER_KEY 10  // код клавиши "Enter"
#define SPACE_KEY 32  // код клавиши "Space"
#define BLOCK 'H'

#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "../../brick_game/common/common.h"

typedef enum {
  DARK_WHITE,  // field
  DARK_GREY,   // walls
  LIGHT_BLUE,  // I_SHAPE
  BLUE,        // J_SHAPE
  ORANGE,      // L_SHAPE
  YELLOW,      // O_SHAPE
  GREEN,       // S_SHAPE
  PURPLE,      // T_SHAPE
  RED          // Z_SHAPE
} Game_colors;

int keys_controller();
void free_matrix(int field_X, int **matrix);
int **create_matrix(int field_X, int field_Y);
int init_game(GameInfo_t *game);
void draw_game_pause(GameInfo_t *game);
void draw_start_menu();
void init_color_pairs();
void drawing_colors_case(int x, int y, int x_modifier, int y_modifier,
                         int **field);
void draw_game_window(GameInfo_t *game);
void draw_score(GameInfo_t *game);
void draw_game_over_pause(GameInfo_t *game);
void draw_game_main(GameInfo_t game);
void init_ncurses();
void end_ncurses();

#endif  // FRONTEND_CLI_H