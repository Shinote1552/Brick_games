#include "../tetris/tetris.h"
#include "controller.h"

void brick_game_loop() {  // tetris
  GameInfo_t game;
  init_game(&game);
  init_ncurses();
  UserAction_t action = Start;

  while (game.pause != Terminate) {
    PLAY_BRICK_GAME;
  }
  end_ncurses();
  free_matrix(GAME_COLS_FIELD_X, game.field);
  free_matrix(4, game.next);
}