/**
 * @file glwid.h
 * @brief Header file for the custom OpenGL widget
 *
 * This header file declares the GLWid class, which is a custom OpenGL widget
 * for displaying 3D objects in the 3D viewer application. It includes necessary
 * Qt OpenGL classes and defines the GLWid class.
 */

#ifndef GLWID_H
#define GLWID_H

#define GL_SILENCE_DEPRECATION

#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QWidget>

extern "C" {
#include "3DViever.h"
}

/**
 * @class GLWid
 * @brief Custom OpenGL widget for displaying 3D objects
 *
 * This class inherits from QOpenGLWidget and implements custom OpenGL
 * functionality for rendering 3D objects. It provides methods for
 * initializing OpenGL, painting 3D scenes, and controlling various display
 * properties.
 */
class GLWid : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT
 public:
  explicit GLWid(QWidget *parent = nullptr);
  data_object data_obj = {0, NULL, 0, 0, 0, 0};
  double max_vertex_value;
  int scale = 50;
  int moveX = 0, moveY = 0, moveZ = 0;
  double cur_moveX = 0, cur_moveY = 0, cur_moveZ = 0;
  int rotateX = 0, rotateY = 0, rotateZ = 0;
  int projection = 1;
  int type_line = 1;
  int type_point = 0;
  double thickness = 1;
  double size_points = 1;
  int format = 0;
  QColor line_color = QColor(255, 255, 0);
  QColor points_color = QColor(0, 0, 255);
  QColor background_color = QColor(0, 0, 0);

  void initializeGL() override;
  void paintGL() override;
  void select_projection();
  void select_line_type();
  void select_thickness();
  void select_size_points();
  void select_type_point();

  QPoint lastPos;  // Последняя позиция курсора мыши

 private:
  void get_max_vertex();

 private:
  ~GLWid() override;
};

#endif  // GLWID_H
