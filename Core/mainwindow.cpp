/**
 * @file mainwindow.cpp
 * @brief Implementation of the MainWindow class for the 3D Viewer application.
 *
 * This file contains the implementation of the MainWindow class, which serves
 * as the main interface for the 3D Viewer application. It handles user
 * interactions, manages the 3D widget, and provides functionality for loading
 * and manipulating 3D models.
 *
 * The MainWindow class is responsible for:
 * - Creating and managing the main window of the application
 * - Handling user input and interactions with UI elements
 * - Managing the 3D widget and its associated functionality
 * - Providing methods for loading, displaying, and manipulating 3D models
 * - Implementing various transformations and rendering options
 * - Handling screenshot functionality
 *
 * The class uses Qt framework for creating the GUI and OpenGL for 3D rendering.
 */

#include "mainwindow.h"

#include <QtDebug>

#include "./ui_mainwindow.h"
#include "QtGifImage/src/gifimage/qgifimage.h"
#include "glwid.h"

/**
 * Constructor for the main window of the 3D viewer application.
 *
 * Initializes the main window, sets up UI components, loads settings,
 * and connects signals for various functionalities.
 *
 * @param parent Pointer to the parent widget (usually nullptr).
 */
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setWindowTitle("3DViewer_v1.0");
  setFixedSize(width(), height());
  settings =
      new QSettings(QCoreApplication::applicationDirPath() + "/settings.ini",
                    QSettings::IniFormat, this);
  timer = new QTimer(this);
  load_settings();
  parameters();
  ft_connect();
}

/**
 * Destructor for the main window of the 3D viewer application.
 *
 * Saves application settings, frees memory allocated for the 3D model data,
 * deletes settings object, and releases UI resources.
 */
MainWindow::~MainWindow() {
  save_settings();
  memory_free(&ui->widget->data_obj);
  delete timer;
  delete settings;
  delete ui;
}

/**
 * Updates the UI parameters based on the current settings of the 3D viewer
 * widget.
 *
 * This function synchronizes the UI elements with the internal state of the
 * 3D viewer widget, updating checkboxes, color labels, and other UI controls
 * according to the current projection type, line style, point type, format,
 * thickness, size, and colors.
 */
void MainWindow::parameters() {
  QString str = " background-color : ";
  QString str2 = " background-color : ";
  QString str3 = " background-color : ";
  ui->widget->line_color = QColor(255, 255, 0);
  ui->widget->points_color = QColor(0, 0, 255);
  ui->widget->background_color = QColor(0, 0, 0);
  if (ui->widget->projection == 1) {
    ui->central->setChecked(true);
  } else if (ui->widget->projection == 0) {
    ui->parallel->setChecked(true);
  }
  if (ui->widget->type_line == 1) {
    ui->solid->setChecked(true);
  } else if (ui->widget->type_line == 0) {
    ui->dashed->setChecked(true);
  }
  if (ui->widget->type_point == 0) {
    ui->nonePoint->setChecked(true);
  } else if (ui->widget->type_point == 1) {
    ui->circlePoint->setChecked(true);
  } else if (ui->widget->type_point == 2) {
    ui->squerePoint->setChecked(true);
  }
  if (ui->widget->format == 0) {
    ui->bmpImage->setChecked(true);
  } else if (ui->widget->format == 1) {
    ui->jpegImage->setChecked(true);
  }
  ui->valueThicknessLines->setValue(ui->widget->thickness);
  ui->valueSizePoints->setValue(ui->widget->size_points);

  str += ui->widget->line_color.name();
  ui->label->setStyleSheet(str);

  str2 += ui->widget->points_color.name();
  ui->labelPointColor->setStyleSheet(str2);

  str3 += ui->widget->background_color.name();
  ui->labelBackgroundColor->setStyleSheet(str3);
  ui->widget->setStyleSheet(str3);
}

/**
 * Connects UI elements to their corresponding slots.
 *
 * This function establishes connections between various UI widgets and their
 * associated slot functions. It handles button clicks, value changes, and other
 * user interactions, linking them to appropriate methods for processing.
 */
