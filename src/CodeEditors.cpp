#include "CodeEditors.hpp"

#include <iostream>

CodeEditors::CodeEditors(QWidget *parent):
  QWidget(parent) {

  // Tab and Editors
  tab = new QTabWidget(this);  
  scratch = new QPlainTextEdit(this);
  tab->addTab(scratch, "scratch");

  // Toolbar and actions
  toolbar = new QToolBar(this);
  
  neweditAction = new QAction("New");
  openfileAction = new QAction("Open");
  savefileAction = new QAction("Save");
  closefileAction = new QAction("Close");
  runAction = new QAction("Run");

  connect(runAction, SIGNAL(triggered()), this, SLOT(run_trig()));

  toolbar->addAction(neweditAction);
  toolbar->addAction(openfileAction);
  toolbar->addAction(savefileAction);
  toolbar->addAction(closefileAction);
  toolbar->addSeparator();
  toolbar->addAction(runAction);

  // Layout
  topbox = new QVBoxLayout(this);
  topbox->addWidget(toolbar);
  topbox->addWidget(tab);

  setLayout(topbox);
}

void CodeEditors::run_trig() {
  QPlainTextEdit *currentedit = dynamic_cast<QPlainTextEdit*>(tab->currentWidget());
  if(currentedit) {
    QString code = currentedit->toPlainText();
    emit run_code(code);
  }
}
