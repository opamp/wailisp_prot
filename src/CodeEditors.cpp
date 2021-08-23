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
  if(index < editors.length() && index >= 0){
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
  if(index < editors.length() && index >= 0) {
    FileEdit *edit = editors.at(index);
    QString path = QFileDialog::getSaveFileName(this, tr("Save File"));
    edit->setFilePath(path);
    QString tabtitle = edit->getTitle();
    tab->setTabText(index + 1, tabtitle);
    edit->save();
  }
}

void CodeEditors::close_trig() {
  int index = tab->currentIndex() - 1;
  if(index < editors.length() && index >= 0) {
    FileEdit *edit = editors.at(index);
    if(edit->isChanged()) {
      QMessageBox msg;
      msg.setWindowTitle("The text has been changed");
      msg.setText("This tab text has been changed.");
      msg.setInformativeText("Do you want to save this tab?");
      msg.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
      msg.setDefaultButton(QMessageBox::Cancel);
      int result = msg.exec();
      if(result == QMessageBox::Save) {
        this->save_trig();
      }else if(result == QMessageBox::Cancel) {
        return;
      }
    }

    tab->removeTab(index + 1);
    delete edit;
    editors.removeAt(index);
  }
}

void CodeEditors::run_trig() {
  int index = tab->currentIndex();
  FileEdit *currentedit = dynamic_cast<FileEdit*>(tab->currentWidget());
  if(currentedit) {
    QString code = currentedit->toPlainText();
    if(index == 0) {
      emit run_code(code);
    }else {
      if(!currentedit->isAssociatedWithFile()) {
        QString path = QFileDialog::getSaveFileName(this, tr("Save File"));
        currentedit->setFilePath(path);
        QString tabtitle = currentedit->getTitle();
        tab->setTabText(index, tabtitle);
      }
      currentedit->save();

      QString load_code = "(load \"" + currentedit->getFilePath() + "\")";
      emit run_code(load_code);
    }
  }
}
