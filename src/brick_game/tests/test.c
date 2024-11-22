#include <check.h>

#include "../tetris/tetris.h"

static GameInfo_t *game_info_test_ptr = NULL;

void free_matrix_test(int field_X, int **matrix);
int **create_matrix_test(int field_X, int field_Y);

void free_matrix_test(int field_X, int **matrix) {
  if (matrix != NULL) {
    for (int i = 0; i < field_X; i++) {
      if (matrix[i] != NULL) {
        free(matrix[i]);
      }
    }
    free(matrix);
  }
}
int **create_matrix_test(int field_X, int field_Y) {
  int **result = (int **)calloc(field_X, sizeof(int *));
  if (result != NULL) {
    for (int i = 0; i < field_X; i++) {
      result[i] = (int *)calloc(field_Y, sizeof(int));
      if (result[i] == NULL) {
        free_matrix_test(i, result);
        break;
      }
      for (int j = 0; j < field_Y; j++) {
        result[i][j] = 0;
      }
    }
  }
  return result;
}
void setup(void) {
  init_game_obeject();
  game_info_test_ptr = (GameInfo_t *)calloc(1, sizeof(GameInfo_t));
  game_info_test_ptr->field =
      create_matrix_test(GAME_COLS_FIELD_X, GAME_ROWS_FIELD_Y);
  game_info_test_ptr->next = create_matrix_test(4, 4);
  game_info_test_ptr->score = 0;
  game_info_test_ptr->high_score = 0;
  game_info_test_ptr->level = 0;
  game_info_test_ptr->speed = 0;
  game_info_test_ptr->pause = 0;
  updateCurrentState(game_info_test_ptr);
  init_game_field();
}
void teardown(void) {
  if (game_info_test_ptr != NULL) {
    if (game_info_test_ptr->field != NULL) {
      free_matrix_test(GAME_COLS_FIELD_X, game_info_test_ptr->field);
    }
    if (game_info_test_ptr->next != NULL) {
      free_matrix_test(4, game_info_test_ptr->next);
    }
    free(game_info_test_ptr);
    game_info_test_ptr = NULL;
  }
}
START_TEST(test_update_current_state) {
  init_game_field();
  ck_assert_int_eq(1, (game_info_test_ptr->field[0][0]));
}
END_TEST
START_TEST(test_user_input_Start) {
  UserAction_t input = Start;
  userInput(input);
  ck_assert_int_eq(START_MENU, game_info_test_ptr->pause);
}
END_TEST
START_TEST(test_user_input_Left) {
  init_high_score_from_file();
  init_game_field();
  init_next_shape();
  shape_matrix_update();
  init_next_shape();
  UserAction_t input = Left;
  input_controller(input);
  update_game_time(input);
  update_shape_in_field();
  int check = 0;
  for (int i = 0; i < 10; i++) {
    if (game_info_test_ptr->field[i + 1][1] > 0) {
      check = 1;
    }
    if (game_info_test_ptr->field[i + 1][2] > 0) {
      check = 1;
    }
  }
  ck_assert_int_eq(check, 1);
}
START_TEST(test_user_input_Right) {
  UserAction_t input = Right;
  init_high_score_from_file();
  init_game_field();
  init_next_shape();
  shape_matrix_update();
  init_next_shape();
  input_controller(input);
  update_game_time(input);
  update_shape_in_field();
  int check = 0;
  for (int i = 0; i < 10; i++) {
    if (game_info_test_ptr->field[i + 1][1] > 0) {
      check = 1;
    }
    if (game_info_test_ptr->field[i + 1][2] > 0) {
      check = 1;
    }
  }
  ck_assert_int_eq(check, 1);
}
START_TEST(test_user_input_Up) {
  UserAction_t input = Up;
  init_high_score_from_file();
  init_game_field();
  init_next_shape();
  shape_matrix_update();
  init_next_shape();
  input_controller(input);
  update_game_time(input);
  update_shape_in_field();
  int check = 0;
  for (int i = 0; i < 10; i++) {
    if (game_info_test_ptr->field[i + 1][1] > 0) {
      check = 1;
    }
    if (game_info_test_ptr->field[i + 1][2] > 0) {
      check = 1;
    }
  }
  ck_assert_int_eq(check, 1);
}
START_TEST(user_input_Action) {
  UserAction_t input = Action;
  init_high_score_from_file();
  init_game_field();
  init_next_shape();
  shape_matrix_update();
  init_next_shape();
  input_controller(input);
  update_game_time(input);
  update_shape_in_field();
  int check = 0;
  for (int i = 0; i < 10; i++) {
    if (game_info_test_ptr->field[i + 1][19] > 0) {
      check = 1;
    }
    if (game_info_test_ptr->field[i + 1][20] > 0) {
      check = 1;
    }
  }
  ck_assert_int_eq(check, 1);
}
END_TEST
START_TEST(test_user_input_init) {
  UserAction_t input = Start;
  init_high_score_from_file();
  init_game_field();
  init_next_shape();
  shape_matrix_update();
  init_next_shape();
  for (int i = 0; i < 20; i++) {
    input_controller(input);
    update_game_time(input);
    update_shape_in_field();
  }
  for (int i = 0; i < 10; i++) {
    game_info_test_ptr->field[i + 1][17] = 3;
    game_info_test_ptr->field[i + 1][18] = 3;
    game_info_test_ptr->field[i + 1][19] = 3;
    game_info_test_ptr->field[i + 1][20] = 3;
  }
  check_top_rows();
  game_info_test_ptr->score = 100;
  check_for_full_rows();
  update_game_time(input);
  level_update();
  game_info_test_ptr->score = 300;
  check_for_full_rows();
  update_game_time(input);
  level_update();
  game_info_test_ptr->score = 700;
  check_for_full_rows();
  update_game_time(input);
  level_update();
  game_info_test_ptr->score = 1500;
  check_for_full_rows();
  update_game_time(input);
  level_update();
  int check = 0;
  for (int i = 0; i < 10; i++) {
    if (game_info_test_ptr->field[i + 1][19] > 0) {
      check = 1;
    }
    if (game_info_test_ptr->field[i + 1][20] > 0) {
      check = 1;
    }
  }
  ck_assert_int_eq(check, 1);
}
END_TEST
START_TEST(test_shapes) {
  int **shape = create_matrix_test(4, 4);
  init_matrix_with_shapes_colored(shape, 0, 0, I_SHAPE);
  ck_assert_int_eq(shape[1][1], I_SHAPE);
  init_matrix_with_shapes_colored(shape, 0, 0, J_SHAPE);
  ck_assert_int_eq(shape[1][1], J_SHAPE);
  init_matrix_with_shapes_colored(shape, 0, 0, L_SHAPE);
  ck_assert_int_eq(shape[1][1], L_SHAPE);
  init_matrix_with_shapes_colored(shape, 0, 0, O_SHAPE);
  ck_assert_int_eq(shape[1][1], O_SHAPE);
  init_matrix_with_shapes_colored(shape, 0, 0, S_SHAPE);
  ck_assert_int_eq(shape[1][1], S_SHAPE);
  init_matrix_with_shapes_colored(shape, 0, 0, T_SHAPE);
  ck_assert_int_eq(shape[1][1], T_SHAPE);
  init_matrix_with_shapes_colored(shape, 0, 0, Z_SHAPE);
  ck_assert_int_eq(shape[1][1], Z_SHAPE);
  init_matrix_with_shapes_colored(shape, 0, 0, Z_SHAPE + 1);
  ck_assert_int_eq(shape[1][1], I_SHAPE);
}
END_TEST
START_TEST(test_shape_copy) {
  UserAction_t input = Start;
  init_high_score_from_file();
  init_game_field();
  init_next_shape();
  shape_matrix_update();
  init_next_shape();
  input_controller(Start);
  update_game_time(Start);
  update_shape_in_field();
  rotate_shape();
  init_high_score_from_file();
  init_game_field();
  init_next_shape();
  shape_matrix_update();
  init_next_shape();
  input_controller(Down);
  update_game_time(Down);
  update_shape_in_field();
  int check = 0;
  for (int i = 0; i < 10; i++) {
    if (game_info_test_ptr->field[i + 1][19] == 0) {
      check = 1;
    }
    if (game_info_test_ptr->field[i + 1][20] == 0) {
      check = 1;
    }
  }
  ck_assert_int_eq(check, 1);
}
END_TEST
START_TEST(test_try_move_shape) {
  int temp[SHAPE_SIZE][SHAPE_SIZE] = {{0, 0, 0, 0},
                                      {0, S_SHAPE, S_SHAPE, 0},
                                      {S_SHAPE, S_SHAPE, 0, 0},
                                      {0, 0, 0, 0}};
  int offset = 1;
  ck_assert_int_eq(try_move_shape(temp, offset), true);
}
END_TEST
START_TEST(test_file_hightscore) {
  UserAction_t input = Action;
  init_high_score_from_file();
  init_game_field();
  init_next_shape();
  shape_matrix_update();
  init_next_shape();
  input_controller(input);
  update_game_time(input);
  update_shape_in_field();
  game_info_test_ptr->score = 1000;
  write_high_score_to_file();
  int check = 0;
  FILE *fp = fopen("./brick_game/tetris/hightscores/high_score.txt", "r");
  if (fp == NULL) {
    fprintf(stderr, "Error opening file\n");
    return;
  } else {
    fscanf(fp, "%d", &check);
    fclose(fp);
  }
  ck_assert_int_eq(game_info_test_ptr->score, check);
}
END_TEST
START_TEST(test_score_speed) {
  UserAction_t input = Action;
  init_high_score_from_file();
  init_game_field();
  init_next_shape();
  shape_matrix_update();
  init_next_shape();
  input_controller(input);
  update_game_time(input);
  update_shape_in_field();
  game_info_test_ptr->score = 1000;
}
END_TEST
Suite *tetris_tests_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("Tetris Core Tests");
  tc_core = tcase_create("Core");
  tcase_add_checked_fixture(tc_core, setup, teardown);
  tcase_add_test(tc_core, test_update_current_state);
  tcase_add_test(tc_core, test_user_input_Start);
  tcase_add_test(tc_core, test_user_input_Left);
  tcase_add_test(tc_core, test_user_input_Right);
  tcase_add_test(tc_core, test_user_input_Up);
  tcase_add_test(tc_core, test_user_input_init);
  tcase_add_test(tc_core, test_shapes);
  tcase_add_test(tc_core, test_shape_copy);
  tcase_add_test(tc_core, test_file_hightscore);
  tcase_add_test(tc_core, test_score_speed);
  tcase_add_test(tc_core, test_try_move_shape);
  suite_add_tcase(s, tc_core);
  return s;
}
int main() {
  srand(time(NULL));
  int failed = 0;
  Suite *result[] = {tetris_tests_suite(), NULL};
  for (int i = 0; result[i] != NULL; i++) {
    SRunner *runner = srunner_create(result[i]);
    srunner_run_all(runner, CK_NORMAL);
    failed += srunner_ntests_failed(runner);
    srunner_free(runner);
  }
  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}