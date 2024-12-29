/**
 * @file affine.c
 * @brief Module for handling transformations (move, rotate, scale) of 3D
 * objects
 *
 * This module provides functions to manipulate 3D objects by applying
 * transformations such as moving, rotating, and scaling. It operates on the
 * vertex array matrix of the 3D object, modifying its position, orientation,
 * and size.
 *
 * Key features:
 * - Move objects along X, Y, and Z axes
 * - Rotate objects around X, Y, and Z axes
 * - Scale objects uniformly
 *
 * Functions in this module:
 * - move(): Applies a general transformation to any axis
 * - move_x(), move_y(), move_z(): Specialized functions for moving along X,
 * Y, Z axes
 * - rotate(): Applies a general rotation around any axis
 * - rotate_x(), rotate_y(), rotate_z(): Specialized functions for rotating
 * around X, Y, Z axes
 * - scale(): Uniformly scales the object
 */

#include "3DViever.h"

/**
 * @brief Moves a 3D object along the X-axis
 *
 * @param data_obj Pointer to the 3D object structure
 * @param new_value New position along the X-axis
 * @param old_value Old position along the X-axis
 */
void move_x(data_object *data_obj, double new_value, double old_value) {
  if (data_obj->vertex_array.matrix) {
    for (size_t i = 3; i < (data_obj->vertex_count + 1) * 3; i += 3) {
      data_obj->vertex_array.matrix[i] += (new_value - old_value);
    }
  }
}

/**
 * @brief Moves a 3D object along the Y-axis
 *
 * @param data_obj Pointer to the 3D object structure
 * @param new_value New position along the Y-axis
 * @param old_value Old position along the Y-axis
 */
void move_y(data_object *data_obj, double new_value, double old_value) {
  if (data_obj->vertex_array.matrix) {
    for (size_t i = 4; i < (data_obj->vertex_count + 1) * 3; i += 3) {
      data_obj->vertex_array.matrix[i] += (new_value - old_value);
    }
  }
}

/**
 * @brief Moves a 3D object along the Z-axis
 *
 * @param data_obj Pointer to the 3D object structure
 * @param new_value New position along the Z-axis
 * @param old_value Old position along the Z-axis
 */
void move_z(data_object *data_obj, double new_value, double old_value) {
  if (data_obj->vertex_array.matrix) {
    for (size_t i = 5; i < (data_obj->vertex_count + 1) * 3; i += 3) {
      data_obj->vertex_array.matrix[i] += (new_value - old_value);
    }
  }
}

/**
 * @brief Rotates a 3D object around the X-axis
 *
 * @param data_obj Pointer to the 3D object structure
 * @param new_angle New rotation angle in degrees
 * @param old_angle Old rotation angle in degrees
 */
void rotate_x(data_object *data_obj, double new_angle, double old_angle) {
  new_angle = new_angle * M_PI / 180.0;
  old_angle = old_angle * M_PI / 180.0;
  for (size_t i = 0; i < (data_obj->vertex_count + 1) * 3; i += 3) {
    double y = data_obj->vertex_array.matrix[i + 1];
    double z = data_obj->vertex_array.matrix[i + 2];
    // x = x; y = y * cos + z * sin; z = -y * sin + z * cos;
    data_obj->vertex_array.matrix[i + 1] =
        y * cosf(new_angle - old_angle) + z * sinf(new_angle - old_angle);
    data_obj->vertex_array.matrix[i + 2] =
        -y * sinf(new_angle - old_angle) + z * cosf(new_angle - old_angle);
  }
}

/**
 * @brief Rotates a 3D object around the Y-axis
 *
 * @param data_obj Pointer to the 3D object structure
 * @param new_angle New rotation angle in degrees
 * @param old_angle Old rotation angle in degrees
 */
void rotate_y(data_object *data_obj, double new_angle, double old_angle) {
  new_angle = new_angle * M_PI / 180.0;
  old_angle = old_angle * M_PI / 180.0;
  for (size_t i = 0; i < (data_obj->vertex_count + 1) * 3; i += 3) {
    double x = data_obj->vertex_array.matrix[i];
    double z = data_obj->vertex_array.matrix[i + 2];
    // x = x * cos + z * sin; y = y; z = -x * sin + z * cos;
    data_obj->vertex_array.matrix[i] =
        x * cosf(new_angle - old_angle) + z * sinf(new_angle - old_angle);
    data_obj->vertex_array.matrix[i + 2] =
        -x * sinf(new_angle - old_angle) + z * cosf(new_angle - old_angle);
  }
}

/**
 * @brief Rotates a 3D object around the Z-axis
 *
 * @param data_obj Pointer to the 3D object structure
 * @param new_angle New rotation angle in degrees
 * @param old_angle Old rotation angle in degrees
 */
void rotate_z(data_object *data_obj, double new_angle, double old_angle) {
  new_angle = new_angle * M_PI / 180.0;
  old_angle = old_angle * M_PI / 180.0;
  for (size_t i = 0; i < (data_obj->vertex_count + 1) * 3; i += 3) {
    double x = data_obj->vertex_array.matrix[i];
    double y = data_obj->vertex_array.matrix[i + 1];
    // x = x * cos - y * sin; y = x * sin + y * cos; z = z;
    data_obj->vertex_array.matrix[i] =
        x * cosf(new_angle - old_angle) - y * sinf(new_angle - old_angle);
    data_obj->vertex_array.matrix[i + 1] =
        x * sinf(new_angle - old_angle) + y * cosf(new_angle - old_angle);
  }
}

/**
 * @brief Scales a 3D object
 *
 * @param data_obj Pointer to the 3D object structure
 * @param new_scale New scale factor
 * @param old_scale Old scale factor
 */
void scale(data_object *data_obj, int new_scale, int old_scale) {
  for (size_t i = 3; i < (data_obj->vertex_count + 1) * 3; i++) {
    data_obj->vertex_array.matrix[i] *= (double)new_scale / (double)old_scale;
  }
}
