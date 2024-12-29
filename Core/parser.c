/**
 * @file parser.c
 * @brief Module for parsing 3D model files (.obj)
 *
 * This module contains functions for parsing .obj files and creating data
 * structures to represent 3D models. It includes functions for counting
 * vertices and polygons, parsing vertex coordinates, and creating matrices and
 * polygons.
 *
 * Key features:
 * - Parses .obj files to extract 3D model information
 * - Counts vertices and polygons in the input file
 * - Stores parsed vertex coordinates in a matrix
 * - Creates polygon arrays based on edge counts
 * - Allocates memory for matrices and polygons as needed
 * - Provides functions for freeing allocated memory when done
 *
 * Usage:
 *   1. Initialize a data_object structure
 *   2. Call parser() to parse the .obj file
 *   3. Access parsed data through the data_object structure
 */

#include "3DViever.h"

/**
 * @brief Parses vertex coordinates from an .obj file
 *
 * Reads vertex coordinates from the file and stores them in the vertex_array
 * of the data_object struct.
 *
 * @param file Pointer to the .obj file
 * @param data_obj Pointer to the data_object struct
 * @return OK if successful, ERROR otherwise
 */
int parser_vert_pol(FILE *file, data_object *data_obj) {
  int status = OK;
  char *buff = NULL;
  size_t len = 0, count = 1;
  double x = 0, y = 0, z = 0;
  long tmp;
  char *istr;
  char str[1025] = "";
  int i = 3, j = 0, m = 0;
  if (!data_obj && !data_obj->polygon_array) status = ERROR;
  while ((getline(&buff, &len, file)) != -1) {
    if ((buff[0] == 'v') && (buff[1] == ' ')) {
      if (sscanf(buff, "v %lf %lf %lf", &x, &y, &z) == 3) {
        count++;
        data_obj->vertex_array.matrix[i++] = x;
        data_obj->vertex_array.matrix[i++] = y;
        data_obj->vertex_array.matrix[i++] = z;
      } else
        status = ERROR;
    } else if ((buff[0] == 'f') &&
               (buff[1] == ' ')) {  // записываем в массив координаты ребер
      strcpy(str, buff);
      istr = strtok(buff + 1, " ");  // Выделение первой части строки
      while (istr != NULL && atoi(istr) != 0) {  // Выделение последующих частей
        data_obj->edges_count++;
        istr = strtok(NULL, " ");  // Выделение очередной части строки
      }
      if (create_polygon(data_obj->edges_count, &data_obj->polygon_array[m]) ==
          OK) {
        istr = strtok(str + 1, " ");
        while (istr != NULL) {  // Выделение последующих частей
          data_obj->all_edges_count++;
          tmp = atoi(istr);
          if (data_obj->polygon_array && data_obj->polygon_array[m].polygon) {
            if (tmp < 0) {
              data_obj->polygon_array[m].polygon[j++] = count + tmp;
            } else {
              data_obj->polygon_array[m].polygon[j++] = atoi(istr);
            }
          }
          istr = strtok(NULL, " ");  // Выделение очередной части строки
        }
        data_obj->edges_count = 0;
        m++;
      }
    }
    j = 0;
  }
  if (buff) free(buff);
  return status;
}

/**
 * @brief Counts vertices and polygons in an .obj file
 *
 * Reads through the file once to count the number of vertices and polygons.
 *
 * @param file Pointer to the .obj file
 * @param data_obj Pointer to the data_object struct
 */
void count_vert_pol(FILE *file, data_object *data_obj) {
  char *buff = NULL;
  size_t len = 0;
  while ((getline(&buff, &len, file)) != EOF) {
    if ((buff[0] == 'v') && (buff[1] == ' '))
      data_obj->vertex_count++;
    else if ((buff[0] == 'f') && (buff[1] == ' ')) {
      data_obj->polygon_count++;  // далее будем считать количество ребер
    }
  }
  if (buff) free(buff);
}

