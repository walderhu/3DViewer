/**
 * @file mainwindow.h
 * @brief Header file for the main window of the 3D viewer application
 *
 * This header file defines the interface for the main window of the 3D viewer
 * application. It includes necessary Qt classes and defines the MainWindow
 * class.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QBrush>
#include <QColor>
#include <QColorDialog>
#include <QDialog>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QPalette>
#include <QPixmap>
#include <QScreen>
#include <QSettings>
#include <QTimer>
#include <QVBoxLayout>
#include <QVector>
#include <QWidget>

#include "QtGifImage/src/gifimage/qgifimage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

 private slots:
  void parameters();
  void ft_connect();
  void reset();
  void openFile_clicked();
  void run_clicked();
  void central_clicked();
  void parallel_clicked();
  void rescaling_valueChanged(int value);
  void resTransX_valueChanged(int value);
  void resTransY_valueChanged(int value);
  void resTransZ_valueChanged(int value);
  void resRotateX_valueChanged(int value);
  void resRotateY_valueChanged(int value);
  void resRotateZ_valueChanged(int value);
  void solid_clicked();
  void dashed_clicked();
  void valueThicknessLines_valueChanged(double arg1);
  void lineColor_clicked();
  void nonePoint_clicked();
  void circlePoint_clicked();
  void squerePoint_clicked();
  void valueSizePoints_valueChanged(double arg1);
  void pointsColor_clicked();
  void backgroungColor_clicked();
  void on_resRotateX_input_valueChanged(int arg1);
  void on_resRotateZ_input_valueChanged(int arg1);
  void on_resRotateY_input_valueChanged(int arg1);
  void on_resTransX_input_valueChanged(double arg1);
  void on_resTransY_input_valueChanged(double arg1);
  void on_resTransZ_input_valueChanged(double arg1);
  void on_rescaling_input_valueChanged(int arg1);
  void resetAll_clicked();
  void tabWidget_currentChanged(int index);
  void screenshotButton_clicked();
  void bmpImage_clicked();
  void jpegImage_clicked();
  void gif_clicked();
  void save_gif();

 public:
  double max_vertex;
  void save_settings();
  void load_settings();
  void get_max_vertex();

  //
  QPoint lastPos;  // Последняя позиция курсора мыши
  bool LeftMousePressed = false;  // Флаг нажатия левой кнопки мыши
  //   bool RightMousePressed = false;  // Флаг нажатия правой кнопки мыши

  void mousePressEvent(QMouseEvent* event);
  void mouseReleaseEvent(QMouseEvent* event);
  void mouseMoveEvent(QMouseEvent* event);
  void wheelEvent(QWheelEvent* event);
  void keyPressEvent(QKeyEvent* event);

 private:
  Ui::MainWindow* ui;
  QSettings* settings;
  QTimer* timer;
  int count_frames;
  QImage frames[50];
};
#endif  // MAINWINDOW_H