void MainWindow::ft_connect() {
  connect(ui->openFile, SIGNAL(clicked()), this, SLOT(openFile_clicked()));
  connect(ui->run, SIGNAL(clicked()), this, SLOT(run_clicked()));
  connect(ui->central, SIGNAL(clicked()), this, SLOT(central_clicked()));
  connect(ui->parallel, SIGNAL(clicked()), this, SLOT(parallel_clicked()));
  connect(ui->rescaling, SIGNAL(valueChanged(int)), this,
          SLOT(rescaling_valueChanged(int)));
  connect(ui->resTransX, SIGNAL(valueChanged(int)), this,
          SLOT(resTransX_valueChanged(int)));
  connect(ui->resTransY, SIGNAL(valueChanged(int)), this,
          SLOT(resTransY_valueChanged(int)));
  connect(ui->resTransZ, SIGNAL(valueChanged(int)), this,
          SLOT(resTransZ_valueChanged(int)));
  connect(ui->resRotateX, SIGNAL(valueChanged(int)), this,
          SLOT(resRotateX_valueChanged(int)));
  connect(ui->resRotateY, SIGNAL(valueChanged(int)), this,
          SLOT(resRotateY_valueChanged(int)));
  connect(ui->resRotateZ, SIGNAL(valueChanged(int)), this,
          SLOT(resRotateZ_valueChanged(int)));
  connect(ui->solid, SIGNAL(clicked()), this, SLOT(solid_clicked()));
  connect(ui->dashed, SIGNAL(clicked()), this, SLOT(dashed_clicked()));
  connect(ui->valueThicknessLines, SIGNAL(valueChanged(double)), this,
          SLOT(valueThicknessLines_valueChanged(double)));
  connect(ui->lineColor, SIGNAL(clicked()), this, SLOT(lineColor_clicked()));
  connect(ui->nonePoint, SIGNAL(clicked()), this, SLOT(nonePoint_clicked()));
  connect(ui->circlePoint, SIGNAL(clicked()), this,
          SLOT(circlePoint_clicked()));
  connect(ui->squerePoint, SIGNAL(clicked()), this,
          SLOT(squerePoint_clicked()));
  connect(ui->valueSizePoints, SIGNAL(valueChanged(double)), this,
          SLOT(valueSizePoints_valueChanged(double)));
  connect(ui->pointsColor, SIGNAL(clicked()), this,
          SLOT(pointsColor_clicked()));
  connect(ui->backgroungColor, SIGNAL(clicked()), this,
          SLOT(backgroungColor_clicked()));
  connect(ui->resetAll, SIGNAL(clicked()), this, SLOT(resetAll_clicked()));
  connect(ui->tabWidget, SIGNAL(currentChanged(int)), this,
          SLOT(tabWidget_currentChanged(int)));
  connect(ui->screenshotButton, SIGNAL(clicked()), this,
          SLOT(screenshotButton_clicked()));
  connect(ui->bmpImage, SIGNAL(clicked()), this, SLOT(bmpImage_clicked()));
  connect(ui->jpegImage, SIGNAL(clicked()), this, SLOT(jpegImage_clicked()));
  connect(ui->gif, SIGNAL(clicked()), this, SLOT(gif_clicked()));
  connect(timer, &QTimer::timeout, this, &MainWindow::save_gif);
}

/**
 * Resets all transformation and scaling values to their default states.
 *
 * This function resets the UI controls for rescaling, translation, and rotation
 * to their initial values. It sets all sliders and input fields to zero or
 * fifty percent, effectively resetting any applied transformations.
 */
void MainWindow::reset() {
  ui->rescaling->setValue(50);
  ui->rescaling_input->setValue(50);
  ui->resTransX->setValue(0);
  ui->resTransY->setValue(0);
  ui->resTransZ->setValue(0);
  ui->resTransX_input->setValue(0);
  ui->resTransY_input->setValue(0);
  ui->resTransZ_input->setValue(0);
  ui->resRotateX->setValue(0);
  ui->resRotateY->setValue(0);
  ui->resRotateZ->setValue(0);
  ui->resRotateX_input->setValue(0);
  ui->resRotateY_input->setValue(0);
  ui->resRotateZ_input->setValue(0);
}

/**
 * Handles the click event for opening a .obj file.
 *
 * Opens a file dialog allowing the user to select a .obj file. Sets the
 * selected filename in the UI's fileName field.
 */
