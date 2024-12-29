#include "s21_3DViever_Tests.h"

START_TEST(test_move_x) {
  data_object *data_obj = initialize_data_object(1);
  move_x(data_obj, 5.0, 1.0);
  ck_assert_double_eq(data_obj->vertex_array.matrix[3], 5.0);
  free_data_object(data_obj);
}

START_TEST(test_move_y) {
  data_object *data_obj = initialize_data_object(1);
  move_y(data_obj, 5.0, 1.0);
  ck_assert_double_eq(data_obj->vertex_array.matrix[4], 5.0);
  free_data_object(data_obj);
}

START_TEST(test_move_z) {
  data_object *data_obj = initialize_data_object(1);
  move_z(data_obj, 5.0, 1.0);
  ck_assert_double_eq(data_obj->vertex_array.matrix[5], 5.0);
  free_data_object(data_obj);
}

Suite *s21_move_x_Tests() {
  Suite *s = suite_create("\033[42m-=s21_move_x test=-\033[0m");
  TCase *t = tcase_create("main tcase");
  tcase_add_test(t, test_move_x);

  suite_add_tcase(s, t);
  return s;
}

Suite *s21_move_y_Tests() {
  Suite *s = suite_create("\033[42m-=s21_move_y test=-\033[0m");
  TCase *t = tcase_create("main tcase");
  tcase_add_test(t, test_move_y);

  suite_add_tcase(s, t);
  return s;
}

Suite *s21_move_z_Tests() {
  Suite *s = suite_create("\033[42m-=s21_move_z test=-\033[0m");
  TCase *t = tcase_create("main tcase");
  tcase_add_test(t, test_move_z);

  suite_add_tcase(s, t);
  return s;
}
