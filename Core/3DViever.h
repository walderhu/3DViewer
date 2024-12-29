/**
 * @file 3DViever.h
 * @brief Header file for 3D Viewer
 *
 * This file contains definitions of data structures and function declarations
 * for working with 3D objects.
 */

#ifndef S21_3D_VIEVER_H
#define S21_3D_VIEVER_H

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif  // _GNU_SOURCE

#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @struct matr
 * @brief Matrix structure
 *
 * This structure represents a two-dimensional matrix.
 */
typedef struct matr {
  double *matrix;
  size_t rows;
  size_t colums;
} matrix_t;

/**
 * @struct poly
 * @brief Polygon structure
 *
 * This structure represents a polygon with one dimension.
 */
typedef struct poly {
  unsigned int *polygon;
  size_t colums;
} polygon_t;

/**
 * @struct data_obj
 * @brief Data Object Structure
 *
 * This structure contains information about a 3D object, including vertices,
 * polygons, and edges.
 */
typedef struct data_obj {
  size_t vertex_count;
  matrix_t vertex_array;
  size_t polygon_count;
  size_t edges_count;
  size_t all_edges_count;
  polygon_t *polygon_array;
} data_object;

/**
 * @enum status
 * @brief Status enumeration
 *
 * Defines possible operation statuses.
 */
enum status { OK, ERROR };

int parser(char *file_name, data_object *data_obj);
void count_vert_pol(FILE *file, data_object *data_obj);
void memory_free_matrix(matrix_t *old_matrix);
void memory_free(data_object *data_obj);
int create_matrix(size_t rows, size_t colums, matrix_t *new_matrix);
int create_polygon(size_t col, polygon_t *new_polygon);
void memory_free_polygon(polygon_t *old_polygon);
void move_x(data_object *data_obj, double new_value, double old_value);
void move_y(data_object *data_obj, double new_value, double old_value);
void move_z(data_object *data_obj, double new_value, double old_value);
void rotate_x(data_object *data_obj, double new_angle, double old_angle);
void rotate_y(data_object *data_obj, double new_angle, double old_angle);
void rotate_z(data_object *data_obj, double new_angle, double old_angle);
void scale(data_object *data_obj, int new_scale, int old_scale);

#endif  // S21_3D_VIEVER_H