void MainWindow::openFile_clicked() {
  QString rootPath = QDir::rootPath();
  QString str_filename = QFileDialog::getOpenFileName(
      this, tr("Open .obj file:"), rootPath, tr("Obj Files (*.obj)"));
  ui->fileName->setText(str_filename);
}

/**
 * Handles the click event for processing and displaying a selected .obj file.
 *
 * Resets transformations, reads the selected .obj file, parses its contents,
 * updates UI elements with file information, and displays the 3D model.
 *
 * @note If the file cannot be parsed, an error message is displayed.
 */
void MainWindow::run_clicked() {
  reset();
  QString file =
      ui->fileName->text();  // получаем имя файла из информации о файле
  QByteArray file_nameUtf8 = file.toUtf8();  // кодировка UTF8
  char* file_name = file_nameUtf8.data();  // массив символов имени файла
  char* obj_name = strrchr(file_name, '/') + 1;
  if (QFile::exists(file_name)) {  // если имя файла есть
    memory_free(&ui->widget->data_obj);
    ui->widget->data_obj = {0, NULL, 0, 0, 0, 0};
    if (parser(file_name, &ui->widget->data_obj) == OK) {
      ui->valueInfoFileName->setText(obj_name);
      get_max_vertex();
      ui->widget->max_vertex_value = max_vertex;
      ui->widget->update();
    } else {
      QMessageBox::information(this, "ERROR", "Select the correct obj-file");
    }
  }
  ui->valueNumderVertices->setText(
      QString::number(ui->widget->data_obj.vertex_count));
  ui->valueNumberEdges->setText(
      QString::number(ui->widget->data_obj.all_edges_count));
}

/**
 * Finds the maximum absolute vertex coordinate value in the 3D model.
 *
 * Iterates through the vertex array to find the largest absolute coordinate
 * value among all vertices. This maximum value is stored in the `max_vertex`
 * variable and used for scaling purposes.
 */
void MainWindow::get_max_vertex() {
  max_vertex = -1;
  for (int i = 3; i < (ui->widget->data_obj.vertex_count + 1) * 3; i++) {
    if (abs(ui->widget->data_obj.vertex_array.matrix[i]) > max_vertex) {
      max_vertex = abs(ui->widget->data_obj.vertex_array.matrix[i]);
    }
  }
}

/**
 * Saves the current application settings to persistent storage.
 *
 * Stores various configuration options, including projection mode, line type,
 * thickness, point size, point type, colors, and more, using the QSettings API.
 */
void MainWindow::save_settings() {
  settings->setValue("projection", ui->widget->projection);
  settings->setValue("type_line", ui->widget->type_line);
  settings->setValue("thickness", ui->widget->thickness);
  settings->setValue("size_points", ui->widget->size_points);
  settings->setValue("type_point", ui->widget->type_point);
  settings->setValue("line_color", ui->widget->line_color);
  settings->setValue("points_color", ui->widget->points_color);
  settings->setValue("background_color", ui->widget->background_color);
}

/**
 * Loads saved application settings from persistent storage.
 *
 * Retrieves various configuration options, including projection mode, line
 * type, thickness, point size, point type, colors, and more, from the QSettings
 * API and applies them to the 3D viewer widget.
 */
void MainWindow::load_settings() {
  ui->widget->projection = settings->value("projection").toInt();
  ui->widget->type_line = settings->value("type_line").toInt();
  ui->widget->thickness = settings->value("thickness").toDouble();
  ui->widget->size_points = settings->value("size_points").toDouble();
  ui->widget->type_point = settings->value("type_point").toInt();
  ui->widget->line_color = settings->value("line_color").toString();
  ui->widget->points_color = settings->value("points_color").toString();
  ui->widget->background_color = settings->value("background_color").toString();
}

/**
 * Switches the 3D viewer to central projection mode.
 *
 * When called, this function sets the projection type to central projection
 * (orthographic projection) and triggers an update of the 3D viewer widget.
 */
void MainWindow::central_clicked() {
  ui->widget->projection = 1;
  ui->widget->update();
}

/**
 * Switches the 3D viewer to parallel projection mode.
 *
 * When called, this function sets the projection type to parallel projection
 * and triggers an update of the 3D viewer widget.
 */
void MainWindow::parallel_clicked() {
  ui->widget->projection = 0;
  ui->widget->update();
}

