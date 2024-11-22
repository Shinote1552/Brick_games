#ifndef SNAKE_H
#define SNAKE_H

#include <deque>
#include <fstream>
#include <iostream>

#include "../../common/common.h"

#define PLAY_BRICK_GAME                     \
  game = snake.updateCurrentState(&game);   \
  draw_game_main(game);                     \
  action = (UserAction_t)keys_controller(); \
  snake.userInput(action);

typedef enum { S_FIELD, S_WALLS, S_FOOD, S_SNAKE = 6 } BrickType_t;

typedef enum { S_UP, S_DOWN, S_LEFT, S_RIGHT } Direction_t;

namespace s21 {
static const int kInitSnakeLength = 4;
static const std::string kHighScoreFilePath =
    "./brick_game/snake/model/hightscores/high_score.txt";
class Snake  // model MVC
{
  struct SnakeCoordinates {
    int x;
    int y;
    SnakeCoordinates(int x, int y) : x(x), y(y) {}
    SnakeCoordinates() : x(0), y(0) {}
  };

 private:
  Game_menu game_menu_;
  FinitState_machine_t FSM_state_;
  std::deque<SnakeCoordinates> snake_;
  int direction_;
  int length_;

  void initHighScoreFromFile(GameInfo_t *game_info);
  void writeHighScoreToFile(GameInfo_t *game_info);
  void init_game(GameInfo_t *game_info);
  void initField(GameInfo_t *game_info);
  void initSnake();
  void spawn_food(GameInfo_t *game_info);
  void updateHead(GameInfo_t *game_info);
  void updateTail(GameInfo_t *game_info);
  void updateDirection(int new_direction);
  bool checkCollision(GameInfo_t *game_info, int x, int y);
  void updateSnakeInField(GameInfo_t *game_info);
  void updateGameTime(GameInfo_t *game_info);
  void checkGamecore(GameInfo_t *game_info);
  void feedTheSnake(GameInfo_t *game_info);
  void updateLevel(GameInfo_t *game_info);

 public:
  Snake();
  ~Snake();
  GameInfo_t updateCurrentState(GameInfo_t *game_info);
  void userInput(UserAction_t action);
};
}  // namespace s21

#endif  // SNAKE_H