#include "snake.h"

namespace s21 {
Snake::Snake()
    : game_menu_(START_MENU),
      FSM_state_(Initialize),
      snake_(),
      direction_(S_UP),
      length_(kInitSnakeLength) {}
Snake::~Snake() {}
void Snake::initHighScoreFromFile(GameInfo_t* game_info) {
  std::ifstream file(kHighScoreFilePath);
  if (file.is_open()) {
    file >> game_info->high_score;
    file.close();
  }
}
void Snake::writeHighScoreToFile(GameInfo_t* game_info) {
  std::ifstream file(kHighScoreFilePath);
  int scoreFile;
  if (!file.is_open()) {
    std::ofstream newFile(kHighScoreFilePath);
    newFile << game_info->score;
    newFile.close();
    return;
  }
  file >> scoreFile;
  file.close();
  if (game_info->score > scoreFile) {
    std::ofstream newFile(kHighScoreFilePath);
    newFile << game_info->score;
    newFile.close();
  }
}
void Snake::initField(GameInfo_t* game_info) {
  for (int i = 0; i < 12; i++) {
    game_info->field[i][0] = S_WALLS;
    game_info->field[i][GAME_ROWS_FIELD_Y - 1] = S_WALLS;
  }
  for (int i = 0; i < 22; i++) {
    game_info->field[0][i] = S_WALLS;
    game_info->field[GAME_COLS_FIELD_X - 1][i] = S_WALLS;
  }
}
void Snake::initSnake() {
  for (int i = 0; i < kInitSnakeLength; ++i) {
    snake_.emplace_back(SnakeCoordinates(0 + 5, i + 5));
  }
}
void Snake::init_game(GameInfo_t* game_info) {
  initField(game_info);
  initSnake();
  initHighScoreFromFile(game_info);
}
void Snake::spawn_food(GameInfo_t* game_info) {
  SnakeCoordinates food;
  do {
    food.x = rand() % (GAME_COLS_FIELD_X - 2) + 1;
    food.y = rand() % (GAME_ROWS_FIELD_Y - 2) + 1;
  } while (game_info->field[food.x][food.y] != S_FIELD);
  game_info->field[food.x][food.y] = S_FOOD;
}
void Snake::updateHead(GameInfo_t* game_info) {
  SnakeCoordinates newHead =
      SnakeCoordinates{snake_.front().x, snake_.front().y};
  bool collision = false;
  switch (direction_) {
    case S_UP:
      collision = checkCollision(game_info, 0, -1);
      if (!collision) newHead.y--;
      break;
    case S_DOWN:
      collision = checkCollision(game_info, 0, 1);
      if (!collision) newHead.y++;
      break;
    case S_LEFT:
      collision = checkCollision(game_info, -1, 0);
      if (!collision) newHead.x--;
      break;
    case S_RIGHT:
      collision = checkCollision(game_info, 1, 0);
      if (!collision) newHead.x++;
      break;
  }
  if (!collision) {
    snake_.push_front(newHead);
    game_info->field[snake_.back().x + 1][snake_.back().y + 1] = S_FIELD;
    snake_.pop_back();
  }
}
void Snake::updateSnakeInField(GameInfo_t* game_info) {
  for (int i = 0; i < length_; i++) {
    int newX = snake_[i].x + 1;
    int newY = snake_[i].y + 1;
    if (game_info->field[newX][newY] == S_FIELD ||
        game_info->field[newX][newY] == S_FOOD) {
      game_info->field[newX][newY] = S_SNAKE;
    }
  }
}
bool Snake::checkCollision(GameInfo_t* game_info, int x, int y) {
  int newX = snake_.front().x + x + S_WALLS;
  int newY = snake_.front().y + y + S_WALLS;
  if (game_info->field[newX][newY] == S_WALLS ||
      game_info->field[newX][newY] == S_SNAKE) {
    game_info->field[newX][newY] = 8;
    FSM_state_ = Game_over;
    game_menu_ = TERMINATE_MENU;
    return true;
  } else if (game_info->field[newX][newY] == S_FOOD) {
    FSM_state_ = Attaching;
    return false;
  }
  return false;
}
void Snake::updateLevel(GameInfo_t* game_info) {
  if (game_info->score >= 5 && game_info->score <= 50) {
    game_info->level = game_info->score / 5;
  }
  game_info->speed = game_info->level;
}
void Snake::feedTheSnake(GameInfo_t* game_info) {
  length_++;
  snake_.push_back(SnakeCoordinates{snake_.back().x, snake_.back().y});
  game_info->score += 1;
  updateLevel(game_info);
}
void Snake::checkGamecore(GameInfo_t* game_info) {
  if (game_info->score >= 200 || length_ >= 200) {
    FSM_state_ = Game_over;
    game_menu_ = GAME_WIN;
  }
}
void Snake::updateGameTime(GameInfo_t* game_info) {
  game_info->pause = game_menu_;
  if (game_info->pause == PAUSE_MENU) {
    return;
  }
  updateHead(game_info);
  updateSnakeInField(game_info);
  checkGamecore(game_info);
}
GameInfo_t Snake::updateCurrentState(GameInfo_t* game_info) {
  switch (FSM_state_) {
    case Initialize:
      init_game(game_info);
      FSM_state_ = Spawn;
      break;
    case Spawn:
      spawn_food(game_info);
      FSM_state_ = Move;
      break;
    case Move:
      updateGameTime(game_info);
      break;
    case Attaching:
      feedTheSnake(game_info);
      FSM_state_ = Spawn;
      break;
    case Game_over:
      game_info->pause = game_menu_;
      writeHighScoreToFile(game_info);
      break;
  }
  return *game_info;
}
void Snake::userInput(UserAction_t action) {
  if (FSM_state_ == Move) {
    switch (action) {
      case Action:
        break;
      case Pause:
        if (game_menu_ == PAUSE_MENU) {
          game_menu_ = START_MENU;
        } else {
          game_menu_ = PAUSE_MENU;
        }
        break;
      case Start:
        break;
      case Up:
        if (direction_ != S_DOWN) {
          direction_ = S_UP;
        }
        break;
      case Down:
        if (direction_ != S_UP) {
          direction_ = S_DOWN;
        }
        break;
      case Left:
        if (direction_ != S_RIGHT) {
          direction_ = S_LEFT;
        }
        break;
      case Right:
        if (direction_ != S_LEFT) {
          direction_ = S_RIGHT;
        }
        break;
      case Terminate:
        FSM_state_ = Game_over;
        game_menu_ = TERMINATE_MENU;
        break;
      case Empty_key:
        break;
      default:
        break;
    }
  }
}
}  // namespace s21
