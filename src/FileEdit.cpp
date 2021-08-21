#include "FileEdit.hpp"


FileEdit::FileEdit(QWidget* parent):
  QPlainTextEdit(parent) {
  changed = false;

  connect(this, SIGNAL(textChanged()), this, SLOT(setChanged()));
}

bool FileEdit::isAssociatedWithFile() {
  return not getFilePath().isEmpty();
}

bool FileEdit::isChanged() {
  return this->changed;
}

void FileEdit::setFilePath(QString path) {
  file.setFileName(path);
  QString npath = path.replace(QChar('\\'), QChar('/'));
  QList<QString> files = npath.split("/");
  
  if(files.length() >= 2) {
    title[1] = files.last();
    files.pop_back();
    title[0] = files.last();
    emit titleChanged(getTitle());
  }else if(files.length() == 1) {
    title[1] = files.last();
    emit titleChanged(getTitle());
  }
}

QString FileEdit::getTitle(bool full) {
  if(full) {
    return title[0] + QString("/") + title[1];
  }else {
    return title[1];
  }
}


QString FileEdit::getFilePath() {
  return file.fileName();
}

void FileEdit::save() {
  if(isAssociatedWithFile()) {
    if(!file.open(QIODevice::WriteOnly)) {
      // error
    }

    QTextStream out(&file);
    out << this->toPlainText();
    file.close();
    changed = false;
  }
}

void FileEdit::load() {
  if(isAssociatedWithFile() && file.exists()) {
    if(!file.open(QIODevice::ReadOnly)) {
      // error
    }

    QTextStream in(&file);
    this->setPlainText(in.readAll());

    file.close();
    changed = false;
  }
}

void FileEdit::setChanged() {
  changed = true;
}
