#include "tetris.h"
static GameInfo_t* game_info = NULL;
static MainGameObject_t* game_object = NULL;

void init_matrix_with_shapes_colored(int** matrix, int x, int y, int id) {
  switch (id) {
    case I_SHAPE:
      matrix[0 + x][0 + y] = 0;
      matrix[0 + x][1 + y] = I_SHAPE;
      matrix[1 + x][0 + y] = 0;
      matrix[1 + x][1 + y] = I_SHAPE;
      matrix[2 + x][0 + y] = 0;
      matrix[2 + x][1 + y] = I_SHAPE;
      matrix[3 + x][0 + y] = 0;
      matrix[3 + x][1 + y] = I_SHAPE;
      break;
    case J_SHAPE:
      matrix[0 + x][0 + y] = J_SHAPE;
      matrix[0 + x][1 + y] = J_SHAPE;
      matrix[1 + x][0 + y] = 0;
      matrix[1 + x][1 + y] = J_SHAPE;
      matrix[2 + x][0 + y] = 0;
      matrix[2 + x][1 + y] = J_SHAPE;
      matrix[3 + x][0 + y] = 0;
      matrix[3 + x][1 + y] = 0;
      break;
    case L_SHAPE:
      matrix[0 + x][0 + y] = 0;
      matrix[0 + x][1 + y] = L_SHAPE;
      matrix[1 + x][0 + y] = 0;
      matrix[1 + x][1 + y] = L_SHAPE;
      matrix[2 + x][0 + y] = L_SHAPE;
      matrix[2 + x][1 + y] = L_SHAPE;
      matrix[3 + x][0 + y] = 0;
      matrix[3 + x][1 + y] = 0;
      break;
    case O_SHAPE:
      matrix[0 + x][0 + y] = 0;
      matrix[0 + x][1 + y] = 0;
      matrix[1 + x][0 + y] = O_SHAPE;
      matrix[1 + x][1 + y] = O_SHAPE;
      matrix[2 + x][0 + y] = O_SHAPE;
      matrix[2 + x][1 + y] = O_SHAPE;
      matrix[3 + x][0 + y] = 0;
      matrix[3 + x][1 + y] = 0;
      break;
    case S_SHAPE:
      matrix[0 + x][0 + y] = 0;
      matrix[0 + x][1 + y] = S_SHAPE;
      matrix[1 + x][0 + y] = S_SHAPE;
      matrix[1 + x][1 + y] = S_SHAPE;
      matrix[2 + x][0 + y] = S_SHAPE;
      matrix[2 + x][1 + y] = 0;
      matrix[3 + x][0 + y] = 0;
      matrix[3 + x][1 + y] = 0;
      break;
    case T_SHAPE:
      matrix[0 + x][0 + y] = 0;
      matrix[0 + x][1 + y] = T_SHAPE;
      matrix[1 + x][0 + y] = T_SHAPE;
      matrix[1 + x][1 + y] = T_SHAPE;
      matrix[2 + x][0 + y] = 0;
      matrix[2 + x][1 + y] = T_SHAPE;
      matrix[3 + x][0 + y] = 0;
      matrix[3 + x][1 + y] = 0;
      break;
    case Z_SHAPE:
      matrix[0 + x][0 + y] = Z_SHAPE;
      matrix[0 + x][1 + y] = 0;
      matrix[1 + x][0 + y] = Z_SHAPE;
      matrix[1 + x][1 + y] = Z_SHAPE;
      matrix[2 + x][0 + y] = 0;
      matrix[2 + x][1 + y] = Z_SHAPE;
      matrix[3 + x][0 + y] = 0;
      matrix[3 + x][1 + y] = 0;
      break;
    default:
      matrix[0 + x][0 + y] = 0;
      matrix[0 + x][1 + y] = I_SHAPE;
      matrix[1 + x][0 + y] = 0;
      matrix[1 + x][1 + y] = I_SHAPE;
      matrix[2 + x][0 + y] = 0;
      matrix[2 + x][1 + y] = I_SHAPE;
      matrix[3 + x][0 + y] = 0;
      matrix[3 + x][1 + y] = I_SHAPE;
      break;
  }
}
void init_high_score_from_file() {
  FILE* fp = fopen(HIGH_SCORE_FILE_PATH, "r");
  if (fp != NULL) {
    fscanf(fp, "%d", &game_info->high_score);
    fclose(fp);
  }
}
void write_high_score_to_file() {
  init_high_score_from_file();
  const char* filename = HIGH_SCORE_FILE_PATH;
  FILE* fp = fopen(filename, "w");

  if (fp != NULL) {
    if (game_info->score > game_info->high_score) {
      fprintf(fp, "%d", game_info->score);
      fclose(fp);
    }
  }
}
void shape_matrix_update() {
  for (int i = 0; i < SHAPE_SIZE; i++) {
    for (int j = 0; j < SHAPE_SIZE; j++) {
      game_object->shape[i][j] = FIELD;
      if (game_info->next[i][j] > 1) {
        game_object->shape[i][j] = game_info->next[i][j];
      }
    }
  }
}
void init_game_field() {
  for (int i = 0; i < GAME_COLS_FIELD_X; i++) {
    game_info->field[i][0] = WALLS;
    game_info->field[i][GAME_ROWS_FIELD_Y - 1] = WALLS;
  }

  for (int i = 0; i < GAME_ROWS_FIELD_Y; i++) {
    game_info->field[0][i] = WALLS;
    game_info->field[GAME_COLS_FIELD_X - 1][i] = WALLS;
  }
}
void init_next_shape() {
  game_object->x = SHAPE_SIZE;
  game_object->y = 1;
  TetrominoShape id = (TetrominoShape)(rand() % (Z_SHAPE) + 2);
  init_matrix_with_shapes_colored(game_info->next, 0, 0, id);
}
void update_score(int full_lines) {
  switch (full_lines) {
    case 1:
      game_info->score += 100;
      break;
    case 2:
      game_info->score += 300;
      break;
    case 3:
      game_info->score += 700;
      break;
    case 4:
      game_info->score += 1500;
      break;
    default:
      break;
  }
  if (game_info->score > game_info->high_score) {
    game_info->high_score = game_info->score;
  }
}
bool is_full_line(int y) {
  for (int x = 1; x < GAME_COLS_FIELD_X - 1; x++) {
    if (game_info->field[x][y] < 2) {
      return false;
    }
  }
  return true;
}
void clear_line(int y) {
  for (int newX = 1; newX < GAME_COLS_FIELD_X - 1; newX++) {
    game_info->field[newX][y] = 0;
  }
}
void drop_lines_above(int y) {
  for (int newY = y; newY > 1; newY--) {
    for (int new_newX = 1; new_newX < GAME_COLS_FIELD_X - 1; new_newX++) {
      game_info->field[new_newX][newY] = game_info->field[new_newX][newY - 1];
    }
  }
}
void check_for_full_rows() {
  int full_lines = 0;
  for (int y = GAME_ROWS_FIELD_Y - 1; y > 1; y--) {
    if (is_full_line(y)) {
      full_lines++;
      clear_line(y);
      drop_lines_above(y);
      y++;
    }
  }
  update_score(full_lines);
}
void update_shape_in_field() {
  for (int i = 0; i < SHAPE_SIZE; i++) {
    for (int j = 0; j < SHAPE_SIZE; j++) {
      int newX = game_object->x + i;
      int newY = game_object->y + j;
      if (game_object->shape[i][j] > 1) {
        game_info->field[newX][newY] = game_object->shape[i][j];
      }
    }
  }
}
int check_collision(int dx, int dy, int shape[SHAPE_SIZE][SHAPE_SIZE]) {
  for (int i = 0; i < SHAPE_SIZE; i++) {
    for (int j = 0; j < SHAPE_SIZE; j++) {
      if (shape[i][j] > 1) {
        int newX = game_object->x + i + dx;
        int newY = game_object->y + j + dy;
        if (newX < 1 || newX > GAME_COLS_FIELD_X - 2 || newY < 0 ||
            newY > GAME_ROWS_FIELD_Y - 2) {
          return 1;
        }
        if (game_info->field[newX][newY] > 1) {
          return 1;
        }
      }
    }
  }
  return 0;
}
void remove_shape_drom_field() {
  for (int i = 0; i < SHAPE_SIZE; i++) {
    for (int j = 0; j < SHAPE_SIZE; j++) {
      if (game_object->shape[i][j] > WALLS) {
        game_info->field[i + game_object->x][j + game_object->y] = FIELD;
      }
    }
  }
}
void copy_shape(int temp[SHAPE_SIZE][SHAPE_SIZE]) {
  for (int i = 0; i < SHAPE_SIZE; i++) {
    for (int j = 0; j < SHAPE_SIZE; j++) {
      game_object->shape[i][j] = temp[i][j];
    }
  }
}
bool try_move_shape(int temp[SHAPE_SIZE][SHAPE_SIZE], int offset) {
  if (!check_collision(offset, 0, temp) &&
      game_object->shape[1][1] != O_SHAPE) {
    game_object->x += offset;  // Сместить влево или вправо
    copy_shape(temp);
    return true;
  }
  return false;
}
bool try_update_shape(int temp[SHAPE_SIZE][SHAPE_SIZE]) {
  if (!check_collision(0, 0, temp) && game_object->shape[1][1] != O_SHAPE) {
    copy_shape(temp);
    return true;
  }

  if (try_move_shape(temp, -1) || try_move_shape(temp, 1)) {
    return true;
  }

  return false;
}
void rotate_90_degrees(int temp[SHAPE_SIZE][SHAPE_SIZE]) {
  for (int i = 0; i < SHAPE_SIZE; i++) {
    for (int j = 0; j < SHAPE_SIZE; j++) {
      temp[3 - j][i] = game_object->shape[i][j];
    }
  }
}
void rotate_shape() {
  int temp[SHAPE_SIZE][SHAPE_SIZE];
  remove_shape_drom_field();
  rotate_90_degrees(temp);

  if (try_update_shape(temp) && game_info->pause == PAUSE_MENU) {
    update_shape_in_field();
  }
}

