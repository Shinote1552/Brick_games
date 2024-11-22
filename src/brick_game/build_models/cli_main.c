#include "../controller/controller.h"

int main() {
  init_ncurses();
  draw_start_menu();
  brick_game_loop();
  delwin(stdscr);
  endwin();
  return 0;
}
