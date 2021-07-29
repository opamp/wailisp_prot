#include "MainWindow.hpp"

MainWindow::MainWindow() {
  // Action init
  exitAction = new QAction(tr("E&xit"), this);

  connect(exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

  // Nenu init
  fileMenu = menuBar()->addMenu(tr("&File"));
  fileMenu->addAction(exitAction);

  // Widget init
  central = new CentralWidget();
  setCentralWidget(central);
  setWindowTitle(tr("GuiREPL"));
}