/**
 * Resets all transformations when switching tabs in the tab widget.
 *
 * This function is triggered when the current tab changes in the tab widget.
 * It calls the resetAll_clicked() method to reset all transformations applied
 * to the 3D model when switching between tabs.
 *
 * @param index The index of the newly selected tab.
 */
void MainWindow::tabWidget_currentChanged(int index) { resetAll_clicked(); }

/**
 * Handles changes to the rescaling value.
 *
 * When called, this function applies scaling to the 3D model based on the given
 * value. It updates the scale factor, resets the input value, and triggers an
 * update of the 3D viewer widget.
 *
 * @param value The new rescaling value.
 */
void MainWindow::rescaling_valueChanged(int value) {
  if (value != 0 && ui->widget->data_obj.vertex_array.matrix) {
    scale(&ui->widget->data_obj, value, ui->widget->scale);
    ui->widget->scale = value;
    ui->rescaling_input->setValue(50);
    ui->widget->update();
  }
}

/**
 * Handles changes to the rescaling input value.
 *
 * When called, this function applies scaling to the 3D model based on the given
 * input value. It updates the scale factor, resets the main rescaling slider,
 * and triggers an update of the 3D viewer widget.
 *
 * @param arg1 The new input value for rescaling.
 */
void MainWindow::on_rescaling_input_valueChanged(int arg1) {
  if (ui->widget->data_obj.vertex_array.matrix) {
    if (arg1 == 0) arg1 = 1;
    scale(&ui->widget->data_obj, arg1, ui->widget->scale);
    ui->widget->scale = arg1;
    ui->rescaling->setValue(50);
    ui->widget->update();
  }
}

/**
 * Handles changes to the X-axis translation value.
 *
 * When called, this function applies translation along the X-axis to the 3D
 * model based on the given value. It updates the translation factors, resets
 * the input value, and triggers an update of the 3D viewer widget.
 *
 * @param value The new X-axis translation value.
 */
void MainWindow::resTransX_valueChanged(int value) {
  if (ui->widget->data_obj.vertex_array.matrix) {
    double new_moveX = ui->widget->max_vertex_value * value / 100;
    move_x(&ui->widget->data_obj, new_moveX, ui->widget->cur_moveX);
    ui->widget->moveX = value;
    ui->widget->cur_moveX = new_moveX;
    ui->resTransX_input->setValue(0);
    ui->widget->update();
  }
}

/**
 * Handles changes to the X-axis translation input value.
 *
 * When called, this function applies translation along the X-axis to the 3D
 * model based on the given input value. It updates the translation factors,
 * resets the main translation slider, sets the input range, and triggers an
 * update of the 3D viewer widget.
 *
 * @param arg1 The new X-axis translation input value.
 */
void MainWindow::on_resTransX_input_valueChanged(double arg1) {
  move_x(&ui->widget->data_obj, arg1, ui->widget->cur_moveX);
  ui->resTransX_input->setMaximum(3 * ui->widget->max_vertex_value);
  ui->resTransX_input->setMinimum(-3 * ui->widget->max_vertex_value);
  ui->widget->cur_moveX = arg1;
  int value = arg1 * 100 / ui->widget->max_vertex_value;
  ui->widget->moveX = value;
  ui->resTransX->setValue(0);
  ui->widget->update();
}

/**
 * Handles changes to the Y-axis translation value.
 *
 * When called, this function applies translation along the Y-axis to the 3D
 * model based on the given value. It updates the translation factors, resets
 * the input value, and triggers an update of the 3D viewer widget.
 *
 * @param value The new Y-axis translation value.
 */
void MainWindow::resTransY_valueChanged(int value) {
  if (ui->widget->data_obj.vertex_array.matrix) {
    double new_moveY = ui->widget->max_vertex_value * value / 100;
    move_y(&ui->widget->data_obj, new_moveY, ui->widget->cur_moveY);
    ui->widget->moveY = value;
    ui->widget->cur_moveY = new_moveY;
    ui->resTransY_input->setValue(0);
    ui->widget->update();
  }
}

/**
 * Handles changes to the Y-axis translation input value.
 *
 * Applies translation along the Y-axis to the 3D model based on the given input
 * value. Updates the slider range and resets the main slider value.
 *
 * @param arg1 The new Y-axis translation input value.
 */
