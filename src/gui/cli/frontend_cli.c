#include "frontend_cli.h"

int keys_controller() {
  int user_action_keychar = -1;
  int ch_key = getch();
  switch (ch_key) {
    case KEY_UP:
    case 'w':
      user_action_keychar = Up;
      break;
    case KEY_DOWN:
    case 's':
      user_action_keychar = Down;
      break;
    case KEY_LEFT:
    case 'a':
      user_action_keychar = Left;
      break;
    case KEY_RIGHT:
    case 'd':
      user_action_keychar = Right;
      break;
    case ESCAPE:
    case 'q':
      user_action_keychar = Terminate;
      break;
    case ENTER_KEY:
      user_action_keychar = Start;
      break;
    case SPACE_KEY:
      user_action_keychar = Action;
      break;
    case 'p':
      user_action_keychar = Pause;
      break;
    default:
      user_action_keychar = -1;
      break;
  }
  return user_action_keychar;
}
void free_matrix(int field_X, int** matrix) {
  if (matrix != NULL) {
    for (int i = 0; i < field_X; i++) {
      if (matrix[i] != NULL) {
        free(matrix[i]);
      }
    }
    free(matrix);
  }
}
int** create_matrix(int field_X, int field_Y) {
  int** result = (int**)calloc(field_X, sizeof(int*));
  if (result != NULL) {
    for (int i = 0; i < field_X; i++) {
      result[i] = (int*)calloc(field_Y, sizeof(int));
      if (result[i] == NULL) {
        free_matrix(i, result);
        break;
      }
      for (int j = 0; j < field_Y; j++) {
        result[i][j] = 0;
      }
    }
  }
  return result;
}
int init_game(GameInfo_t* game) {
  if (game == NULL) {
    return 1;
  }
  game->field = create_matrix(GAME_COLS_FIELD_X, GAME_ROWS_FIELD_Y);
  game->next = create_matrix(4, 4);
  game->score = 0;
  game->high_score = 0;
  game->level = 0;
  game->speed = 0;
  game->pause = 0;
  if (game->field == NULL || game->next == NULL) {
    return 2;
  } else {
    return 0;
  }
}
void init_color_pairs() {
  start_color();
  use_default_colors();
  init_color(DARK_WHITE, 100, 100, 100);
  init_color(DARK_GREY, 50, 50, 50);
  init_color(LIGHT_BLUE, 400, 400, 1000);
  init_color(BLUE, 0, 0, 1000);
  init_color(ORANGE, 1000, 500, 0);
  init_color(YELLOW, 1000, 1000, 0);
  init_color(GREEN, 0, 1000, 0);
  init_color(PURPLE, 500, 0, 1000);
  init_color(RED, 1000, 0, 0);
  init_pair(0, DARK_WHITE, -1);
  init_pair(1, DARK_GREY, -1);
  init_pair(2, LIGHT_BLUE, -1);
  init_pair(3, BLUE, -1);
  init_pair(4, ORANGE, -1);
  init_pair(5, YELLOW, -1);
  init_pair(6, GREEN, -1);
  init_pair(7, PURPLE, -1);
  init_pair(8, RED, -1);
}
void drawing_colors_case(int x, int y, int x_modifier, int y_modifier,
                         int** field) {
  wattron(stdscr, A_BOLD);
  switch (field[x][y]) {
    case 0:  // FIELD
      wattron(stdscr, COLOR_PAIR(DARK_GREY));
      mvwaddch(stdscr, y + y_modifier, x + x_modifier, '.');
      wattroff(stdscr, COLOR_PAIR(DARK_GREY));
      break;
    case 1:  // WALL
      wattron(stdscr, COLOR_PAIR(DARK_WHITE));
      mvwaddch(stdscr, y + y_modifier, x + x_modifier, BLOCK);
      wattroff(stdscr, COLOR_PAIR(DARK_WHITE));
      break;
    case 2:  // I_SHAPE
      wattron(stdscr, COLOR_PAIR(LIGHT_BLUE));
      mvwaddch(stdscr, y + y_modifier, x + x_modifier, '#');
      wattroff(stdscr, COLOR_PAIR(LIGHT_BLUE));
      break;
    case 3:  // J_SHAPE
      wattron(stdscr, COLOR_PAIR(BLUE));
      mvwaddch(stdscr, y + y_modifier, x + x_modifier, '#');
      wattroff(stdscr, COLOR_PAIR(BLUE));
      break;
    case 4:  // L_SHAPE
      wattron(stdscr, COLOR_PAIR(ORANGE));
      mvwaddch(stdscr, y + y_modifier, x + x_modifier, '#');
      wattroff(stdscr, COLOR_PAIR(ORANGE));
      break;
    case 5:  // O_SHAPE
      wattron(stdscr, COLOR_PAIR(YELLOW));
      mvwaddch(stdscr, y + y_modifier, x + x_modifier, '#');
      wattroff(stdscr, COLOR_PAIR(YELLOW));
      break;
    case 6:  // S_SHAPE
      wattron(stdscr, COLOR_PAIR(GREEN));
      mvwaddch(stdscr, y + y_modifier, x + x_modifier, '#');
      wattroff(stdscr, COLOR_PAIR(GREEN));
      break;
    case 7:  // T_SHAPE
      wattron(stdscr, COLOR_PAIR(PURPLE));
      mvwaddch(stdscr, y + y_modifier, x + x_modifier, '#');
      wattroff(stdscr, COLOR_PAIR(PURPLE));
      break;
    case 8:  // Z_SHAPE
      wattron(stdscr, COLOR_PAIR(RED));
      mvwaddch(stdscr, y + y_modifier, x + x_modifier, '#');
      wattroff(stdscr, COLOR_PAIR(RED));
      break;
    default:
      break;
  }
  wattroff(stdscr, A_BOLD);
}
void draw_game_window(GameInfo_t* game) {
  init_color_pairs();
  wattron(stdscr, A_BOLD);
  box(stdscr, 0, 0);
  wattroff(stdscr, A_BOLD);
  for (int x = 0; x < GAME_COLS_FIELD_X; x++) {
    for (int y = 0; y < GAME_ROWS_FIELD_Y; y++) {
      drawing_colors_case(x, y, 1, 1, game->field);
    }
  }
  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 2; y++) {
      drawing_colors_case(x, y, 18, 12, game->next);
    }
  }
  wrefresh(stdscr);
}
void draw_score(GameInfo_t* game) {
  mvwprintw(stdscr, 2, 16, "High Score: %d", game->high_score);
  mvwprintw(stdscr, 3, 16, "Score: %d", game->score);
  mvwprintw(stdscr, 4, 16, "Level: %d", game->level);
}
void draw_game_pause(GameInfo_t* game) {
  wclear(stdscr);
  mvwprintw(stdscr, 1, 1, "PAUSE MENU");
  mvwprintw(stdscr, 2, 1, "PRESS SPACE");
  mvwprintw(stdscr, 3, 1, "OR ENTER");
  mvwprintw(stdscr, 4, 1, "TO CONTINUE");
  mvwprintw(stdscr, 5, 1, "SCORE: %d", game->score);
  wrefresh(stdscr);
}
void draw_start_menu() {
  mvwprintw(stdscr, 1, 1, "START MENU");
  mvwprintw(stdscr, 2, 1, "PRESS START");
  mvwprintw(stdscr, 3, 1, "TO CONTINUE");
  while (getch() != ENTER_KEY) {
  }
}
void draw_game_over_pause(GameInfo_t* game) {
  wclear(stdscr);
  mvwprintw(stdscr, 1, 1, "GAME OVER!");
  mvwprintw(stdscr, 2, 1, "PRESS KEY");
  mvwprintw(stdscr, 3, 1, "TO QUIT");
  mvwprintw(stdscr, 5, 1, "SCORE: %d", game->score);
  wrefresh(stdscr);
  while (1) {
    int ch = -1;
    ch = keys_controller();
    if (ch > 0) {
      game->pause = TERMINATE_MENU;
      break;
    }
  }
  wclear(stdscr);
}
void draw_game_win_menu(GameInfo_t* game) {
  wclear(stdscr);
  mvwprintw(stdscr, 1, 1, "YOU WIN!");
  mvwprintw(stdscr, 2, 1, "PRESS KEY");
  mvwprintw(stdscr, 3, 1, "TO QUIT");
  mvwprintw(stdscr, 5, 1, "SCORE: %d", game->score);
  wrefresh(stdscr);
  while (1) {
    int ch = -1;
    ch = keys_controller();
    if (ch > 0) {
      game->pause = TERMINATE_MENU;
      break;
    }
  }
  wclear(stdscr);
}
void freeze_drawing_time(GameInfo_t* game) {
  wtimeout(stdscr, (unsigned int)(levelspeeds[game->level] * 3000));
}
void draw_game_main(GameInfo_t game) {
  freeze_drawing_time(&game);
  switch (game.pause) {
    case START_MENU:
      draw_game_window(&game);
      draw_score(&game);
      break;
    case PAUSE_MENU:
      draw_game_pause(&game);
      break;
    case TERMINATE_MENU:
      draw_game_over_pause(&game);
      break;
    case GAME_WIN:
      draw_game_win_menu(&game);
      break;
    default:
      break;
  }
  wrefresh(stdscr);
}
void init_ncurses() {
  initscr();
  noecho();
  cbreak();
  curs_set(0);
  wclear(stdscr);
  box(stdscr, 0, 0);
  use_default_colors();
  init_color_pairs();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
}
void end_ncurses() {
  wclear(stdscr);
  wrefresh(stdscr);
  endwin();
}