void update_game_time(UserAction_t action) {
  remove_shape_drom_field();
  if (action == Right) {
    return;
  } else if (action == Left) {
    return;
  } else if (action == Up) {
    return;
  }
  if (!check_collision(0, 1, game_object->shape)) {
    game_object->y++;
  } else {
    game_object->FSM_state = Attaching;
  }
  update_shape_in_field();
}
void move_down() {
  remove_shape_drom_field();
  if (!check_collision(0, 1, game_object->shape)) {
    game_object->y++;
  }
  update_shape_in_field();
}
void move_left() {
  remove_shape_drom_field();
  if (!check_collision(-1, 0, game_object->shape)) {
    game_object->x--;
  }
  update_shape_in_field();
}
void move_right() {
  remove_shape_drom_field();
  if (!check_collision(1, 0, game_object->shape)) {
    game_object->x++;
  }
  update_shape_in_field();
}
void level_update() {
  if (game_info->score >= 600 && game_info->score <= 5400) {
    game_info->level = game_info->score / 600;
  }else if (game_info->score > 5400) {
    game_info->level = 9;
  }
  game_info->speed = game_info->level;
}
void shape_action() {
  remove_shape_drom_field();
  while (!check_collision(0, 1, game_object->shape)) {
    game_object->y++;
  }
  update_shape_in_field();
}
void input_pause() {
  if (game_info->pause == PAUSE_MENU) {
    game_info->pause = START_MENU;
  } else {
    game_info->pause = PAUSE_MENU;
  }
}
void input_controller(UserAction_t action) {
  switch (action) {
    case Start:
      break;
    case Pause:
      input_pause();
      break;
    case Terminate:
      game_info->pause = TERMINATE_MENU;
      break;
    case Left:
      move_left();
      break;
    case Right:
      move_right();
      break;
    case Up:
      rotate_shape();
      break;
    case Down:
      move_down();
      break;
    case Action:
      shape_action();
      break;
    default:
      break;
  }
}
void init_game_obeject() {
  if (game_object == NULL) {
    game_object = (MainGameObject_t*)calloc(1, sizeof(MainGameObject_t));  //
    if (game_object == NULL) {
      fprintf(stderr, "Error allocating memory\n");
      return;
    }
    game_object->FSM_state = Initialize;
    srand(time(NULL));
  }
}
void check_top_rows() {
  remove_shape_drom_field();
  for (int i = 0; i < 10; i++) {
    if (game_info->field[i + 1][1] != 0 || game_info->field[i + 1][2] != 0) {
      game_object->FSM_state = Game_over;
    }
  }
  update_shape_in_field();
}
void userInput(UserAction_t action) {
  init_game_obeject();
  switch (game_object->FSM_state) {
    case Initialize:
      init_high_score_from_file();
      init_game_field();
      init_next_shape();
      shape_matrix_update();
      game_object->FSM_state = Spawn;
      break;
    case Spawn:
      shape_matrix_update();
      init_next_shape();
      game_object->FSM_state = Move;
      break;
    case Move:
      if (game_info->pause == PAUSE_MENU) {
        if (action == Pause) {
          input_pause();
        }
        break;
      }
      input_controller(action);
      update_game_time(action);
      update_shape_in_field();
      break;
    case Attaching:
      check_top_rows();
      check_for_full_rows();
      level_update();
      if (game_object->FSM_state == Attaching) {
        game_object->FSM_state = Spawn;
      }
      break;
    case Game_over:
      write_high_score_to_file();
      if (game_object != NULL) {
        free(game_object);
        game_object = NULL;
      }
      game_info->pause = TERMINATE_MENU;
      break;
    default:
      break;
  }
}
GameInfo_t updateCurrentState(GameInfo_t* game_info_ptr) {
  game_info = game_info_ptr;
  return *game_info;
}