void MainWindow::on_resTransY_input_valueChanged(double arg1) {
  move_y(&ui->widget->data_obj, arg1, ui->widget->cur_moveY);
  ui->resTransY_input->setMaximum(3 * ui->widget->max_vertex_value);
  ui->resTransY_input->setMinimum(-3 * ui->widget->max_vertex_value);
  ui->widget->cur_moveY = arg1;
  int value = arg1 * 100 / ui->widget->max_vertex_value;
  ui->widget->moveY = value;
  ui->resTransY->setValue(0);
  ui->widget->update();
}

/**
 * Handles changes to the Z-axis translation value.
 *
 * Applies translation along the Z-axis to the 3D model based on the given
 * value. Updates the translation factors, resets the input value, and triggers
 * an update of the 3D viewer widget.
 *
 * @param value The new Z-axis translation value.
 */
void MainWindow::resTransZ_valueChanged(int value) {
  if (ui->widget->data_obj.vertex_array.matrix) {
    double new_moveZ = ui->widget->max_vertex_value * value / 100;
    move_z(&ui->widget->data_obj, new_moveZ, ui->widget->cur_moveZ);
    ui->widget->moveZ = value;
    ui->widget->cur_moveZ = new_moveZ;
    ui->resTransZ_input->setValue(0);
    ui->widget->update();
  }
}

/**
 * Handles changes to the Z-axis translation input value.
 *
 * Applies translation along the Z-axis to the 3D model based on the given input
 * value. Updates the slider range and resets the main slider value.
 *
 * @param arg1 The new Z-axis translation input value.
 */
void MainWindow::on_resTransZ_input_valueChanged(double arg1) {
  move_z(&ui->widget->data_obj, arg1, ui->widget->cur_moveZ);
  ui->resTransZ_input->setMaximum(3 * ui->widget->max_vertex_value);
  ui->resTransZ_input->setMinimum(-3 * ui->widget->max_vertex_value);
  ui->widget->cur_moveZ = arg1;
  int value = arg1 * 100 / ui->widget->max_vertex_value;
  ui->widget->moveZ = value;
  ui->resTransZ->setValue(0);
  ui->widget->update();
}

/**
 * Handles changes to the X-axis rotation value.
 *
 * Applies rotation around the X-axis to the 3D model based on the given value.
 * Updates the rotation factor, resets the input value, and triggers an update
 * of the 3D viewer widget.
 *
 * @param value The new X-axis rotation value.
 */
void MainWindow::resRotateX_valueChanged(int value) {
  if (value != 0 && ui->widget->data_obj.vertex_array.matrix) {
    rotate_x(&ui->widget->data_obj, value, ui->widget->rotateX);
    ui->widget->rotateX = value;
    ui->resRotateX_input->setValue(0);
    ui->widget->update();
  }
}

/**
 * Handles changes to the X-axis rotation input value.
 *
 * Applies rotation around the X-axis to the 3D model based on the given input
 * value. Updates the rotation factor, resets the main slider value, and
 * triggers an update of the 3D viewer widget.
 *
 * @param arg1 The new X-axis rotation input value.
 */
void MainWindow::on_resRotateX_input_valueChanged(int arg1) {
  if (ui->widget->data_obj.vertex_array.matrix) {
    rotate_x(&ui->widget->data_obj, arg1, ui->widget->rotateX);
    ui->widget->rotateX = arg1;
    ui->resRotateX->setValue(0);
    ui->widget->update();
  }
}

/**
 * Handles changes to the Y-axis rotation value.
 *
 * Applies rotation around the Y-axis to the 3D model based on the given value.
 * Updates the rotation factor, resets the input value, and triggers an update
 * of the 3D viewer widget.
 *
 * @param value The new Y-axis rotation value.
 */
void MainWindow::resRotateY_valueChanged(int value) {
  if (value != 0 && ui->widget->data_obj.vertex_array.matrix) {
    rotate_y(&ui->widget->data_obj, value, ui->widget->rotateY);
    ui->widget->rotateY = value;
    ui->resRotateY_input->setValue(0);
    ui->widget->update();
  }
}

/**
 * Handles changes to the Y-axis rotation input value.
 *
 * Applies rotation around the Y-axis to the 3D model based on the given input
 * value. Updates the rotation factor, resets the main slider value, and
 * triggers an update of the 3D viewer widget.
 *
 * @param arg1 The new Y-axis rotation input value.
 */
