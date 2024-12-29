/**
 * @class GLWid
 * @brief A custom OpenGL widget for displaying 3D objects
 *
 * This class extends QOpenGLWidget to provide a specialized OpenGL rendering
 * environment for 3D visualization. It handles initialization, painting, and
 * various settings for projecting and drawing 3D objects.
 *
 * Key features:
 * - Supports both frustum and orthographic projections
 * - Allows customization of line types, thickness, and colors
 * - Enables point cloud visualization with smooth shading
 * - Handles vertex and polygon data for efficient rendering
 *
 * Usage:
 * - Initialize OpenGL functions in initializeGL()
 * - Set up projection, line type, thickness, and color in paintGL()
 * - Access and modify data_obj for customizing rendered objects
 */

#include "glwid.h"

#include <QtGui/qevent.h>

#include <QtDebug>

/**
 * @brief Constructor
 * @param parent Parent widget
 */
GLWid::GLWid(QWidget *parent) : QOpenGLWidget{parent} {}

/**
 * @brief Destructor
 * Frees allocated memory
 */
GLWid::~GLWid() { memory_free(&data_obj); }

/**
 * @brief Initializes OpenGL functions
 */
void GLWid::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
}

/**
 * @brief Paints the OpenGL scene
 */
void GLWid::paintGL() {
  glClearColor(background_color.redF(), background_color.greenF(),
               background_color.blueF(), 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  select_projection();
  select_thickness();
  select_size_points();
  select_line_type();
  if (data_obj.polygon_count != 0) {
    glVertexPointer(3, GL_DOUBLE, 0, data_obj.vertex_array.matrix);
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3f(line_color.redF(), line_color.greenF(), line_color.blueF());
    for (int i = 0; i < data_obj.polygon_count; i++) {
      glDrawElements(GL_LINE_LOOP, data_obj.polygon_array[i].colums,
                     GL_UNSIGNED_INT, data_obj.polygon_array[i].polygon);
    }
    if (type_line == 0) {
      glDisable(GL_LINE_STIPPLE);
    }
    if (type_point != 0) select_type_point();
    glDisableClientState(GL_VERTEX_ARRAY);
  }
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

/**
 * @brief Selects the projection matrix
 */
void GLWid::select_projection() {
  if (projection == 1) {
    glFrustum(-1 * max_vertex_value, 1 * max_vertex_value,
              -1 * max_vertex_value, 1 * max_vertex_value, 1 * max_vertex_value,
              10 * max_vertex_value);
    glTranslatef(0, 0, -2.2 * max_vertex_value);
  } else
    glOrtho(-1.1 * max_vertex_value, 1.1 * max_vertex_value,
            -1.1 * max_vertex_value, 1.1 * max_vertex_value,
            -1.1 * max_vertex_value, 10 * max_vertex_value);
}

/**
 * @brief Sets the line type
 */
void GLWid::select_line_type() {
  if (type_line == 0) {
    glEnable(GL_LINE_STIPPLE);  // разрешаем рисовать препывистую линию
    glLineStipple(2, 0x00FF);  // dashed
  }
}

/**
 * @brief Sets the line thickness
 */
void GLWid::select_thickness() { glLineWidth(thickness); }

/**
 * @brief Sets the line type
 */
void GLWid::select_size_points() { glPointSize(size_points); }

/**
 * @brief Selects the point type
 */
void GLWid::select_type_point() {
  if (type_point == 1) {
    glEnable(GL_POINT_SMOOTH);
  }
  glColor3f(points_color.redF(), points_color.greenF(), points_color.blueF());
  glDrawArrays(GL_POINTS, 1, data_obj.vertex_count);
  glDisable(GL_POINT_SMOOTH);
  if (type_point == 1) {
    glDisable(GL_POINT);
  }
}
