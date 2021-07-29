#include <QApplication>
#include <libguile.h>
#include "MainWindow.hpp"



int main(int argc, char** argv) {
  QApplication app(argc, argv);
  app.setApplicationName("GuiREPL");

  MainWindow* window = new MainWindow();
  window->show();

  return app.exec();
}