/**
 * @brief Main function for parsing an .obj file
 *
 * Initializes the data_object struct, counts vertices and polygons, then parses
 * the vertex coordinates.
 *
 * @param file_name Name of the .obj file to parse
 * @param data_obj Pointer to the data_object struct
 * @return OK if successful, ERROR otherwise
 */
int parser(char *file_name, data_object *data_obj) {
  if (file_name == NULL || data_obj == NULL) return ERROR;
  FILE *file = fopen(file_name, "r");
  int status = OK;
  if (file) {
    count_vert_pol(file, data_obj);
    if (data_obj->polygon_count > 0) {
      data_obj->polygon_array =
          (polygon_t *)calloc(data_obj->polygon_count, sizeof(polygon_t));
    }
    if (create_matrix(data_obj->vertex_count + 1, (size_t)3,
                      &data_obj->vertex_array) == OK) {
      fseek(file, 0, SEEK_SET);  // возврат к началу файла
      status = parser_vert_pol(file, data_obj);
    } else
      status = ERROR;
    fclose(file);
  } else
    status = ERROR;
  return status;
}

/**
 * @brief Creates a new polygon array
 *
 * Allocates memory for a new polygon array based on the number of polygons.
 *
 * @param col Number of columns in the polygon
 * @param new_polygon Pointer to the new polygon_t structure
 * @return OK if successful, ERROR otherwise
 */
int create_polygon(size_t col, polygon_t *new_polygon) {
  int status = OK;
  if (new_polygon) {
    if (col > 0) {
      new_polygon->colums = col;
      new_polygon->polygon = (unsigned int *)calloc(col, sizeof(unsigned int));
    } else {
      printf("Polygon creation ERROR");
      status = ERROR;
      new_polygon->polygon = NULL;
    }
  }
  return status;
}

/**
 * @brief Creates a new matrix
 *
 * Allocates memory for a new matrix based on the specified dimensions.
 *
 * @param rows Number of rows in the matrix
 * @param colums Number of columns in the matrix
 * @param new_matrix Pointer to the new matrix_t structure
 * @return OK if successful, ERROR otherwise
 */
int create_matrix(size_t rows, size_t colums, matrix_t *new_matrix) {
  int status = OK;
  if (rows > 0 && colums > 0) {
    new_matrix->rows = rows;
    new_matrix->colums = colums;
    new_matrix->matrix = (double *)calloc(rows * colums, sizeof(double));
  } else {
    printf("Matrix creation ERROR");
    status = ERROR;
    new_matrix->matrix = NULL;
  }
  return status;
}

/**
 * @brief Frees memory allocated for a matrix
 *
 * Frees the memory allocated for the matrix and resets the pointer.
 *
 * @param old_matrix Pointer to the matrix_t structure
 */
void memory_free_matrix(matrix_t *old_matrix) {
  free(old_matrix->matrix);
  old_matrix->matrix = NULL;
}

/**
 * @brief Frees memory allocated for a polygon
 *
 * Frees the memory allocated for the polygon and resets the pointer.
 *
 * @param old_polygon Pointer to the polygon_t structure
 */

void memory_free_polygon(polygon_t *old_polygon) {
  free(old_polygon->polygon);
  old_polygon->polygon = NULL;
}

/**
 * @brief Frees all allocated memory for the data_object
 *
 * Frees memory for vertex arrays, polygon arrays, and resets pointers.
 *
 * @param data_obj Pointer to the data_object struct
 */
void memory_free(data_object *data_obj) {
  if (data_obj != NULL) {
    if (data_obj->vertex_array.matrix != NULL)
      memory_free_matrix(&data_obj->vertex_array);
    if (data_obj->polygon_array != NULL) {
      for (size_t i = 0; i < data_obj->polygon_count; i++) {
        if (data_obj->polygon_array[i].polygon != NULL)
          memory_free_polygon(&data_obj->polygon_array[i]);
      }
      free(data_obj->polygon_array);
      data_obj->polygon_array = NULL;
    }
    data_obj = NULL;
  }
}