#include "CodeEditors.hpp"

#include <iostream>

CodeEditors::CodeEditors(QWidget *parent):
  QWidget(parent) {

  // Tab and Editors
  tab = new QTabWidget(this);  
  scratch = new FileEdit(this);
  tab->addTab(scratch, "scratch");

  // Toolbar and actions
  toolbar = new QToolBar(this);
  
  neweditAction = new QAction("New");
  openfileAction = new QAction("Open");
  savefileAction = new QAction("Save");
  saveasfileAction = new QAction("Save As");
  closefileAction = new QAction("Close");
  runAction = new QAction("Run");

  connect(neweditAction, SIGNAL(triggered()), this, SLOT(new_trig()));
  connect(openfileAction, SIGNAL(triggered()), this, SLOT(open_trig()));
  connect(savefileAction, SIGNAL(triggered()), this, SLOT(save_trig()));
  connect(saveasfileAction, SIGNAL(triggered()), this, SLOT(saveas_trig()));
  connect(closefileAction, SIGNAL(triggered()), this, SLOT(close_trig()));
  connect(runAction, SIGNAL(triggered()), this, SLOT(run_trig()));

  toolbar->addAction(neweditAction);
  toolbar->addAction(openfileAction);
  toolbar->addAction(savefileAction);
  toolbar->addAction(saveasfileAction);
  toolbar->addAction(closefileAction);
  toolbar->addSeparator();
  toolbar->addAction(runAction);

  // Layout
  topbox = new QVBoxLayout(this);
  topbox->addWidget(toolbar);
  topbox->addWidget(tab);

  tabcount = 0;

  setLayout(topbox);
}

void CodeEditors::selectLastTab() {
  tab->setCurrentIndex(tab->count() - 1);
}

void CodeEditors::new_trig() {
  tabcount += 1;
  FileEdit *edit = new FileEdit(this);
  QString tabtitle = QString("code ") + QString::number(tabcount);
  tab->addTab(edit, tabtitle);
  editors.append(edit);
  selectLastTab();
}

void CodeEditors::open_trig() {
  QString path = QFileDialog::getOpenFileName(this, tr("Open File"));
  FileEdit *edit = new FileEdit(this);
  edit->setFilePath(path);
  edit->load();
  QString tabtitle = edit->getTitle();
  tab->addTab(edit, tabtitle);
  editors.append(edit);
  selectLastTab();
}

void CodeEditors::save_trig() {
  int index = tab->currentIndex() - 1;
  if(index < editors.length()){
    FileEdit *edit = editors.at(index);
    if(edit->isAssociatedWithFile()) {
      edit->save();
    }else {
      saveas_trig();
    }
  }
}

void CodeEditors::saveas_trig() {
  int index = tab->currentIndex() - 1;
  if(index < editors.length()) {
    FileEdit *edit = editors.at(index);
    QString path = QFileDialog::getSaveFileName(this, tr("Save File"));
    edit->setFilePath(path);
    QString tabtitle = edit->getTitle();
    tab->setTabText(index, tabtitle);
    edit->save();
  }
}

void CodeEditors::close_trig() {
  
}

void CodeEditors::run_trig() {
  QPlainTextEdit *currentedit = dynamic_cast<QPlainTextEdit*>(tab->currentWidget());
  if(currentedit) {
    QString code = currentedit->toPlainText();
    emit run_code(code);
  }
}