void MainWindow::on_resRotateY_input_valueChanged(int arg1) {
  if (ui->widget->data_obj.vertex_array.matrix) {
    rotate_y(&ui->widget->data_obj, arg1, ui->widget->rotateY);
    ui->widget->rotateY = arg1;
    ui->resRotateY->setValue(0);
    ui->widget->update();
  }
}

/**
 * Handles changes to the Z-axis rotation value.
 *
 * Applies rotation around the Z-axis to the 3D model based on the given value.
 * Updates the rotation factor, resets the input value, and triggers an update
 * of the 3D viewer widget.
 *
 * @param value The new Z-axis rotation value.
 */
void MainWindow::resRotateZ_valueChanged(int value) {
  if (value != 0 && ui->widget->data_obj.vertex_array.matrix) {
    rotate_z(&ui->widget->data_obj, value, ui->widget->rotateZ);
    ui->widget->rotateZ = value;
    ui->resRotateZ_input->setValue(0);
    ui->widget->update();
  }
}

/**
 * Handles changes to the Z-axis rotation input value.
 *
 * Applies rotation around the Z-axis to the 3D model based on the given input
 * value. Updates the rotation factor, resets the main slider value, and
 * triggers an update of the 3D viewer widget.
 *
 * @param arg1 The new Z-axis rotation input value.
 */
void MainWindow::on_resRotateZ_input_valueChanged(int arg1) {
  if (ui->widget->data_obj.vertex_array.matrix) {
    rotate_z(&ui->widget->data_obj, arg1, ui->widget->rotateZ);
    ui->widget->rotateZ = arg1;
    ui->resRotateZ->setValue(0);
    ui->widget->update();
  }
}

/**
 * Resets all transformations when switching tabs in the tab widget.
 *
 * This function is triggered when the current tab changes in the tab widget.
 * It calls the resetAll_clicked() method to reset all transformations applied
 * to the 3D model when switching between tabs.
 *
 * @param index The index of the newly selected tab.
 */
void MainWindow::resetAll_clicked() {
  reset();
  MainWindow::run_clicked();
}

/**
 * Switches the 3D viewer to solid line mode.
 *
 * When called, this function sets the line type to solid and triggers an update
 * of the 3D viewer widget.
 */
void MainWindow::solid_clicked() {
  ui->widget->type_line = 1;
  ui->widget->update();
}

/**
 * Switches the 3D viewer to dashed line mode.
 *
 * When called, this function sets the line type to dashed and triggers an
 * update of the 3D viewer widget.
 */
void MainWindow::dashed_clicked() {
  ui->widget->type_line = 0;
  ui->widget->update();
}

/**
 * Changes the thickness of lines in the 3D viewer.
 *
 * Updates the line thickness based on the given value and triggers an update
 * of the 3D viewer widget.
 *
 * @param arg1 The new thickness value for the lines.
 */
void MainWindow::valueThicknessLines_valueChanged(double arg1) {
  ui->widget->thickness = arg1;
  ui->widget->update();
}

/**
 * Changes the color of lines in the 3D viewer.
 *
 * Opens a color dialog allowing the user to select a new line color,
 * updates the UI label with the selected color, and triggers an update
 * of the 3D viewer widget.
 */
void MainWindow::lineColor_clicked() {
  ui->widget->line_color = QColorDialog::getColor(
      Qt::white, this, "", QColorDialog::DontUseNativeDialog);
  QString str = " background-color : ";
  str += ui->widget->line_color.name();
  ui->label->setStyleSheet(str);
  ui->widget->update();
}

/**
 * Sets the point type to none in the 3D viewer.
 *
 * When called, this function sets the point type to none and triggers an update
 * of the 3D viewer widget.
 */
void MainWindow::nonePoint_clicked() {
  ui->widget->type_point = 0;
  ui->widget->update();
}

/**
 * Sets the point type to circle in the 3D viewer.
 *
 * When called, this function sets the point type to circle and triggers an
 * update of the 3D viewer widget.
 */
void MainWindow::circlePoint_clicked() {
  ui->widget->type_point = 1;
  ui->widget->update();
}

