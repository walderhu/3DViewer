#ifndef S21_3D_VIEVER_TEST_H
#define S21_3D_VIEVER_TEST_H

#include <check.h>
#include <stdio.h>

#include "../Core/3DViever.h"

int run_testcase(Suite *testcase);
void run_tests(void);
Suite *s21_parser_Tests();
Suite *s21_move_x_Tests();
Suite *s21_move_y_Tests();
Suite *s21_move_z_Tests();

Suite *s21_rotate_x_Tests();
Suite *s21_rotate_y_Tests();
Suite *s21_rotate_z_Tests();

Suite *s21_scale_Tests();
data_object *initialize_data_object(size_t vertex_count);
void free_data_object(data_object *data_obj);
#endif
