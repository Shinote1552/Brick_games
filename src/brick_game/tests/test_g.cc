#include "../snake/model/snake.h"
#include "gtest/gtest.h"

void initGameInfo(GameInfo_t* gameInfo_) {
  gameInfo_->pause = 0;
  gameInfo_->score = 0;
  gameInfo_->level = 0;
  gameInfo_->speed = 0;
  gameInfo_->high_score = 0;
  gameInfo_->field = new int*[GAME_COLS_FIELD_X];
  for (int i = 0; i < GAME_COLS_FIELD_X; i++) {
    gameInfo_->field[i] = new int[GAME_ROWS_FIELD_Y];
    for (int j = 0; j < GAME_ROWS_FIELD_Y; j++) {
      gameInfo_->field[i][j] = 0;
    }
  }
  gameInfo_->next = new int*[SHAPE_MATRIX_SIZE];
  for (int i = 0; i < SHAPE_MATRIX_SIZE; i++) {
    gameInfo_->next[i] = new int[SHAPE_MATRIX_SIZE];
    for (int j = 0; j < SHAPE_MATRIX_SIZE; j++) {
      gameInfo_->next[i][j] = 0;
    }
  }
}
void freeGameInfo(GameInfo_t* gameInfo_) {
  for (int i = 0; i < GAME_COLS_FIELD_X; i++) {
    delete[] gameInfo_->field[i];
  }
  delete[] gameInfo_->field;
  for (int i = 0; i < SHAPE_MATRIX_SIZE; i++) {
    delete[] gameInfo_->next[i];
  }
  delete[] gameInfo_->next;
}
TEST(Snake, test1) {
  GameInfo_t game_info;
  UserAction_t action_info;
  initGameInfo(&game_info);
  s21::Snake snake;
  action_info = Up;
  while (game_info.pause != TERMINATE_MENU) {
    snake.updateCurrentState(&game_info);
    snake.userInput(action_info);
  }
  EXPECT_EQ(1, game_info.field[0][0]);
  freeGameInfo(&game_info);
}
TEST(Snake, test2) {
  GameInfo_t game_info;
  UserAction_t action_info;
  initGameInfo(&game_info);
  s21::Snake snake;
  action_info = Down;
  snake.updateCurrentState(&game_info);
  snake.userInput(action_info);
  action_info = Left;
  snake.updateCurrentState(&game_info);
  snake.userInput(action_info);
  action_info = Right;
  snake.updateCurrentState(&game_info);
  snake.userInput(action_info);
  action_info = Start;
  snake.updateCurrentState(&game_info);
  snake.userInput(action_info);
  action_info = Pause;
  snake.updateCurrentState(&game_info);
  snake.userInput(action_info);
  action_info = Pause;
  snake.updateCurrentState(&game_info);
  snake.userInput(action_info);
  action_info = Terminate;
  snake.updateCurrentState(&game_info);
  snake.userInput(action_info);
  EXPECT_EQ(1, game_info.field[0][0]);
  freeGameInfo(&game_info);
}
TEST(Snake, test3) {
  GameInfo_t game_info;
  UserAction_t action_info;
  initGameInfo(&game_info);
  s21::Snake snake;
  action_info = Right;
  snake.updateCurrentState(&game_info);
  snake.userInput(action_info);
  action_info = Right;
  snake.updateCurrentState(&game_info);
  snake.userInput(action_info);
  action_info = Right;
  snake.updateCurrentState(&game_info);
  snake.userInput(action_info);
  action_info = Right;
  snake.updateCurrentState(&game_info);
  snake.userInput(action_info);
  EXPECT_EQ(1, game_info.field[0][0]);
  freeGameInfo(&game_info);
}
TEST(Snake, test4) {
  GameInfo_t game_info;
  UserAction_t action_info;
  initGameInfo(&game_info);
  s21::Snake snake;
  action_info = Right;
  snake.updateCurrentState(&game_info);
  snake.userInput(action_info);
  action_info = Right;
  snake.updateCurrentState(&game_info);
  snake.userInput(action_info);
  action_info = Down;
  snake.updateCurrentState(&game_info);
  snake.userInput(action_info);
  action_info = Down;
  snake.updateCurrentState(&game_info);
  snake.userInput(action_info);
  action_info = Down;
  snake.updateCurrentState(&game_info);
  snake.userInput(action_info);
  action_info = Down;
  snake.updateCurrentState(&game_info);
  snake.userInput(action_info);
  action_info = Down;
  snake.updateCurrentState(&game_info);
  snake.userInput(action_info);
  action_info = Empty_key;
  snake.updateCurrentState(&game_info);
  snake.userInput(action_info);
  EXPECT_EQ(1, game_info.field[0][0]);
  freeGameInfo(&game_info);
}
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
