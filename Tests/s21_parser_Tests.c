#include <limits.h>

#include "s21_3DViever_Tests.h"
START_TEST(test_parser_null_file_name) {
  data_object data_obj;
  int status = parser(NULL, &data_obj);
  ck_assert_int_eq(status, ERROR);
}
END_TEST

START_TEST(test_parser_null_data_obj) {
  int status = parser("test.txt", NULL);
  ck_assert_int_eq(status, ERROR);
}
END_TEST

START_TEST(test_parser_file_not_found) {
  data_object data_obj;
  int status = parser("non_existent_file.txt", &data_obj);
  ck_assert_int_eq(status, ERROR);
}
END_TEST

START_TEST(test_parser_success) {
  data_object data_obj = {0};
  char *file_name = "ball.obj";
  int result = parser(file_name, &data_obj);
  memory_free(&data_obj);
  remove(file_name);
}
END_TEST

START_TEST(test_parser_large_model) {
  data_object data_obj = {0};
  char *file_name = "large_model.obj";
  int result = parser(file_name, &data_obj);
  memory_free(&data_obj);
  remove(file_name);
}
END_TEST

START_TEST(test_parser_non_existent_file) {
  data_object data_obj = {0};
  char *file_name = "non_existent_file.obj";
  int result = parser(file_name, &data_obj);
  ck_assert_int_eq(result, ERROR);
  memory_free(&data_obj);
}
END_TEST

START_TEST(test_parser_large_numbers) {
  data_object data_obj = {0};
  char *file_name = "large_numbers.obj";
  int result = parser(file_name, &data_obj);
  memory_free(&data_obj);
  remove(file_name);
}
END_TEST

data_object *initialize_data_object(size_t vertex_count) {
  data_object *data_obj = malloc(sizeof(data_object));
  data_obj->vertex_count = vertex_count;
  data_obj->vertex_array.matrix =
      malloc((vertex_count + 1) * 3 * sizeof(double));

  for (size_t i = 0; i < vertex_count + 1; i++) {
    data_obj->vertex_array.matrix[i * 3] = (double)i;
    data_obj->vertex_array.matrix[i * 3 + 1] = (double)i;
    data_obj->vertex_array.matrix[i * 3 + 2] = (double)i;
  }

  return data_obj;
}

void free_data_object(data_object *data_obj) {
  if (data_obj) {
    free(data_obj->vertex_array.matrix);
    free(data_obj);
  }
}

START_TEST(succes_test) {
  char *file_name = "../Obj/cat.obj";
  char *obj_name = strrchr(file_name, '/');
  if (obj_name) {
    obj_name++;
  } else {
    obj_name = (char *)file_name;
  }

  data_object data_obj = {0, NULL, 0, 0, 0, 0};
  int result = parser(file_name, &data_obj);

  if (result == OK) {
    printf("File loaded successfully: %s\n", obj_name);
  } else {
    fprintf(stderr, "Error: Failed to load file %s\n", file_name);
  }
  memory_free(&data_obj);
}
END_TEST

START_TEST(Err_test) {
  char *file_name = "../Obj/no_exist_file.obj";
  char *obj_name = strrchr(file_name, '/');
  if (obj_name) {
    obj_name++;
  } else {
    obj_name = (char *)file_name;
  }

  data_object data_obj = {0, NULL, 0, 0, 0, 0};
  int result = parser(file_name, &data_obj);

  if (result == OK) {
    printf("File loaded successfully: %s\n", obj_name);
  } else {
    fprintf(stderr, "Error: Failed to load file %s\n", file_name);
  }
  memory_free(&data_obj);
}
END_TEST

START_TEST(create_polygon_error_test) {
  polygon_t test_polygon;
  memset(&test_polygon, 0, sizeof(test_polygon));
  test_polygon.colums = 0;

  int result = create_polygon(0, &test_polygon);
  ck_assert_int_eq(result, ERROR);
  ck_assert_ptr_eq(test_polygon.polygon, NULL);

  printf("create_polygon error test passed\n");
}
END_TEST

START_TEST(create_matrix_error_test) {
  matrix_t test_matrix;
  memset(&test_matrix, 0, sizeof(test_matrix));

  int result = create_matrix(0, 0, &test_matrix);
  ck_assert_int_eq(result, ERROR);
  ck_assert_ptr_eq(test_matrix.matrix, NULL);

  printf("create_matrix error test passed\n");
}
END_TEST

START_TEST(parser_error_test) {
  data_object data_obj;
  memset(&data_obj, 0, sizeof(data_object));
  int result = parser(NULL, &data_obj);
  ck_assert_int_eq(result, ERROR);
  result = parser("test.txt", NULL);
  ck_assert_int_eq(result, ERROR);
  result = parser("non_existent_file.txt", &data_obj);
  ck_assert_int_eq(result, ERROR);
  printf("parser error test passed\n");
}
END_TEST

START_TEST(parser_matrix_creation_error_test) {
  data_object data_obj;
  memset(&data_obj, 0, sizeof(data_object));
  data_obj.vertex_count = INT_MAX;
  FILE *temp_file = tmpfile();
  if (!temp_file) {
    perror("Failed to create temporary file");
    exit(EXIT_FAILURE);
  }

  fprintf(temp_file, "v 0 0 0\n");
  rewind(temp_file);
  int result = parser("temporary_file", &data_obj);
  fclose(temp_file);
  ck_assert_int_eq(result, ERROR);
  memory_free(&data_obj);
  printf("parser matrix creation error test passed\n");
}
END_TEST

Suite *s21_parser_Tests(void) {
  Suite *s = suite_create("\033[42m-=s21_parser test=-\033[0m");
  TCase *t = tcase_create("main tcase");
  tcase_add_test(t, test_parser_null_file_name);
  tcase_add_test(t, test_parser_null_data_obj);
  tcase_add_test(t, test_parser_file_not_found);
  tcase_add_test(t, test_parser_success);
  tcase_add_test(t, test_parser_large_model);
  tcase_add_test(t, test_parser_non_existent_file);
  tcase_add_test(t, test_parser_large_numbers);
  tcase_add_test(t, succes_test);
  tcase_add_test(t, Err_test);
  tcase_add_test(t, create_polygon_error_test);
  tcase_add_test(t, create_matrix_error_test);
  tcase_add_test(t, parser_error_test);
  tcase_add_test(t, parser_matrix_creation_error_test);

  suite_add_tcase(s, t);
  return s;
}
