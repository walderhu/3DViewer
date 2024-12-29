/**
 * @file main.cpp
 * @brief Main application file
 * @author vleilani walderhu
 * @version 1.0
 *
 * Description of the main application file. Here describes
 * the structure and operation of the main window of the application.
 */

#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}
