#ifndef COMMON_H
#define COMMON_H

#define GAME_ROWS_FIELD_Y 22
#define GAME_COLS_FIELD_X 12
#define SHAPE_MATRIX_SIZE 4

#ifdef __cplusplus
extern "C" {
#endif
#include <stdbool.h>

typedef enum {
  START_MENU,
  PAUSE_MENU,
  TERMINATE_MENU,
  GAME_OVER_MENU,
  GAME_WIN
} Game_menu;

typedef enum {
  Initialize,
  Spawn,
  Move,
  Attaching,
  Game_over
} FinitState_machine_t;

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action,
  Empty_key
} UserAction_t;

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

static const double levelspeeds[] = {
    0.388,     // level 1
    0.2598,    // level 2
    0.1775,    // level 3
    0.1236,    // level 4
    0.0879,    // level 5
    0.06361,   // level 6
    0.04693,   // level 7
    0.035256,  // level 8
    0.026977,  // level 9
    0.021017   // level 10
};

void userInput(UserAction_t action);
GameInfo_t updateCurrentState(GameInfo_t *game_info_ptr);

#ifdef __cplusplus
}
#endif

#endif  // COMMON_H
