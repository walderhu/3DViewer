#include "s21_3DViever_Tests.h"

int main(void) {
  run_tests();
  return 0;
}

int run_testcase(Suite *testcase) {
  int result = 1;
  static int counter_testcase = 1;
  if (counter_testcase > 1) counter_testcase++;
  SRunner *sr = srunner_create(testcase);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  result = srunner_ntests_failed(sr);
  srunner_free(sr);
  return result;
}

void run_tests(void) {
  Suite *list_cases[] = {
      s21_parser_Tests(),   s21_move_x_Tests(),   s21_move_y_Tests(),
      s21_move_z_Tests(),   s21_rotate_x_Tests(), s21_rotate_y_Tests(),
      s21_rotate_z_Tests(), s21_scale_Tests(),    NULL};
  int number_failed = 0;
  int number_success = 0;
  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    if (run_testcase(*current_testcase) != 0)
      number_failed++;
    else
      number_success++;
  }
  printf("\e[32mSuccess: %d\e[0m\n\e[31mFailures: %d\e[0m\n", number_success,
         number_failed);
}
