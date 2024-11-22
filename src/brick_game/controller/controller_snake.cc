#include "../snake/model/snake.h"
#include "controller.h"

void brick_game_loop() {  // snake
  GameInfo_t game;
  init_game(&game);
  init_ncurses();
  UserAction_t action = Start;
  s21::Snake snake;

  while (game.pause != Terminate && game.pause != GAME_WIN) {
    PLAY_BRICK_GAME;
  }
  end_ncurses();
  free_matrix(GAME_COLS_FIELD_X, game.field);
  free_matrix(4, game.next);
}