/**
 * Sets the point type to square in the 3D viewer.
 *
 * When called, this function sets the point type to square and triggers an
 * update of the 3D viewer widget.
 */
void MainWindow::squerePoint_clicked() {
  ui->widget->type_point = 2;
  ui->widget->update();
}

/**
 * Changes the size of points in the 3D viewer.
 *
 * Updates the point size based on the given value and triggers an update
 * of the 3D viewer widget.
 *
 * @param arg1 The new size value for the points.
 */
void MainWindow::valueSizePoints_valueChanged(double arg1) {
  ui->widget->size_points = arg1;
  ui->widget->update();
}

/**
 * Changes the color of points in the 3D viewer.
 *
 * Opens a color dialog allowing the user to select a new point color,
 * updates the UI label with the selected color, and triggers an update
 * of the 3D viewer widget.
 */
void MainWindow::pointsColor_clicked() {
  ui->widget->points_color = QColorDialog::getColor(
      Qt::white, this, "", QColorDialog::DontUseNativeDialog);
  QString str = " background-color : ";
  str += ui->widget->points_color.name();
  ui->labelPointColor->setStyleSheet(str);
  ui->widget->update();
}

/**
 * Changes the background color of the 3D viewer.
 *
 * Opens a color dialog allowing the user to select a new background color,
 * updates the UI label with the selected color, applies the color to the
 * widget, and triggers an update of the 3D viewer widget.
 */
void MainWindow::backgroungColor_clicked() {
  ui->widget->background_color = QColorDialog::getColor(
      Qt::white, this, "", QColorDialog::DontUseNativeDialog);
  QString str = " background-color : ";
  str += ui->widget->background_color.name();
  ui->labelBackgroundColor->setStyleSheet(str);
  ui->widget->setStyleSheet(str);
  ui->widget->update();
}

/**
 * Captures and saves a screenshot of the 3D viewer.
 *
 * Grabs the current view of the 3D widget, opens a file dialog for the user to
 * choose a save location, and saves the screenshot in the selected format (BMP
 * or JPEG).
 */
void MainWindow::screenshotButton_clicked() {
  QPixmap screen;
  screen = ui->widget->grab();
  QString screen_path;
  if (ui->widget->format == 0) {
    screen_path = QFileDialog::getSaveFileName(this, tr("Save File"), "",
                                               tr("Images (*.bmp)"));
  }
  if (ui->widget->format == 1) {
    screen_path = QFileDialog::getSaveFileName(this, tr("Save File"), "",
                                               tr("Images (*.jpeg)"));
  }
  screen.save(screen_path);  // save cохраняет пиксельную карту screen в файл
                             // screen_path
}

/**
 * Sets the image format to BMP for screenshots.
 *
 * When called, this function sets the format to BMP and triggers an update
 * of the 3D viewer widget.
 */
void MainWindow::bmpImage_clicked() {
  ui->widget->format = 0;
  ui->widget->update();
}

/**
 * Sets the image format to JPEG for screenshots.
 *
 * When called, this function sets the format to JPEG and triggers an update
 * of the 3D viewer widget.
 */
void MainWindow::jpegImage_clicked() {
  ui->widget->format = 1;
  ui->widget->update();
}

/**
 * Starts capturing frames for GIF animation creation.
 *
 * When called, this function initializes the frame counter and starts a timer
 * to capture frames at regular intervals. The captured frames will later be
 * combined into a GIF animation.
 *
 * @note The timer interval is set to 100ms, resulting in approximately 10
 * frames per second.
 */
void MainWindow::gif_clicked() {
  count_frames = 0;
  timer->start(100);  // 100ms = 10 кадров в секунду
}

/**
 * Saves the captured frames as a GIF animation or continues frame capture.
 *
 * This function checks if the number of captured frames has reached the limit
 * (50). If not, it captures another frame and increments the counter. If the
 * limit is reached, it stops the timer, creates a GIF image, adds all captured
 * frames to it without delay, prompts the user to save the GIF file, and resets
 * the frame counter.
 *
 * @note The GIF animation is saved with dimensions 640x480 pixels.
 */
