#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP
#include <QtWidgets>
#include "CentralWidget.hpp"

class MainWindow : public QMainWindow {
Q_OBJECT
public:
  MainWindow();

private:
  QAction *exitAction;

  QMenu *fileMenu;

  CentralWidget* central;
};

#endif
