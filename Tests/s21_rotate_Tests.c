#include "s21_3DViever_Tests.h"

START_TEST(test_rotate_x) {
  data_object *data_obj = initialize_data_object(1);
  rotate_x(data_obj, 90.0, 0.0);
  free_data_object(data_obj);
}

START_TEST(test_rotate_y) {
  data_object *data_obj = initialize_data_object(1);
  rotate_y(data_obj, 90.0, 0.0);
  free_data_object(data_obj);
}

START_TEST(test_rotate_z) {
  data_object *data_obj = initialize_data_object(1);
  rotate_z(data_obj, 90.0, 0.0);
  free_data_object(data_obj);
}

START_TEST(test_scale) {
  data_object *data_obj = initialize_data_object(1);
  scale(data_obj, 2, 1);
  ck_assert_double_eq(data_obj->vertex_array.matrix[3], 2.0);
  ck_assert_double_eq(data_obj->vertex_array.matrix[4], 2.0);
  ck_assert_double_eq(data_obj->vertex_array.matrix[5], 2.0);
  free_data_object(data_obj);
}

Suite *s21_rotate_x_Tests() {
  Suite *s = suite_create("\033[42m-=s21_rotate_x test=-\033[0m");
  TCase *t = tcase_create("main tcase");
  tcase_add_test(t, test_rotate_x);

  suite_add_tcase(s, t);
  return s;
}

Suite *s21_rotate_y_Tests() {
  Suite *s = suite_create("\033[42m-=s21_rotate_y test=-\033[0m");
  TCase *t = tcase_create("main tcase");
  tcase_add_test(t, test_rotate_y);

  suite_add_tcase(s, t);
  return s;
}

Suite *s21_rotate_z_Tests() {
  Suite *s = suite_create("\033[42m-=s21_rotate_z test=-\033[0m");
  TCase *t = tcase_create("main tcase");
  tcase_add_test(t, test_rotate_z);

  suite_add_tcase(s, t);
  return s;
}

Suite *s21_scale_Tests() {
  Suite *s = suite_create("\033[42m-=s21_scale test=-\033[0m");
  TCase *t = tcase_create("main tcase");
  tcase_add_test(t, test_scale);

  suite_add_tcase(s, t);
  return s;
}