void MainWindow::save_gif() {
  if (count_frames < 50) {  // 10 * 5 сек
    frames[count_frames] =
        ui->widget->grab()
            .toImage();  // grab() функция QPixmap. toImage() конвертирует
                         // QPixmap в QImage. Это нужно для addFrame()
    count_frames++;
  } else {
    timer->stop();
    QGifImage gif(QSize(640, 480));
    for (int i = 0; i < count_frames; i++) {
      gif.addFrame(frames[i], 0);  // объединить фреймы в gif без задержки
    }
    QString gif_path = QFileDialog::getSaveFileName(
        this, tr("Save File"), "", tr("Gif-animation (*.gif)"));
    gif.save(gif_path);
    count_frames = 0;
  }
}

/**
 * Handles mouse press events for the main window.
 *
 * This function processes left mouse button presses. It updates the
 * LeftMousePressed flag and stores the position of the mouse cursor
 * where the press occurred.
 *
 * @param event Pointer to the QMouseEvent containing information about the
 * mouse press event.
 */
void MainWindow::mousePressEvent(QMouseEvent* event) {
  LeftMousePressed = event->buttons().testFlag(Qt::LeftButton);
  lastPos = event->pos();
}

/**
 * Handles mouse release events for the main window.
 *
 * This function processes the release of the left mouse button. It updates the
 * LeftMousePressed flag to indicate that no mouse buttons are currently
 * pressed.
 *
 * @param event Pointer to the QMouseEvent containing information about the
 * mouse release event.
 */
void MainWindow::mouseReleaseEvent(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton) LeftMousePressed = false;
}

/**
 * Handles mouse movement events for the main window.
 *
 * This function processes mouse movements while the left mouse button is
 * pressed. It calculates the change in mouse position, updates rotation angles,
 * and triggers rotation changes for the 3D viewer.
 *
 * @param event Pointer to the QMouseEvent containing information about the
 * mouse move event.
 */
void MainWindow::mouseMoveEvent(QMouseEvent* event) {
  static float angleX = 0;
  static float angleY = 0;
  static float sensitivity = 0.5f;

  if (LeftMousePressed) {
    QPoint curPos = event->pos();

    float dx = (curPos.x() - lastPos.x()) * sensitivity;
    float dy = (curPos.y() - lastPos.y()) * sensitivity;
    angleX += dy;
    angleY -= dx;
    resRotateX_valueChanged(angleX);
    resRotateY_valueChanged(angleY);
    this->lastPos = curPos;
  }
}

/**
 * Handles wheel events for the main window, implementing zoom functionality.
 *
 * This function processes mouse wheel rotations to adjust the scale of the 3D
 * viewer. It calculates the new scale based on the wheel delta, ensures the
 * scale stays within defined boundaries, and triggers a rescale operation.
 *
 * @param event Pointer to the QWheelEvent containing information about the
 * wheel event.
 */
void MainWindow::wheelEvent(QWheelEvent* event) {
  static float newScale = ui->widget->scale;
  static float min_border = 0.0f;
  static float max_border = 100.0f;
  static float sensitivity = 0.1f;

  float delta = event->angleDelta().y() * sensitivity;
  newScale = qBound(min_border, newScale + delta, max_border);
  rescaling_valueChanged((int)newScale);
}

/**
 * Handles keyboard events for the main window, controlling 3D model
 * translations.
 *
 * This function processes key presses to translate the 3D model along the X and
 * Y axes. It responds to W, S, D, and A keys, adjusting the model's position
 * accordingly. The translation values are bounded within specified limits and
 * trigger corresponding value changed events.
 *
 * @param event Pointer to the QKeyEvent containing information about the key
 * press event.
 */
void MainWindow ::keyPressEvent(QKeyEvent* event) {
  int key = event->key();
  static float maxBorder = 100;
  static float minBorder = -100;
  static float step = 5;
  float value;
  if (key == Qt::Key_W) {
    value = ui->widget->moveY + step;
    resTransY_valueChanged(qBound(minBorder, value, maxBorder));
  } else if (key == Qt::Key_S) {
    value = ui->widget->moveY - step;
    resTransY_valueChanged(qBound(minBorder, value, maxBorder));
  } else if (key == Qt::Key_D) {
    value = ui->widget->moveX + step;
    resTransX_valueChanged(qBound(minBorder, value, maxBorder));
  } else if (key == Qt::Key_A) {
    value = ui->widget->moveX - step;
    resTransX_valueChanged(qBound(minBorder, value, maxBorder));
  }
  event->accept();
}
